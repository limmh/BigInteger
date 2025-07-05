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

	class DivisionByZeroException : public std::exception
	{
	public:
		virtual const char *what() const noexcept override;
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
