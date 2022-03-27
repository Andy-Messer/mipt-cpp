//
// Created by andrey on 18.05.2021.
//

#ifndef UNTITLED13_FASTALLOCATOR_H
#define UNTITLED13_FASTALLOCATOR_H

#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include <cstddef>
#include <type_traits>
#include <cassert>
#include <tuple>
#include <cstring>
#include <string>
#include <algorithm>

class bucket {
public:

    const std::size_t BlockSize;
    const std::size_t BlockCount;

    bucket(std::size_t block_size, std::size_t block_count);

    ~bucket();

    bool belongs(void *ptr) const noexcept;

    [[nodiscard]] void *allocate(std::size_t bytes) noexcept;

    void deallocate(void *ptr, std::size_t bytes) noexcept;


private:
    [[nodiscard]] std::size_t
    find_contiguous_blocks(std::size_t n) const noexcept;

    void set_blocks_in_use(std::size_t index, std::size_t n) noexcept;

    void set_blocks_free(std::size_t index, std::size_t n) noexcept;

    std::byte *m_data{nullptr};

    std::byte *m_ledger{nullptr};

};

bool bucket::belongs(void *ptr) const noexcept {
    const auto p = static_cast<const std::byte *>(ptr);
    const std::size_t dist = static_cast<std::size_t>(p - m_data);
    if (dist >= BlockCount)
        return false;
    return true;
}

std::size_t bucket::find_contiguous_blocks(std::size_t n) const noexcept {
    std::size_t index = 0;
    std::size_t exit_index = index;
    std::size_t count = 0;
    std::size_t block_index = 0;
    while (index + (block_index * 8) < BlockCount) {
        if ((index % 8 == 0) && (index != 0)) {
            block_index = block_index + 1;
            index = 0;
            exit_index = 0;
        }
        if (((*(m_ledger + block_index) >> index) & (std::byte) (1)) ==
            (std::byte) (0)) {
            count++;
        } else {
            count = 0;
            exit_index = index + 1;
        }
        if (count == n) {
            return exit_index + (block_index * 8);
        }
        index++;
    }
    return BlockCount;
}

void bucket::set_blocks_in_use(std::size_t index, std::size_t n) noexcept {
    std::size_t block_index = index / 8;
    index %= 8;
    std::size_t count = 0;
    while (index + (block_index * 8) < BlockCount && count < n) {
        if ((index % 8 == 0) && (index != 0)) {
            block_index = block_index + 1;
            index = 0;
        }
        std::byte *cp = m_ledger + block_index;
        *(cp) |= ((std::byte) (1) << (index));
        index++;
        count++;
    }
}

void bucket::set_blocks_free(std::size_t index, std::size_t n) noexcept {
    std::size_t block_index = index / 8;
    index %= 8;
    std::size_t count = 0;
    while (index + (block_index * 8) < BlockCount && count < n) {
        if ((index % 8 == 0) && (index != 0)) {
            block_index = block_index + 1;
            index = 0;
        }
        *(m_ledger + block_index) &= (~((std::byte) (1) << (index)));
        index++;
        count++;
    }
}

bucket::bucket(std::size_t block_size, std::size_t block_count)
        : BlockSize{block_size}, BlockCount{block_count} {

    const auto data_size = BlockCount * BlockSize;
    m_data = static_cast<std::byte *> (std::malloc(data_size));
    assert(m_data != nullptr);

    const auto ledger_size = 1 + ((BlockCount - 1) / BlockSize);
    m_ledger = static_cast<std::byte *>(std::malloc(ledger_size));
    assert(m_ledger != nullptr);

    std::memset(m_data, 0, data_size);
    std::memset(m_ledger, 0, ledger_size);
}

bucket::~bucket() {
    std::free(m_ledger);
    std::free(m_data);
}

void *bucket::allocate(std::size_t bytes) noexcept {
    const auto n = 1 + ((bytes - 1) / BlockSize);

    const auto index = find_contiguous_blocks(n);
    if (index == BlockCount) {
        return nullptr;
    }

    set_blocks_in_use(index, n);
    return m_data + (index * BlockSize);
}

void bucket::deallocate(void *ptr, std::size_t bytes) noexcept {
    const auto p = static_cast<const std::byte *>(ptr);
    const std::size_t dist = static_cast<std::size_t>(p - m_data);

    const auto index = dist / BlockSize;

    const auto n = 1 + ((bytes - 1) / BlockSize);

    set_blocks_free(index, n);
}

template<std::size_t id>
struct bucket_descriptors {
    using type = std::tuple<>;
};
struct bucket_cfg16 {
    static constexpr std::size_t BlockSize = 24;
    static constexpr std::size_t BlockCount = 40000000;
};
struct bucket_cfg32 {
    static constexpr std::size_t BlockSize = 32;
    static constexpr std::size_t BlockCount = 1000000;
};
struct bucket_cfg1024 {
    static constexpr std::size_t BlockSize = 1024;
    static constexpr std::size_t BlockCount = 500000;
};
template<>
struct bucket_descriptors<1> {
    using type = std::tuple<bucket_cfg16, bucket_cfg32, bucket_cfg1024>;
};
template<std::size_t id>
using bucket_descriptors_t = typename bucket_descriptors<id>::type;

template<std::size_t id>
static constexpr std::size_t bucket_count = std::tuple_size<bucket_descriptors_t<id>>::value;

template<std::size_t id>
using pool_type = std::array<bucket, bucket_count<id>>;

template<std::size_t id, std::size_t Idx>
struct get_size
        : std::integral_constant<std::size_t, std::tuple_element_t<Idx, bucket_descriptors_t<id>>::BlockSize> {
};

template<std::size_t id, std::size_t Idx>
struct get_count :
        std::integral_constant<std::size_t, std::tuple_element_t<Idx, bucket_descriptors_t<id>>::BlockCount> {
};

template<std::size_t id, std::size_t... Idx>
auto &get_instance(std::index_sequence<Idx...>) noexcept {
    static pool_type<id> instance{{{get_size<id, Idx>::value, get_count<id, Idx>::value} ...}};
    return instance;
}

template<std::size_t id>
auto &get_instance() noexcept {
    return get_instance<id>(std::make_index_sequence<bucket_count<id>>());
}

struct info {
    std::size_t index{0};
    std::size_t block_count{0};
    std::size_t waste{0};

    bool operator<(const info &other) const noexcept {
        return (waste == other.waste) ? block_count < other.block_count :
               waste < other.waste;
    }
};

bool cmp(const info &a, const info &b) {
    return a < b;
}

template<std::size_t id>
[[nodiscard]] void *allocate(std::size_t bytes) {
    auto &pool = get_instance<id>();
    std::array<info, bucket_count<id>> deltas;
    std::size_t index = 0;
    for (const auto &bucket: pool) {
        deltas[index].index = index;
        if (bucket.BlockSize >= bytes) {
            deltas[index].waste = bucket.BlockSize - bytes;
            deltas[index].block_count = 1;
        } else {
            const auto n = 1 + ((bytes - 1) / bucket.BlockSize);
            const auto storage_required = n * bucket.BlockSize;
            deltas[index].waste = storage_required - bytes;
            deltas[index].block_count = n;
        }
        ++index;
    }
    std::sort(deltas.begin(), deltas.end(), cmp);
    for (const auto &d:deltas)
        if (auto ptr = pool[d.index].allocate(bytes); ptr != nullptr) {
            return ptr;
        }
    throw std::bad_alloc{};
}

template<std::size_t id>
void deallocate(void *ptr, std::size_t bytes) noexcept {
    auto &pool = get_instance<id>();
    for (auto &bucket:pool) {
        if (bucket.belongs(ptr)) {
            bucket.deallocate(ptr, bytes);
            return;
        }
    }
}

template<size_t id>
constexpr bool is_defined() noexcept {
    return bucket_count<id> != 0;
}

template<size_t id>
bool initialize() noexcept {
    (void) get_instance<id>();
    return is_defined<id>();
}

namespace instrument {
    template<std::size_t id, typename T, std::size_t size>
    void type_reg() {}
}

template<typename T, std::size_t id = 1>
class FastAllocator {
public:
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef T &reference;
    typedef const T &const_reference;
    typedef T value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    template<class U>
    struct rebind {
        using other = FastAllocator<U, id>;
    };
    struct propagate_on_container_copy_assignment : std::false_type {
    };

    T *address(T &r) const {
        return &r;
    }

    const T *address(const T &s) const {
        return &s;
    }

    FastAllocator() {
        initialize<id>();
    };

    template<class U>
    FastAllocator(const FastAllocator<U, id> &) {}

    template<class U>
    FastAllocator &operator=(const FastAllocator<U, id> &) {
        return *this;
    }

    FastAllocator &select_on_container_copy_construction() {
        return *this;
    }

    const FastAllocator &select_on_container_copy_construction() const {
        return *this;
    }


    bool operator==(const FastAllocator<T, id> &) {
        return true;
    }

    bool operator!=(const FastAllocator<T, id> &other) {
        return !(*this == other);
    }

    ~FastAllocator() = default;

    T *allocate(size_t n) {
        instrument::type_reg<id, T, sizeof(T)>();
        if (is_defined<id>() && n == 1) {
            return static_cast<T *>(::allocate < id > (sizeof(T) * n));
        } else {
            T *const pv = reinterpret_cast<T *>(::operator new(n * sizeof(T)));
            return static_cast<T *>(pv);
        }
    }

    void deallocate(T *ptr, size_t n) {
        if (is_defined<id>() && n == 1) {
            ::deallocate < id > (ptr, sizeof(T) * n);
        } else {
            ::operator delete(ptr);
        }
    }

    template<typename ...Args>
    void construct(T *const p, const Args &...args) const {
        void *const pv = static_cast<void *>(p);
        new(pv) T(args...);
    }

    void destroy(T *const p) const {
        p->~T();
    };

};

template<class T, typename Allocator = std::allocator<T>>
class List {
    typedef T value_type;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::reference reference;
    typedef typename Allocator::const_reference const_reference;
    typedef size_t size_type;

    struct Node {
        value_type element;
        Node *next = nullptr;
        Node *prev = nullptr;

        Node() = default;

        Node(const value_type &newValue, Node *newNext,
             Node *newPrev) :
                element(newValue), next(newNext), prev(newPrev) {}
    };

    typedef typename std::allocator_traits<Allocator>::template rebind_alloc<Node> RebindAllocator;
    typedef typename std::allocator_traits<Allocator>::template rebind_traits<Node> AllocTraits;

    void swap(List<T, Allocator> &x) {
        std::swap(x.sz, this->sz);
        std::swap(x.head, this->head);
        std::swap(x.tail, this->tail);
    }

//-------------------Values-------------------------------------------------------------------------------------------//
    RebindAllocator allocator;
    Node *head = nullptr;
    Node *tail = nullptr;
    size_type sz = 0;
//--------------------------------------------------------------------------------------------------------------------//
public:

    RebindAllocator get_allocator() const {
        return allocator;
    }

    List(const Allocator &other_allocator = Allocator()) : sz(0) {
        this->allocator = other_allocator;
        head = reinterpret_cast<Node *>(new int8_t[sizeof(Node)]);
        head->next = head;
        head->prev = head;
        tail = head;
    }

    void push_back(const_reference x) {
        Node *valueNode = AllocTraits::allocate(this->allocator, 1);
        AllocTraits::construct(this->allocator, valueNode, x, head, tail);
        if (sz == 0) head->next = valueNode;
        tail->next = valueNode;
        tail = valueNode;
        head->prev = tail;
        ++sz;
    }

    void push_front(const_reference x) {
        Node *valueNode = AllocTraits::allocate(this->allocator, 1);
        AllocTraits::construct(this->allocator, valueNode, x, head->next, head);
        if (sz == 0) {
            tail = valueNode;
            tail->next = head;
            head->prev = tail;
        }
        head->next->prev = valueNode;
        head->next = valueNode;
        ++sz;
    }

    void pop_front() {
        Node *del_elem = head->next;
        head->next = head->next->next;
        head->next->prev = head;
        if (sz == 1) {
            tail = head;
            tail->next = head;
            tail->prev = head;
        }
        AllocTraits::destroy(allocator, del_elem);
        AllocTraits::deallocate(allocator, del_elem, 1);
        --sz;
    }

    void pop_back() {
        Node *del_elem = tail;
        tail = tail->prev;
        tail->next = head;
        head->prev = tail;
        AllocTraits::destroy(allocator, del_elem);
        AllocTraits::deallocate(allocator, del_elem, 1);
        --sz;
    }

    List(size_t n,[[maybe_unused]] const Allocator &other_allocator = Allocator()) {
        head = reinterpret_cast<Node *>(new int8_t[sizeof(Node)]);
        head->next = head;
        head->prev = head;
        tail = head;
        for (size_t i = 0; i < n; ++i) {
            Node *valueNode = AllocTraits::allocate(this->allocator, 1);
            AllocTraits::construct(this->allocator, valueNode);
            if (sz == 0) head->next = valueNode;
            tail->next = valueNode;
            valueNode->prev = tail;
            valueNode->next = head;
            tail = valueNode;

            ++sz;
        }
        head->prev = tail;
    }

    List(size_type n, const value_type &value,
         const Allocator &other_allocator = Allocator()) {
        head = reinterpret_cast<Node *>(new int8_t[sizeof(Node)]);
        head->next = head;
        head->prev = head;
        tail = head;
        for (size_t i = 0; i < n; ++i) {
            this->push_back(value);
        }
    }

    List<T, Allocator>(const List<T, Allocator> &other) {
        allocator = AllocTraits::select_on_container_copy_construction(
                other.allocator);
        head = reinterpret_cast<Node *>(new int8_t[sizeof(Node)]);
        head->next = head;
        head->prev = head;
        tail = head;
        for (auto &x:other) {
            Node *valueNode = AllocTraits::allocate(allocator, 1);
            AllocTraits::construct(allocator, valueNode, x, head, tail);
            tail->next = valueNode;
            tail = valueNode;
            ++sz;
        }

        head->prev = tail;
    }

    List &operator=(const List<T, Allocator> &other) {
        List<T, Allocator> cp = other;
        swap(cp);
        if (AllocTraits::propagate_on_container_copy_assignment::value &&
            allocator != other.allocator) {
            allocator = other.allocator;
        }
        return *this;
    }

    size_t size() const {
        return sz;
    }

    template<bool is_const>
    class base_iterator
            : public std::iterator<std::bidirectional_iterator_tag, typename std::conditional<is_const, const T, T>::type> {
    private:

        typedef typename std::conditional<is_const, const T &, T &>::type Reference;
        typedef typename std::conditional<is_const, const T *, T *>::type Pointer;
        typedef typename std::conditional<is_const, const Node *, Node *>::type Node_pointer;

        friend class List<T, Allocator>;

        Node_pointer tail_local = tail;
    public:
        base_iterator(Node_pointer global_tail) : tail_local(
                const_cast<Node_pointer>(global_tail)) {}

        base_iterator(const base_iterator<false> &other) : tail_local(
                const_cast<Node_pointer>(other.tail_local)) {}


        base_iterator<false> base() {
            return base_iterator<false>(const_cast<Node *>(tail_local)->next);
        }

        base_iterator<true> base() const {
            return base_iterator<true>(const_cast<Node *>(tail_local)->next);
        }

        Reference operator*() const {
            return tail_local->element;
        }

        Pointer operator->() const {
            return &(tail_local->element);
        }

        base_iterator &operator++() {
            tail_local = tail_local->next;
            return *this;
        }

        base_iterator &operator--() {
            tail_local = tail_local->prev;
            return *this;
        }

        base_iterator operator++(int) {
            base_iterator cp = *this;
            tail_local = tail_local->next;
            return cp;
        }

        base_iterator operator--(int) {
            base_iterator cp = *this;
            tail_local = tail_local->prev;
            return cp;
        }

        bool operator==(const base_iterator &other) const {
            return tail_local == other.tail_local;
        }

        bool operator!=(const base_iterator &other) const {
            return !(*this == other);
        }

    };

    typedef base_iterator<false> iterator;
    typedef base_iterator<true> const_iterator;

    iterator begin() {
        return iterator(head->next);
    }

    const_iterator begin() const {
        return const_iterator(head->next);
    }

    const_iterator cbegin() const {
        return const_iterator(head->next);
    }

    iterator end() {
        return iterator(tail->next);
    }

    const_iterator end() const {
        return const_iterator(tail->next);
    }

    const_iterator cend() const {
        return const_iterator(tail->next);
    }

    typedef typename std::reverse_iterator<base_iterator<false>> reverse_iterator;
    typedef typename std::reverse_iterator<base_iterator<true>> const_reverse_iterator;

    reverse_iterator rbegin() {
        return reverse_iterator(head);
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(head);
    }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(head);
    }

    reverse_iterator rend() {
        return reverse_iterator(head->prev);
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(head->prev);
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(head->prev);
    }

    void insert(iterator iter, const_reference value) {
        Node *valueNode = AllocTraits::allocate(allocator, 1);
        AllocTraits::construct(allocator, valueNode, value, iter.tail_local,
                               iter.tail_local->prev);
        iter.tail_local->prev->next = valueNode;
        iter.tail_local->prev = valueNode;
        ++sz;
    }

    void insert(const_iterator iter, const_reference value) {
        Node *valueNode = AllocTraits::allocate(allocator, 1);
        AllocTraits::construct(allocator, valueNode, value,
                               const_cast<Node *>(iter.tail_local),
                               iter.tail_local->prev);
        const_cast<Node *>(iter.tail_local)->prev->next = valueNode;
        const_cast<Node *>(iter.tail_local)->prev = valueNode;
        ++sz;
    }

    void erase(iterator iter) {
        Node *del_elem = iter.tail_local;
        iter.tail_local->next->prev = iter.tail_local->prev;
        iter.tail_local->prev->next = iter.tail_local->next;
        if (tail == iter.tail_local)
            tail = tail->prev;
        AllocTraits::destroy(allocator, del_elem);
        AllocTraits::deallocate(allocator, del_elem, 1);
        --sz;
    }

    void erase(const_iterator iter) {
        Node *del_elem = const_cast<Node *>(iter.tail_local);
        if (tail == iter.tail_local)
            tail = tail->prev;
        iter.tail_local->next->prev = iter.tail_local->prev;
        iter.tail_local->prev->next = iter.tail_local->next;
        AllocTraits::destroy(allocator, del_elem);
        AllocTraits::deallocate(allocator, del_elem, 1);
        --sz;
    }

    ~List() {
        while (sz != 0) {
            Node *del_elem = tail;
            tail = tail->prev;
            AllocTraits::destroy(allocator, del_elem);
            AllocTraits::deallocate(allocator, del_elem, 1);
            sz--;
        }
        delete[] reinterpret_cast<int8_t *>(head);
    }
};

#endif //UNTITLED13_FASTALLOCATOR_H
