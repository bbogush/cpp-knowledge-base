/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include "fixed_ring_buffer.h"

#include <iostream>

using namespace cpp_knowledge_base::fixed_ring_buffer;

int main()
{
    FixedRingBuffer<int, 8> buffer;

    buffer.get_back_slot() = 1;
    buffer.push_back();

    buffer.push_back(2);

    std::cout << buffer.get_front() << "\n";
    buffer.pop_front();

    return 0;
}
