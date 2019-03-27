/*
The MIT License (MIT)

Copyright (c) 2019 MH Lim

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef BIG_INTEGER_HELPER_HPP
#define BIG_INTEGER_HELPER_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

static_assert(static_cast<uint64_t>(INT64_MIN) == 0x8000000000000000U, "The minimum hexadecimal value of 64-bit integer must be hexadecimal 8000000000000000.");
static_assert(static_cast<uint64_t>(INT64_MAX) == 0x7FFFFFFFFFFFFFFFU, "The maximum hexadecimal value of 64-bit integer must be hexadecimal 7FFFFFFFFFFFFFFF.");
static_assert(UINT64_MAX == 0xFFFFFFFFFFFFFFFFU, "The maximum hexadecimal value of 64-bit integer must be hexadecimal FFFFFFFFFFFFFFFF.");

namespace BigIntegerHelper
{

inline bool sign_bit_is_set(uint64_t block)
{
	return ((block & static_cast<uint64_t>(INT64_MIN)) != 0U);
}

void sign_extend(std::vector<uint64_t>& integer, size_t extra_nblocks);

void make_size_the_same(std::vector<uint64_t>& integer1, std::vector<uint64_t>& integer2);

void make_size_the_same_and_sign_extend(std::vector<uint64_t>& integer1, std::vector<uint64_t>& integer2);

void resize_to_minimum_blocks(std::vector<uint64_t>& integer);

inline constexpr int minimum_integer_base()
{
	return 2;
}

inline constexpr int maximum_integer_base()
{
	return 36;
}

// digit: a value between '0' and '9' or 'A' and 'Z' or 'a' and 'z'
// base: a value between 2 and 36
// returns a value between 0 and 35, returns -1 on error
int digit_to_integer(char digit, int base);

char digit_to_char(int digit_value, int base, bool upper_case);

// integer <<= num_bits
void shift_left(std::vector<uint64_t>& integer, size_t num_bits);
// integer >>= num_bits
void shift_right(std::vector<uint64_t>& integer, size_t num_bits);
// dest |= src
void bitwise_or(std::vector<uint64_t>& dest, const std::vector<uint64_t>& src);
// dest &= src
void bitwise_and(std::vector<uint64_t>& dest, const std::vector<uint64_t>& src);
// dest ^= src
void bitwise_xor(std::vector<uint64_t>& dest, const std::vector<uint64_t>& src);

} // namespace

#endif
