# C++ Code Style Guide

This document defines the coding style for this C++ project. The goal is **readability, consistency, and safety**.

---

## Table of Contents

- [Background](#background)
  - [Goals of the Style Guide](#goals-of-the-style-guide)
- [C++ Version](#c-version)
- [Header Files](#header-files)
  - [Self-contained Headers](#self-contained-headers)
  - [The #define Guard](#the-define-guard)
  - [Include What You Use](#include-what-you-use)
  - [Forward Declarations](#forward-declarations)
  - [Defining Functions in Header Files](#defining-functions-in-header-files)
  - [Names and Order of Includes](#names-and-order-of-includes)
- [Scoping](#scoping)
  - [Namespaces](#namespaces)
  - [Internal Linkage](#internal-linkage)
  - [Local Variables](#local-variables)
  - [Static and Global Variables](#static-and-global-variables)
  - [thread_local Variables](#thread_local-variables)
- [Classes](#classes)
  - [Doing Work in Constructors](#doing-work-in-constructors)
  - [Implicit Conversions](#implicit-conversions)
  - [Copyable and Movable Types](#copyable-and-movable-types)
  - [Structs vs. Classes](#structs-vs-classes)
  - [Structs vs. Pairs and Tuples](#structs-vs-pairs-and-tuples)
  - [Inheritance](#inheritance)
  - [Operator Overloading](#operator-overloading)
  - [Access Control](#access-control)
  - [Declaration Order](#declaration-order)
- [Functions](#functions)
  - [Inputs and Outputs](#inputs-and-outputs)
  - [Write Short Functions](#write-short-functions)
  - [Function Overloading](#function-overloading)
  - [Default Arguments](#default-arguments)
  - [Trailing Return Type Syntax](#trailing-return-type-syntax)
- [Tooling](#tooling)
- [Other C++ Features](#other-c-features)
  - [Ownership and Smart Pointers](#ownership-and-smart-pointers)
  - [Rvalue References](#rvalue-references)
  - [Friends](#friends)
  - [Exceptions](#exceptions)
  - [noexcept](#noexcept)
  - [Run-Time Type Information (RTTI)](#run-time-type-information-rtti)
  - [Casting](#casting)
  - [Streams](#streams)
  - [Preincrement and Predecrement](#preincrement-and-predecrement)
  - [Use of const](#use-of-const)
    - [Where to put the const](#where-to-put-the-const)
  - [Use of constexpr, constinit, and consteval](#use-of-constexpr-constinit-and-consteval)
  - [Integer Types](#integer-types)
    - [On Unsigned Integers](#on-unsigned-integers)
  - [Floating-Point Types](#floating-point-types)
  - [Architecture Portability](#architecture-portability)
  - [Preprocessor Macros](#preprocessor-macros)
  - [0 and nullptr/NULL](#0-and-nullptrnull)
  - [sizeof](#sizeof)
  - [Type Deduction (including auto)](#type-deduction-including-auto)
    - [Function template argument deduction](#function-template-argument-deduction)
    - [Local variable type deduction](#local-variable-type-deduction)
    - [Return type deduction](#return-type-deduction)
    - [Function parameter type deduction](#function-parameter-type-deduction)
    - [Lambda init captures](#lambda-init-captures)
    - [Structured bindings](#structured-bindings)
  - [Class Template Argument Deduction](#class-template-argument-deduction)
  - [Designated Initializers](#designated-initializers)
  - [Lambda Expressions](#lambda-expressions)
  - [Template Metaprogramming](#template-metaprogramming)
  - [Concepts and Constraints](#concepts-and-constraints)
  - [C++20 modules](#c20-modules)
  - [Coroutines](#coroutines)
  - [Disallowed standard library features](#disallowed-standard-library-features)
  - [Third-party Libraries](#third-party-libraries)
  - [Boost](#boost)
  - [std::hash](#stdhash)
  - [Nonstandard Extensions](#nonstandard-extensions)
  - [Aliases](#aliases)
  - [Switch Statements](#switch-statements)
- [Inclusive Language](#inclusive-language)
- [Naming](#naming)
  - [Choosing Names](#choosing-names)
  - [File Names](#file-names)
  - [Type Names](#type-names)
  - [Concept Names](#concept-names)
  - [Variable Names](#variable-names)
    - [Common Variable names](#common-variable-names)
    - [Class Data Members](#class-data-members)
    - [Struct Data Members](#struct-data-members)
  - [Constant Names](#constant-names)
  - [Function Names](#function-names)
  - [Namespace Names](#namespace-names)
  - [Enumerator Names](#enumerator-names)
  - [Template Parameter Names](#template-parameter-names)
  - [Macro Names](#macro-names)
  - [Aliases](#aliases-1)
  - [Exceptions to Naming Rules](#exceptions-to-naming-rules)
- [Comments](#comments)
  - [Comment Style](#comment-style)
  - [File Comments](#file-comments)
    - [Legal Notice and Author Line](#legal-notice-and-author-line)
  - [Struct and Class Comments](#struct-and-class-comments)
    - [Class Comments](#class-comments)
  - [Function Comments](#function-comments)
    - [Function Declarations](#function-declarations)
    - [Function Definitions](#function-definitions)
  - [Variable Comments](#variable-comments)
    - [Class Data Members](#class-data-members-1)
    - [Global Variables](#global-variables)
  - [Implementation Comments](#implementation-comments)
    - [Explanatory Comments](#explanatory-comments)
    - [Function Argument Comments](#function-argument-comments)
    - [Don'ts](#donts)
  - [Punctuation, Spelling, and Grammar](#punctuation-spelling-and-grammar)
  - [TODO Comments](#todo-comments)
  - [Deprecation Comments](#deprecation-comments)
- [Formatting](#formatting)
  - [Line Length](#line-length)
  - [Non-ASCII Characters](#non-ascii-characters)
  - [Spaces vs. Tabs](#spaces-vs-tabs)
  - [Function Declarations and Definitions](#function-declarations-and-definitions)
  - [Lambda Expressions](#lambda-expressions-1)
  - [String Literals](#string-literals)
  - [Floating-point Literals](#floating-point-literals)
  - [Function Calls](#function-calls)
  - [Braced Initializer List Format](#braced-initializer-list-format)
  - [Looping and branching statements](#looping-and-branching-statements)
  - [Pointer and Reference Expressions and Types](#pointer-and-reference-expressions-and-types)
  - [Boolean Expressions](#boolean-expressions)
  - [Return Values](#return-values)
  - [Variable and Array Initialization](#variable-and-array-initialization)
  - [Preprocessor Directives](#preprocessor-directives)
  - [Class Format](#class-format)
  - [Constructor Initializer Lists](#constructor-initializer-lists)
  - [Namespace Formatting](#namespace-formatting)
  - [Horizontal Whitespace](#horizontal-whitespace)
    - [General](#general)
    - [Loops and Conditionals](#loops-and-conditionals)
    - [Operators](#operators)
    - [Templates and Casts](#templates-and-casts)
  - [Vertical Whitespace](#vertical-whitespace)
- [Exceptions to the Rules](#exceptions-to-the-rules)
  - [Existing Non-conformant Code](#existing-non-conformant-code)
  - [Windows Code](#windows-code)
- [References](#references)

---

## Background

- C++ is powerful but complex; style rules manage that complexity.
- Style covers more than formatting: naming, scoping, ownership, and API design.
- This guide assumes familiarity with C++; it is not a C++ tutorial.

### Goals of the Style Guide

- Optimize for the **reader**, not the writer.
- Be consistent within this codebase and with `.clang-format`.
- Avoid surprising or hard-to-maintain constructs.

---

## C++ Version

- Target **C++20**.
- Avoid non-standard language extensions unless approved; see [Nonstandard Extensions](#nonstandard-extensions).

---

## Header Files

- Every `.cpp` file should have a matching `.h` file when it defines reusable APIs (tests and tiny `main()` files are exceptions).
- Use `*.h` and `*.cpp` extensions.
- Use `snake_case` for file names.
- Every file must include the project license header.

### Self-contained Headers

- Headers must compile on their own — include everything they need.
- Use `#include <...>` for standard/system headers; `#include "..."` for project and third-party headers.
- Expose only public API from headers; keep implementation details in `.cpp` files.
- Do not use `.inl.h` split headers; put template/inline definitions in the header when required.

```cpp
// License comes here
#ifndef NETWORK_SOCKET_H
#define NETWORK_SOCKET_H

#include <cstdint>
#include <string>

namespace network {

class Socket {
public:
    explicit Socket(int fd);
    int send(const std::string &data);

private:
    int fd;
};

} // namespace network

#endif // NETWORK_SOCKET_H
```

### The #define Guard

- Every header uses `#ifndef` / `#define` / `#endif` guards.
- Guard name is the file path in uppercase: `PATH_TO_FILE_H`.

```cpp
#ifndef FOO_BAR_BAZ_H
#define FOO_BAR_BAZ_H
// ...
#endif // FOO_BAR_BAZ_H
```

### Include What You Use

- Include headers for every symbol you use directly; do not rely on transitive includes.

```cpp
// OK
#include <vector>
std::vector<int> v;

// Wrong — <vector> not included
std::vector<int> v;
```

### Forward Declarations

- Prefer `#include` over forward declarations when practical.
- Do not forward-declare symbols you do not own.
- Avoid forward declarations that hide dependencies or break when APIs evolve.

```cpp
// Prefer
#include "other_module.h"

// Only when include cost is high and dependency is stable
class ExpensiveType;
void register_type(const ExpensiveType &value);
```

### Defining Functions in Header Files

- Define functions in headers only when `inline`, `constexpr`, or templates require it.
- Keep public inline bodies short (roughly ≤10 lines); put larger bodies in `.cpp` or private sections.

```cpp
// OK in header
inline int square(int x)
{
    return x * x;
}

template<typename T>
T clamp(T val, T lo, T hi)
{
    return std::max(lo, std::min(val, hi));
}
```

### Names and Order of Includes

**Project order** (overrides Google):

1. Own header (in `.cpp` files)
2. Application/project headers
3. Third-party headers
4. C++ standard library headers
5. C/system headers

Separate groups with a blank line; sort alphabetically within each group.

```cpp
#include "foo.h"

#include "bar.h"

#include <boost/system/error_code.hpp>

#include <iostream>
#include <vector>

#include <sys/ioctl.h>
```

---

## Scoping

### Namespaces

- Place project code in named namespaces.
- Use unique names based on the project name and possibly its path.
- Do not use `using namespace` in headers.
- Do not use inline namespaces.
- Close namespaces with a comment.
- Wrap the entire source file after includes, forward declarations of classes from other namespaces and defines.
- Prefer single-line nested namespaces. 

```cpp
// my_component.h
#include <iostream>

class my_project::other_component;

namespace my_project::my_component {

// All declarations are within the namespace scope.
class MyComponent {
public:
    void foo();
};

} // namespace my_project::my_component

// my_component.cpp
#include "my_component.h"

#include <vector>

namespace my_project::my_component {

// Definition of functions is within scope of the namespace.
void MyComponent::foo()
{
    ...
}

} // namespace my_project::my_component
```

### Internal Linkage

- Use anonymous namespaces or `static` in `.cpp` for file-local symbols.
- Do not use anonymous namespaces in headers.

```cpp
namespace {
void helper() {}
} // namespace
```

### Local Variables

- Declare variables in the narrowest scope, as close to first use as possible.
- Initialize at declaration.

```cpp
// OK
int jobs = num_jobs();
func(jobs);

for (int i = 0; i < jobs; ++i) {
}

// Wrong
int jobs;
int i;
...
func(jobs);
for (i = 0; i < jobs; ++i) {
}
```

### Static and Global Variables

- Avoid any dynamic initialization of a global/static object that depends on another non-trivial global/static object in a different translation unit.

```cpp
// OK - trivial
// config.cpp
constexpr int g_config = 1;

// logger.cpp
extern int g_config;
constexpr int g_logger_config = g_config;

// OK - initialization on first use
// config.cpp
const std::string &get_config()
{
    static const std::string config = "project";
    return config;
}

// logger.cpp
std::string get_prefix()
{
    return get_config() + ":";
}

// Wrong - initialization order undefined
// config.cpp
const std::string g_config = "project";

// logger.cpp
const std::string g_prefix = g_config + ":";
```

- Avoid global/file-local static objects whose destructors depend on other non-trivially destructible global/file-local static objects.

```cpp
// OK - no external dependencies
// logger.cpp
struct Logger {
    ~Logger() {
        std::cout << "shutdown\n";
    }
};

Logger g_logger;

// Wrong - destruction order undefined
// config.cpp
std::string g_config = "project";

// logger.cpp
extern std::string g_config;

struct Logger {
    ~Logger() {
        std::cout << "closing logs for " << g_config;
    }
};

Logger g_logger;
```

### thread_local Variables

- Prefer `thread_local` over other ways of defining thread-local data.

```cpp
// OK
thread_local Parser parser;

// Wrong
std::unordered_map<std::thread::id, Parser> data;
```

- Avoid any dynamic initialization of a `thread_local` object that depends on another non-trivial `thread_local` object in a different translation unit.

- Avoid `thread_local` objects whose destructors depend on other non-trivially destructible `thread_local` objects in different translation units.

---

## Classes

### Doing Work in Constructors

- Avoid virtual calls in constructors.
- Keep constructors lightweight.
- Use factories or `init()` for work that can fail (this project does not use exceptions as primary error flow).

```cpp
// OK
Foo::Foo()
{
}

int Foo::init()
{
    return connect_to_database();
}

// Wrong
Foo::Foo()
{
    connect_to_database();
}
```

### Implicit Conversions

- Mark single-argument constructors and conversion operators `explicit`.
- Copy/move constructors stay non-`explicit`.
- Constructor with single std::initializer_list parameter should omit explicit, in order to support copy-initialization (e.g., MyType m = {1, 2};).

```cpp
class Buffer {
public:
    explicit Buffer(std::size_t size);
    Buffer(const Buffer &buffer);
    Buffer(Buffer &&buffer) noexcept;
    Buffer(std::initializer_list<char> values);
    explicit operator bool() const noexcept;
};
```

### Copyable and Movable Types

- Make copy/move intent explicit (Rule of Five or Rule of Zero).
- Move operations should be `noexcept` when defined.

```cpp
class Socket {
public:
    Socket() = default;
    ~Socket();
    Socket(const Socket &) = delete;
    Socket &operator=(const Socket &) = delete;
    Socket(Socket &&) noexcept;
    Socket &operator=(Socket &&) noexcept;
};
```

### Structs vs. Classes

- `struct` for passive data with public fields and no invariants.
- `class` when methods enforce invariants.

```cpp
struct Point { double x, y; };

class Circle {
public:
    explicit Circle(Point center, double radius);
    int set_radius(double radius);

private:
    Point center;
    double radius; // invariant: radius > 0
};
```

### Structs vs. Pairs and Tuples

- Prefer named `struct` over `std::pair` / `std::tuple` when fields have meaning.

```cpp
struct Range { double low, high; };
```

### Inheritance

- Prefer composition over inheritance.
- Use `public` inheritance only; annotate overrides with `override` / `final`.
- Polymorphic bases need virtual destructors.
- Limit multiple implementation inheritance.

```cpp
class Base {
public:
    virtual ~Base() = default;
    virtual void process() = 0;
};

class Derived : public Base {
public:
    void process() override;
};
```

### Operator Overloading

- Overload only when meaning matches built-in operators (`==`, `<<`, etc.).
- Do not overload `&&`, `||`, `,`, or unary `&`.
- Do not use user-defined literals.
- Prefer `operator==` (and `operator<=>` when a total order is obvious).

### Access Control

- Data members are `private` unless the type is a passive `struct`.
- Use `protected` sparingly — only for hooks intended for subclasses.

### Declaration Order

- Order: `public` → `protected` → `private`.
- Within each section: types, constants, constructors, destructor, methods, data.

```cpp
class Foo {
public:
    using Id = int;
    explicit Foo(Id id);
    Id get_id() const noexcept;

private:
    Id id;
};
```

---

## Functions

### Inputs and Outputs

- Prefer return values over output parameters.
- Inputs: pass by value (cheap copies) or `const &` (read-only).
- Outputs: non-optional outputs use references; optional outputs use pointers.
- **Inputs before outputs.**

```cpp
int get_id(const std::string &name, Id &id);  // OK
void bad(Id &id, const std::string &name);    // Wrong — output first
```

### Write Short Functions

- Keep functions focused; consider splitting around 40 lines.
- Extract helpers instead of deep nesting.

### Function Overloading

- Overload only when call sites are clear without knowing the exact overload.
- Prefer `std::string_view` over parallel `std::string` / `const char*` overloads.

### Default Arguments

- Allowed on non-virtual functions when the default is stable.
- Banned on virtual functions.
- Prefer overloads when defaults harm readability or binary size.

### Trailing Return Type Syntax

- Use only for lambdas, template-heavy returns, or when it clearly improves readability.

```cpp
template <typename T, typename U>
auto add(T a, U b) -> decltype(a + b);
```

---

## Tooling

- Format code with **clang-format** using the project `.clang-format` in the repository root.
- **Formatting rules in `.clang-format` and this document override Google defaults** (e.g. 100-column limit, function brace on its own line, pointer/reference alignment).
- Configure your editor to format on save when possible.

---

## Other C++ Features

### Ownership and Smart Pointers

- Prefer single, clear owners; express transfers with `std::unique_ptr`.
- Use `std::shared_ptr` only for shared ownership that is truly needed.
- Never use `std::auto_ptr`.

```cpp
std::unique_ptr<Foo> make_foo();
void consume(std::unique_ptr<Foo> foo);
```

### Rvalue References

- Use `&&` for move constructors/assignment, `std::forward` for forwarding, and consuming APIs.
- Do not use rvalue references casually in non-move APIs.

### Friends

- Allowed when it keeps encapsulation; define friends in the same file when possible.

### Exceptions

- Use exceptions only for truly exceptional cases — not normal control flow.
- Expected failures return status codes, `std::optional`, or error types.

```cpp
// OK — invariant violation
void set_size(std::size_t size)
{
    if (size == 0) {
        throw std::logic_error("size must be positive");
    }
}

// Wrong — missing file is expected
if (!std::filesystem::exists(path)) {
    throw std::runtime_error("file not found");
}
```

### noexcept

- Mark non-throwing functions `noexcept`, especially move operations.

```cpp
Socket(Socket &&) noexcept;
Socket &operator=(Socket &&) noexcept;
```

### Run-Time Type Information (RTTI)

- Avoid `dynamic_cast` and `typeid` in production code; prefer virtual dispatch or visitors.
- RTTI is acceptable in tests when necessary.

### Casting

- Use C++ named casts; never C-style casts.
- `static_cast` for safe conversions; `reinterpret_cast` only for low-level code.

```cpp
auto x = static_cast<double>(value);
// Wrong: (double)value
```

### Streams

- No `std::cout` / `std::cerr` in production code; use the project logger.
- Avoid stream formatting state; prefer structured logging.

```cpp
log_info("value={}", value);
```

### Preincrement and Predecrement

- Prefer `++i` / `--i` unless postfix semantics are required.

```cpp
for (auto it = v.begin(); it != v.end(); ++it) { }
```

### Use of const

- Use `const` on parameters, locals (when helpful), and member functions that do not mutate logical state.
- `const` on by-value parameters is discouraged in declarations.

```cpp
const std::string &name() const;
void process(const Request &req);
```

#### Where to put the const

- **Project style:** attach `*` / `&` to the **variable name** (see Formatting), not `const int* p` vs `int const* p` debates.
- Be consistent within a file.

### Use of constexpr, constinit, and consteval

- Use `constexpr` for compile-time constants and functions.
- Use `constinit` for static/thread-local storage requiring constant initialization.
- Use `consteval` when evaluation must happen at compile time only.
- Prefer `constexpr` over macros for constants.

```cpp
constexpr int max_buffer = 4096;
constexpr int factorial(int n) { return n <= 1 ? 1 : n * factorial(n - 1); }
```

### Integer Types

- Use `<cstdint>` (`int32_t`, `uint64_t`, etc.) when size matters.
- Use `std::size_t` for sizes and container indices.
- Avoid bare `int` for domain values with implicit width requirements.

```cpp
uint64_t order_id;
std::size_t count = vec.size();
```

#### On Unsigned Integers

- Avoid unsigned types except for bit patterns, modular arithmetic, or APIs that require them.
- Do not use `unsigned` merely to mean “non-negative”.

### Floating-Point Types

- Use `float` and `double` only; avoid `long double`.
- Include a decimal point in literals (`1.0`, `0.5f`).

### Architecture Portability

- Do not assume sizes of `int`, `long`, or pointers.
- Use `<cstdint>` and portable formatting (`log_info`, not `printf` with wrong length modifiers).
- Store addresses as `uintptr_t` when needed as integers.

```cpp
int64_t value = ...;
log_info("value={}", value);
```

### Preprocessor Macros

- Avoid macros for constants and functions; use `constexpr` and `inline`.
- Reserve macros for include guards and conditional compilation.
- Macros must be ALL_CAPS; protect arguments and full expression with parentheses.
- Multi-statement macros use `do { ... } while (0)`.
- Prefer `#if defined(X)` over `#ifdef`; document `#endif` conditions.

```cpp
#define SQUARE(x) ((x) * (x))
```

### 0 and nullptr/NULL

- Use `nullptr` for null pointers; never `0` or `NULL`.
- Use `'\0'` for the null character.

```cpp
int *p = nullptr;
if (!p) { }
```

### sizeof

- Prefer `sizeof(variable)` over `sizeof(Type)`.

```cpp
memset(&data, 0, sizeof(data));
```

### Type Deduction (including auto)

- Use `auto` when it improves clarity or safety; do not use it to hide important types.
- Use `auto*` / `auto&` when the pointer/reference qualification matters.

#### Function template argument deduction

- Let the compiler deduce template arguments when clear.

#### Local variable type deduction

```cpp
auto it = map.find(key);           // OK when type is obvious
const auto &entry = items.front(); // OK — preserve reference
```

#### Return type deduction

- Avoid `auto` return types on public APIs unless the type is obvious or template code requires it.

#### Function parameter type deduction

- Generic lambdas may use `auto` parameters; prefer explicit types in public APIs.

#### Lambda init captures

```cpp
auto worker = [buffer = std::move(buf)]() { process(buffer); };
```

#### Structured bindings

```cpp
const auto [iter, inserted] = map.insert({key, value});
```

### Class Template Argument Deduction

- Use CTAD when it simplifies code and the deduced type is correct.
- Prefer explicit types when deduction is surprising.

```cpp
std::vector names = std::vector<std::string>{"a", "b"};
```

### Designated Initializers

- Use designated initializers (C++20) for structs with many fields — improves readability.

```cpp
Config cfg {
    .host = "localhost",
    .port = 8080,
};
```

### Lambda Expressions

- Prefer lambdas over `std::bind`.
- Capture by reference only when lifetime is guaranteed.

### Template Metaprogramming

- Use templates when they reduce duplication without harming readability.
- Prefer concepts (C++20) over SFINAE when possible.

### Concepts and Constraints

- Use `requires` clauses to document template requirements.

```cpp
template <std::integral T>
T twice(T value) { return value * 2; }
```

### C++20 modules

- Not used in this project yet; continue with headers until a project-wide modules policy exists.

### Coroutines

- Avoid coroutines unless there is a clear, reviewed use case and team familiarity.

### Disallowed standard library features

- `std::auto_ptr` — use `std::unique_ptr`.
- Avoid deprecated facilities; follow compiler warnings.

### Third-party Libraries

- Prefer established libraries already in the project over ad-hoc implementations.
- Match third-party naming only at integration boundaries.

### Boost

- Use Boost libraries already approved for the project (e.g. error codes, utilities).
- Do not add new Boost dependencies without review.

### std::hash

- Specialize `std::hash` in the same namespace as the type only when required for standard containers.
- Ensure hash and equality are consistent.

```cpp
namespace my_project {

struct Id { std::uint64_t value; };

} // namespace my_project

template <>
struct std::hash<my_project::Id> {
    std::size_t operator()(const my_project::Id &id) const noexcept
    {
        return std::hash<std::uint64_t>{}(id.value);
    }
};
```

### Nonstandard Extensions

- Avoid compiler-specific extensions unless isolated, documented, and reviewed.
- Prefer standard C++20 equivalents when they exist.
- Wrap unavoidable extensions in portability macros or headers — do not scatter them through business logic.

```cpp
// Wrong — GCC/Clang-only attribute in public API
__attribute__((packed)) struct Header { int id; };

// OK — standard attribute
[[nodiscard]] int parse(const std::string &input);

// Wrong — vendor builtin in application code
int count = __builtin_popcount(flags);

// OK — standard library / portable code
int count = std::popcount(flags); // C++20

// Wrong — inline assembly without abstraction
asm("nop");

// OK — isolated platform layer (document why standard C++ is insufficient)
#if defined(__GNUC__)
#define FORCE_INLINE __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE inline
#endif
```

### Aliases

- Prefer `using` over `typedef`.
- Type aliases at the appropriate scope — public API types in headers, local aliases in `.cpp`.

```cpp
using Id = std::uint64_t;
```

### Switch Statements

- Always include `default`.
- Mark intentional fall-through with `[[fallthrough]]`.
- See [Formatting](#looping-and-branching-statements) for layout rules.

```cpp
switch (state) {
case State::Idle:
    reset();
    break;
case State::Running:
    tick();
    [[fallthrough]];
case State::Stopping:
    shutdown();
    break;
default:
    break;
}
```

---

## Inclusive Language

- Use respectful, inclusive terminology in names and comments.
- Replace offensive or exclusionary terms when touching related code.

---

## Naming

### Choosing Names

- Clarity over cleverness.
- Names reflect meaning at their scope — short in tight loops, descriptive in public APIs.
- **Project style:** lowercase `snake_case` for functions, variables, and constants (overrides Google `MixedCase` / `kConstant` style).
- Do not use `_` or `__` prefixes reserved for the implementation.

### File Names

- `snake_case.h` / `snake_case.cpp`.
- One primary type per file when reasonable.

### Type Names

- Classes, structs, enums: **PascalCase**.

```cpp
class OrderBook {};
enum class Color { COLOR_RED, COLOR_GREEN };
```

### Concept Names

- PascalCase, noun phrase describing the requirement.

```cpp
template <typename T>
concept Hashable = requires(T value) {
    { std::hash<T>{}(value) } -> std::convertible_to<std::size_t>;
};
```

### Variable Names

- Locals and members: `snake_case`.
- **No trailing underscore** on members (overrides Google `member_` style).
- Do not encode type in the name (`i32_count`).

```cpp
class Session {
    int user_id;
    std::string display_name;
};
```

#### Common Variable names

- Short names (`i`, `it`) only in tiny scopes; descriptive names elsewhere.

#### Class Data Members

- Same as variables: `snake_case`, no trailing underscore.

#### Struct Data Members

- Public struct fields use `snake_case`.

### Constant Names

- `snake_case` with `constexpr` / `const` (overrides Google `kConstantName`).

```cpp
constexpr int max_retries = 5;
```

### Function Names

- `snake_case` for free functions and methods.

```cpp
void process_order();
int compute_hash();
```

### Namespace Names

- All lowercase, short, typically no underscores.

```cpp
namespace myproject {}
```

### Enumerator Names

- **All uppercase** with a common prefix (project convention).

```cpp
enum class Color {
    COLOR_RED,
    COLOR_GREEN,
};
```

### Template Parameter Names

- PascalCase for type parameters; concise but meaningful (`T`, `Iterator`, `Allocator`).

### Macro Names

- ALL_CAPS with project prefix.

```cpp
#define MYPROJECT_ASSERT(x) ...
```

### Aliases

- `snake_case` for type aliases at namespace scope when they are not public type names.

### Exceptions to Naming Rules

- Standard-like traits (`value_type`, `iterator`) may use library conventions.
- Third-party callbacks may match external API naming.

---

## Comments

- Explain **why**, not **what**.
- Keep comments accurate.
- Use `//` for comments; `/* */` only to disable code temporarily.
- Single space after `//`.

### Comment Style

```cpp
// Adjust price to avoid crossing the spread
int adjusted = price - spread;
```

### File Comments

- Brief one-line purpose at the top (after license).

```cpp
// order_book.h - limit order book with O(log n) insert/cancel
```

#### Legal Notice and Author Line

- Every file includes the project license header.
- Do not add per-author ownership lines unless required by project policy.

### Struct and Class Comments

- Document invariants and thread-safety expectations when non-obvious.

```cpp
// Thread-safe order book. Public methods take the internal mutex.
class OrderBook {};
```

#### Class Comments

- Same as struct/class comments — focus on usage and invariants.

### Function Comments

- Document non-obvious preconditions, postconditions, and ownership.

#### Function Declarations

```cpp
// Returns the best bid, or std::nullopt if the book is empty.
[[nodiscard]] std::optional<Price> best_bid() const;
```

#### Function Definitions

- Comment only when behavior is not obvious from code.

### Variable Comments

- Comment members only when units or semantics are unclear.

```cpp
double tick_size; // minimum price increment, USD
```

#### Class Data Members

- Trailing end-of-line comments for non-obvious fields.

#### Global Variables

- Avoid globals; if unavoidable, document lifetime and threading.

### Implementation Comments

#### Explanatory Comments

- Use for tricky algorithms, protocol details, or workarounds.

#### Function Argument Comments

- Prefer clear parameter names over arg comments; comment only when names are insufficient.

#### Don'ts

- Do not restate the code (`// increment i`).

### Punctuation, Spelling, and Grammar

- Complete sentences; American English.

### TODO Comments

- Include owner or ticket reference.

```cpp
// TODO(alice): replace with lock-free queue — JIRA-1234
```

### Deprecation Comments

- Mark deprecated APIs with `[[deprecated]]` and migration guidance.

```cpp
[[deprecated("Use new_api() instead")]]
void old_api();
```

---

## Formatting

**`.clang-format` is authoritative** for mechanical layout. Summary of project rules (overrides Google 80-column, Attach braces for functions, left-pointer style):

### Line Length

- Limit lines to **100 characters**.

### Non-ASCII Characters

- Source files are UTF-8.
- Avoid non-ASCII in identifiers; acceptable in comments when needed (e.g. units).

### Spaces vs. Tabs

- **4 spaces** for indentation; never tabs.

### Function Declarations and Definitions

- Return type on the same line as the function name.
- **Opening brace on its own line** for functions (overrides Google).
- Attach `*` / `&` to the **variable name**.
- Empty parameter lists omit `void` unless C linkage requires it.
- Do not align parameters or prototypes.

```cpp
const char *my_func(int param1, char *param2, bool param3,
    bool param4);

void process()
{
}
```

### Lambda Expressions

- Short lambdas inline; multi-line lambdas indented like function bodies.

```cpp
auto f = [](int x) { return x * 2; };

auto g = [&](const Request &r) {
    validate(r);
    submit(r);
};
```

### String Literals

- Split long literals with adjacent strings, not `\` continuation.

```cpp
log_info("This is a long message that exceeds the column limit so we "
         "split it across lines");
```

### Floating-point Literals

- Always include a decimal point (`1.0`, `0.5f`).

### Function Calls

- No space before `(`; no space after `(`; space after each comma.

```cpp
sum(4, 3);       // OK
sum (4, 3);      // Wrong
```

### Braced Initializer List Format

- Short lists inline; longer lists one element per line.
- Space inside braces: `{ 1, 2, 3 }`.

```cpp
std::vector<int> v = { 1, 2, 3 };
```

### Looping and branching statements

- **Control-statement brace on same line** (`if`, `for`, `while`, `else`) — overrides Google for functions only.
- Always brace `if` / `for` / `while` bodies.
- `else` / `else if` on the same line as the closing `}`.
- `while` of `do-while` on the same line as the closing `}` of `do`.
- Prefer `continue` / early `return` over deep nesting; no `else` after `return`.

```cpp
if (a) {
    do_a();
} else if (b) {
    do_b();
} else {
    do_c();
}

do {
    step();
} while (condition);
```

**Switch layout** (project rules):

- Always `default`.
- `case` labels not indented; body indented once.
- No space before `:`; one space after `:` when case body is on same line.
- Braces for `case` locals: `case 0: { ... break; }`.

```cpp
switch (c) {
case 0:
    do_a();
    break;
default:
    break;
}
```

### Pointer and Reference Expressions and Types

- `*` and `&` bind to the **name**, not the type.

```cpp
int *ptr;
const std::string &ref;
```

### Boolean Expressions

- Do not compare to `0`, `false`, or `nullptr`; use truthiness / `!`.
- Constant on the right: `length == 5` not `5 == length`.

```cpp
if (length) { }      // OK
if (!ptr) { }         // OK
if (ptr == nullptr) { } // Wrong
```

### Return Values

- No parentheses around simple `return` values.
- Pointer functions return `nullptr` on failure.
- `int` status: `0` success, negative for errors.
- `bool` predicates return `true` / `false` directly — not `0` / `1`.
- No bare `return;` at end of `void` functions.
- Exit early on errors.

```cpp
int open_file()
{
    if (error) {
        return -1;
    }
    return 0;
}
```

### Variable and Array Initialization

- Prefer brace initialization `{}` to avoid narrowing.

```cpp
int x { 42 };     // OK
int y = 3.14;     // Wrong — narrowing
```

### Preprocessor Directives

- See [Preprocessor Macros](#preprocessor-macros); do not indent code inside `#if`.

### Class Format

- Access specifiers aligned with `class`; members indented 4 spaces.
- **Class opening brace on same line** (differs from functions).

```cpp
class Foo {
public:
    explicit Foo(int id);
    int get_id() const noexcept;

private:
    int id;
};
```

### Constructor Initializer Lists

- Break after colon; one member per line when wrapping.

```cpp
Foo::Foo(int id, std::string name)
    : id(id),
      name(std::move(name))
{
}
```

### Namespace Formatting

- No extra indent inside namespaces; comment closing braces.

```cpp
namespace my_project::net {

class Socket {};

} // namespace my_project::net
```

### Horizontal Whitespace

#### General

- One space around binary operators and assignment.
- No space after unary operators; no space before postfix `++`/`--`.
- No trailing whitespace.

#### Loops and Conditionals

- Space after `if` / `for` / `while` / `switch` before `(`.

#### Operators

- See General; do not align operators across lines.

#### Templates and Casts

- No space in `static_cast<int>(value)`.

### Vertical Whitespace

- At most one blank line between logical sections.
- No blank line at start or end of a function body.

---

## Exceptions to the Rules

### Existing Non-conformant Code

- Match surrounding style in legacy code; prefer dedicated style-only cleanups over mixed-style functional changes.

### Windows Code

- Platform-specific code may follow Windows API conventions where necessary (e.g. exception usage on that platform).
- Keep platform differences localized and documented.

---

## References

- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [LLVM Coding Standards](https://llvm.org/docs/CodingStandards.html)

---

**Any deviation from this style must be justified and documented.**
