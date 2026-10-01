/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <atomic>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <thread>
#include <type_traits>

template<typename T>
    requires std::is_trivially_copyable_v<T> && std::is_default_constructible_v<T>
class SpmcSeqLock {
    // Number of 64-bit words needed to store T
    static constexpr size_t size_words = (sizeof(T) + 7) / 8;

public:
    void write(const T &v)
    {
        uint64_t buf[size_words] {};
        std::memcpy(buf, &v, sizeof(T));

        uint64_t s = seq.load(std::memory_order_relaxed);
        seq.store(s + 1, std::memory_order_relaxed); // Set odd (writing)
        std::atomic_thread_fence(std::memory_order_release);

        for (size_t i = 0; i < size_words; ++i) {
            words[i].store(buf[i], std::memory_order_relaxed);
        }

        seq.store(s + 2, std::memory_order_release); // Set even (done writing)
    }

    T read() const
    {
        uint64_t buf[size_words];
        uint64_t s0, s1;
        do {
            // Wait for writer to finish
            while ((s0 = seq.load(std::memory_order_acquire)) & 0x01) {
                std::this_thread::yield();
            }

            for (size_t i = 0; i < size_words; ++i) {
                buf[i] = words[i].load(std::memory_order_relaxed);
            }

            std::atomic_thread_fence(std::memory_order_acquire);
            s1 = seq.load(std::memory_order_relaxed);
        } while (s0 != s1);
        T v;
        std::memcpy(&v, buf, sizeof(T));
        return v;
    }

private:
    std::atomic<uint64_t> words[size_words] {};
    std::atomic<uint64_t> seq { 0 };
};

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
