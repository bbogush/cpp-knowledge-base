# Facade Pattern

## Description

The **Facade** pattern provides a simplified interface to a complex subsystem. It hides the
complexity of the subsystem behind a single unified interface, making the subsystem easier to use.

---

## Key Features

- **Simplified Interface**: Exposes a high-level interface that makes the subsystem easier to use
  without exposing its internal complexity.
- **Loose Coupling**: Clients depend only on the `Facade`, not on individual subsystem classes.
- **Single Entry Point**: Centralizes interaction with the subsystem, reducing the number of objects
  clients deal with.

---

## Participants

| Role              | In `facade.cpp`         | Responsibility                                                                                    |
| ----------------- | ----------------------- | ------------------------------------------------------------------------------------------------- |
| `Facade`          | `HomeTheaterFacade`     | Provides `watch_movie()` and `end_movie()` high-level operations                                  |
| Subsystem classes | `Player`, `SoundSystem` | Implement low-level operations (`on()`, `off()`, `play()`, `set_volume()`); unaware of the facade |
| Client            | `main()`                | Uses only `HomeTheaterFacade`, unaware of `Player` or `SoundSystem` internals                     |

---

## Advantages

- Reduces complexity for clients by providing a simpler interface.
- Decouples client code from subsystem internals, making subsystem changes transparent.
- Can layer multiple facades over a complex subsystem for different use cases.

---

## Disadvantages

- Can become a "god object" if it accumulates too many responsibilities.
- May hide useful subsystem features that advanced clients need.
- Does not prevent clients from accessing subsystem classes directly if needed.

---

## UML Diagram

```mermaid
classDiagram
    direction LR

    class HomeTheaterFacade {
        -player : Player&
        -sound_system : SoundSystem&
        +watch_movie(movie : string) void
        +end_movie() void
    }

    class Player {
        +on() void
        +play(movie : string) void
        +off() void
    }

    class SoundSystem {
        +on() void
        +set_volume(level : int) void
        +off() void
    }

    HomeTheaterFacade --> Player : uses
    HomeTheaterFacade --> SoundSystem : uses
```
