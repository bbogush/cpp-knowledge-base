# Fixed Ring Buffer

## Description

A **Fixed Ring Buffer** (circular buffer) is a FIFO queue of fixed capacity backed by a single contiguous array. Elements are pushed at the back and popped from the front; when the end of the array is reached, positions wrap around to the beginning, so storage is reused without moving elements or allocating memory.

---

## Key Features

- **O(1) push and pop**: Inserting at the back and removing from the front are constant time.
- **Fixed memory**: Elements are stored inline in a `std::array<T, capacity>`, with no dynamic allocation.
- **Power-of-two capacity**: Enforced at compile time, so wrapping is a cheap bit mask instead of a modulo or a branch.
- **Zero-copy write**: `get_back_slot` exposes the next free slot so the element can be filled in place and then committed with `push_back()`.
- **Full capacity usable**: All `capacity` slots can hold data - no slot is sacrificed to distinguish "full" from "empty".

---

## Limitations

- **Not thread-safe.** There is no synchronization; concurrent access from multiple threads requires external locking.
- **Capacity must be a power of two.** Other values are rejected at compile time.
- **No overflow/underflow handling.** Pushing into a full buffer or reading/popping an empty one is a precondition violation, checked only by `assert` in debug builds.
- **`T` must be default constructible.** All slots are constructed up front as part of the `std::array`.
- **Popped elements are not destroyed.** `pop_front` only advances `head`; the old object stays in its slot until it is overwritten, so resources it owns are released late.
- **Fixed capacity.** The buffer never grows.
