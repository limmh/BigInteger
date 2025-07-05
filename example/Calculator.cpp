#include "BigInteger.hpp"
#include <iostream>
#include <string>

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
		cout << "Usage: " << argv[0] << " <integer> <operator: + or - or x or / or rem> <integer>\n";
		return 0;
	}

	BigInteger n1 = argv[1];
	BigInteger n2 = argv[3];
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
	else
	{
		cout << "Invalid operator: " << op << '\n';
		return 0;
	}

	cout << result << '\n';
	return 0;
}
