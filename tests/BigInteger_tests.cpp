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

#include "catch.hpp"

TEST_CASE("Default value is zero")
{
	BigInteger number;
	REQUIRE(number == 0);
	REQUIRE("0" == BigInteger::toString(number));
}

TEST_CASE("Initialize to zero")
{
	BigInteger number = 0;
	REQUIRE(number == 0);
	REQUIRE("0" == BigInteger::toString(number));
}

TEST_CASE("Initialize to -1")
{
	BigInteger number = -1;
	REQUIRE(number == -1);
	REQUIRE("-1" == BigInteger::toString(number));
}

TEST_CASE("Initialize to 1")
{
	BigInteger number = 1;
	REQUIRE(number == 1);
	REQUIRE("1" == BigInteger::toString(number));
}

TEST_CASE("Initialize to -10")
{
	BigInteger number = -10;
	REQUIRE(number == -10);
	REQUIRE("-10" == BigInteger::toString(number, 10, true));
	REQUIRE("-10" == BigInteger::toString(number, 10, false));
	REQUIRE("-A" == BigInteger::toString(number, 16, true));
	REQUIRE("-a" == BigInteger::toString(number, 16, false));
	REQUIRE("-1010" == BigInteger::toString(number, 2, true));
	REQUIRE("-1010" == BigInteger::toString(number, 2, false));
}

TEST_CASE("Initialize to 10")
{
	BigInteger number = 10;
	REQUIRE(number == 10);
	REQUIRE("10" == BigInteger::toString(number, 10, true));
	REQUIRE("10" == BigInteger::toString(number, 10, false));
	REQUIRE("A" == BigInteger::toString(number, 16, true));
	REQUIRE("a" == BigInteger::toString(number, 16, false));
	REQUIRE("1010" == BigInteger::toString(number, 2, true));
	REQUIRE("1010" == BigInteger::toString(number, 2, false));
}

TEST_CASE("Initialize to 101")
{
	BigInteger number = 101;
	REQUIRE(number == 101);
	REQUIRE("101" == BigInteger::toString(number));
}

TEST_CASE("Initialize to -101")
{
	BigInteger number = -101;
	REQUIRE(number == -101);
	REQUIRE("-101" == BigInteger::toString(number));
}

TEST_CASE("Initialize to -1010")
{
	BigInteger number = -1010;
	REQUIRE(number == -1010);
	REQUIRE("-1010" == BigInteger::toString(number));
}

TEST_CASE("Initialize to 1010")
{
	BigInteger number = 1010;
	REQUIRE(number == 1010);
	REQUIRE("1010" == BigInteger::toString(number));
}

TEST_CASE("Initialize to -10101")
{
	BigInteger number = -10101;
	REQUIRE(number == -10101);
	REQUIRE("-10101" == BigInteger::toString(number));
}

TEST_CASE("Initialize to 10101")
{
	BigInteger number = 10101;
	REQUIRE(number == 10101);
	REQUIRE("10101" == BigInteger::toString(number));
}

TEST_CASE("Initialize to -123456789")
{
	BigInteger number = "-123456789";
	REQUIRE(number == -123456789);
	REQUIRE(number == -123456789L);
	REQUIRE("-123456789" == BigInteger::toString(number));
}

TEST_CASE("Initialize to 123456789")
{
	BigInteger number = 123456789;
	REQUIRE(number == 123456789);
	REQUIRE(number == 123456789L);
	REQUIRE("123456789" == BigInteger::toString(number));
}

TEST_CASE("Initialize to -987654321")
{
	BigInteger number = "-987654321";
	REQUIRE(number == -987654321);
	REQUIRE(number == -987654321L);
	REQUIRE("-987654321" == BigInteger::toString(number));
}

TEST_CASE("Initialize to 987654321")
{
	BigInteger number = 987654321;
	REQUIRE(number == 987654321);
	REQUIRE(number == 987654321L);
	REQUIRE("987654321" == BigInteger::toString(number));
}

TEST_CASE("Post-increment")
{
	BigInteger number = "18446744073709551615";
	BigInteger number2 = number++;
	REQUIRE("18446744073709551616" == BigInteger::toString(number));
	REQUIRE("18446744073709551615" == BigInteger::toString(number2));
}

TEST_CASE("Pre-increment")
{
	BigInteger number = "18446744073709551615";
	BigInteger number2 = ++number;
	REQUIRE("18446744073709551616" == BigInteger::toString(number));
	REQUIRE("18446744073709551616" == BigInteger::toString(number2));
}

TEST_CASE("Initialize to -99999999999999999999")
{
	BigInteger number = "-99999999999999999999";
	REQUIRE("-99999999999999999999" == BigInteger::toString(number));
}

TEST_CASE("Initialize to 99999999999999999999")
{
	BigInteger number = "99999999999999999999";
	REQUIRE("99999999999999999999" == BigInteger::toString(number));
}

TEST_CASE("Perform -99999999999999999999 - 1")
{
	BigInteger number = "-99999999999999999999";
	number -= 1;
	REQUIRE("-100000000000000000000" == BigInteger::toString(number));
}

TEST_CASE("Perform -99999999999999999999 - 2")
{
	BigInteger number = "-99999999999999999999";
	number -= 2;
	REQUIRE("-100000000000000000001" == BigInteger::toString(number));
}

TEST_CASE("Perform 99999999999999999999 + 1")
{
	BigInteger number = "99999999999999999999";
	number += 1;
	REQUIRE("100000000000000000000" == BigInteger::toString(number));
}

TEST_CASE("Perform 99999999999999999999 + 2")
{
	BigInteger number = "99999999999999999999";
	number += 2;
	REQUIRE("100000000000000000001" == BigInteger::toString(number));
}

TEST_CASE("Perform -9223372036854775808 - 1")
{
	BigInteger number = "-9223372036854775808";
	number--;
	REQUIRE("-9223372036854775809" == BigInteger::toString(number));
}

TEST_CASE("Perform 9223372036854775808 + 1")
{
	BigInteger number = "9223372036854775807";
	number++;
	REQUIRE("9223372036854775808" == BigInteger::toString(number));
}

TEST_CASE("Positive number + positive number")
{
	BigInteger n1 = "999999999999999999999999999999";
	BigInteger n2 = 1;
	BigInteger result = n1 + n2;
	REQUIRE("1000000000000000000000000000000" == BigInteger::toString(result));
}

TEST_CASE("Negative number + negative number")
{
	BigInteger n1 = "-999999999999999999999999999999";
	BigInteger n2 = -1;
	BigInteger result = n1 + n2;
	REQUIRE("-1000000000000000000000000000000" == BigInteger::toString(result));
}

TEST_CASE("Negative number + positive number")
{
	BigInteger n1 = "-999999999999999999999999999999";
	BigInteger n2 = 1;
	BigInteger result = n1 + n2;
	REQUIRE("-999999999999999999999999999998" == BigInteger::toString(result));
}

TEST_CASE("Positive number + negative number")
{
	BigInteger n1 = "999999999999999999999999999999";
	BigInteger n2 = -1;
	BigInteger result = n1 + n2;
	REQUIRE("999999999999999999999999999998" == BigInteger::toString(result));
}

TEST_CASE("Positive number - positive number")
{
	BigInteger n1 = "999999999999999999999999999999";
	BigInteger n2 = 1;
	BigInteger result = n1 - n2;
	REQUIRE("999999999999999999999999999998" == BigInteger::toString(result));
}

TEST_CASE("Negative number - negative number")
{
	BigInteger n1 = "-999999999999999999999999999999";
	BigInteger n2 = -1;
	BigInteger result = n1 - n2;
	REQUIRE("-999999999999999999999999999998" == BigInteger::toString(result));
}

TEST_CASE("Negative number - positive number")
{
	BigInteger n1 = "-999999999999999999999999999999";
	BigInteger n2 = 1;
	BigInteger result = n1 - n2;
	REQUIRE("-1000000000000000000000000000000" == BigInteger::toString(result));
}

TEST_CASE("Positive number - negative number")
{
	BigInteger n1 = "999999999999999999999999999999";
	BigInteger n2 = -1;
	BigInteger result = n1 - n2;
	REQUIRE("1000000000000000000000000000000" == BigInteger::toString(result));
}

TEST_CASE("Multiplication (1)")
{
	BigInteger n1 = 100;
	BigInteger n2 = 100;
	BigInteger result = n1 * n2;
	REQUIRE(result == 10000);
	REQUIRE("10000" == BigInteger::toString(result));
}

TEST_CASE("Multiplication (2)")
{
	BigInteger n1 = 100;
	BigInteger n2 = "99999999999999999999999";
	BigInteger result = n1 * n2;
	REQUIRE("9999999999999999999999900" == BigInteger::toString(result));
}

TEST_CASE("Multiplication (3)")
{
	BigInteger n1 = "99999999999999999999999";
	BigInteger n2 = 100;
	BigInteger result = n1 * n2;
	REQUIRE("9999999999999999999999900" == BigInteger::toString(result));
}

TEST_CASE("Multiplication (4)")
{
	BigInteger n1 = "99999999999999999999";
	BigInteger n2 = -100;
	BigInteger result = n1 * n2;
	REQUIRE("-9999999999999999999900" == BigInteger::toString(result));
}

TEST_CASE("Multiplication (5)")
{
	BigInteger n1 = "-99999999999999999999";
	BigInteger n2 = 100;
	BigInteger result = n1 * n2;
	REQUIRE("-9999999999999999999900" == BigInteger::toString(result));
}

TEST_CASE("Multiplication (6)")
{
	BigInteger n1 = -100;
	BigInteger n2 = "99999999999999999999";
	BigInteger result = n1 * n2;
	REQUIRE("-9999999999999999999900" == BigInteger::toString(result));
}

TEST_CASE("Multiplication (7)")
{
	BigInteger n1 = 100;
	BigInteger n2 = "-99999999999999999999";
	BigInteger result = n1 * n2;
	REQUIRE("-9999999999999999999900" == BigInteger::toString(result));
}

TEST_CASE("Multiplication (8)")
{
	BigInteger n1 = -1;
	BigInteger n2 = -1;
	BigInteger result = n1 * n2;
	REQUIRE(result == 1);
	REQUIRE("1" == BigInteger::toString(result));
}

TEST_CASE("Multiplication (9)")
{
	BigInteger n1 = 0;
	BigInteger n2 = 0;
	BigInteger result = n1 * n2;
	REQUIRE(result == 0);
	REQUIRE("0" == BigInteger::toString(result));
}

TEST_CASE("Multiplication (10)")
{
	BigInteger n1 = 1;
	BigInteger n2 = 0;
	BigInteger result = n1 * n2;
	REQUIRE(result == 0);
	REQUIRE("0" == BigInteger::toString(result));
}

TEST_CASE("Multiplication (11)")
{
	BigInteger n1 = 0;
	BigInteger n2 = 1;
	BigInteger result = n1 * n2;
	REQUIRE(result == 0);
	REQUIRE("0" == BigInteger::toString(result));
}

TEST_CASE("Division (1)")
{
	BigInteger number = BigInteger(100) / BigInteger(100);
	REQUIRE(number == 1);
	REQUIRE("1" == BigInteger::toString(number));
}

TEST_CASE("Division (2)")
{
	BigInteger number = BigInteger(-101) / BigInteger(100);
	REQUIRE(number == -1);
	REQUIRE("-1" == BigInteger::toString(number));
}

TEST_CASE("Remainder (1)")
{
	BigInteger number = BigInteger(100) % BigInteger(100);
	REQUIRE(number == 0);
	REQUIRE("0" == BigInteger::toString(number));
}

TEST_CASE("Remainder (2)")
{
	BigInteger number = BigInteger(101) % BigInteger(100);
	REQUIRE(number == 1);
	REQUIRE("1" == BigInteger::toString(number));
}

TEST_CASE("Remainder (3)")
{
	BigInteger number = BigInteger(-101) % BigInteger(100);
	REQUIRE(number == -1);
	REQUIRE("-1" == BigInteger::toString(number));
}

TEST_CASE("Add two big numbers (1)")
{
	BigInteger n1 = "123456789123456789123456789123456789";
	BigInteger n2 = "987654321987654321987654321987654321";
	BigInteger result = n1 + n2;
	std::string result_text = BigInteger::toString(result);
	REQUIRE("1111111111111111111111111111111111110" == result_text);
}

TEST_CASE("Add two big numbers (2)")
{
	BigInteger n1 = "123456789123456789123456789123456789123456789123456789123456789123456789";
	BigInteger n2 = "987654321987654321987654321987654321987654321987654321987654321987654321";
	BigInteger result = n1 + n2;
	std::string result_text = BigInteger::toString(result);
	REQUIRE("1111111111111111111111111111111111111111111111111111111111111111111111110" == result_text);
}

TEST_CASE("Multiply two big numbers (1)")
{
	BigInteger n1 = "123456789123456789123456789123456789123456789123456789123456789123456789";
	BigInteger n2 = "987654321987654321987654321987654321987654321987654321987654321987654321";
	BigInteger result = n1 * n2;
	std::string result_text = BigInteger::toString(result);
	REQUIRE("121932631356500531591068431825636332060204232294772132529340032763907932754610570520042670285474770050906869816338969581771069347203169112635269" == result_text);
}

TEST_CASE("Subtract a big integer from a big integer (1)")
{
	BigInteger n1 = "123456789123456789123456789123456789123456789123456789123456789123456789";
	BigInteger n2 = "987654321987654321987654321987654321987654321987654321987654321987654321";
	BigInteger result = n1 - n2;
	std::string result_text = BigInteger::toString(result);
	REQUIRE("-864197532864197532864197532864197532864197532864197532864197532864197532" == result_text);
}

TEST_CASE("Subtract a big integer from a big integer (2)")
{
	BigInteger n1 = "123456789123456789123456789123456789123456789123456789123456789123456789";
	BigInteger n2 = "987654321987654321987654321987654321987654321987654321987654321987654321";
	BigInteger result = n2 - n1;
	std::string result_text = BigInteger::toString(result);
	REQUIRE("864197532864197532864197532864197532864197532864197532864197532864197532" == result_text);
}

TEST_CASE("Unary plus (1)")
{
	BigInteger n = 0;
	n = +n;
	REQUIRE(n == 0);
	REQUIRE("0" == BigInteger::toString(n));
}

TEST_CASE("Unary plus (2)")
{
	BigInteger n = -1;
	n = +n;
	REQUIRE(n == -1);
	REQUIRE("-1" == BigInteger::toString(n));
}

TEST_CASE("Unary plus (3)")
{
	BigInteger n = 1;
	n = +n;
	REQUIRE(n == 1);
	REQUIRE("1" == BigInteger::toString(n));
}

TEST_CASE("Unary plus (4)")
{
	BigInteger n = "-999999999999999999999999999999999999999";
	n = +n;
	REQUIRE("-999999999999999999999999999999999999999" == BigInteger::toString(n));
}

TEST_CASE("Unary plus (5)")
{
	BigInteger n = "999999999999999999999999999999999999999";
	n = +n;
	REQUIRE("999999999999999999999999999999999999999" == BigInteger::toString(n));
}

TEST_CASE("Unary minus (1)")
{
	BigInteger n = 0;
	n = -n;
	REQUIRE(n == 0);
	REQUIRE("0" == BigInteger::toString(n));
}

TEST_CASE("Unary minus (2)")
{
	BigInteger n = -1;
	n = -n;
	REQUIRE(n == 1);
	REQUIRE("1" == BigInteger::toString(n));
}

TEST_CASE("Unary minus (3)")
{
	BigInteger n = 1;
	n = -n;
	REQUIRE(n == -1);
	REQUIRE("-1" == BigInteger::toString(n));
}

TEST_CASE("Unary minus (4)")
{
	BigInteger n = "-999999999999999999999999999999999999999";
	n = -n;
	REQUIRE("999999999999999999999999999999999999999" == BigInteger::toString(n));
}

TEST_CASE("Unary minus (5)")
{
	BigInteger n = "999999999999999999999999999999999999999";
	n = -n;
	REQUIRE("-999999999999999999999999999999999999999" == BigInteger::toString(n));
}

TEST_CASE("Division by zero (1)")
{
	BigInteger n = 1;
	try
	{
		n /= 0;
	}
	catch (BigInteger::DivisionByZeroException&)
	{
		REQUIRE(n == 1);
	}
}

TEST_CASE("Division by zero (2)")
{
	BigInteger n = 1;
	try
	{
		BigInteger result = n / 0;
	}
	catch (BigInteger::DivisionByZeroException&)
	{
		REQUIRE(n == 1);
	}
}
