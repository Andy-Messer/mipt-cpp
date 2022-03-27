//
// Created by Admin on 04.05.2021.
//

#ifndef DEQUE_DEQUE_H
#define DEQUE_DEQUE_H

#include <iostream>
#include <type_traits>
#include <vector>

template<typename T>
class Deque {
private:

    template<class U>
    struct Position_struct {
        U row;
        U column;

        Position_struct(std::pair<U, U> x) : row(x.first), column(x.second) {}

        Position_struct &operator=(std::pair<U, U> x) {
            row = x.first;
            column = x.second;
            return *this;
        }

        Position_struct() = default;

        Position_struct &operator++(int) {
            Position_struct cp = *this;
            ++column;
            if (column == block_sz) {
                column = 0;
                ++row;
            }
            return cp;
        }

        Position_struct &operator++() {
            ++column;
            if (column == block_sz) {
                column = 0;
                ++row;
            }
            return *this;
        }

        Position_struct<U> operator--(int) {
            base_iterator cp = *this;
            --column;
            if (column < 0) {
                column = block_sz - 1;
                --row;
            }
            return cp;
        }

        Position_struct &operator--() {
            --column;
            if (column < 0) {
                column = block_sz - 1;
                --row;
            }
            return *this;
        }
    };

    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;

    static const int block_sz = 256;

    T **mem;
    int sz = 0;
    int cap = 0;

    Position_struct<int> bpos, epos;

    void swap(Deque<T> &copy) {
        std::swap(sz, copy.sz);
        std::swap(cap, copy.cap);
        std::swap(bpos, copy.bpos);
        std::swap(epos, copy.epos);
        std::swap(mem, copy.mem);
    }

public:

    Deque<T>() = default;

    Deque<T>(const Deque<T> &other) {
        mem = new T *[other.cap];
        sz = other.sz;
        cap = other.cap;
        bpos = other.bpos;
        epos = other.epos;
        for (int i = 0; i < cap; i++) {
            mem[i] = reinterpret_cast<T *>(new int8_t[block_sz * sizeof(T)]);
            std::uninitialized_copy(other.mem[i], other.mem[i] + block_sz,
                                    mem[i]);
        }
    }

    Deque<T>(const int new_sz) {
        cap = 2 * (new_sz / block_sz + 1);
        sz = new_sz;
        mem = (new T *[cap]);
        for (int i = 0; i < cap; ++i)
            mem[i] = reinterpret_cast<T *>(new int8_t[block_sz * sizeof(T)]);
        bpos = {cap / 2 - (sz / 2 / block_sz + 1),
                block_sz - (sz / 2 % block_sz + 1)};
        epos = bpos;
        for (int i = 0; i < new_sz; ++i) {
            if (epos.column == block_sz - 1) {
                ++epos.row;
            }
            epos.column = (epos.column + 1) % block_sz;
        }

    }

    Deque<T>(int n, const T &value) {
        *this = Deque<T>(n);
        for (int i = 0; i < n; i++) {

            (*this)[i] = value;
        }
    }

    Deque<T> &operator=(const Deque<T> &other) {
        Deque<T> copy(other);
        swap(copy);
        return *this;
    }

    size_t size() const {
        return sz;
    }

    T &operator[](int ind) {
        int x = bpos.row + (bpos.column + ind) / block_sz;
        int y = (bpos.column + ind) % block_sz;
        return mem[x][y];
    }

    const T &operator[](int ind) const {
        int x = bpos.row + (bpos.column + ind) / block_sz;
        int y = (bpos.column + ind) % block_sz;
        return mem[x][y];
    }

    T &at(int ind) {
        if (ind < 0 || ind >= sz) {
            throw std::out_of_range("");
        }
        return mem[bpos.row + (bpos.column + ind) / block_sz][
                (bpos.column + ind) % block_sz];
    }

    const T &at(int ind) const {
        if (ind < 0 || ind >= sz) {
            throw std::out_of_range("");
        }
        return mem[bpos.row + (bpos.column + ind) / block_sz][
                (bpos.column + ind) % block_sz];
    }

    void push_back(const T &value) {
        ++epos;
        if (cap > epos.row && sz != 0) {
            --epos;
            mem[epos.row][epos.column] = value;
            ++epos;
            sz++;
        } else {
            sz++;
            --epos;
            Deque<T> new_dq = Deque<T>(sz);
            for (int i = 0; i < sz - 1; i++) {
                new_dq[i] = (*this)[i];
            }
            new_dq[sz - 1] = value;

            (*this) = std::move(new_dq);
        }
    }

    void pop_back() {
        if (sz > 0) {
            (*this)[sz].~T();
            --sz;
            --epos;
        }
    }

    void push_front(const T &value) {
        --bpos;
        if (bpos.row < 0 || sz == 0) {
            ++bpos;
            sz++;
            Deque<T> new_dq = Deque<T>(sz);
            for (int i = 1; i < sz; i++) {
                new_dq[i] = (*this)[i - 1];
            }
            new_dq[0] = value;

            (*this) = std::move(new_dq);
        } else {
            mem[bpos.row][bpos.column] = value;
            sz++;
        }
    }

    void pop_front() {
        if (sz > 0) {
            (*this)[0].~T();
            ++bpos;
            --sz;
        }
    }

    template<bool is_const>
    class base_iterator
            : public std::iterator<std::random_access_iterator_tag, value_type> {
    private:

        typedef typename std::conditional<is_const, const T **, T **>::type Storage;
        typedef typename std::conditional<is_const, const T *, T *>::type Pointer;
        typedef typename std::conditional<is_const, const T &, T &>::type Reference;
        typedef typename std::conditional<is_const, const int, int>::type Position;

        Storage st;
        Position_struct<Position> pos;

    public:
        base_iterator(T **new_st, Position new_row, Position new_column) :
                st(const_cast<Storage>(new_st)), pos({new_row, new_column}) {}

        int operator-(const base_iterator &other) const {
            return (this->pos.row - other.pos.row) * block_sz + pos.column -
                   other.pos.column;
        }

        Reference operator*() const {
            return st[pos.row][pos.column];
        }

        Pointer operator->() const {
            return &st[pos.row][pos.column];
        }

        base_iterator &operator++() {
            ++pos.column;
            if (pos.column == block_sz) {
                pos.column = 0;
                ++pos.row;
            }
            return *this;
        }

        base_iterator &operator--() {
            --pos.column;
            if (pos.column < 0) {
                pos.column = block_sz - 1;
                --pos.row;
            }
            return *this;
        }

        base_iterator &operator++(int) {
            base_iterator cp = *this;
            ++pos.column;
            if (pos.column == block_sz) {
                pos.column = 0;
                ++pos.row;
            }
            return cp;
        }

        base_iterator &operator--(int) {
            base_iterator cp = *this;
            --pos.column;
            if (pos.column < 0) {
                pos.column = block_sz - 1;
                --pos.row;
            }
            return cp;
        }

        base_iterator &operator+=(int movement) {
            if (movement < 0) {
                if (movement > pos.column) {
                    movement -= pos.column;
                    pos.column = 0;
                    pos.row--;
                    pos.row -= (movement) / block_sz;
                    pos.column = block_sz - (movement) % block_sz;
                } else {
                    pos.row -= (movement) / block_sz;
                    pos.column = pos.column - (movement) % block_sz;
                }
            } else {
                pos.row += (movement + pos.column) / block_sz;
                pos.column = (movement + pos.column) % block_sz;
            }
            return *this;
        }

        base_iterator &operator-=(int movement) {
            if (movement > 0) {
                if (movement > pos.column) {
                    movement -= pos.column;
                    pos.column = 0;
                    pos.row--;
                    pos.row -= (movement) / block_sz;
                    pos.column = block_sz - (movement) % block_sz;
                } else {
                    pos.row -= (movement) / block_sz;
                    pos.column = pos.column - (movement) % block_sz;
                }
            } else {
                pos.row += (movement + pos.column) / block_sz;
                pos.column = (movement + pos.column) % block_sz;
            }
            return *this;
        }

        base_iterator operator+(const int movement) const {
            base_iterator cp = *this;
            cp += movement;
            return cp;
        }

        base_iterator<false> operator-(const int movement) const {
            base_iterator<false> cp(const_cast<T **>(st), pos.row, pos.column);
            cp -= movement;
            return cp;
        }

        bool operator==(const base_iterator &other) const {
            return ((*this).st == other.st &&
                    (*this).pos.row == other.pos.row &&
                    (*this).pos.column == other.pos.column) ||
                   (*this) - other == 0 ||
                   other - (*this) == 0;
        }

        bool operator!=(const base_iterator &other) const {
            return !(*this == other);
        }

        bool operator<(const base_iterator &other) const {
            return !(*this > other);
        }

        bool operator>(const base_iterator &other) const {
            return (*this - other) > 0;
        }

        bool operator<=(const base_iterator &other) const {
            return (*this < other) || (*this == other);
        }

        bool operator>=(const base_iterator &other) const {
            return (*this > other) || (*this == other);
        }
    };

    typedef base_iterator<false> iterator;
    typedef base_iterator<true> const_iterator;

    void insert(iterator it, const T &val) {
        T cp = val;
        while (it != this->end()) {
            std::swap(*it, cp);
            ++it;
        }
        (*this).push_back(cp);
    }

    void erase(iterator it) {
        while (it + 1 != (*this).end()) {
            *it = *(it + 1);
            ++it;
        }
        (*this).pop_back();
    }

    iterator begin() {
        return iterator(mem, bpos.row, bpos.column);
    }

    const_iterator begin() const {
        return const_iterator(mem, bpos.row, bpos.column);
    }


    const_iterator cbegin() const {
        return const_iterator(mem, bpos.row, bpos.column);
    }

    iterator end() {
        return iterator(mem, epos.row, epos.column);
    }

    const_iterator end() const {
        return const_iterator(mem, epos.row, epos.column);
    }


    const_iterator cend() const {
        return const_iterator(mem, epos.row, epos.column);
    }

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    reverse_iterator rbegin() const {
        return reverse_iterator(iterator(mem, bpos.row, bpos.column));
    }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(
                const_iterator(mem, bpos.row, bpos.column));
    }

    reverse_iterator rend() const {
        return reverse_iterator(iterator(mem, epos.row, epos.column));
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(
                const_iterator(mem, epos.row, epos.column));
    }
};

#endif //DEQUE_DEQUE_H
