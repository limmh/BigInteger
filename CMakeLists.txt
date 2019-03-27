cmake_minimum_required(VERSION 3.0)
project(BigInteger)

if (UNIX)
    add_compile_options(-Wall -Wextra -Wpedantic -std=gnu++11)
endif (UNIX)

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(example)
