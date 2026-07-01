/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>

class Circle;
class Rectangle;

class Visitor {
public:
    virtual ~Visitor() = default;

    virtual void visit(Circle &circle) = 0;
    virtual void visit(Rectangle &rectangle) = 0;
};

class Shape {
public:
    virtual ~Shape() = default;
    virtual void accept(Visitor &visitor) = 0;
};

class Circle : public Shape {
public:
    explicit Circle(double radius) : radius(radius)
    {
    }

    double get_radius() const
    {
        return radius;
    }

    void accept(Visitor &visitor) override
    {
        visitor.visit(*this);
    }

private:
    double radius;
};

class Rectangle : public Shape {
public:
    Rectangle(double width, double height) : width(width), height(height)
    {
    }

    double get_width() const
    {
        return width;
    }
    double get_height() const
    {
        return height;
    }

    void accept(Visitor &visitor) override
    {
        visitor.visit(*this);
    }

private:
    double width;
    double height;
};

class AreaVisitor : public Visitor {
public:
    void visit(Circle &circle) override
    {
        double area = 3.14159 * circle.get_radius() * circle.get_radius();
        std::cout << "Area of Circle: " << area << std::endl;
    }
    void visit(Rectangle &rectangle) override
    {
        double area = rectangle.get_width() * rectangle.get_height();
        std::cout << "Area of Rectangle: " << area << std::endl;
    }
};

int main()
{
    Circle circle(5.0);
    Rectangle rectangle(4.0, 6.0);

    AreaVisitor area_visitor;
    circle.accept(area_visitor);
    rectangle.accept(area_visitor);

    return 0;
}
