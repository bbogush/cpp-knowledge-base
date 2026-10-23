/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include "spmc_seqlock.h"

#include <iostream>

using namespace cpp_knowledge_base::spmc_seqlock;

int main()
{
    SpmcSeqLock<int> seq;
    seq.write(1);
    seq.write(2);
    seq.write(3);
    int value = seq.read();

    std::cout << "Read value: " << value << '\n';

    return 0;
}
