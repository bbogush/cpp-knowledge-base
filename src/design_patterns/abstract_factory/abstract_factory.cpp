/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <memory>

class Button {
public:
    virtual ~Button() = default;
    virtual void render() const = 0;
};

class Checkbox {
public:
    virtual ~Checkbox() = default;
    virtual void render() const = 0;
};

class WindowsButton : public Button {
public:
    void render() const override
    {
        std::cout << "Rendering Windows Button" << std::endl;
    }
};

class WindowsCheckbox : public Checkbox {
public:
    void render() const override
    {
        std::cout << "Rendering Windows Checkbox" << std::endl;
    }
};

class LinuxButton : public Button {
public:
    void render() const override
    {
        std::cout << "Rendering Linux Button" << std::endl;
    }
};

class LinuxCheckbox : public Checkbox {
public:
    void render() const override
    {
        std::cout << "Rendering Linux Checkbox" << std::endl;
    }
};

class GUIFactory {
public:
    virtual ~GUIFactory() = default;
    virtual std::unique_ptr<Button> create_button() const = 0;
    virtual std::unique_ptr<Checkbox> create_checkbox() const = 0;
};

class WindowsFactory : public GUIFactory {
public:
    std::unique_ptr<Button> create_button() const override
    {
        return std::make_unique<WindowsButton>();
    }

    std::unique_ptr<Checkbox> create_checkbox() const override
    {
        return std::make_unique<WindowsCheckbox>();
    }
};

class LinuxFactory : public GUIFactory {
public:
    std::unique_ptr<Button> create_button() const override
    {
        return std::make_unique<LinuxButton>();
    }

    std::unique_ptr<Checkbox> create_checkbox() const override
    {
        return std::make_unique<LinuxCheckbox>();
    }
};

int main()
{
    std::unique_ptr<GUIFactory> factory;
    std::string os = "Windows"; // This could be determined at runtime

    if (os == "Windows") {
        factory = std::make_unique<WindowsFactory>();
    } else if (os == "Linux") {
        factory = std::make_unique<LinuxFactory>();
    }

    auto button = factory->create_button();
    auto checkbox = factory->create_checkbox();

    button->render();
    checkbox->render();

    return 0;
}
