/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <list>
#include <unordered_map>

class LRUCache {
public:
    explicit LRUCache(int capacity) : capacity(capacity)
    {
    }

    int get(int key)
    {
        auto map_it = m.find(key);
        if (map_it == m.end()) {
            return -1;
        }

        auto list_it = map_it->second;
        l.splice(l.begin(), l, list_it);

        return list_it->second;
    }

    void put(int key, int value)
    {
        auto map_it = m.find(key);
        if (map_it != m.end()) {
            auto list_it = map_it->second;
            l.splice(l.begin(), l, list_it);
            list_it->second = value;
            return;
        }
        if (m.size() == capacity) {
            auto key = l.back().first;
            l.pop_back();
            m.erase(key);
        }
        l.push_front({ key, value });
        m[key] = l.begin();
    }

private:
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> m;
    std::list<std::pair<int, int>> l;
    size_t capacity;
};

int main()
{
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    std::cout << cache.get(1) << "\n"; // returns 1
    cache.put(3, 3); // evicts key 2
    std::cout << cache.get(2) << "\n"; // returns -1 (not found)
    cache.put(4, 4); // evicts key 3
    std::cout << cache.get(3) << "\n"; // returns -1 (not found)
    std::cout << cache.get(4) << "\n"; // returns 4

    return 0;
}
