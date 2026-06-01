# Big Integer

## Introduction

This is an arbitrary-precision integer library implemented in C++11.

## Motivation

There are certain use cases, e.g. calculating factorials and Nth powers of integers, that will result in very large integer results
which cannot fit into 32-bit or 64-bit built-in integers due to their limited widths.
A usual solution is to use arbitrary precision integers which are only limited by the amount of memory available to an application.

Unlike some programming languages, there is no standardized big integer or arbitrary-precision integer API in C++.
The Python programming language supports big integers natively, while Java and C# have their versions of big integer APIs.
The absence of a standard big integer API in C++ is not a restriction because
there are many open-source third-party big integer APIs for C++.
GNU Multiple Precision Arithmetic Library (GMP) is a C library which supports arbitrary precision integers,
so it can also be used in C++ codebases as well.

The main reason for the creation of the library is to demonstrate how an arbitrary precision integer API can be implemented in C++.
As C++ supports operator overloading for user-defined types, arithmetic and bitwise operations make use of overloaded operators
to behave in a similar way to the corresponding operators of primitive integer types.

## Supported platforms

- Ubuntu (may work on other Linux or POSIX platforms)
- Windows

## Supported features and operations

- Arithmetic operations (+, -, *, / and %)
- Arithmetic assignment operations (+=, -=, *=, /=, %=)
- Bitwise operations (&, |, ^, <<, >>)
- Bitwise assignment operations (&=, |=, ^=, <<=, >>=)
- Unary operations (+, -, ~)
- Comparisons (==, !=, >, >=, <, <=)
- Conversion from string
- Conversion to string

## Unit tests

Unit tests are available and more test cases may be added in the future.

## Sample application

A simple command line calculator is provided as an example.

## Compiling the source code

CMakeLists.txt files are provided.
CMake is required to generate the project build files or Make files.

## Convenience 

- Intuitive and easy-to-use API
- Easy to integrate into existing C++ codebases

## Constraints

- Only integer operations are supported. No support for fixed point or floating point numbers.
- No built-in thread safety. External mutexes are necessary for thread safety.
- The internal implementation is not optimized for performance.
- Not suitable for embedded system applications due to dynamic memory allocations during runtime.
- Lack of support for custom allocators.

## Implementation details

- The internal representation is std::vector<uint64_t>, i.e. a dynamic array of unsigned 64-bit integer blocks.
- A big integer is represented as a two's complement binary number.

## License

MIT license
