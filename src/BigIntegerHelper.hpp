#ifndef BIG_INTEGER_HELPER_HPP
#define BIG_INTEGER_HELPER_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

static_assert(static_cast<uint64_t>(INT64_MIN) == 0x8000000000000000ULL, "The minimum hexadecimal value of 64-bit integer must be hexadecimal 8000000000000000.");
static_assert(static_cast<uint64_t>(INT64_MAX) == 0x7FFFFFFFFFFFFFFFULL, "The maximum hexadecimal value of 64-bit integer must be hexadecimal 7FFFFFFFFFFFFFFF.");
static_assert(UINT64_MAX == 0xFFFFFFFFFFFFFFFFULL, "The maximum hexadecimal value of 64-bit integer must be hexadecimal FFFFFFFFFFFFFFFF.");

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

constexpr int minimum_integer_base()
{
	return 2;
}

constexpr int maximum_integer_base()
{
	return 36;
}

// digit: a value between '0' and '9' or 'between A' and 'Z' or between 'a' and 'z'
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
