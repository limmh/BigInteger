#include "BigIntegerHelper.hpp"
#include <cassert>
#include <cctype>
#include <climits>

static_assert(8 == CHAR_BIT, "One byte must contain 8 bits.");

namespace BigIntegerHelper
{

void sign_extend(std::vector<uint64_t>& integer, size_t extra_nblocks)
{
	size_t nblocks = integer.size();
	bool extra_nblocks_ok = (extra_nblocks <= (SIZE_MAX - nblocks));
	assert(extra_nblocks_ok);
	if ((extra_nblocks > 0) && extra_nblocks_ok)
	{
		const uint64_t pattern = ((nblocks > 0) && sign_bit_is_set(integer[nblocks - 1])) ? ~static_cast<uint64_t>(0U) : 0U;
		size_t new_nblocks = nblocks + extra_nblocks;
		integer.resize(new_nblocks, pattern);
	}
}

void make_size_the_same(std::vector<uint64_t>& integer1, std::vector<uint64_t>& integer2)
{
	size_t nblocks1 = integer1.size();
	size_t nblocks2 = integer2.size();
	if (nblocks1 > nblocks2)
	{
		integer2.resize(nblocks1, 0U);
	}
	else if (nblocks1 < nblocks2)
	{
		integer1.resize(nblocks2, 0U);
	}
}

void make_size_the_same_and_sign_extend(std::vector<uint64_t>& integer1, std::vector<uint64_t>& integer2)
{
	const size_t nblocks1 = integer1.size();
	const size_t nblocks2 = integer2.size();
	const size_t diff = (nblocks1 > nblocks2) ? (nblocks1 - nblocks2) : (nblocks2 - nblocks1);
	std::vector<uint64_t>& integer = (nblocks1 > nblocks2) ? integer2 : integer1;

	if (diff > 0)
	{
		sign_extend(integer, diff);
	}
}

void resize_to_minimum_blocks(std::vector<uint64_t>& integer)
{
	const size_t num_blocks = integer.size();
	if (num_blocks < 2)
	{
		return;
	}

	const size_t last_index = num_blocks - 1;
	const bool sign_bit_status = sign_bit_is_set(integer[last_index]);
	const uint64_t pattern = (sign_bit_status) ? UINT64_MAX : 0U;

	if (integer[last_index] != pattern)
	{
		return;
	}

	for (size_t i = last_index; i > 0; --i)
	{
		size_t prev_index = i - 1;
		assert(prev_index < i);

		if (pattern == integer[prev_index])
		{
			if (0 == prev_index)
			{
				auto it = integer.begin() + i;
				integer.erase(it, integer.end());
			}
		}
		else if (sign_bit_status == sign_bit_is_set(integer[prev_index]))
		{
			auto it = integer.begin() + i;
			integer.erase(it, integer.end());
			break;
		}
		else
		{
			if ((i + 1) < num_blocks)
			{
				auto it = integer.begin() + i + 1;
				integer.erase(it, integer.end());
			}
			break;
		}
	}
}

int digit_to_integer(char digit, int base)
{
	constexpr int min_base = minimum_integer_base();
	constexpr int max_base = maximum_integer_base();
	int value = -1;

	if ((min_base <= base) && (base <= 10))
	{
		if (::isdigit(digit))
		{
			int digit_value = digit - '0';
			if (digit_value < base)
			{
				value = digit_value;
			}
		}
	}
	else if (base <= max_base)
	{
		if (digit >= 'A' && digit <= 'Z')
		{
			value = digit - 'A' + 10;
		}
		else if (digit >= 'a' && digit <= 'z')
		{
			value = digit - 'a' + 10;
		}
	}

	return value;
}

char digit_to_char(int digit_value, int base, bool upper_case)
{
	constexpr int min_base = minimum_integer_base();
	constexpr int max_base = maximum_integer_base();
	char c = '\0';
	const char *digits = (upper_case) ? "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" : "0123456789abcdefghijklmnopqrstuvwxyz";

	assert((min_base <= base) && (base <= max_base));
	assert((0 <= digit_value) && (digit_value <= base));

	if ((min_base <= base) && (base <= max_base) && (0 <= digit_value) && (digit_value < base))
	{
		const int index = digit_value;
		c = digits[index];
	}

	return c;
}

void shift_left(std::vector<uint64_t>& integer, size_t num_bits)
{
	if (num_bits > 0)
	{
		const size_t num_bits_per_block = sizeof(integer[0]) * CHAR_BIT;
		const size_t offset = num_bits / num_bits_per_block;
		const size_t remaining_num_bits = num_bits % num_bits_per_block;
		const size_t extra_num_blocks = (remaining_num_bits > 0) ? (offset + 1) : offset;

		const size_t num_blocks = ((SIZE_MAX - extra_num_blocks) >= integer.size()) ? (extra_num_blocks + integer.size()) : SIZE_MAX;
		sign_extend(integer, extra_num_blocks);

		if (offset > 0)
		{
			const size_t start = num_blocks - 1;
			const size_t end = offset - 1;

			for (size_t i = start; i > end; --i)
			{
				integer[i] = integer[i - offset];
			}

			for (size_t i = 0; i <= end; ++i)
			{
				integer[i] = 0U;
			}
		}

		if (remaining_num_bits > 0)
		{
			const size_t num_bits_to_shift = num_bits_per_block - remaining_num_bits;

			for (size_t i = (num_blocks - 1); i > 0; --i)
			{
				integer[i] <<= remaining_num_bits;
				integer[i] |= (integer[i - 1] >> num_bits_to_shift);
			}

			integer[0] <<= remaining_num_bits;
		}

		resize_to_minimum_blocks(integer);
	}
}

void shift_right(std::vector<uint64_t>& integer, size_t num_bits)
{
	if (num_bits > 0)
	{
		const size_t num_bits_per_block = sizeof(integer[0]) * CHAR_BIT;
		const size_t offset = num_bits / num_bits_per_block;
		const size_t remaining_num_bits = num_bits % num_bits_per_block;
		const size_t extra_num_blocks = (remaining_num_bits > 0) ? (offset + 1) : offset;

		const size_t num_blocks = ((SIZE_MAX - extra_num_blocks) >= integer.size()) ? (extra_num_blocks + integer.size()) : SIZE_MAX;
		sign_extend(integer, extra_num_blocks);

		if (offset > 0)
		{
			const size_t start = num_blocks - 1;
			const size_t end = num_blocks - offset;

			for (size_t i = 0; i < end; ++i)
			{
				integer[i] = integer[i + offset];
			}

			for (size_t i = start; i >= end; --i)
			{
				integer[i] = 0U;
			}
		}

		if (remaining_num_bits > 0)
		{
			const size_t num_bits_to_shift = num_bits_per_block - remaining_num_bits;

			for (size_t i = 0; i < (num_blocks - 1); ++i)
			{
				integer[i] >>= remaining_num_bits;
				integer[i] |= (integer[i + 1] << num_bits_to_shift);
			}

			integer[num_blocks - 1] >>= remaining_num_bits;
		}

		resize_to_minimum_blocks(integer);
	}
}

void bitwise_or(std::vector<uint64_t>& dest, const std::vector<uint64_t>& src)
{
	std::vector<uint64_t> operand = src;
	make_size_the_same(dest, operand);
	for (size_t i = 0; i < dest.size(); ++i)
	{
		dest[i] |= operand[i];
	}
}

void bitwise_and(std::vector<uint64_t>& dest, const std::vector<uint64_t>& src)
{
	std::vector<uint64_t> operand = src;
	make_size_the_same(dest, operand);
	for (size_t i = 0; i < dest.size(); ++i)
	{
		dest[i] &= operand[i];
	}
}

void bitwise_xor(std::vector<uint64_t>& dest, const std::vector<uint64_t>& src)
{
	std::vector<uint64_t> operand = src;
	make_size_the_same(dest, operand);
	for (size_t i = 0; i < dest.size(); ++i)
	{
		dest[i] ^= operand[i];
	}
}

} // namespace
