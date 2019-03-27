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

#ifndef BIG_INTEGER_HPP
#define BIG_INTEGER_HPP

#include <cstdint>
#include <exception>
#include <string>
#include <vector>

class BigInteger
{
public:
	BigInteger();
	~BigInteger() = default;
	BigInteger(const BigInteger&) = default;
	BigInteger& operator=(const BigInteger&) = default;
	BigInteger(BigInteger&&) = default;
	BigInteger& operator=(BigInteger&&) = default;

	// Special copy constructors
	BigInteger(int n);
	BigInteger(long n);
	BigInteger(long long n);
	BigInteger(unsigned int n);
	BigInteger(unsigned long n);
	BigInteger(unsigned long long n);
	BigInteger(const char *n);

	// Special copy assignment operators
	BigInteger& operator=(int n);
	BigInteger& operator=(long n);
	BigInteger& operator=(long long n);
	BigInteger& operator=(unsigned int n);
	BigInteger& operator=(unsigned long n);
	BigInteger& operator=(unsigned long long n);
	BigInteger& operator=(const char *n);

	// Unary operators
	BigInteger operator~() const;
	BigInteger operator+() const;
	BigInteger operator-() const;

	// Comparison operators
	bool operator==(const BigInteger& n) const;
	bool operator!=(const BigInteger& n) const;
	bool operator>(const BigInteger& n) const;
	bool operator>=(const BigInteger& n) const;
	bool operator<(const BigInteger& n) const;
	bool operator<=(const BigInteger& n) const;

	// Bitwise assignment operators
	BigInteger& operator&=(const BigInteger& n);
	BigInteger& operator|=(const BigInteger& n);
	BigInteger& operator^=(const BigInteger& n);
	BigInteger& operator<<=(size_t n);
	BigInteger& operator>>=(size_t n);

	// Bitwise operators
	BigInteger operator&(const BigInteger& n) const;
	BigInteger operator|(const BigInteger& n) const;
	BigInteger operator^(const BigInteger& n) const;
	BigInteger operator<<(size_t n) const;
	BigInteger operator>>(size_t n) const;

	// Arithmetic assignment operators
	BigInteger& operator+=(const BigInteger& n);
	BigInteger& operator-=(const BigInteger& n);
	BigInteger& operator*=(const BigInteger& n);
	BigInteger& operator/=(const BigInteger& n);
	BigInteger& operator%=(const BigInteger& n);

	// Arithmetic operators
	BigInteger operator+(const BigInteger& n) const;
	BigInteger operator-(const BigInteger& n) const;
	BigInteger operator*(const BigInteger& n) const;
	BigInteger operator/(const BigInteger& n) const;
	BigInteger operator%(const BigInteger& n) const;

	// Pre-increment and pre-decrement operators
	BigInteger& operator++();
	BigInteger& operator--();

	// Post-increment and post-decrement operators
	BigInteger operator++(int);
	BigInteger operator--(int);

public:
	class DivisionByZeroException : public std::exception
	{
		virtual const char *what() const override;
	};

	// divide operation that returns the result as well as the remainder
	// throws DivisionByZeroException if the divisor is zero
	static BigInteger divide(BigInteger dividend, BigInteger divisor, BigInteger& remainder);

	// Converts a string to a big integer
	static BigInteger fromString(const char *str, int base = 10);
	static BigInteger fromString(const std::string& str, int base = 10);

	// Converts a big integer to a string
	static std::string toString(BigInteger n, int base = 10, bool upper_case = true);

	// Converts a big integer to a native integer
	template <typename T>
	static T ToIntegerType(const BigInteger& bigInt)
	{
		static_assert(std::is_integral<T>::value, "The type must be an integral type, e.g. int, unsigned int, etc.");
		return static_cast<T>(bigInt.value[0]);
	}

private:
	std::vector<uint64_t> value;
};

#endif
