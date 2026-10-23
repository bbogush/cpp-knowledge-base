/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include "spsc_triple_buffer.h"

#include <iostream>

using namespace cpp_knowledge_base::spsc_triple_buffer;

int main()
{
    SpscTripleBuffer<int> buffer;
    buffer.write(1);
    buffer.write(2);
    buffer.write(3);
    int value;
    buffer.read(value);
    std::cout << "Read value: " << value << "\n";

    return 0;
}
