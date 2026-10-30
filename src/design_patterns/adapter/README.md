# Adapter Pattern

## Description

The **Adapter** pattern converts the interface of a class into another interface that clients
expect. It allows classes with incompatible interfaces to work together by wrapping the existing
class in a new interface.

---

## Key Features

- **Interface Translation**: Bridges the gap between an existing class (`LegacyPrinter`) and a
  required interface (`Printer`).
- **Single Responsibility**: The adaptation logic is isolated in the `PrinterAdapter` class, keeping
  both `Printer` and `LegacyPrinter` unchanged.
- **Open/Closed Principle**: New adapters can be introduced without modifying existing client code
  or the adaptee.

---

## Participants

| Role      | In `adapter.cpp` | Responsibility                                                                                      |
| --------- | ---------------- | --------------------------------------------------------------------------------------------------- |
| `Target`  | `Printer`        | Defines the domain-specific interface the client uses via `print()`                                 |
| `Adaptee` | `LegacyPrinter`  | Contains the existing functionality (`legacy_print()`) with an incompatible interface               |
| `Adapter` | `PrinterAdapter` | Wraps `LegacyPrinter` (via `unique_ptr`) and translates `print()` calls into `legacy_print()` calls |
| Client    | `main()`         | Works with `Printer` interface, unaware of the underlying `LegacyPrinter`                           |

---

## Advantages

- Enables reuse of existing classes without modifying their source code.
- Decouples the client from the concrete implementation of the adaptee.
- A single adapter can work with multiple adaptees sharing a common interface.

---

## Disadvantages

- Adds an extra layer of indirection, which can complicate the design.
- Sometimes it is simpler to change the adaptee directly if its source is available.
- Object adapter (composition-based) cannot override adaptee behavior; class adapter
  (inheritance-based) can but sacrifices flexibility.

---

## UML Diagram

```mermaid
classDiagram
    direction LR

    class Printer {
        <<interface>>
        +print(message : string) void*
    }

    class LegacyPrinter {
        +legacy_print(message : string) void
    }

    class PrinterAdapter {
        -legacy_printer : unique_ptr~LegacyPrinter~
        +print(message : string) void
    }

    Printer <|-- PrinterAdapter
    PrinterAdapter o--> LegacyPrinter : wraps
```
