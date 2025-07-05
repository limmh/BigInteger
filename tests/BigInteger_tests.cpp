#include "BigInteger.hpp"
#include "unit_testing.h"

#define TEST_CASE(ID, DESCRIPTION) TEST(ID, DESCRIPTION)
#define REQUIRE(CONDITION) ASSERT(CONDITION)

TEST_CASE(test_1, "Default value is zero")
{
	BigInteger number;
	REQUIRE(number == 0);
	REQUIRE("0" == BigInteger::toString(number));
}

TEST_CASE(test_2, "Initialize to zero")
{
	BigInteger number = 0;
	REQUIRE(number == 0);
	REQUIRE("0" == BigInteger::toString(number));
}

TEST_CASE(test_3, "Initialize to -1")
{
	BigInteger number = -1;
	REQUIRE(number == -1);
	REQUIRE("-1" == BigInteger::toString(number));
}

TEST_CASE(test_4, "Initialize to 1")
{
	BigInteger number = 1;
	REQUIRE(number == 1);
	REQUIRE("1" == BigInteger::toString(number));
}

TEST_CASE(test_5, "Initialize to -10")
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

TEST_CASE(test_6, "Initialize to 10")
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

TEST_CASE(test_7, "Initialize to 101")
{
	BigInteger number = 101;
	REQUIRE(number == 101);
	REQUIRE("101" == BigInteger::toString(number));
}

TEST_CASE(test_8, "Initialize to -101")
{
	BigInteger number = -101;
	REQUIRE(number == -101);
	REQUIRE("-101" == BigInteger::toString(number));
}

TEST_CASE(test_9, "Initialize to -1010")
{
	BigInteger number = -1010;
	REQUIRE(number == -1010);
	REQUIRE("-1010" == BigInteger::toString(number));
}

TEST_CASE(test_10, "Initialize to 1010")
{
	BigInteger number = 1010;
	REQUIRE(number == 1010);
	REQUIRE("1010" == BigInteger::toString(number));
}

TEST_CASE(test_11, "Initialize to -10101")
{
	BigInteger number = -10101;
	REQUIRE(number == -10101);
	REQUIRE("-10101" == BigInteger::toString(number));
}

TEST_CASE(test_12, "Initialize to 10101")
{
	BigInteger number = 10101;
	REQUIRE(number == 10101);
	REQUIRE("10101" == BigInteger::toString(number));
}

TEST_CASE(test_13, "Initialize to -123456789")
{
	BigInteger number = "-123456789";
	REQUIRE(number == -123456789);
	REQUIRE(number == -123456789L);
	REQUIRE("-123456789" == BigInteger::toString(number));
}

TEST_CASE(test_14, "Initialize to 123456789")
{
	BigInteger number = 123456789;
	REQUIRE(number == 123456789);
	REQUIRE(number == 123456789L);
	REQUIRE("123456789" == BigInteger::toString(number));
}

TEST_CASE(test_15, "Initialize to -987654321")
{
	BigInteger number = "-987654321";
	REQUIRE(number == -987654321);
	REQUIRE(number == -987654321L);
	REQUIRE("-987654321" == BigInteger::toString(number));
}

TEST_CASE(test_16, "Initialize to 987654321")
{
	BigInteger number = 987654321;
	REQUIRE(number == 987654321);
	REQUIRE(number == 987654321L);
	REQUIRE("987654321" == BigInteger::toString(number));
}

TEST_CASE(test_17, "Post-increment")
{
	BigInteger number = "18446744073709551615";
	BigInteger number2 = number++;
	REQUIRE("18446744073709551616" == BigInteger::toString(number));
	REQUIRE("18446744073709551615" == BigInteger::toString(number2));
}

TEST_CASE(test_18, "Pre-increment")
{
	BigInteger number = "18446744073709551615";
	BigInteger number2 = ++number;
	REQUIRE("18446744073709551616" == BigInteger::toString(number));
	REQUIRE("18446744073709551616" == BigInteger::toString(number2));
}

TEST_CASE(test_19, "Initialize to -99999999999999999999")
{
	BigInteger number = "-99999999999999999999";
	REQUIRE("-99999999999999999999" == BigInteger::toString(number));
}

TEST_CASE(test_20, "Initialize to 99999999999999999999")
{
	BigInteger number = "99999999999999999999";
	REQUIRE("99999999999999999999" == BigInteger::toString(number));
}

TEST_CASE(test_21, "Perform -99999999999999999999 - 1")
{
	BigInteger number = "-99999999999999999999";
	number -= 1;
	REQUIRE("-100000000000000000000" == BigInteger::toString(number));
}

TEST_CASE(test_22, "Perform -99999999999999999999 - 2")
{
	BigInteger number = "-99999999999999999999";
	number -= 2;
	REQUIRE("-100000000000000000001" == BigInteger::toString(number));
}

TEST_CASE(test_23, "Perform 99999999999999999999 + 1")
{
	BigInteger number = "99999999999999999999";
	number += 1;
	REQUIRE("100000000000000000000" == BigInteger::toString(number));
}

TEST_CASE(test_24, "Perform 99999999999999999999 + 2")
{
	BigInteger number = "99999999999999999999";
	number += 2;
	REQUIRE("100000000000000000001" == BigInteger::toString(number));
}

TEST_CASE(test_25, "Perform -9223372036854775808 - 1")
{
	BigInteger number = "-9223372036854775808";
	number--;
	REQUIRE("-9223372036854775809" == BigInteger::toString(number));
}

TEST_CASE(test_26, "Perform 9223372036854775808 + 1")
{
	BigInteger number = "9223372036854775807";
	number++;
	REQUIRE("9223372036854775808" == BigInteger::toString(number));
}

TEST_CASE(test_27, "Positive number + positive number")
{
	BigInteger n1 = "999999999999999999999999999999";
	BigInteger n2 = 1;
	BigInteger result = n1 + n2;
	REQUIRE("1000000000000000000000000000000" == BigInteger::toString(result));
}

TEST_CASE(test_28, "Negative number + negative number")
{
	BigInteger n1 = "-999999999999999999999999999999";
	BigInteger n2 = -1;
	BigInteger result = n1 + n2;
	REQUIRE("-1000000000000000000000000000000" == BigInteger::toString(result));
}

TEST_CASE(test_29, "Negative number + positive number")
{
	BigInteger n1 = "-999999999999999999999999999999";
	BigInteger n2 = 1;
	BigInteger result = n1 + n2;
	REQUIRE("-999999999999999999999999999998" == BigInteger::toString(result));
}

TEST_CASE(test_30, "Positive number + negative number")
{
	BigInteger n1 = "999999999999999999999999999999";
	BigInteger n2 = -1;
	BigInteger result = n1 + n2;
	REQUIRE("999999999999999999999999999998" == BigInteger::toString(result));
}

TEST_CASE(test_31, "Positive number - positive number")
{
	BigInteger n1 = "999999999999999999999999999999";
	BigInteger n2 = 1;
	BigInteger result = n1 - n2;
	REQUIRE("999999999999999999999999999998" == BigInteger::toString(result));
}

TEST_CASE(test_32, "Negative number - negative number")
{
	BigInteger n1 = "-999999999999999999999999999999";
	BigInteger n2 = -1;
	BigInteger result = n1 - n2;
	REQUIRE("-999999999999999999999999999998" == BigInteger::toString(result));
}

TEST_CASE(test_33, "Negative number - positive number")
{
	BigInteger n1 = "-999999999999999999999999999999";
	BigInteger n2 = 1;
	BigInteger result = n1 - n2;
	REQUIRE("-1000000000000000000000000000000" == BigInteger::toString(result));
}

TEST_CASE(test_34, "Positive number - negative number")
{
	BigInteger n1 = "999999999999999999999999999999";
	BigInteger n2 = -1;
	BigInteger result = n1 - n2;
	REQUIRE("1000000000000000000000000000000" == BigInteger::toString(result));
}

TEST_CASE(test_35, "Multiplication (1)")
{
	BigInteger n1 = 100;
	BigInteger n2 = 100;
	BigInteger result = n1 * n2;
	REQUIRE(result == 10000);
	REQUIRE("10000" == BigInteger::toString(result));
}

TEST_CASE(test_36, "Multiplication (2)")
{
	BigInteger n1 = 100;
	BigInteger n2 = "99999999999999999999999";
	BigInteger result = n1 * n2;
	REQUIRE("9999999999999999999999900" == BigInteger::toString(result));
}

TEST_CASE(test_37, "Multiplication (3)")
{
	BigInteger n1 = "99999999999999999999999";
	BigInteger n2 = 100;
	BigInteger result = n1 * n2;
	REQUIRE("9999999999999999999999900" == BigInteger::toString(result));
}

TEST_CASE(test_38, "Multiplication (4)")
{
	BigInteger n1 = "99999999999999999999";
	BigInteger n2 = -100;
	BigInteger result = n1 * n2;
	REQUIRE("-9999999999999999999900" == BigInteger::toString(result));
}

TEST_CASE(test_39, "Multiplication (5)")
{
	BigInteger n1 = "-99999999999999999999";
	BigInteger n2 = 100;
	BigInteger result = n1 * n2;
	REQUIRE("-9999999999999999999900" == BigInteger::toString(result));
}

TEST_CASE(test_40, "Multiplication (6)")
{
	BigInteger n1 = -100;
	BigInteger n2 = "99999999999999999999";
	BigInteger result = n1 * n2;
	REQUIRE("-9999999999999999999900" == BigInteger::toString(result));
}

TEST_CASE(test_41, "Multiplication (7)")
{
	BigInteger n1 = 100;
	BigInteger n2 = "-99999999999999999999";
	BigInteger result = n1 * n2;
	REQUIRE("-9999999999999999999900" == BigInteger::toString(result));
}

TEST_CASE(test_42, "Multiplication (8)")
{
	BigInteger n1 = -1;
	BigInteger n2 = -1;
	BigInteger result = n1 * n2;
	REQUIRE(result == 1);
	REQUIRE("1" == BigInteger::toString(result));
}

TEST_CASE(test_43, "Multiplication (9)")
{
	BigInteger n1 = 0;
	BigInteger n2 = 0;
	BigInteger result = n1 * n2;
	REQUIRE(result == 0);
	REQUIRE("0" == BigInteger::toString(result));
}

TEST_CASE(test_44, "Multiplication (10)")
{
	BigInteger n1 = 1;
	BigInteger n2 = 0;
	BigInteger result = n1 * n2;
	REQUIRE(result == 0);
	REQUIRE("0" == BigInteger::toString(result));
}

TEST_CASE(test_45, "Multiplication (11)")
{
	BigInteger n1 = 0;
	BigInteger n2 = 1;
	BigInteger result = n1 * n2;
	REQUIRE(result == 0);
	REQUIRE("0" == BigInteger::toString(result));
}

TEST_CASE(test_46, "Division (1)")
{
	BigInteger number = BigInteger(100) / BigInteger(100);
	REQUIRE(number == 1);
	REQUIRE("1" == BigInteger::toString(number));
}

TEST_CASE(test_47, "Division (2)")
{
	BigInteger number = BigInteger(-101) / BigInteger(100);
	REQUIRE(number == -1);
	REQUIRE("-1" == BigInteger::toString(number));
}

TEST_CASE(test_48, "Remainder (1)")
{
	BigInteger number = BigInteger(100) % BigInteger(100);
	REQUIRE(number == 0);
	REQUIRE("0" == BigInteger::toString(number));
}

TEST_CASE(test_49, "Remainder (2)")
{
	BigInteger number = BigInteger(101) % BigInteger(100);
	REQUIRE(number == 1);
	REQUIRE("1" == BigInteger::toString(number));
}

TEST_CASE(test_50, "Remainder (3)")
{
	BigInteger number = BigInteger(-101) % BigInteger(100);
	REQUIRE(number == -1);
	REQUIRE("-1" == BigInteger::toString(number));
}

TEST_CASE(test_51, "Add two big numbers (1)")
{
	BigInteger n1 = "123456789123456789123456789123456789";
	BigInteger n2 = "987654321987654321987654321987654321";
	BigInteger result = n1 + n2;
	std::string result_text = BigInteger::toString(result);
	REQUIRE("1111111111111111111111111111111111110" == result_text);
}

TEST_CASE(test_52, "Add two big numbers (2)")
{
	BigInteger n1 = "123456789123456789123456789123456789123456789123456789123456789123456789";
	BigInteger n2 = "987654321987654321987654321987654321987654321987654321987654321987654321";
	BigInteger result = n1 + n2;
	std::string result_text = BigInteger::toString(result);
	REQUIRE("1111111111111111111111111111111111111111111111111111111111111111111111110" == result_text);
}

TEST_CASE(test_53, "Multiply two big numbers (1)")
{
	BigInteger n1 = "123456789123456789123456789123456789123456789123456789123456789123456789";
	BigInteger n2 = "987654321987654321987654321987654321987654321987654321987654321987654321";
	BigInteger result = n1 * n2;
	std::string result_text = BigInteger::toString(result);
	REQUIRE("121932631356500531591068431825636332060204232294772132529340032763907932754610570520042670285474770050906869816338969581771069347203169112635269" == result_text);
}

TEST_CASE(test_54, "Subtract a big integer from a big integer (1)")
{
	BigInteger n1 = "123456789123456789123456789123456789123456789123456789123456789123456789";
	BigInteger n2 = "987654321987654321987654321987654321987654321987654321987654321987654321";
	BigInteger result = n1 - n2;
	std::string result_text = BigInteger::toString(result);
	REQUIRE("-864197532864197532864197532864197532864197532864197532864197532864197532" == result_text);
}

TEST_CASE(test_55, "Subtract a big integer from a big integer (2)")
{
	BigInteger n1 = "123456789123456789123456789123456789123456789123456789123456789123456789";
	BigInteger n2 = "987654321987654321987654321987654321987654321987654321987654321987654321";
	BigInteger result = n2 - n1;
	std::string result_text = BigInteger::toString(result);
	REQUIRE("864197532864197532864197532864197532864197532864197532864197532864197532" == result_text);
}

TEST_CASE(test_56, "Unary plus (1)")
{
	BigInteger n = 0;
	n = +n;
	REQUIRE(n == 0);
	REQUIRE("0" == BigInteger::toString(n));
}

TEST_CASE(test_57, "Unary plus (2)")
{
	BigInteger n = -1;
	n = +n;
	REQUIRE(n == -1);
	REQUIRE("-1" == BigInteger::toString(n));
}

TEST_CASE(test_58, "Unary plus (3)")
{
	BigInteger n = 1;
	n = +n;
	REQUIRE(n == 1);
	REQUIRE("1" == BigInteger::toString(n));
}

TEST_CASE(test_59, "Unary plus (4)")
{
	BigInteger n = "-999999999999999999999999999999999999999";
	n = +n;
	REQUIRE("-999999999999999999999999999999999999999" == BigInteger::toString(n));
}

TEST_CASE(test_60, "Unary plus (5)")
{
	BigInteger n = "999999999999999999999999999999999999999";
	n = +n;
	REQUIRE("999999999999999999999999999999999999999" == BigInteger::toString(n));
}

TEST_CASE(test_61, "Unary minus (1)")
{
	BigInteger n = 0;
	n = -n;
	REQUIRE(n == 0);
	REQUIRE("0" == BigInteger::toString(n));
}

TEST_CASE(test_62, "Unary minus (2)")
{
	BigInteger n = -1;
	n = -n;
	REQUIRE(n == 1);
	REQUIRE("1" == BigInteger::toString(n));
}

TEST_CASE(test_63, "Unary minus (3)")
{
	BigInteger n = 1;
	n = -n;
	REQUIRE(n == -1);
	REQUIRE("-1" == BigInteger::toString(n));
}

TEST_CASE(test_64, "Unary minus (4)")
{
	BigInteger n = "-999999999999999999999999999999999999999";
	n = -n;
	REQUIRE("999999999999999999999999999999999999999" == BigInteger::toString(n));
}

TEST_CASE(test_65, "Unary minus (5)")
{
	BigInteger n = "999999999999999999999999999999999999999";
	n = -n;
	REQUIRE("-999999999999999999999999999999999999999" == BigInteger::toString(n));
}

TEST_CASE(test_66, "Division by zero (1)")
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

TEST_CASE(test_67, "Division by zero (2)")
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

TEST_CASE(test_68, "Equality comparison (1)")
{
	BigInteger n1 = 0;
	BigInteger n2 = 0;
	REQUIRE(n1 == n2);
}

TEST_CASE(test_69, "Equality commparison (2)")
{
	BigInteger n1 = -1;
	BigInteger n2 = -1;
	REQUIRE(n1 == n2);
}

TEST_CASE(test_70, "Equality commparison (3)")
{
	BigInteger n1 = 1;
	BigInteger n2 = 1;
	REQUIRE(n1 == n2);
}

TEST_CASE(test_71, "Equality commparison (4)")
{
	BigInteger n1 = "-999999999999999999999999999999";
	BigInteger n2 = "-999999999999999999999999999999";
	REQUIRE(n1 == n2);
}

TEST_CASE(test_72, "Equality commparison (5)")
{
	BigInteger n1 = "999999999999999999999999999999";
	BigInteger n2 = "999999999999999999999999999999";
	REQUIRE(n1 == n2);
}

TEST_CASE(test_73, "Non-equality comparison (1)")
{
	BigInteger n1 = 0;
	BigInteger n2 = 1;
	REQUIRE(n1 != n2);
}

TEST_CASE(test_74, "Non-equality commparison (2)")
{
	BigInteger n1 = -1;
	BigInteger n2 = 0;
	REQUIRE(n1 != n2);
}

TEST_CASE(test_75, "Non-equality commparison (3)")
{
	BigInteger n1 = 1;
	BigInteger n2 = -1;
	REQUIRE(n1 != n2);
}

TEST_CASE(test_76, "Non-equality commparison (4)")
{
	BigInteger n1 = "-999999999999999999999999999999";
	BigInteger n2 = "999999999999999999999999999999";
	REQUIRE(n1 != n2);
}

TEST_CASE(test_77, "Non-equality commparison (5)")
{
	BigInteger n1 = "999999999999999999999999999999";
	BigInteger n2 = "-999999999999999999999999999999";
	REQUIRE(n1 != n2);
}

TEST_CASE(test_78, "Greater than comparison (1)")
{
	BigInteger n1 = 0;
	BigInteger n2 = -1;
	REQUIRE(n1 > n2);
}

TEST_CASE(test_79, "Greater than comparison (2)")
{
	BigInteger n1 = 1;
	BigInteger n2 = 0;
	REQUIRE(n1 > n2);
}

TEST_CASE(test_80, "Greater than commparison (3)")
{
	BigInteger n1 = "999999999999999999999999999999";
	BigInteger n2 = "-999999999999999999999999999999";
	REQUIRE(n1 > n2);
}

TEST_CASE(test_81, "Greater than or equal to comparison (1)")
{
	BigInteger n1 = 0;
	BigInteger n2 = -1;
	REQUIRE(n1 >= n2);
}

TEST_CASE(test_82, "Greater than or equal to comparison (2)")
{
	BigInteger n1 = 1;
	BigInteger n2 = 0;
	REQUIRE(n1 >= n2);
}

TEST_CASE(test_83, "Greater than or equal to commparison (3)")
{
	BigInteger n1 = "999999999999999999999999999999";
	BigInteger n2 = "-999999999999999999999999999999";
	REQUIRE(n1 >= n2);
}

TEST_CASE(test_84, "Greater than or equal to comparison (4)")
{
	BigInteger n1 = 0;
	BigInteger n2 = 0;
	REQUIRE(n1 >= n2);
}

TEST_CASE(test_85, "Greater than or equal to comparison (5)")
{
	BigInteger n1 = 1;
	BigInteger n2 = 1;
	REQUIRE(n1 >= n2);
}

TEST_CASE(test_86, "Greater than or equal to commparison (6)")
{
	BigInteger n1 = "999999999999999999999999999999";
	BigInteger n2 = "999999999999999999999999999999";
	REQUIRE(n1 >= n2);
}

TEST_CASE(test_87, "Greater than or equal to comparison (7)")
{
	BigInteger n1 = -1;
	BigInteger n2 = -1;
	REQUIRE(n1 >= n2);
}

TEST_CASE(test_88, "Greater than or equal to commparison (8)")
{
	BigInteger n1 = "-999999999999999999999999999999";
	BigInteger n2 = "-999999999999999999999999999999";
	REQUIRE(n1 >= n2);
}

TEST_CASE(test_89, "Smaller than comparison (1)")
{
	BigInteger n1 = -1;
	BigInteger n2 = 0;
	REQUIRE(n1 < n2);
}

TEST_CASE(test_90, "Smaller than comparison (2)")
{
	BigInteger n1 = 0;
	BigInteger n2 = 1;
	REQUIRE(n1 < n2);
}

TEST_CASE(test_91, "Smaller than commparison (3)")
{
	BigInteger n1 = "-999999999999999999999999999999";
	BigInteger n2 = "999999999999999999999999999999";
	REQUIRE(n1 < n2);
}

TEST_CASE(test_92, "Smaller than or equal to comparison (1)")
{
	BigInteger n1 = -1;
	BigInteger n2 = 0;
	REQUIRE(n1 <= n2);
}

TEST_CASE(test_93, "Smaller than or equal to comparison (2)")
{
	BigInteger n1 = 0;
	BigInteger n2 = 1;
	REQUIRE(n1 <= n2);
}

TEST_CASE(test_94, "Smaller than or equal to commparison (3)")
{
	BigInteger n1 = "-999999999999999999999999999999";
	BigInteger n2 = "999999999999999999999999999999";
	REQUIRE(n1 <= n2);
}

TEST_CASE(test_95, "Smaller than or equal to comparison (4)")
{
	BigInteger n1 = 0;
	BigInteger n2 = 0;
	REQUIRE(n1 <= n2);
}

TEST_CASE(test_96, "Smaller than or equal to comparison (5)")
{
	BigInteger n1 = 1;
	BigInteger n2 = 1;
	REQUIRE(n1 <= n2);
}

TEST_CASE(test_97, "Smaller than or equal to commparison (6)")
{
	BigInteger n1 = "999999999999999999999999999999";
	BigInteger n2 = "999999999999999999999999999999";
	REQUIRE(n1 <= n2);
}

TEST_CASE(test_98, "Smaller than or equal to comparison (7)")
{
	BigInteger n1 = -1;
	BigInteger n2 = -1;
	REQUIRE(n1 <= n2);
}

TEST_CASE(test_99, "Smaller than or equal to commparison (8)")
{
	BigInteger n1 = "-999999999999999999999999999999";
	BigInteger n2 = "-999999999999999999999999999999";
	REQUIRE(n1 <= n2);
}

void run_all_tests()
{
	DEFINE_LIST_OF_TESTS(tests) {
		test_1, test_2, test_3, test_4, test_5, test_6, test_7, test_8, test_9, test_10,
		test_11, test_12, test_13, test_14, test_15, test_16, test_17, test_18, test_19, test_20,
		test_21, test_22, test_23, test_24, test_25, test_26, test_27, test_28, test_29, test_30,
		test_31, test_32, test_33, test_34, test_35, test_36, test_37, test_38, test_39, test_40,
		test_41, test_42, test_43, test_44, test_45, test_46, test_47, test_48, test_49, test_50,
		test_51, test_52, test_53, test_54, test_55, test_56, test_57, test_58, test_59, test_60,
		test_61, test_62, test_63, test_64, test_65, test_66, test_67, test_68, test_69, test_70,
		test_71, test_72, test_73, test_74, test_75, test_76, test_77, test_78, test_79, test_80,
		test_81, test_82, test_83, test_84, test_85, test_86, test_87, test_88, test_89, test_90,
		test_91, test_92, test_93, test_94, test_95, test_96, test_97, test_98, test_99
	};
	PRINT_FILE_NAME();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
}
