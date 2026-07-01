/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <memory>
#include <string>

class Computer {
public:
    class Builder {
    public:
        Builder(const std::string &cpu, const std::string &motherboard) :
            computer(std::unique_ptr<Computer>(new Computer(cpu, motherboard)))
        {
        }

        Builder &set_gpu(bool value)
        {
            computer->has_gpu = value;
            return *this;
        }

        Builder &set_ram(int gb)
        {
            computer->ram_gb = gb;
            return *this;
        }

        Builder &set_storage(int tb)
        {
            computer->storage_tb = tb;
            return *this;
        }

        Computer build() const
        {
            return std::move(*computer);
        }

    private:
        std::unique_ptr<Computer> computer;
    };

    void print() const
    {
        std::cout << "CPU: " << cpu << "\n"
                  << "Motherboard: " << motherboard << "\n"
                  << "GPU: " << (has_gpu ? "Yes" : "No") << "\n"
                  << "RAM: " << ram_gb << "GB\n"
                  << "Storage: " << storage_tb << "TB\n";
    }

private:
    std::string cpu;
    std::string motherboard;
    bool has_gpu = false;
    int ram_gb = 8;
    int storage_tb = 1;

    // Private constructor
    Computer(const std::string &cpu, const std::string &motherboard) :
        cpu(cpu), motherboard(motherboard)
    {
    }
};

int main()
{
    Computer pc =
        Computer::Builder("Intel i9", "ASUS Z790").set_gpu(true).set_ram(32).set_storage(2).build();

    pc.print();

    return 0;
}
