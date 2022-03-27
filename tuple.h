#include <utility>
#include <tuple>

/*
▀█▀ █░█ █▀▄ █░░ █▀▀
░█░ █░█ █░█ █░▄ █▀▀
░▀░ ░▀░ █▀░ ▀▀▀ ▀▀▀
*/
template<typename... _Elements>
class Tuple {};
/*
█░░ ▀ █▄░█ █░▄▀
█░▄ █ █░▀█ █▀▄░
▀▀▀ ▀ ▀░░▀ ▀░▀▀
 */
//https://github.com/KrotovAndrey/Cpp_Course_MIPT/blob/Tuple/Tuple/Tuple_implementation.md
//-----------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
/*
▄▀▀░ █▀▀ ▀█▀ ▀█▀ █▀▀ █▀▀▄ ▄▀▀
█░▀▌ █▀▀ ░█░ ░█░ █▀▀ █▐█▀ ░▀▄
▀▀▀░ ▀▀▀ ░▀░ ░▀░ ▀▀▀ ▀░▀▀ ▀▀░
 */
//--------------------------------------------------------------------------------------------------------------------//
template<size_t i, typename _Head, typename... _Tail>
class __get_helper_rv {
public:
    typedef typename __get_helper_rv<i - 1, _Tail...>::return_type return_type;

    static return_type get(Tuple<_Head, _Tail...> &&tuple) {
        return __get_helper_rv<i - 1, _Tail...>::get(std::move(tuple));
    }
};

template<typename _Head, typename... _Tail>
class __get_helper_rv<0, _Head, _Tail...> {
public:
    typedef _Head &&return_type;

    static return_type get(Tuple<_Head, _Tail...> &&tuple) {
        return std::move(tuple.head);
    }
};

template<size_t i, typename _Head, typename... _Tail>
typename __get_helper_rv<i, _Head, _Tail...>::return_type
get(Tuple<_Head, _Tail...> &&tuple) {
    return __get_helper_rv<i, _Head, _Tail...>::get(std::move(tuple));
};


template<size_t i, typename _Head, typename... _Tail>
class __get_helper_lv {
public:
    typedef typename __get_helper_lv<i - 1, _Tail...>::return_type return_type;

    static return_type get(Tuple<_Head, _Tail...> &tuple) {
        return __get_helper_lv<i - 1, _Tail...>::get(tuple);
    }
};

template<typename _Head, typename... _Tail>
class __get_helper_lv<0, _Head, _Tail...> {
public:
    typedef _Head &return_type;

    static return_type get(Tuple<_Head, _Tail...> &tuple) {
        return tuple.head;
    }
};

template<size_t i, typename _Head, typename... _Tail>
typename __get_helper_lv<i, _Head, _Tail...>::return_type
get(Tuple<_Head, _Tail...> &tuple) {
    return __get_helper_lv<i, _Head, _Tail...>::get(tuple);
};


template<size_t i, typename _Head, typename... _Tail>
class __get_helper_const_lv {
public:
    typedef typename __get_helper_const_lv<
            i - 1, _Tail...>::return_type return_type;

    static return_type get(const Tuple<_Head, _Tail...> &tuple) {
        return __get_helper_const_lv<i - 1, _Tail...>::get(tuple);
    }
};

template<typename _Head, typename... _Tail>
class __get_helper_const_lv<0, _Head, _Tail...> {
public:
    typedef const _Head &return_type;

    static return_type get(const Tuple<_Head, _Tail...> &tuple) {
        return tuple.head;
    }
};

template<size_t i, typename _Head, typename... _Tail>
typename __get_helper_const_lv<i, _Head, _Tail...>::return_type
get(const Tuple<_Head, _Tail...> &tuple) {
    return __get_helper_const_lv<i, _Head, _Tail...>::get(tuple);
};


template<typename T, typename _Head, typename... _Tail>
class __get_helper_rv_type {
public:
    typedef typename __get_helper_rv_type<T, _Tail...>::return_type return_type;

    static return_type get(Tuple<_Head, _Tail...> &&tuple) {
        return __get_helper_rv_type<T, _Tail...>::get(std::move(tuple));
    }
};

template<typename T, typename... _Tail>
class __get_helper_rv_type<T, T, _Tail...> {
public:
    typedef T &&return_type;

    static return_type get(Tuple<T, _Tail...> &&tuple) {
        return std::move(tuple.head);
    }
};

template<typename T, typename _Head, typename... _Tail>
typename __get_helper_rv_type<T, _Head, _Tail...>::return_type
get(Tuple<_Head, _Tail...> &&tuple) {
    return __get_helper_rv_type<T, _Head, _Tail...>::get(std::move(tuple));
}

template<typename T, typename _Head, typename... _Tail>
class __get_helper_lv_type {
public:
    typedef typename __get_helper_lv_type<T, _Tail...>::return_type return_type;

    static return_type get(Tuple<_Head, _Tail...> &tuple) {
        return __get_helper_lv_type<T, _Tail...>::get(tuple);
    }
};

template<typename T, typename... _Tail>
class __get_helper_lv_type<T, T, _Tail...> {
public:
    typedef T &return_type;

    static return_type get(Tuple<T, _Tail...> &tuple) {
        return tuple.head;
    }
};

template<typename T, typename _Head, typename... _Tail>
typename __get_helper_lv_type<T, _Head, _Tail...>::return_type
get(Tuple<_Head, _Tail...> &tuple) {
    return __get_helper_lv_type<T, _Head, _Tail...>::get(tuple);
};


template<typename T, typename _Head, typename... _Tail>
class __get_helper_const_lv_type {
public:
    typedef typename __get_helper_const_lv_type<T, _Tail...>::return_type return_type;

    static return_type get(const Tuple<_Head, _Tail...> &tuple) {
        return __get_helper_const_lv_type<T, _Tail...>::get(tuple);
    }
};

template<typename T, typename... _Tail>
class __get_helper_const_lv_type<T, T, _Tail...> {
public:
    typedef const T &return_type;

    static return_type get(const Tuple<T, _Tail...> &tuple) {
        return tuple.head;
    }
};

template<typename T, typename _Head, typename... _Tail>
typename __get_helper_const_lv_type<T, _Head, _Tail...>::return_type
get(const Tuple<_Head, _Tail...> &tuple) {
    return __get_helper_const_lv_type<T, _Head, _Tail...>::get(tuple);
}




template<typename    _Head,
       	 typename... _Tail>
class Tuple<_Head, _Tail...> : public Tuple<_Tail...> {
private:
    typedef Tuple<_Tail...> tail_type;
    typedef _Head           value_type;

public:
    Tuple() : Tuple<_Tail...>(), head(_Head()) {}
    value_type head;
    template<typename UHead, typename... UTail,
            typename std::enable_if<std::is_constructible<value_type, UHead &&>::value, void *>::type = nullptr>
    explicit Tuple(UHead &&value, UTail &&... tail) :
            Tuple<_Tail...>(std::forward<UTail>(tail)...),
            head(std::forward<UHead>(value)) {}

    Tuple &operator=(const Tuple<_Head, _Tail...> &other)     = default;

    Tuple &operator=(Tuple<_Head, _Tail...> &&other) noexcept           = default;

    Tuple(const Tuple<_Head, _Tail...> &other)                = default;

    Tuple(Tuple<_Head, _Tail...> &&other) noexcept            = default;

    template<typename UHead, typename... UTail>
    Tuple& operator=(const Tuple<UHead, UTail...> &other){
        head = other.head;
        if constexpr (sizeof...(UTail) > 0){
            Tuple<_Tail...> (std::forward<UTail>(other)...);
        }
        return *this;
    }

    ~Tuple() = default;

    void swap(Tuple<_Head, _Tail...> &other) {
        tail_type::swap(static_cast<tail_type &>(other));

        std::swap(head, other.head);
    }
/*
▄▀▀░ █▀▀ ▀█▀ ▀█▀ █▀▀ █▀▀▄ ▄▀▀
█░▀▌ █▀▀ ░█░ ░█░ █▀▀ █▐█▀ ░▀▄
▀▀▀░ ▀▀▀ ░▀░ ░▀░ ▀▀▀ ▀░▀▀ ▀▀░
 */
    const tail_type &__get_helper_tail() const {
        return static_cast<const tail_type &>(*this);
    }

    const value_type &__get_helper_head() const {
        return head;
    }

    tail_type &__get_helper_tail() {
        return static_cast<tail_type &>(*this);
    }

    value_type &__get_helper_head() {
        return head;
    }
private:
//-------------------------------------------//
    template<typename T, typename    _Head_base,
            typename... _Tail_base>
    friend
    class __get_helper_lv_type;
//-------------------------------------------//
    template<typename T, typename    _Head_base,
            typename... _Tail_base>
    friend
    class __get_helper_const_lv_type;
//-------------------------------------------//
    template<size_t i, typename    _Head_base,
            typename... _Tail_base>
    friend
    class __get_helper_const_lv;
//-------------------------------------------//
    template<typename T, typename    _Head_base,
            typename... _Tail_base>
    friend
    class __get_helper_rv_type;
//-------------------------------------------//
    template<size_t i, typename    _Head_base,
            typename... _Tail_base>
    friend
    class __get_helper_rv;
//-------------------------------------------//
    template<size_t i, typename    _Head_base,
            typename... _Tail_base>
    friend
    class __get_helper_lv;
//-------------------------------------------//
};


template<>
class Tuple<> {
public:
    void swap([[maybe_unused]]Tuple<> &other) {}
};


template<typename... Types>
Tuple<typename std::decay<Types>::type...> makeTuple(Types &&... values) {
    return Tuple<typename std::decay<Types>::type...>(
            std::forward<Types>(values)...);
}
//--------------------------------------------------------------------------------------------------------------------//
/*
▄▀▄ █▀▄ █▀▀ █▀▀▄ ▄▀▄ ▀█▀ ▄▀▄ █▀▀▄ ▄▀▀
█░█ █░█ █▀▀ █▐█▀ █▀█ ░█░ █░█ █▐█▀ ░▀▄
░▀░ █▀░ ▀▀▀ ▀░▀▀ ▀░▀ ░▀░ ░▀░ ▀░▀▀ ▀▀░
 */
//--------------------------------------------------------------------------------------------------------------------//
template<typename _Head, typename... _Tail>
bool operator==(const Tuple<_Head, _Tail...> &first_tuple,
                const Tuple<_Head, _Tail...> &second_tuple) {
    return first_tuple.__get_helper_head() == second_tuple.__get_helper_head() &&
           first_tuple.__get_helper_tail() == second_tuple.__get_helper_tail();
};

template<typename... _Elements>
bool operator==([[maybe_unused]]const Tuple<> &first_tuple,[[maybe_unused]] const Tuple<> &second_tuple) {
    return true;
};

template<typename... _Elements>
bool operator!=(const Tuple<_Elements...> &first_tuple, const Tuple<_Elements...> &second_tuple) {
    return !(first_tuple == second_tuple);
};

template<typename _Head, typename... _Tail>
[[maybe_unused]]bool operator<=(const Tuple<_Head, _Tail...> &first_tuple,
                const Tuple<_Head, _Tail...> &second_tuple) {
    return first_tuple.__get_helper_head() < second_tuple.__get_helper_head() ||
           (first_tuple.__get_helper_head() == second_tuple.__get_helper_head() &&
            first_tuple.__get_helper_tail() <= second_tuple.__get_helper_tail());
};

template<typename... _Elements>
bool operator<=([[maybe_unused]]const Tuple<> &first_tuple,[[maybe_unused]] const Tuple<> &second_tuple) {
    return true;
};

template<typename... _Elements>
bool operator>(const Tuple<_Elements...> &first_tuple, const Tuple<_Elements...> &second_tuple) {
    return !(first_tuple <= second_tuple);
};

template<typename... _Elements>
bool operator>=(const Tuple<_Elements...> &first_tuple, const Tuple<_Elements...> &second_tuple) {
    return first_tuple > second_tuple || first_tuple == second_tuple;
};

template<typename... _Elements>
bool operator<(const Tuple<_Elements...> &first_tuple, const Tuple<_Elements...> &second_tuple) {
    return !(first_tuple >= second_tuple);
};

//--------------------------------------------------------------------------------------------------------------------//
/*
▀█▀ █░█ █▀▄ █░░ █▀▀ ▄▀ ▄▀▄ ▀█▀
░█░ █░█ █░█ █░▄ █▀▀ █░ █▀█ ░█░
░▀░ ░▀░ █▀░ ▀▀▀ ▀▀▀ ░▀ ▀░▀ ░▀░
 */
//--------------------------------------------------------------------------------------------------------------------//
template<typename _Head, typename... _Tail, typename... Types2>
Tuple<_Head, _Tail..., Types2...>
tupleCat2(Tuple<_Head, _Tail...> first_tuple, Tuple<Types2...> second_tuple) {
    return Tuple<_Head, _Tail..., Types2...>(std::move(first_tuple.__get_helper_head()),
                                             tupleCat2(std::move(
                                                     first_tuple.__get_helper_tail()),
                                                       std::move(second_tuple)));
}

template<typename... Types>
Tuple<Types...> tupleCat2([[maybe_unused]]Tuple<> first_tuple, Tuple<Types...> second_tuple) {
    return second_tuple;
}

template<typename Tuple, typename... restTuples>
auto tupleCat(Tuple &&tuple, restTuples &&... tuples) {
    return tupleCat2(std::forward<Tuple>(tuple),
                     tupleCat(std::forward<restTuples>(tuples)...));
}

template<typename Tuple, typename... restTuples>
auto tupleCat(Tuple &&tuple) {
    return Tuple(std::forward<Tuple>(tuple));
}
