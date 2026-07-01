/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <memory>
#include <string>

class Shape {
public:
    virtual ~Shape() = default;
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual void draw() const = 0;
};

class Circle : public Shape {
public:
    explicit Circle(double radius) : radius(radius)
    {
    }

    std::unique_ptr<Shape> clone() const override
    {
        return std::make_unique<Circle>(*this);
    }

    void draw() const override
    {
        std::cout << "Drawing a circle with radius " << radius << std::endl;
    }

private:
    double radius;
};

int main()
{
    Circle circle(5.0);
    std::unique_ptr<Shape> cloned_circle = circle.clone();
    cloned_circle->draw();

    return 0;
}
