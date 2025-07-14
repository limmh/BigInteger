#include "BigInteger.hpp"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

ostream& operator<<(ostream& os, const BigInteger& n)
{
	os << BigInteger::toString(n);
	return os;
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		cout << "Usage: " << argv[0] << " <integer> <operator> <integer>\n";
		cout << "Supported operators:\n";
		cout << "+: plus\n";
		cout << "-: minus\n";
		cout << "x: multiply\n";
		cout << "/: divide\n";
		cout << "rem: remainder\n";
		cout << "bitwise_and: performs bitwise AND operation\n";
		cout << "bitwise_or: performs bitwise OR operation\n";
		cout << "invert_bits: inverts all bits of an integer, usage: \"\" invert_bits <integer>\n";
		cout << "and (AND): performs logical AND operation\n";
		cout << "or (OR): performs logical OR operation\n";
		cout << "not (NOT): performs logical NOT operation, usage: \"\" not <integer>\n";
		return 0;
	}

	BigInteger n1; 
	const size_t length1 = strlen(argv[1]);
	if (length1 == 4 &&
		(argv[1][0] == 'T' || argv[1][0] == 't') &&
		(argv[1][1] == 'R' || argv[1][1] == 'r') &&
		(argv[1][2] == 'U' || argv[1][2] == 'u') &&
		(argv[1][3] == 'E' || argv[1][3] == 'e') )
	{
		n1 = 1;
	}
	else if (length1 == 5 &&
		(argv[1][0] == 'F' || argv[1][0] == 'f') &&
		(argv[1][1] == 'A' || argv[1][1] == 'a') &&
		(argv[1][2] == 'L' || argv[1][2] == 'l') &&
		(argv[1][3] == 'S' || argv[1][3] == 's') &&
		(argv[1][4] == 'E' || argv[1][4] == 'e') )
	{
		n1 = 0;
	}
	else
	{
		n1 = argv[1];
	}

	BigInteger n2; 
	const size_t length2 = strlen(argv[3]);
	if (length2 == 4 &&
		(argv[3][0] == 'T' || argv[3][0] == 't') &&
		(argv[3][1] == 'R' || argv[3][1] == 'r') &&
		(argv[3][2] == 'U' || argv[3][2] == 'u') &&
		(argv[3][3] == 'E' || argv[3][3] == 'e') )
	{
		n2 = 1;
	}
	else if (length2 == 5 &&
		(argv[3][0] == 'F' || argv[3][0] == 'f') &&
		(argv[3][1] == 'A' || argv[3][1] == 'a') &&
		(argv[3][2] == 'L' || argv[3][2] == 'l') &&
		(argv[3][3] == 'S' || argv[3][3] == 's') &&
		(argv[3][4] == 'E' || argv[3][4] == 'e') )
	{
		n2 = 0;
	}
	else
	{
		n2 = argv[3];
	}

	BigInteger result;
	const string op = argv[2];

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
		result = n1 / n2;
	}
	else if (op == "rem")
	{
		result = n1 % n2;
	}
	else if (op == "bitwise_and")
	{
		result = n1 & n2;
	}
	else if (op == "bitwise_or")
	{
		result = n1 | n2;
	}
	else if (op == "bitwise_xor")
	{
		result = n1 ^ n2;
	}
	else if (argv[1][0] == '\0' && op == "invert_bits")
	{
		result = ~n2;
	}
	else if (op == "and" || op == "AND")
	{
		result = n1 && n2;
	}
	else if (op == "or" || op == "OR")
	{
		result = n1 || n2;
	}
	else if (argv[1][0] == '\0' && (op == "not" || op == "NOT"))
	{
		result = !n2;
	}
	else
	{
		cout << "Invalid operation: " << "\"" << argv[1] << " " << argv[2] << " " << argv[3] << "\"" << '\n';
		return 0;
	}

	cout << result << '\n';
	return 0;
}
