/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>

class Singleton {
public:
    static Singleton &instance()
    {
        static Singleton singleton;

        return singleton;
    }

    Singleton(const Singleton &other) = delete;
    Singleton &operator=(const Singleton &other) = delete;

    Singleton(Singleton &&other) = delete;
    Singleton &operator=(Singleton &&other) = delete;

    void do_something() const
    {
        std::cout << "Hello\n";
    }

private:
    Singleton() = default;
    ~Singleton() = default;
};

int main()
{
    Singleton &singleton = Singleton::instance();
    singleton.do_something();

    return 0;
}
