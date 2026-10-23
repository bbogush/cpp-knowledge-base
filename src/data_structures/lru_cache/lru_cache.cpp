/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include "lru_cache.h"

#include <iostream>

using namespace cpp_knowledge_base::lru_cache;

int main()
{
    LRUCache<int, int> cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    std::cout << cache.get(1).value_or(-1) << "\n"; // returns 1
    cache.put(3, 3); // evicts key 2
    std::cout << cache.get(2).value_or(-1) << "\n"; // returns -1 (not found)
    cache.put(4, 4); // evicts key 1
    std::cout << cache.get(1).value_or(-1) << "\n"; // returns -1 (not found)
    std::cout << cache.get(4).value_or(-1) << "\n"; // returns 4

    return 0;
}
