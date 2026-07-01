/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <memory>

// Implementor
class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void render_circle(float x, float y, float radius) const = 0;
};

class OpenGLRenderer : public Renderer {
public:
    void render_circle(float x, float y, float radius) const override
    {
        std::cout << "OpenGL Renderer: Drawing circle at (" << x << ", " << y << ") with radius "
                  << radius << std::endl;
    }
};

class DirectXRenderer : public Renderer {
public:
    void render_circle(float x, float y, float radius) const override
    {
        std::cout << "DirectX Renderer: Drawing circle at (" << x << ", " << y << ") with radius "
                  << radius << std::endl;
    }
};

// Abstraction
class Shape {
public:
    explicit Shape(std::shared_ptr<Renderer> renderer) : renderer(std::move(renderer))
    {
    }
    virtual ~Shape() = default;
    virtual void draw() const = 0;

protected:
    std::shared_ptr<Renderer> renderer;
};

class Circle : public Shape {
public:
    Circle(std::shared_ptr<Renderer> renderer, float x, float y, float radius) :
        Shape(std::move(renderer)), x(x), y(y), radius(radius)
    {
    }

    void draw() const override
    {
        renderer->render_circle(x, y, radius);
    }

private:
    float x, y, radius;
};

int main()
{
    auto opengl_renderer = std::make_shared<OpenGLRenderer>();
    auto directx_renderer = std::make_shared<DirectXRenderer>();

    Circle circle1(opengl_renderer, 1.0f, 2.0f, 3.0f);
    Circle circle2(directx_renderer, 4.0f, 5.0f, 6.0f);

    circle1.draw();
    circle2.draw();

    return 0;
}
