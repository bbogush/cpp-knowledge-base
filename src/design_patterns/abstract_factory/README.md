# Abstract Factory Pattern

## Description

The **Abstract Factory** pattern provides an interface for creating **families of related objects** without specifying their concrete classes.
It groups factories that share a common theme, ensuring products from one factory are compatible with each other.

---

## Key Features

- **Family Consistency**: All products created by a concrete factory belong to the same variant, guaranteeing compatibility.
- **Open/Closed Principle**: New product families are added by implementing a new concrete factory - existing client code is untouched.
- **Abstraction Over Creation**: The client works with factories and products solely through abstract interfaces, unaware of any concrete type.

---

## Participants

| Role | In `abstract_factory.cpp` | Responsibility |
|---|---|---|
| Abstract Product A | `Button` | Abstract interface for buttons |
| Abstract Product B | `Checkbox` | Abstract interface for checkboxes |
| Concrete Products A | `WindowsButton`, `LinuxButton` | Platform-specific button implementations |
| Concrete Products B | `WindowsCheckbox`, `LinuxCheckbox` | Platform-specific checkbox implementations |
| Abstract Factory | `GUIFactory` | Declares `create_button()` and `create_checkbox()` factory methods |
| Concrete Factories | `WindowsFactory`, `LinuxFactory` | Create matching GUI widgets for a specific platform |
| Client | `main()` | Uses the abstract factory and products without knowing their concrete types |

---

## Advantages

- Guarantees that products from a single factory are mutually compatible.
- Isolates concrete classes from client code - clients depend only on abstractions.
- Switching product families requires changing only the concrete factory.

---

## Disadvantages

- Adding a new product type requires changing the abstract factory interface and all its concrete implementations.
- Can lead to a large number of classes when there are many products and variants.

---

## UML Diagram

```mermaid
classDiagram
    direction LR

    class Button {
        <<interface>>
        +render() void*
    }

    class Checkbox {
        <<interface>>
        +render() void*
    }

    class WindowsButton {
        +render() void
    }

    class LinuxButton {
        +render() void
    }

    class WindowsCheckbox {
        +render() void
    }

    class LinuxCheckbox {
        +render() void
    }

    class GUIFactory {
        <<interface>>
        +create_button()* unique_ptr~Button~
        +create_checkbox()* unique_ptr~Checkbox~
    }

    class WindowsFactory {
        +create_button() unique_ptr~Button~
        +create_checkbox() unique_ptr~Checkbox~
    }

    class LinuxFactory {
        +create_button() unique_ptr~Button~
        +create_checkbox() unique_ptr~Checkbox~
    }

    Button <|-- WindowsButton
    Button <|-- LinuxButton
    Checkbox <|-- WindowsCheckbox
    Checkbox <|-- LinuxCheckbox
    GUIFactory <|-- WindowsFactory
    GUIFactory <|-- LinuxFactory
    WindowsFactory ..> WindowsButton : creates
    WindowsFactory ..> WindowsCheckbox : creates
    LinuxFactory ..> LinuxButton : creates
    LinuxFactory ..> LinuxCheckbox : creates
    GUIFactory ..> Button : uses
    GUIFactory ..> Checkbox : uses
```
