# SPSC Triple Buffer

## Description

An **SPSC (Single Producer, Single Consumer) Triple Buffer** is a lock-free data structure for passing the **latest value** from one thread to another. Unlike a queue, it does not keep a history: if the producer writes several times before the consumer reads, the consumer sees only the most recent value and the older ones are dropped.

It is commonly used where a consumer always needs the freshest state and stale updates are worthless - e.g., sensor readings, game/render state handed from a simulation thread to a render thread, audio parameter updates, telemetry snapshots.

---

## Key Features

- **Wait-free for the producer**: `write` never blocks and never waits for the consumer.
- **Non-blocking for the consumer**: `read` never blocks; if nothing new has arrived it returns the last value it read.
- **Latest-value semantics**: Unread updates are overwritten by newer ones.
- **No tearing**: The producer and consumer never touch the same buffer at the same time, so the consumer always sees a complete value.
- **Fixed memory**: Exactly three cache aligned slots of `T`, no dynamic allocation.

---

## How It Works

The structure holds three buffers, and each one has exactly one role at any time:

| Role           | Owner    | Purpose                                         |
|----------------|----------|-------------------------------------------------|
| `write_index`  | Producer | Private slot the producer fills next.           |
| `read_index`   | Consumer | Private slot the consumer is currently reading. |
| `next_index`   | Shared   | Slot holding the most recently published value. |

The shared slot index and a **new data** flag are packed into a single `std::atomic<uint8_t>`:

```
bit 2     : new_data_flag
bits 0..1 : next_index
```

**Write**

1. Store the value into the producer's private buffer (`buffer[write_index]`).
2. Atomically swap: publish `write_index` as the new shared slot and set the new data flag.
3. The previous shared slot becomes the producer's new private buffer.

**Read**

1. If the new data flag is clear, return `buffer[read_index]` (the cached value).
2. Otherwise, atomically swap: give `read_index` back as the shared slot and clear the flag.
3. The previously shared slot becomes the consumer's new private buffer, and its value is returned.

Because each operation is a single atomic exchange of a slot index, the two threads only ever hand buffers to each other through the shared slot and never access the same buffer concurrently.

---

## Usage

```cpp
SpscTripleBuffer<int> buffer;

// Producer thread
buffer.write(1);
buffer.write(2);
buffer.write(3);

// Consumer thread
int value;
buffer.read(value); // value == 3; updates 1 and 2 were overwritten
```

---

## Limitations

- **Exactly one producer and one consumer.** Multiple writers or readers break the ownership invariants.
- **Not a queue.** Intermediate values are lost by design; use an SPSC ring buffer if every update must be delivered.
- **Copies data.** `read` copies the value out, so very large `T` makes reads expensive.
- **Initial read.** Before the first `write`, `read` returns a default-constructed `T`.
