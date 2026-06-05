#include "BigInteger.hpp"
#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
#include <cstring>

using namespace std;

ostream& operator<<(ostream& os, const BigInteger& n)
{
	os << BigInteger::toString(n);
	return os;
}

static bool is_integer(const char *str, size_t length)
{
	bool result = true;
	size_t i = 0U;

	while (i < length) // skip leading zeros
	{
		if (!::isspace(str[i]))
		{
			break;
		}
		++i;
	}

	if (i < length) // check whether the first meaningful character is a plus or minus sign
	{
		if (str[i] == '+' || str[i] == '-')
		{
			++i;
		}
	}

	while (i < length) // skip the zeros between the sign and the first digit
	{
		if (!::isspace(str[i]))
		{
			break;
		}
		++i;
	}

	result = (i < length);

	for (; i < length; ++i)
	{
		if (!::isdigit(str[i]))
		{
			result = false;
			break;
		}
	}

	return result;
}

static BigInteger factorial(const BigInteger &integer)
{
	BigInteger result = 1;
	BigInteger n = integer;
	const BigInteger zero = 0; 
	while (n > zero) {
		result *= n;
		--n;
	}
	return result;
}

static BigInteger integer_power(const BigInteger &base, const BigInteger &exponent)
{
	BigInteger result = 1;
	BigInteger n = exponent;
	for (; n > 0; --n) {
		result *= base;
	}
	return result;
}

static void print_usage(const char *program_name)
{
	assert(program_name != nullptr);
	cout << "Usage: " << program_name << " <integer> <operator> <integer>\n";
	cout << "Supported operators:\n";
	cout << "+: plus\n";
	cout << "-: minus\n";
	cout << "x: multiply\n";
	cout << "/: divide\n";
	cout << "rem: remainder\n";
	cout << "bit_and (bitwise_and): performs bitwise AND operation\n";
	cout << "bit_or (bitwise_or): performs bitwise OR operation\n";
	cout << "xor (XOR): performs bitwise XOR operation\n";
	cout << "invert: inverts all bits of an integer, usage: invert <integer>\n";
	cout << "and (AND): performs logical AND operation\n";
	cout << "or (OR): performs logical OR operation\n";
	cout << "not (NOT): performs logical NOT operation, usage: not <integer>\n";
	cout << "^ (power): performs operand1 to the power of operand2\n";
	cout << "factorial: performs a factorial operation.\n";
}

int main(int argc, char *argv[])
{
	if (argc < 3 || argc > 4)
	{
		print_usage(argv[0]);
		return 0;
	}

	int error_code = 0;
	const int number_of_operands = (argc == 3) ? 1 : 2;
	const string op = (number_of_operands == 1) ? argv[1] : argv[2];

	BigInteger n1;
	const char *operand1 = (number_of_operands == 1) ? argv[2] : argv[1];
	const size_t length1 = strlen(operand1);
	if (length1 == 4 &&
		(operand1[0] == 'T' || operand1[0] == 't') &&
		(operand1[1] == 'R' || operand1[1] == 'r') &&
		(operand1[2] == 'U' || operand1[2] == 'u') &&
		(operand1[3] == 'E' || operand1[3] == 'e') )
	{
		n1 = 1;
	}
	else if (length1 == 5 &&
		(operand1[0] == 'F' || operand1[0] == 'f') &&
		(operand1[1] == 'A' || operand1[1] == 'a') &&
		(operand1[2] == 'L' || operand1[2] == 'l') &&
		(operand1[3] == 'S' || operand1[3] == 's') &&
		(operand1[4] == 'E' || operand1[4] == 'e') )
	{
		n1 = 0;
	}
	else if (is_integer(operand1, length1))
	{
		n1 = operand1;
	}
	else
	{
		error_code = 1;
		cout << operand1 << " is not an integer.\n";
	}

	BigInteger n2;
	if (number_of_operands == 2)
	{
		const char *operand2 = argv[3];
		const size_t length2 = strlen(operand2);
		if (length2 == 4 &&
			(operand2[0] == 'T' || operand2[0] == 't') &&
			(operand2[1] == 'R' || operand2[1] == 'r') &&
			(operand2[2] == 'U' || operand2[2] == 'u') &&
			(operand2[3] == 'E' || operand2[3] == 'e') )
		{
			n2 = 1;
		}
		else if (length2 == 5 &&
			(operand2[0] == 'F' || operand2[0] == 'f') &&
			(operand2[1] == 'A' || operand2[1] == 'a') &&
			(operand2[2] == 'L' || operand2[2] == 'l') &&
			(operand2[3] == 'S' || operand2[3] == 's') &&
			(operand2[4] == 'E' || operand2[4] == 'e') )
		{
			n2 = 0;
		}
		else if (is_integer(operand2, length2))
		{
			n2 = operand2;
		}
		else
		{
			error_code = 2;
			cout << operand2 << " is not an integer.\n";
		}
	}

	if (error_code != 0)
	{
		return error_code;
	}

	BigInteger result;

	if (op == "+")
	{
		result = n1 + n2;
	}
	else if (op == "-")
	{
		result = n1 - n2;
	}
	else if (op == "x")
	{
		result = n1 * n2;
	}
	else if (op == "/")
	{
		try
		{
			result = n1 / n2;
		}
		catch (BigInteger::DivisionByZeroException&)
		{
			cout << "Integer division by 0 (zero) is undefined.\n";
		}
	}
	else if (op == "rem" || op == "remainder")
	{
		result = n1 % n2;
	}
	else if (op == "bitwise_and" || op == "bit_and")
	{
		result = n1 & n2;
	}
	else if (op == "bitwise_or" || op == "bit_or")
	{
		result = n1 | n2;
	}
	else if (op == "xor" || op == "XOR")
	{
		result = n1 ^ n2;
	}
	else if (op == "invert")
	{
		result = ~n1;
	}
	else if (op == "and" || op == "AND")
	{
		result = n1 && n2;
	}
	else if (op == "or" || op == "OR")
	{
		result = n1 || n2;
	}
	else if (op == "not" || op == "NOT")
	{
		result = !n1;
	}	
	else if (op == "^" || op == "power")
	{
		if (n2 >= 0)
		{
			result = integer_power(n1, n2);
		}
		else
		{
			cout << "The exponent (operand 2) must be 0 or positive.\n";
			error_code = 3;
		}
	}
	else if (op == "factorial")
	{
		result = factorial(n1);
	}
	else
	{
		error_code = 4;
		
		if (number_of_operands == 1)
		{
			cout << "Invalid operation: " << "\"" << argv[1] << " " << argv[2] << "\"" << '\n';
			cout << "Operator " << argv[1] << " is not supported.\n";
		}
		else if (number_of_operands == 2)
		{
			cout << "Invalid operation: " << "\"" << argv[1] << " " << argv[2] << " " << argv[3] << "\"" << '\n';
			cout << "Operator " << argv[2] << " is not supported.\n";
		}
		print_usage(argv[0]);
	}

	if (error_code == 0)
	{
		cout << result << '\n';
	}
	return error_code;
}
