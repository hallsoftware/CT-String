# ct_str - Compile-Time String Library for C++20

A header-only C++20 library for compile-time string manipulation, hashing, and transformation.  All operations are evaluated at compile time using `consteval` functions and class-type non-type template parameters (NTTPs).

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Quick Start](#quick-start)
- [API Reference](#api-reference)
  - [Core Types](#core-types)
  - [String Transformations](#string-transformations)
  - [Query Functions](#query-functions)
  - [Checksum & Hash Functions](#checksum--hash-functions)
- [Design Philosophy](#design-philosophy)
  - [Why C++20?](#why-c20)
  - [Zero Runtime Overhead](#zero-runtime-overhead)
  - [Canonical Storage](#canonical-storage)
  - [Modular Header Design](#modular-header-design)
- [Examples](#examples)
  - [Basic Examples](#basic-examples)
  - [Simple Examples](#simple-examples)
  - [Intermediate Examples](#intermediate-examples)
- [Building the Examples](#building-the-examples)
- [Similar Libraries](#similar-libraries)
  - [Key Differences](#key-differences)
- [TODO List](#todo-list)
- [License](#license)
- [Contributing](#contributing)

## Features

- **Fully Compile-Time**:  All string operations are guaranteed to execute at compile time
- **Type-Safe**:  Leverages C++20's class-type NTTPs for type-safe string literals as template parameters
- **Zero Runtime Overhead**: Strings and transformations are computed during compilation
- **Rich API**: Comprehensive set of string manipulation functions
- **Hash Functions**: CRC32, SHA-256, and SHA-512 computed at compile time
- **Multi-Character Support**: Works with `char`, `wchar_t`, `char8_t`, `char16_t`, and `char32_t`
- **Header-Only**: Simple integration - just include and use

## Requirements

- **C++20 or later** (uses `consteval`, class-type NTTPs, `<=>` operator, `std::remove_cvref_t`)
- A conforming C++20 compiler: 
  - GCC 10+
  - Clang 12+
  - MSVC 19.29+ (Visual Studio 2019 16. 10+)

## Installation

Copy the `ct_str.hpp` file and the `details/` directory to your project's include path.

## Quick Start

```cpp
#include "ct_str.hpp"
#include <iostream>

int main()
{
    // Basic string storage
    using hello = ct_str::StringStore<"Hello, World!">;
    std::cout << hello::c_str() << "\n";
    std::cout << "Length: " << hello::view().size() << "\n";

    // String transformations
    using upper = ct_str::to_upper<"hello">;
    static_assert(upper::view() == "HELLO");

    using reversed = ct_str::reverse<"abc">;
    static_assert(reversed::view() == "cba");

    // Compile-time hashing
    using hash = ct_str::sha256<"password">;
    std::cout << "SHA256: " << hash::hex() << "\n";

    return 0;
}
```

## API Reference

### Core Types

#### `FixedString<CharT, N>`
A compile-time fixed-size character array that can be used as a non-type template parameter. 

```cpp
constexpr ct_str::FixedString str = "hello";  // Deduced as FixedString<char, 6>
static_assert(str.size() == 5);               // Excludes null terminator
```

#### `StringStore<Str>`
The canonical provider for compile-time strings.  Provides static access to string data.

```cpp
using MyStr = ct_str::StringStore<"Hello">;
const char* ptr = MyStr::c_str();           // Get C-string pointer
const char* val = MyStr::value;             // Same as c_str()
auto sv = MyStr::view();                    // Get std::string_view
constexpr auto fwd = MyStr::fwd;            // Get underlying FixedString
```

#### `FixedBytes<N>` and `ByteStore<Bytes>`
Analogous types for byte arrays, used primarily for hash results.

```cpp
using hash = ct_str::sha256<"test">;
const uint8_t* bytes = hash::value;     // Raw bytes (32 bytes for SHA256)
const char* hex = hash::hex();          // Hexadecimal string representation
constexpr auto size = hash::size();     // 32
```

### String Transformations

All transformations return a `StringStore` type alias. 

| Function | Description | Example |
|----------|-------------|---------|
| `substr<Str, Start, Length>` | Extract substring | `substr<"hello", 1, 3>` → `"ell"` |
| `to_upper<Str>` | Convert to uppercase (ASCII) | `to_upper<"Hello">` → `"HELLO"` |
| `to_lower<Str>` | Convert to lowercase (ASCII) | `to_lower<"Hello">` → `"hello"` |
| `reverse<Str>` | Reverse string | `reverse<"abc">` → `"cba"` |
| `left<Str, N>` | Get leftmost N characters | `left<"hello", 2>` → `"he"` |
| `right<Str, N>` | Get rightmost N characters | `right<"hello", 2>` → `"lo"` |
| `append<Strs...>` | Concatenate strings | `append<"a", "b", "c">` → `"abc"` |
| `trim<Str>` | Trim whitespace from both ends | `trim<"  hi  ">` → `"hi"` |
| `trim_left<Str>` | Trim leading whitespace | `trim_left<"  hi">` → `"hi"` |
| `trim_right<Str>` | Trim trailing whitespace | `trim_right<"hi  ">` → `"hi"` |
| `replace<Str, Pat, Rep>` | Replace first occurrence | `replace<"aaa", "a", "b">` → `"baa"` |
| `replace_all<Str, Pat, Rep>` | Replace all occurrences | `replace_all<"aaa", "a", "b">` → `"bbb"` |
| `replace_n<Str, Pat, Rep, N>` | Replace first N occurrences | `replace_n<"aaa", "a", "b", 2>` → `"bba"` |
| `basename<Path>` | Extract filename from path | `basename<"/foo/bar.txt">` → `"bar.txt"` |

### Query Functions

These return `consteval` values (not `StringStore` types).

| Function | Return Type | Description |
|----------|-------------|-------------|
| `at<Str, Pos>()` | `CharT` | Character at position (with bounds check) |
| `find<Str, Pattern, StartPos>()` | `std::size_t` | Find first occurrence |
| `find_char<Str, Ch, StartPos>()` | `std::size_t` | Find first character |
| `rfind<Str, Pattern>()` | `std::size_t` | Find last occurrence |
| `rfind_char<Str, Ch>()` | `std::size_t` | Find last character |
| `starts_with<Str, Pattern>()` | `bool` | Check prefix |
| `ends_with<Str, Pattern>()` | `bool` | Check suffix |
| `contains<Str, Pattern>()` | `bool` | Check if pattern exists |
| `compare<Str1, Str2>()` | `int` | Lexicographic comparison (-1, 0, 1) |

```cpp
static_assert(ct_str::contains<"hello world", "world">());
static_assert(ct_str::starts_with<"hello", "he">());
static_assert(ct_str::find<"abcabc", "bc">() == 1);
static_assert(ct_str::rfind<"abcabc", "bc">() == 4);
```

### Checksum & Hash Functions

| Function | Returns | Output Size | Description |
|----------|-------------|-------------|
| `crc32<Str>` | `uint32_t` | 4 bytes | CRC-32 (IEEE 802.3) |
| `sha256<Str>` | `ByteStore` | 32 bytes | SHA-256 |
| `sha512<Str>` | `ByteStore` | 64 bytes | SHA-512 |

```cpp
const uint32_t crc = ct_str::crc32<"Hello">;
using s256 = ct_str::sha256<"Hello">;
using s512 = ct_str::sha512<"Hello">;

// Access raw bytes
const uint8_t* bytes = s256::value;

// Get hex string representation
std::cout << s256::hex() << "\n";
// Output: 185f8db32271fe25f561a6fc938b2e264306ec304eda518007d1764826381969

// Compare hashes at compile time
static_assert(ct_str::sha256<"a">::fwd != ct_str::sha256<"b">::fwd);
```

## Design Philosophy

### Why C++20? 

This library fundamentally relies on C++20 features that have no equivalent in earlier standards:

1. **Class-Type NTTPs**:  The ability to use `FixedString` as a template parameter (`StringStore<"hello">`) is only possible in C++20+.

2. **`consteval`**: Guarantees compile-time evaluation.  Unlike `constexpr`, which may be evaluated at runtime, `consteval` functions *must* be evaluated at compile time.

3. **Abbreviated Function Templates**: The `auto` parameter syntax (`const auto* data`) simplifies generic code.

### Zero Runtime Overhead

All strings and transformations are computed during compilation. The resulting binaries contain only the final string data—no runtime computation occurs. 

```cpp
// This entire expression is evaluated at compile time
using result = ct_str::to_upper<ct_str::trim<"  hello  ">::fwd>;
// At runtime, only the string "HELLO" exists in the binary
```

### Canonical Storage

The `StringStore` and `ByteStore` types ensure that identical strings share the same storage through template instantiation rules.  This provides automatic string interning at compile time.

### Modular Header Design

The library is split into logical components for maintainability: 

- `fixed_string.hpp` - Core `FixedString` type
- `byte_store.hpp` - `FixedBytes` and `ByteStore` for binary data
- `string_store.hpp` - `StringStore` canonical provider
- `string_fns.hpp` - String manipulation functions
- `path_fns.hpp` - Path-related utilities
- `hash.hpp` - Cryptographic hash functions

## Examples

The library includes examples demonstrating various use cases:

### Basic Examples

These examples introduce core functionality and are perfect for getting started:

#### **basic_string_manipulation.cpp**
Demonstrates fundamental string operations:
- Case conversion (`to_upper`, `to_lower`)
- Substring operations (`substr`, `left`, `right`)
- Concatenation (`append`)
- Whitespace trimming (`trim`, `trim_left`, `trim_right`)
- String reversal
- Find and replace (`replace`, `replace_all`, `replace_n`)
- Searching (`find`, `rfind`, `find_char`)
- String tests (`starts_with`, `ends_with`, `contains`)
- String comparison
- Operation chaining

#### **basic_path_manipulation.cpp**
Covers path operations similar to `std::filesystem::path`:
- Filename extraction (`filename`)
- Stem and extension parsing (`stem`, `extension`)
- Path manipulation (`remove_filename`, `replace_filename`, `replace_extension`)
- Path queries (`has_root_path`, `has_root_name`, `has_root_directory`)
- Path type detection (`is_absolute`, `is_relative`)
- Cross-platform support (Unix and Windows paths)

#### **basic_hash_usage.cpp**
Introduces compile-time cryptographic operations:
- CRC32 checksums for version tagging and integrity checking
- SHA256 hashing with hex output
- SHA512 hashing for enhanced security
- Hash comparison at compile time
- Practical use cases: file integrity, password hashing, configuration verification

#### **basic_usage.cpp**
Comprehensive showcase of all library features:
- Multi-character type support (char, char8_t, wchar_t, char16_t, char32_t)
- String deduplication demonstration
- All string operations in one place
- Character access and substring extraction
- Complex operation chaining
- Compile-time verification examples

### Simple Examples

These examples show straightforward real-world applications:

#### **use_case_config_keys.cpp**
Compile-time configuration system:
- Type-safe configuration keys
- Compile-time key validation (typos cause compile errors)
- Zero runtime string hashing overhead
- CRC32-based key hashing
- Demonstrates how to build a configuration system using compile-time strings

### Intermediate Examples

These examples demonstrate more complex real-world scenarios:

#### **use_case_logger.cpp**
Compile-time logging system:
- Log message formatting at compile time
- Log level tagging (INFO, WARN, ERROR, DEBUG)
- Message deduplication tracking
- CRC32 hash-based message identification
- Compile-time log filtering
- Message composition and chaining
- Performance benefits: no runtime allocation, compile-time message validation

**Features:**
- Zero-overhead log message formatting
- Unique message hashing for log analysis
- Compile-time log level filtering
- Message occurrence counting

#### **use_case_path_builder.cpp**
Advanced path construction and manipulation:
- Template-based path builder
- Automatic path composition from components
- Path decomposition (directory, filename, stem, extension)
- Cross-platform path support (Unix/Windows)
- Relative and absolute path handling
- Build system integration examples

**Features:**
- Type-safe path construction
- Compile-time path validation
- Project structure modeling
- Build tool path generation

#### **use_case_file_registry.cpp**
Compile-time file metadata and registry system:
- File metadata extraction (path, filename, stem, extension)
- CRC32-based unique file IDs
- File type detection by extension (header, source, Python, etc.)
- Registry pattern for managing multiple files
- Filtering files by type
- Dependency tracking demonstrations

**Features:**
- Compile-time file classification
- Type-safe file registry
- Automatic unique ID generation
- File filtering and grouping

## Building the Examples

All examples are configured in CMake and can be built together.

## Similar Libraries

There are several other C++ libraries that provide compile-time string functionality.  Note that search results are limited, so there may be more libraries available.  You can [search GitHub for more options](https://github.com/search?q=language%3Acpp+compile+time+string+consteval+NTTP&type=code).

| Library | Description | C++ Standard |
|---------|-------------|--------------|
| [Tempura FixedString](https://github.com/SteveUlin/tempura) | NTTP-compatible fixed string based on P3094 proposal | C++20 |
| [fixstr](https://github.com/unterumarmansen/fixed_string) | Fixed string library with comprehensive comparison operators | C++20 |
| [miroir](https://github.com/eliossou/miroir) | Reflection library with `const_string` for compile-time strings | C++20 |
| [lager_ext StaticPath](https://github.com/aimoonchen/lager_ext) | Static path lens with `FixedString` for JSON pointer syntax | C++20 |
| [Boost.Hana](https://github.com/boostorg/hana) | Metaprogramming library with `hana::string` for compile-time strings | C++14+ |
| [ctti](https://github.com/Manu343726/ctti) | Compile-time type information with string utilities | C++14+ |

### Key Differences

**ct_str** differentiates itself by providing: 

- **Comprehensive transformation suite** (trim, replace, reverse, case conversion, ...)
- **Path utilities** (filename, extension, ...)
- **Checksum & Hash functions** (CRC32, SHA-256, SHA-512) computed at compile time
- **Unified API** where all string transformations return `StringStore` types
- **ByteStore** for uniform handling of binary data

### TODO List

- Add integer-to-string conversion functions, including base selection and zero-fill options.
- If possible, add floating-point to string conversion functions with precision control.
- Add type-to-string conversion functions.
- Add enum value-to-string conversion functions.
- Add more examples.

## License

BSD-3-Clause License

Copyright 2025 Kevin Hall. 

See [LICENSE](LICENSE) for full license text.

## Contributing

Contributions are welcome! Please feel free to submit issues and pull requests. 