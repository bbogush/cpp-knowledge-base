/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <memory>

class Printer {
public:
    virtual ~Printer() = default;
    virtual void print(const std::string &message) const = 0;
};

class LegacyPrinter {
public:
    void legacy_print(const std::string &message) const
    {
        std::cout << "Legacy Printer: " << message << std::endl;
    }
};

class PrinterAdapter : public Printer {
public:
    explicit PrinterAdapter(std::unique_ptr<LegacyPrinter> legacy_printer) :
        legacy_printer(std::move(legacy_printer))
    {
    }

    void print(const std::string &message) const override
    {
        legacy_printer->legacy_print(message);
    }

private:
    std::unique_ptr<LegacyPrinter> legacy_printer;
};

int main()
{
    std::unique_ptr<LegacyPrinter> legacy_printer = std::make_unique<LegacyPrinter>();
    PrinterAdapter adapter(std::move(legacy_printer));
    adapter.print("Hello, World!");

    return 0;
}
