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

#include "BigInteger.hpp"
#include "BigIntegerHelper.hpp"
#include <cassert>
#include <cctype>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace BigIntegerHelper;

BigInteger::BigInteger() : value(1, 0U)
{
}

BigInteger::BigInteger(int n) : value(1, static_cast<uint64_t>(n))
{
}

BigInteger::BigInteger(long n) : value(1, static_cast<uint64_t>(n))
{
}

BigInteger::BigInteger(long long n) : value(1, static_cast<uint64_t>(n))
{
}

BigInteger::BigInteger(unsigned int n) : value(1, static_cast<uint64_t>(n))
{
	if (sign_bit_is_set(value[0]))
	{
		value.push_back(0U);
	}
}

BigInteger::BigInteger(unsigned long n) : value(1, static_cast<uint64_t>(n))
{
	if (sign_bit_is_set(value[0]))
	{
		value.push_back(0U);
	}
}

BigInteger::BigInteger(unsigned long long n) : value(1, static_cast<uint64_t>(n))
{
	if (sign_bit_is_set(value[0]))
	{
		value.push_back(0U);
	}
}

BigInteger::BigInteger(const char *n)
{
	*this = fromString(n, 10);
}

BigInteger& BigInteger::operator=(int n)
{
	*this = BigInteger(n);
	return *this;
}

BigInteger& BigInteger::operator=(long n)
{
	*this = BigInteger(n);
	return *this;
}

BigInteger& BigInteger::operator=(long long n)
{
	*this = BigInteger(n);
	return *this;
}

BigInteger& BigInteger::operator=(unsigned int n)
{
	*this = BigInteger(n);
	return *this;
}

BigInteger& BigInteger::operator=(unsigned long n)
{
	*this = BigInteger(n);
	return *this;
}

BigInteger& BigInteger::operator=(unsigned long long n)
{
	*this = BigInteger(n);
	return *this;
}

BigInteger& BigInteger::operator=(const char *n)
{
	*this = fromString(n, 10);
	return *this;
}

BigInteger BigInteger::operator~() const
{
	BigInteger result = *this;
	for (auto it = result.value.begin(); it != result.value.end(); ++it)
	{
		uint64_t& block = *it;
		block = ~block;
	}
	return result;
}

BigInteger BigInteger::operator+() const
{
	return *this;
}

BigInteger BigInteger::operator-() const
{
	BigInteger result = ~(*this);
	result += 1;
	return result;
}

bool BigInteger::operator==(const BigInteger& n) const
{
	bool result = true;
	BigInteger n1 = *this;
	BigInteger n2 = n;
	make_size_the_same_and_sign_extend(n1.value, n2.value);
	const size_t size = n1.value.size();

	for (size_t i = 0; i < size; ++i)
	{
		if (n1.value[i] != n2.value[i])
		{
			result = false;
			break;
		}
	}
	return result;
}

bool BigInteger::operator!=(const BigInteger& n) const
{
	return !(*this == n);
}

bool BigInteger::operator>(const BigInteger& n) const
{
	return (*this >= n) && ((*this - n) != 0);
}

bool BigInteger::operator>=(const BigInteger& n) const
{
	BigInteger diff = *this - n;
	return !sign_bit_is_set(diff.value[diff.value.size() - 1]);
}

bool BigInteger::operator<(const BigInteger& n) const
{
	BigInteger diff = *this - n;
	return sign_bit_is_set(diff.value[diff.value.size() - 1]);
}

bool BigInteger::operator<=(const BigInteger& n) const
{
	return (*this < n) || ((*this - n) == 0);
}

BigInteger& BigInteger::operator&=(const BigInteger& n)
{
	bitwise_and(value, n.value);
	return *this;
}

BigInteger& BigInteger::operator|=(const BigInteger& n)
{
	bitwise_or(value, n.value);
	return *this;
}

BigInteger& BigInteger::operator^=(const BigInteger& n)
{
	bitwise_xor(value, n.value);
	return *this;
}

BigInteger& BigInteger::operator<<=(size_t num_bits)
{
	shift_left(value, num_bits);
	return *this;
}

BigInteger& BigInteger::operator>>=(size_t num_bits)
{
	shift_right(value, num_bits);
	return *this;
}

BigInteger BigInteger::operator&(const BigInteger& n) const
{
	BigInteger result = *this;
	result &= n;
	return result;
}

BigInteger BigInteger::operator|(const BigInteger& n) const
{
	BigInteger result = *this;
	result |= n;
	return result;
}

BigInteger BigInteger::operator^(const BigInteger& n) const
{
	BigInteger result = *this;
	result ^= n;
	return result;
}

BigInteger BigInteger::operator<<(size_t n) const
{
	BigInteger result = *this;
	result <<= n;
	return result;
}

BigInteger BigInteger::operator>>(size_t n) const
{
	BigInteger result = *this;
	result >>= n;
	return result;
}

BigInteger& BigInteger::operator+=(const BigInteger& n)
{
	BigInteger operand(n);
	make_size_the_same_and_sign_extend(value, operand.value);
	sign_extend(value, 1);
	sign_extend(operand.value, 1);

	uint64_t carry = 0U;

	for (size_t i = 0; i < value.size(); ++i)
	{
		const uint64_t min_operand = (value[i] < operand.value[i]) ? value[i] : operand.value[i];
		value[i] += operand.value[i];
		if (value[i] < min_operand)
		{
			value[i] += carry;
			carry = 1U;
		}
		else
		{
			value[i] += carry;
			carry = (value[i] < carry) ? 1U : 0U;
		}
	}

	resize_to_minimum_blocks(value);
	return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& n)
{
	*this += (-n);
	return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& n)
{
	const BigInteger zero = 0;
	BigInteger multiplicand(*this);
	BigInteger multiplier(n);
	size_t multiplicand_nblocks = multiplicand.value.size();
	sign_extend(multiplicand.value, multiplier.value.size());
	sign_extend(multiplier.value, multiplicand_nblocks);
	*this = 0;

	while (multiplier != zero)
	{
		if ((multiplier & 1) != zero)
		{
			*this += multiplicand;
		}
		multiplicand <<= 1;
		multiplier >>= 1;
	}

	return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& n)
{
	BigInteger remainder;
	*this = divide(*this, n, remainder);
	return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& n)
{
	BigInteger remainder;
	divide(*this, n, remainder);
	*this = remainder;
	return *this;
}

BigInteger BigInteger::operator+(const BigInteger& n) const
{
	BigInteger result = *this;
	result += n;
	return result;
}

BigInteger BigInteger::operator-(const BigInteger& n) const
{
	BigInteger result = *this;
	result -= n;
	return result;
}

BigInteger BigInteger::operator*(const BigInteger& n) const
{
	BigInteger result = *this;
	result *= n;
	return result;
}

BigInteger BigInteger::operator/(const BigInteger& n) const
{
	BigInteger result = *this;
	result /= n;
	return result;
}

BigInteger BigInteger::operator%(const BigInteger& n) const
{
	BigInteger result = *this;
	result %= n;
	return result;
}

BigInteger& BigInteger::operator++()
{
	*this += 1;
	return *this;
}

BigInteger& BigInteger::operator--()
{
	*this -= 1;
	return *this;
}

BigInteger BigInteger::operator++(int)
{
	BigInteger previous = *this;
	++(*this);
	return previous;
}

BigInteger BigInteger::operator--(int)
{
	BigInteger previous = *this;
	--(*this);
	return previous;
}

const char *BigInteger::DivisionByZeroException::what() const noexcept
{
	return "Big integer division by zero exception.";
}

BigInteger BigInteger::divide(BigInteger dividend, BigInteger divisor, BigInteger& remainder)
{
	if (divisor == 0)
		throw DivisionByZeroException();

	const bool dividend_is_negative = dividend < 0;
	const bool divisor_is_negative = divisor < 0;
	const bool quotient_is_negative = (dividend_is_negative && !divisor_is_negative) || (!dividend_is_negative && divisor_is_negative);

	if (dividend_is_negative)
	{
		dividend = -dividend;
	}

	if (divisor_is_negative)
	{
		divisor = -divisor;
	}

	const size_t num_bits_per_block = sizeof(dividend.value[0]) * CHAR_BIT;
	const size_t num_blocks = dividend.value.size();
	assert(SIZE_MAX / num_bits_per_block >= num_blocks);
	const size_t num_bits = num_blocks * num_bits_per_block;

	remainder = 0;
	BigInteger quotient = 0;
	BigInteger one = 1;
	BigInteger mask;

	for (size_t i = num_bits; i > 0; --i)
	{
		const size_t index = i - 1;
		mask = (dividend >> index) & one;
		remainder <<= 1;
		remainder |= mask;
		if (remainder >= divisor)
		{
			quotient |= one << index;
			remainder -= divisor;
		}
	}

	if (quotient_is_negative)
	{
		quotient = -quotient;
	}

	if (dividend_is_negative)
	{
		remainder = -remainder;
	}

	return quotient;
}

BigInteger BigInteger::fromString(const char *str, int base)
{
	const char *p = str;
	while (::isspace(*p))
	{
		++p;
	}

	bool is_negative = false;
	if ('-' == *p)
	{
		++p;
		is_negative = true;
		while (::isspace(*p))
		{
			++p;
		}
	}
	else if ('+' == *p)
	{
		++p;
		while (::isspace(*p))
		{
			++p;
		}
	}

	constexpr int minimum_base = minimum_integer_base();
	constexpr int maximum_base = maximum_integer_base();

	if (base < minimum_base)
	{
		base = minimum_base;
	}
	else if (base > maximum_base)
	{
		base = maximum_base;
	}

	BigInteger number = 0;

	int digit_value = digit_to_integer(*p, base);
	while ((digit_value >= 0) && (digit_value < base))
	{
		number *= base;
		number += digit_value;
		++p;
		digit_value = digit_to_integer(*p, base);
	}

	if (is_negative)
	{
		number = -number;
	}

	return number;
}

BigInteger BigInteger::fromString(const std::string& str, int base)
{
	return fromString(str.c_str(), base);
}

std::string BigInteger::toString(BigInteger n, int base, bool upper_case)
{
	constexpr int min_base = minimum_integer_base();
	constexpr int max_base = maximum_integer_base();

	if (base < min_base)
	{
		base = min_base;
	}
	else if (base > max_base)
	{
		base = max_base;
	}

	const bool is_negative = (n < 0);
	if (is_negative)
	{
		n = -n;
	}

	const BigInteger zero = 0;
	std::string result;

	if (zero == n)
	{
		result = '0';
		return result;
	}

	uint64_t group_value = base;
	int count = 1;
	while (group_value < UINT32_MAX)
	{
		group_value *= base;
		++count;
	}

	const BigInteger group = group_value;
	BigInteger remainder;

	bool number_is_not_zero = (n != zero);
	while (number_is_not_zero)
	{
		n = divide(n, group, remainder);
		number_is_not_zero = (n != zero);
		uint64_t rem = ToIntegerType<uint64_t>(remainder);

		if (number_is_not_zero)
		{
			int counter = count;
			while (counter != 0)
			{
				int digit_value = static_cast<int>(rem % static_cast<uint64_t>(base));
				rem /= static_cast<uint64_t>(base);
				char c = digit_to_char(digit_value, base, upper_case);
				result += c;
				--counter;
			}
		}
		else
		{
			while (rem != 0)
			{
				int digit_value = static_cast<int>(rem % static_cast<uint64_t>(base));
				rem /= static_cast<uint64_t>(base);
				char c = digit_to_char(digit_value, base, upper_case);
				result += c;
			}
		}
	}

	if (is_negative)
	{
		result += '-';
	}

	std::reverse(result.begin(), result.end());
	return result;
}
