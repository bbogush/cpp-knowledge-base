/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>

template<typename T>
class SharedPtr {
public:
    SharedPtr() = default;

    explicit SharedPtr(T *ptr) : ptr(ptr), ref_count(new size_t { 1 })
    {
    }

    SharedPtr(const SharedPtr &other)
    {
        ptr = other.ptr;
        ref_count = other.ref_count;
        if (ref_count) {
            ++(*ref_count);
        }
    }

    SharedPtr(SharedPtr &&other) noexcept
    {
        ptr = other.ptr;
        ref_count = other.ref_count;
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    ~SharedPtr()
    {
        release();
    }

    SharedPtr &operator=(const SharedPtr &other)
    {
        if (this == &other) {
            return *this;
        }

        release();

        ptr = other.ptr;
        ref_count = other.ref_count;
        if (ref_count) {
            ++(*ref_count);
        }

        return *this;
    }

    SharedPtr &operator=(SharedPtr &&other) noexcept
    {
        if (this == &other) {
            return *this;
        }

        release();

        ptr = other.ptr;
        ref_count = other.ref_count;
        other.ptr = nullptr;
        other.ref_count = nullptr;

        return *this;
    }

    T *get() const
    {
        return ptr;
    }

    T &operator*() const
    {
        return *ptr;
    }

    T *operator->() const
    {
        return ptr;
    }

    size_t use_count() const
    {
        return ref_count ? *ref_count : 0;
    }

    explicit operator bool() const
    {
        return !!ptr;
    }

private:
    T *ptr = nullptr;
    std::size_t *ref_count = nullptr;

    void release()
    {
        if (ref_count && !--(*ref_count)) {
            delete ptr;
            delete ref_count;
        }
        ptr = nullptr;
        ref_count = nullptr;
    }
};

class Foo {
public:
    Foo()
    {
        std::cout << "Foo constructed\n";
    }
    ~Foo()
    {
        std::cout << "Foo destroyed\n";
    }
};

int main()
{
    SharedPtr<Foo> foo(new Foo());
    SharedPtr<Foo> foo2(foo);
    SharedPtr<Foo> foo3 = foo;
    SharedPtr<Foo> foo4(std::move(foo));
    SharedPtr<Foo> foo5 = std::move(foo2);
    std::cout << "Use count: " << foo5.use_count() << "\n";

    return 0;
}
