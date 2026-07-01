/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <memory>
#include <vector>

class FileSystemComponent {
public:
    virtual ~FileSystemComponent() = default;
    virtual void display(int indent = 0) const = 0;
};

class File : public FileSystemComponent {
public:
    explicit File(const std::string &name) : name(name)
    {
    }

    void display(int indent = 0) const override
    {
        std::cout << std::string(indent, ' ') << "File: " << name << std::endl;
    }

private:
    std::string name;
};

class Directory : public FileSystemComponent {
public:
    explicit Directory(const std::string &name) : name(name)
    {
    }

    void add(std::shared_ptr<FileSystemComponent> component)
    {
        components.push_back(component);
    }

    void display(int indent = 0) const override
    {
        std::cout << std::string(indent, ' ') << "Directory: " << name << std::endl;
        for (const auto &component : components) {
            component->display(indent + 2);
        }
    }

private:
    std::string name;
    std::vector<std::shared_ptr<FileSystemComponent>> components;
};

int main()
{
    auto file1 = std::make_shared<File>("file1.txt");
    auto file2 = std::make_shared<File>("file2.txt");

    auto folder1 = std::make_shared<Directory>("Documents");
    auto folder2 = std::make_shared<Directory>("Images");

    folder1->add(file1);
    folder1->add(file2);

    auto root = std::make_shared<Directory>("Root");
    root->add(folder1);
    root->add(folder2);

    root->display();

    return 0;
}
