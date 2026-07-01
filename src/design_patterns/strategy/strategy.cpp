/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <memory>

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual int execute(int a, int b) const = 0;
};

class AddStrategy : public Strategy {
public:
    int execute(int a, int b) const override
    {
        return a + b;
    }
};

class SubtractStrategy : public Strategy {
public:
    int execute(int a, int b) const override
    {
        return a - b;
    }
};

class Context {
public:
    void set_strategy(std::unique_ptr<Strategy> new_strategy)
    {
        strategy = std::move(new_strategy);
    }
    int run(int a, int b) const
    {
        if (strategy) {
            return strategy->execute(a, b);
        }
        return -1;
    }

private:
    std::unique_ptr<Strategy> strategy;
};

int main()
{
    Context context;
    context.set_strategy(std::make_unique<AddStrategy>());
    int res = context.run(5, 3);
    std::cout << "Addition result: " << res << "\n";

    context.set_strategy(std::make_unique<SubtractStrategy>());
    res = context.run(5, 3);
    std::cout << "Subtraction result: " << res << "\n";

    return 0;
}
