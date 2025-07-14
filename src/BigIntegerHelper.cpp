#include "BigIntegerHelper.hpp"
#include <cassert>
#include <cctype>
#include <climits>

static_assert(8 == CHAR_BIT, "One byte must contain 8 bits.");

namespace BigIntegerHelper
{

void sign_extend(std::vector<uint64_t>& integer, size_t extra_nblocks)
{
	const size_t nblocks = integer.size();
	assert(nblocks > 0U);
	const bool extra_nblocks_ok = (extra_nblocks <= (SIZE_MAX - nblocks));
	assert(extra_nblocks_ok);
	if ((extra_nblocks > 0U) && extra_nblocks_ok)
	{
		const uint64_t pattern = ((nblocks > 0U) && sign_bit_is_set(integer[nblocks - 1U])) ? ~static_cast<uint64_t>(0U) : 0U;
		const size_t new_nblocks = nblocks + extra_nblocks;
		integer.resize(new_nblocks, pattern);
	}
}

void make_size_the_same(std::vector<uint64_t>& integer1, std::vector<uint64_t>& integer2)
{
	const size_t nblocks1 = integer1.size();
	const size_t nblocks2 = integer2.size();
	if (nblocks1 > nblocks2)
	{
		integer2.resize(nblocks1, 0U);
	}
	else if (nblocks1 < nblocks2)
	{
		integer1.resize(nblocks2, 0U);
	}
	assert(integer1.size() == integer2.size());
}

void make_size_the_same_and_sign_extend(std::vector<uint64_t>& integer1, std::vector<uint64_t>& integer2)
{
	const size_t nblocks1 = integer1.size();
	const size_t nblocks2 = integer2.size();
	const size_t diff = (nblocks1 > nblocks2) ? (nblocks1 - nblocks2) : (nblocks2 - nblocks1);
	std::vector<uint64_t>& integer = (nblocks1 > nblocks2) ? integer2 : integer1;

	if (diff > 0U)
	{
		sign_extend(integer, diff);
	}
}

void resize_to_minimum_blocks(std::vector<uint64_t>& integer)
{
	const size_t num_blocks = integer.size();
	if (num_blocks < 2U)
	{
		return;
	}

	const size_t last_index = num_blocks - 1U;
	const bool sign_bit_status = sign_bit_is_set(integer[last_index]);
	const uint64_t pattern = (sign_bit_status) ? UINT64_MAX : 0U;

	if (integer[last_index] != pattern)
	{
		return;
	}

	for (size_t i = last_index; i > 0U; --i)
	{
		size_t prev_index = i - 1U;
		assert(prev_index < i);

		if (pattern == integer[prev_index])
		{
			if (0U == prev_index)
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
				auto it = integer.begin() + i + 1U;
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
	assert(base >= min_base && base <= max_base);

	if ((min_base <= base) && (base <= 10))
	{
		assert(digit >= '0' && digit <= '9');
		if (digit >= '0' && digit <= '9')
		{
			value = digit - '0';
		}
	}
	else
	{
		assert((digit >= 'A' && digit <= 'Z') || (digit >= 'a' && digit <= 'z'));
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
	assert((0 <= digit_value) && (digit_value < base));

	if ((min_base <= base) && (base <= max_base) && (0 <= digit_value) && (digit_value < base))
	{
		const int index = digit_value;
		c = digits[index];
	}

	return c;
}

void shift_left(std::vector<uint64_t>& integer, size_t num_bits)
{
	if (0U == num_bits)
	{
		return;
	}

	const size_t num_bits_per_block = sizeof(integer[0]) * CHAR_BIT;
	const size_t offset = num_bits / num_bits_per_block;
	const size_t num_bits_to_shift_per_block = num_bits % num_bits_per_block;
	const size_t extra_num_blocks = (num_bits_to_shift_per_block > 0U) ? (offset + 1U) : offset;

	assert((SIZE_MAX - extra_num_blocks) >= integer.size());
	if ((SIZE_MAX - extra_num_blocks) < integer.size())
	{
		return;
	}

	sign_extend(integer, extra_num_blocks);
	const size_t num_blocks = integer.size();

	if (offset > 0U)
	{
		const size_t final_block_index = num_blocks - 1U;

		for (size_t i = final_block_index; i > (offset - 1U); --i)
		{
			integer[i] = integer[i - offset];
		}

		for (size_t i = 0U; i < offset; ++i)
		{
			integer[i] = 0U;
		}
	}

	if (num_bits_to_shift_per_block > 0U)
	{
		const size_t num_bits_to_copy_from_previous_block = num_bits_per_block - num_bits_to_shift_per_block;

		for (size_t i = (num_blocks - 1U); i > 0U; --i)
		{
			integer[i] <<= num_bits_to_shift_per_block;
			integer[i] |= (integer[i - 1U] >> num_bits_to_copy_from_previous_block);
		}

		integer[0U] <<= num_bits_to_shift_per_block;
	}

	resize_to_minimum_blocks(integer);
}

void shift_right(std::vector<uint64_t>& integer, size_t num_bits)
{
	if (0U == num_bits)
	{
		return;
	}

	const size_t num_bits_per_block = sizeof(integer[0]) * CHAR_BIT;
	size_t offset = num_bits / num_bits_per_block;
	const size_t num_bits_to_shift_per_block = num_bits % num_bits_per_block;
	const size_t num_blocks = integer.size();
	if (offset > num_blocks)
	{
		offset = num_blocks;
	}

	assert(num_blocks > 0U);
	const uint64_t pattern = sign_bit_is_set(integer[num_blocks - 1U]) ? UINT64_MAX : 0U;

	if (offset > 0U)
	{
		for (size_t i = 0U; i < (num_blocks - offset); ++i)
		{
			integer[i] = integer[i + offset];
		}

		for (size_t i = num_blocks - offset; i < num_blocks; ++i)
		{
			integer[i] = pattern;
		}
	}

	if (num_bits_to_shift_per_block > 0U)
	{
		const size_t num_bits_to_copy_from_next_block = num_bits_per_block - num_bits_to_shift_per_block;
		const size_t final_block_index = num_blocks - 1U;
		for (size_t i = 0; i < final_block_index; ++i)
		{
			integer[i] >>= num_bits_to_shift_per_block;
			integer[i] |= (integer[i + 1U] << num_bits_to_copy_from_next_block);
		}

		integer[final_block_index] >>= num_bits_to_shift_per_block;
		integer[final_block_index] |= (pattern << num_bits_to_copy_from_next_block);
	}

	resize_to_minimum_blocks(integer);
}

void bitwise_or(std::vector<uint64_t>& dest, const std::vector<uint64_t>& src)
{
	assert(dest.size() > 0U);
	assert(src.size() > 0U);
	if (dest.size() > src.size())
	{
		const size_t min_num_blocks = src.size();
		const size_t max_num_blocks = dest.size();
		const uint64_t pattern = sign_bit_is_set(src[src.size() - 1U]) ? UINT64_MAX : 0U;
		for (size_t i = 0U; i < min_num_blocks; ++i)
		{
			dest[i] |= src[i];
		}
		for (size_t i = min_num_blocks; i < max_num_blocks; ++i)
		{
			dest[i] |= pattern;
		}
	}
	else
	{
		const size_t extra_nblocks = src.size() - dest.size();
		sign_extend(dest, extra_nblocks);
		assert(src.size() == dest.size());
		for (size_t i = 0U; i < dest.size(); ++i)
		{
			dest[i] |= src[i];
		}
	}
}

void bitwise_and(std::vector<uint64_t>& dest, const std::vector<uint64_t>& src)
{
	assert(dest.size() > 0U);
	assert(src.size() > 0U);
	if (dest.size() > src.size())
	{
		const size_t min_num_blocks = src.size();
		const size_t max_num_blocks = dest.size();
		const uint64_t pattern = sign_bit_is_set(src[src.size() - 1U]) ? UINT64_MAX : 0U;
		for (size_t i = 0U; i < min_num_blocks; ++i)
		{
			dest[i] &= src[i];
		}
		for (size_t i = min_num_blocks; i < max_num_blocks; ++i)
		{
			dest[i] &= pattern;
		}
	}
	else
	{
		const size_t extra_nblocks = src.size() - dest.size();
		sign_extend(dest, extra_nblocks);
		assert(src.size() == dest.size());
		for (size_t i = 0U; i < dest.size(); ++i)
		{
			dest[i] &= src[i];
		}
	}
}

void bitwise_xor(std::vector<uint64_t>& dest, const std::vector<uint64_t>& src)
{
	assert(dest.size() > 0U);
	assert(src.size() > 0U);
	if (dest.size() > src.size())
	{
		const size_t min_num_blocks = src.size();
		const size_t max_num_blocks = dest.size();
		const uint64_t pattern = sign_bit_is_set(src[src.size() - 1U]) ? UINT64_MAX : 0U;
		for (size_t i = 0U; i < min_num_blocks; ++i)
		{
			dest[i] ^= src[i];
		}
		for (size_t i = min_num_blocks; i < max_num_blocks; ++i)
		{
			dest[i] ^= pattern;
		}
	}
	else
	{
		const size_t extra_nblocks = src.size() - dest.size();
		sign_extend(dest, extra_nblocks);
		assert(src.size() == dest.size());
		for (size_t i = 0U; i < dest.size(); ++i)
		{
			dest[i] ^= src[i];
		}
	}
}

void invert_bits(std::vector<uint64_t>& integer)
{
	const size_t num_blocks = integer.size();
	assert(num_blocks > 0U);
	for (size_t i = 0U; i < num_blocks; ++i)
	{
		uint64_t& block_ref = integer[i];
		block_ref = ~block_ref;
	}
}

} // namespace
