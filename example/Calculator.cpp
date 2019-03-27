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
#include <iostream>
#include <string>
#include <vector>

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
		result = n1 + n2;
	else if (op == "-")
		result = n1 - n2;
	else if (op == "x")
		result = n1 * n2;
	else if (op == "/")
		result = n1 / n2;
	else if (op == "rem")
		result = n1 % n2;
	else
	{
		cout << "Invalid operator: " << op << '\n';
		return 0;
	}

	cout << result << '\n';
	return 0;
}
