Big Integer
===========

## Introduction

This is an experimental big integer library.

## Supported platforms

- Windows
- Ubuntu (may work on other Linux or POSIX platforms)

## Supported operations

- Arithmetic operations (+, -, *, / and %)
- Arithmetic assignment operations (+=, -=, *=, /=, %=)
- Bitwise operations (&, |, ^, <<, >>)
- Bitwise assignment operations (&=, |=, ^=, <<=, >>=)
- Unary operations (+, -, ~)
- Comparison (==, !=, >, >=, <, <=)
- Conversion from string
- Conversion to string

## Unit tests

Unit tests are available. More test cases may be added in the future.

## Sample application

An example application, which is a simple command line calculator, is provided.

## Compiling the source code

CMakeLists.txt files are provided.
CMake is required to generate the project files or Make files.

## Constraints

- Only basic operations are supported.
- Thread safety is not provided.
- The internal implementations may not be optimized.
- Not suitable for embedded system applications due to dynamic memory allocations during runtime.

## Implementation details

- The internal representation is std::vector<uint64_t>.
- The big integer is represented as a two's complement binary number.
