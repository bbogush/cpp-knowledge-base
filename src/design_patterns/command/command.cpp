/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <memory>
#include <stack>

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class Light {
public:
    void on() const
    {
        std::cout << "Light is ON" << std::endl;
    }
    void off() const
    {
        std::cout << "Light is OFF" << std::endl;
    }
};

class LightOnCommand : public Command {
public:
    explicit LightOnCommand(Light &light) : light(light)
    {
    }
    void execute() override
    {
        light.on();
    }
    void undo() override
    {
        light.off();
    }

private:
    Light &light;
};

class LightOffCommand : public Command {
public:
    explicit LightOffCommand(Light &light) : light(light)
    {
    }
    void execute() override
    {
        light.off();
    }
    void undo() override
    {
        light.on();
    }

private:
    Light &light;
};

class RemoteControl {
public:
    void submit(std::shared_ptr<Command> command)
    {
        command->execute();
        history.push(command);
    }

    void undo_last()
    {
        if (!history.empty()) {
            history.top()->undo();
            history.pop();
        }
    }

private:
    std::stack<std::shared_ptr<Command>> history;
};

int main()
{
    Light light;

    auto light_on = std::make_shared<LightOnCommand>(light);
    auto light_off = std::make_shared<LightOffCommand>(light);

    RemoteControl remote;

    remote.submit(light_on);
    remote.submit(light_off);

    std::cout << "Undo last command:\n";
    remote.undo_last();

    return 0;
}
