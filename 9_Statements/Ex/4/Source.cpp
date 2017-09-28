/*
[4] (∗2) Write a function atoi(const char∗) that takes a C-style string containing digits and returns
the corresponding int. For example, atoi("123") is 123. Modify atoi() to handle C++ octal and
hexadecimal notation in addition to plain decimal numbers. Modify atoi() to handle the C++
character constant notation.
*/

#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>

int my_atoi(const char* str)
{
	const auto len = std::strlen(str);
	if (!len)
		return 0;

	int mult = 1;
	int res = 0;
	int n = 0;

	// get sign
	bool neg = false;
	if (str[n] == '-')
	{
		neg = true;
		++n;
	}

	// get base
	int base = 10;
	if (str[n] == '0')
	{
		++n;
		if (str[n] == 'x' || str[n] == 'X')
		{
			base = 16;
			++n;
		}
		else
		{
			base = 8;
		}
	}

	// scan digits backwards
	for (int i = len - 1; i >= n; --i)
	{
		const auto ch = str[i];
		char base_letter = 0;
		int offset = 0;
		switch (base)
		{
		case 8:
			if ((ch >= '0') && (ch <= '7'))
				base_letter = '0';
			break;
		case 10:
			if ((ch >= '0') && (ch <= '9'))
				base_letter = '0';
			break;
		case 16:
			if ((ch >= '0') && (ch <= '9'))
			{
				base_letter = '0';
			}
			else if ((ch >= 'a') && (ch <= 'f'))
			{
				base_letter = 'a';
				offset = 10;
			}
			else if ((ch >= 'A') && (ch <= 'F'))
			{
				base_letter = 'A';
				offset = 10;
			}
			break;
		}
		if (!base_letter)
			break;
		res += mult * (ch - base_letter + offset);
		mult *= base;
	}
	return neg ? -res : res;
}

int main()
{
	// DEC
	assert(my_atoi("0") == 0);
	assert(my_atoi("1") == 1);
	assert(my_atoi("a") == 0); // wrong
	assert(my_atoi("10") == 10);
	assert(my_atoi("12") == 12);
	assert(my_atoi("321") == 321);
	assert(my_atoi("321") == 321);
	assert(my_atoi("-2") == -2);
	assert(my_atoi("-0") == 0);

	// OCT
	assert(my_atoi("01") == 1);
	assert(my_atoi("07") == 7);
	assert(my_atoi("010") == 8);
	assert(my_atoi("09") == 0); // wrong
	assert(my_atoi("-011") == -9);

	// HEX
	assert(my_atoi("0x1") == 1);
	assert(my_atoi("0xA") == 10);
	assert(my_atoi("0xf") == 15);
	assert(my_atoi("0xG") == 0); // wrong
	assert(my_atoi("0xFF") == 255);
	assert(my_atoi("-0xB") == -11);
}