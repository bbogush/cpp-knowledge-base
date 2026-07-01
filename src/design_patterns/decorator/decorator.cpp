/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <memory>
#include <string>

class Coffee {
public:
    virtual ~Coffee() = default;
    virtual std::string get_description() const = 0;
    virtual double get_cost() const = 0;
};

class SimpleCoffee : public Coffee {
public:
    std::string get_description() const override
    {
        return "Simple Coffee";
    }
    double get_cost() const override
    {
        return 2.0;
    }
};

class CoffeeDecorator : public Coffee {
public:
    explicit CoffeeDecorator(std::unique_ptr<Coffee> coffee) : coffee(std::move(coffee))
    {
    }
    std::string get_description() const override
    {
        return coffee->get_description();
    }
    double get_cost() const override
    {
        return coffee->get_cost();
    }

protected:
    std::unique_ptr<Coffee> coffee;
};

class MilkDecorator : public CoffeeDecorator {
public:
    explicit MilkDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee))
    {
    }
    std::string get_description() const override
    {
        return coffee->get_description() + ", Milk";
    }
    double get_cost() const override
    {
        return coffee->get_cost() + 0.5;
    }
};

class SugarDecorator : public CoffeeDecorator {
public:
    explicit SugarDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee))
    {
    }
    std::string get_description() const override
    {
        return coffee->get_description() + ", Sugar";
    }
    double get_cost() const override
    {
        return coffee->get_cost() + 0.3;
    }
};

int main()
{
    std::unique_ptr<Coffee> coffee = std::make_unique<SimpleCoffee>();
    std::cout << coffee->get_description() << ": costs $" << coffee->get_cost() << std::endl;

    coffee = std::make_unique<MilkDecorator>(std::move(coffee));
    std::cout << coffee->get_description() << ": costs $" << coffee->get_cost() << std::endl;

    coffee = std::make_unique<SugarDecorator>(std::move(coffee));
    std::cout << coffee->get_description() << ": costs $" << coffee->get_cost() << std::endl;

    return 0;
}
