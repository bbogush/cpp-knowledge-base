/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <atomic>
#include <cstdint>
#include <iostream>
#include <new>
#include <type_traits>
#include <utility>

template<typename T>
class SpscTripleBuffer {
public:
    // Lock-free update.
    // Never waits for the consumer; unread updates may be overwritten.
    template<typename U>
        requires std::is_assignable_v<T &, U &&>
    void write(U &&data)
    {
        // Write data into current private write buffer
        buffer[write_index].value = std::forward<U>(data);

        uint32_t current_state = shared_state.load(std::memory_order_relaxed);
        uint32_t desired;
        uint32_t new_write_index;

        do {
            uint32_t next_index = current_state & next_index_mask;
            desired = write_index | new_data_flag;
            new_write_index = next_index;
        } while (!shared_state.compare_exchange_weak(current_state, desired,
            std::memory_order_acq_rel, std::memory_order_relaxed));

        write_index = new_write_index;
    }

    void read(T &data)
    {
        uint32_t current_state = shared_state.load(std::memory_order_relaxed);

        if (!(current_state & new_data_flag)) {
            // Return cached value if no new data is available
            data = buffer[read_index].value;
            return;
        }

        // Swap next_index with read_index and clear the new_data flag
        uint32_t desired;
        uint32_t new_read_index;

        do {
            new_read_index = current_state & next_index_mask;
            desired = read_index;
        } while (!shared_state.compare_exchange_weak(current_state, desired,
            std::memory_order_acq_rel, std::memory_order_relaxed));

        read_index = new_read_index;
        data = buffer[read_index].value;
    }

private:
    static constexpr size_t cache_line_size = 64;
    struct alignas(cache_line_size) Slot {
        T value {};
    };
    Slot buffer[3];

    static constexpr uint32_t init_next_index = 2;
    // Format: bit 0-1: next_index, bit 2: new_data_flag
    alignas(cache_line_size) std::atomic<uint32_t> shared_state { init_next_index };
    static constexpr uint32_t new_data_flag { 1 << 2 };
    static constexpr uint32_t next_index_mask { 0x03 };

    alignas(cache_line_size) uint32_t write_index { 0 };
    alignas(cache_line_size) uint32_t read_index { 1 };
};

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
