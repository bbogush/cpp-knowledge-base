/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#ifndef CPP_KNOWLEDGE_BASE_LRU_CACHE_H
#define CPP_KNOWLEDGE_BASE_LRU_CACHE_H

#include <cstddef>
#include <list>
#include <optional>
#include <unordered_map>
#include <utility>

namespace cpp_knowledge_base::lru_cache {

template<typename Key, typename Value>
class LRUCache {
public:
    explicit LRUCache(size_t capacity) : capacity(capacity)
    {
    }

    std::optional<Value> get(const Key &key)
    {
        auto map_it = m.find(key);
        if (map_it == m.end()) {
            return std::nullopt;
        }

        auto list_it = map_it->second;
        l.splice(l.begin(), l, list_it);

        return list_it->second;
    }

    void put(const Key &key, const Value &value)
    {
        auto map_it = m.find(key);
        if (map_it != m.end()) {
            auto list_it = map_it->second;
            l.splice(l.begin(), l, list_it);
            list_it->second = value;
            return;
        }
        if (m.size() == capacity) {
            m.erase(l.back().first);
            l.pop_back();
        }
        l.emplace_front(key, value);
        m[key] = l.begin();
    }

private:
    using List = std::list<std::pair<Key, Value>>;

    std::unordered_map<Key, typename List::iterator> m;
    List l;
    size_t capacity;
};

} // namespace cpp_knowledge_base::lru_cache

#endif // CPP_KNOWLEDGE_BASE_LRU_CACHE_H
