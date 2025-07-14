#include "BigInteger.hpp"
#include "BigIntegerHelper.hpp"
#include <cassert>
#include <cctype>
#include <climits>
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
	invert_bits(result.value);
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

bool BigInteger::operator!() const
{
	return (*this == 0);
}

bool BigInteger::operator==(const BigInteger& n) const
{
	assert(value.size() > 0U);
	assert(n.value.size() > 0U);

	const bool is_negative = sign_bit_is_set(value[value.size() - 1U]);
	const bool n_is_negative = sign_bit_is_set(n.value[n.value.size() - 1U]);
	if ((is_negative && !n_is_negative) || (!is_negative && n_is_negative))
	{
		return false;
	}

	const uint64_t sign_block = (is_negative) ? UINT64_MAX : 0U;
	const size_t minimum_number_of_blocks = (value.size() < n.value.size()) ?
			value.size() : n.value.size();
	const size_t maximum_number_of_blocks = (value.size() > n.value.size()) ?
			value.size() : n.value.size();
	const uint64_t *p_larger_block = (value.size() > n.value.size()) ?
			&value[0] : &(n.value[0]);

	for (size_t i = 0U; i < minimum_number_of_blocks; ++i)
	{
		if (value[i] != n.value[i])
		{
			return false;
		}
	}

	for (size_t i = minimum_number_of_blocks; i < maximum_number_of_blocks; ++i)
	{
		if (p_larger_block[i] != sign_block)
		{
			return false;
		}
	}

	return true;
}

bool BigInteger::operator!=(const BigInteger& n) const
{
	return !(*this == n);
}

bool BigInteger::operator>(const BigInteger& n) const
{
	assert(value.size() > 0U);
	assert(n.value.size() > 0U);

	if (*this == n)
	{
		return false;
	}

	const bool is_negative = sign_bit_is_set(value[value.size() - 1U]);
	const bool n_is_negative = sign_bit_is_set(n.value[n.value.size() - 1U]);

	if (!is_negative && n_is_negative)
	{
		return true;
	}
	else if (is_negative && !n_is_negative)
	{
		return false;
	}
	else
	{
		const BigInteger difference = *this - n;
		const bool difference_is_negative = sign_bit_is_set(difference.value[difference.value.size() - 1U]);
		return !difference_is_negative;
	}
}

bool BigInteger::operator>=(const BigInteger& n) const
{
	assert(value.size() > 0U);
	assert(n.value.size() > 0U);

	if (*this == n)
	{
		return true;
	}

	const bool is_negative = sign_bit_is_set(value[value.size() - 1U]);
	const bool n_is_negative = sign_bit_is_set(n.value[n.value.size() - 1U]);

	if (!is_negative && n_is_negative)
	{
		return true;
	}
	else if (is_negative && !n_is_negative)
	{
		return false;
	}
	else
	{
		const BigInteger difference = *this - n;
		const bool difference_is_negative = sign_bit_is_set(difference.value[difference.value.size() - 1U]);
		return !difference_is_negative;
	}
}

bool BigInteger::operator<(const BigInteger& n) const
{
	assert(value.size() > 0U);
	assert(n.value.size() > 0U);

	if (*this == n)
	{
		return false;
	}

	const bool is_negative = sign_bit_is_set(value[value.size() - 1U]);
	const bool n_is_negative = sign_bit_is_set(n.value[n.value.size() - 1U]);

	if (!is_negative && n_is_negative)
	{
		return false;
	}
	else if (is_negative && !n_is_negative)
	{
		return true;
	}
	else
	{
		const BigInteger difference = *this - n;
		const bool difference_is_negative = sign_bit_is_set(difference.value[difference.value.size() - 1U]);
		return difference_is_negative;
	}
}

bool BigInteger::operator<=(const BigInteger& n) const
{
	assert(value.size() > 0U);
	assert(n.value.size() > 0U);

	if (*this == n)
	{
		return true;
	}

	const bool is_negative = sign_bit_is_set(value[value.size() - 1U]);
	const bool n_is_negative = sign_bit_is_set(n.value[n.value.size() - 1U]);

	if (!is_negative && n_is_negative)
	{
		return false;
	}
	else if (is_negative && !n_is_negative)
	{
		return true;
	}
	else
	{
		const BigInteger difference = *this - n;
		const bool difference_is_negative = sign_bit_is_set(difference.value[difference.value.size() - 1U]);
		return difference_is_negative;
	}
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
	sign_extend(value, 1U);
	sign_extend(operand.value, 1U);

	uint64_t carry = 0U;

	for (size_t i = 0; i < value.size(); ++i)
	{
		const uint64_t minimum_operand = (value[i] < operand.value[i]) ? value[i] : operand.value[i];
		value[i] += operand.value[i];
		if (value[i] < minimum_operand)
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
	const BigInteger one = 1;
	BigInteger multiplicand(*this);
	BigInteger multiplier(n);
	size_t multiplicand_nblocks = multiplicand.value.size();
	sign_extend(multiplicand.value, multiplier.value.size());
	sign_extend(multiplier.value, multiplicand_nblocks);
	*this = 0;

	const bool multiplicand_is_negative = sign_bit_is_set(multiplicand.value[multiplicand.value.size() - 1]);
	const bool multiplier_is_negative = sign_bit_is_set(multiplier.value[multiplier.value.size() - 1]);
	const bool result_is_negative = (multiplicand_is_negative && !multiplier_is_negative) || (!multiplicand_is_negative && multiplier_is_negative);

	if (multiplicand_is_negative)
	{
		multiplicand = -multiplicand;
	}

	if (multiplier_is_negative)
	{
		multiplier = -multiplier;
	}

	while (multiplier != zero)
	{
		if ((multiplier & one) != zero)
		{
			*this += multiplicand;
		}
		multiplicand <<= 1U;
		multiplier >>= 1U;
	}

	if (result_is_negative)
	{
		*this = -(*this);
	}

	return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& n)
{
	*this = divide(*this, n, nullptr);
	return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& n)
{
	BigInteger remainder;
	(void) divide(*this, n, &remainder);
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

bool BigInteger::operator&&(const BigInteger& n) const
{
	const BigInteger zero = 0;
	return (*this != zero) && (n != zero);
}

bool BigInteger::operator||(const BigInteger& n) const
{
	const BigInteger zero = 0;
	return (*this != zero) || (n != zero);
}

const char *BigInteger::DivisionByZeroException::what() const noexcept
{
	return "Big integer division by zero exception.";
}

BigInteger BigInteger::divide(BigInteger dividend, BigInteger divisor, BigInteger *p_remainder)
{
	const BigInteger zero = 0;
	if (divisor == zero)
	{
		throw DivisionByZeroException();
	}

	const bool dividend_is_negative = dividend < zero;
	const bool divisor_is_negative = divisor < zero;
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

	BigInteger remainder = 0;
	BigInteger quotient = 0;
	const BigInteger one = 1;
	BigInteger mask = 0;

	for (size_t i = num_bits; i > 0U; --i)
	{
		const size_t num_bits_to_shift = i - 1U;
		mask = (dividend >> num_bits_to_shift) & one;
		remainder <<= 1U;
		remainder |= mask;
		if (remainder >= divisor)
		{
			quotient |= (one << num_bits_to_shift);
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

	if (p_remainder != nullptr)
	{
		*p_remainder = remainder;
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

	while (*p >= '0' && *p <= '9')
	{
		const int digit_value = digit_to_integer(*p, base);
		number *= base;
		number += digit_value;
		++p;
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
		n = divide(n, group, &remainder);
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
