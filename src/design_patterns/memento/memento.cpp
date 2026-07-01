/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <memory>
#include <stack>
#include <string>

// State snapshot (Memento)
class Memento {
public:
    explicit Memento(const std::string &state) : state(state)
    {
    }

    std::string get_state() const
    {
        return state;
    }

private:
    std::string state;
};

// Originator
class TextEditor {
public:
    void write(const std::string &text)
    {
        content += text;
    }

    void show() const
    {
        std::cout << content << std::endl;
    }

    std::shared_ptr<Memento> save() const
    {
        return std::make_shared<Memento>(content);
    }

    void restore(const std::shared_ptr<Memento> &memento)
    {
        content = memento->get_state();
    }

private:
    std::string content;
};

// Caretaker
class History {
public:
    void push(const std::shared_ptr<Memento> &memento)
    {
        history.push(memento);
    }

    std::shared_ptr<Memento> pop()
    {
        if (history.empty()) {
            return nullptr;
        }
        auto memento = history.top();
        history.pop();
        return memento;
    }

private:
    std::stack<std::shared_ptr<Memento>> history;
};

int main()
{
    TextEditor editor;
    History history;

    editor.write("Hello, ");
    history.push(editor.save());

    editor.write("world!");
    history.push(editor.save());

    editor.show(); // Output: Hello, world!
    editor.restore(history.pop());
    editor.show(); // Output: Hello, world!
    editor.restore(history.pop());
    editor.show(); // Output: Hello,

    return 0;
}
