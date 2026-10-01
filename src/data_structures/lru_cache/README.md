# LRU Cache

## Description

An **LRU (Least Recently Used) Cache** is a fixed-capacity data structure that evicts the **least recently used** entry when the cache is full and a new entry needs to be inserted.

It is commonly used in systems where you want fast access to frequently used data but memory is limited — e.g., CPU caches, database query caches, web browser history.

---

## Key Features

- **O(1) get**: Retrieve a value by key in constant time.
- **O(1) put**: Insert or update a key-value pair in constant time.
- **LRU Eviction**: When capacity is exceeded, the least recently used item is automatically removed.
- **Recency Tracking**: Both `get` and `put` mark the accessed entry as most recently used.

---
