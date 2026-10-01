# SPMC SeqLock

## Description

An **SPMC (Single Producer, Multiple Consumer) SeqLock** (sequence lock) is a synchronization primitive for sharing a small value between one writer and many readers. The writer never waits for readers; readers detect a concurrent write through a **sequence counter** and simply retry.

It is commonly used for data that is read very often and written rarely, where readers must not slow the writer down - e.g., market data snapshots, system clock/time-keeping data (the Linux kernel uses seqlocks for `jiffies` and `timekeeper`), configuration or statistics published by one thread.

---

## Key Features

- **Writer never blocks**: `write` never waits for readers, no matter how many there are.
- **Readers never write shared memory**: Readers only load, so they cause no cache-line contention with each other and scale well.
- **Latest-value semantics**: Each write overwrites the previous value; there is no history.
- **No tearing**: A reader only returns a value that was not modified while it was being copied.
- **Fixed memory**: The value is stored inline as an array of 64-bit atomic words, with no dynamic allocation.

---

## How It Works

The structure holds the value and a sequence counter `seq`:

| `seq` value | Meaning                                  |
|-------------|------------------------------------------|
| even        | No write in progress, data is consistent. |
| odd         | Writer is modifying the data.            |

**Write**

1. Increment `seq` to an odd value (write in progress).
2. Release fence, so the odd counter becomes visible no later than any of the new data.
3. Store the value word by word into the atomic storage (relaxed).
4. Increment `seq` to the next even value with a release store (write finished).

**Read**

1. Load `seq` with acquire into `s0`; while it is odd, spin and wait for the writer.
2. Copy the value word by word out of the atomic storage (relaxed).
3. Acquire fence, then load `seq` again into `s1`.
4. If `s0 != s1`, a write overlapped the copy - discard it and retry from step 1.
5. Otherwise, the copy is consistent and is returned.

The data is stored as `std::atomic<uint64_t>` words rather than a plain `T` on purpose: readers race with the writer by design, and a race on non-atomic memory is undefined behaviour in C++, even if the torn result is later discarded. Relaxed atomic accesses make the race well-defined, while the fences provide the ordering (see H.-J. Boehm, *"Can Seqlocks Get Along with Programming Language Memory Models?"*).

---

## Usage

```cpp
struct Point {
    int x;
    int y;
};

SpmcSeqLock<Point> point;

// Writer thread
point.write({ 1, 2 });
point.write({ 3, 4 });

// Any number of reader threads
Point p = point.read(); // {3, 4} - never a mix like {1, 4}
```

---

## Limitations

- **Exactly one writer.** Concurrent writers corrupt the sequence counter; protect `write` with a mutex if multiple producers are needed.
- **`T` must be trivially copyable and default constructible.** The value is copied with `memcpy`; types owning resources (`std::string`, `std::vector`, ...) are not allowed.
- **Readers can starve.** Under a continuous stream of writes a reader may retry indefinitely.
- **Readers busy-wait.** A reader spins while a write is in progress, so it suits short writes and small `T`.
- **Copies data.** Every read (including retries) copies the whole value, so large `T` makes reads expensive.
- **Not a queue.** Intermediate values are lost by design.
- **Initial read.** Before the first `write`, `read` returns a zero-initialized `T`.
