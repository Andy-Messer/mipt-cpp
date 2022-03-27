#pragma once

#include <memory>
#include <tuple>

template<class>
class Function;

template<class Callable, class... Args>
class Function<Callable(Args...)> {
private:
    std::tuple<Callable(*)(void *, Args &&...),
            void (*)(void *, void *),
            void (*)(void *)> PtrStorage;
    size_t storageSZ = 0;
    std::unique_ptr<std::byte[]> storage;

    void construct_from_other(Function<Callable(Args...)> &it, const Function<Callable(Args...)> &other) {
        it.storage.reset(new std::byte[other.storageSZ]);
        it.storageSZ = other.storageSZ;
        it.PtrStorage = other.PtrStorage;
        std::get<1>(PtrStorage)(it.storage.get(), other.storage.get());
    }

    template<class Functor>
    static void create(Functor *dest, Functor *src) {
        new(dest) Functor(*src);
    }

    template<class Functor>
    static void destroy(Functor *func) {
        func->~Functor();
    }

    template<class Functor>
    static Callable invoke(Functor *func, Args &&... args) {
        return (*func)(std::forward<Args>(args)...);
    }

public:
    Function() = default;

    template<class Functor>
    explicit Function(Functor f):PtrStorage(
            (reinterpret_cast <Callable(*)(void *, Args &&...)>(invoke<Functor>)),
            (reinterpret_cast <void (*)(void *, void *)>(create<Functor>)),
            (reinterpret_cast < void (*)(void *)>(destroy<Functor>))),
                                 storageSZ(sizeof(Functor)),
                                 storage(new std::byte[sizeof(Functor)]) {
        std::get<1>(PtrStorage)(storage.get(), std::addressof(f));
    }

    Function(const Function &other) {
        construct_from_other(*this, other);
    }

    Function &operator=(const Function &other) {
        construct_from_other(*this, other);
        return *this;
    }

    ~Function() {
        std::get<2>(PtrStorage)(storage.get());
    }

    Callable operator()(Args &&... args) const {
        return std::get<0>(PtrStorage)(storage.get(), std::forward<Args>(args)...);
    }
};
