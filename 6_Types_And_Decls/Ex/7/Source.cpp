/*
[7] (?1.5) Write a program that prints out the letters 'a'..'z' and the digits '0'..'9' and their integer
values. Do the same for other printable characters. Do the same again but use hexadecimal
notation.
*/

#include <cctype>
#include <iostream>

int main()
{
	for (unsigned char c = 0; c != 255; ++c)
	{
		if (std::isprint(c))
		{
			std::cout << c << " " << std::dec << static_cast<int>(c) << " "
				<< std::hex << static_cast<int>(c) << "\n";
		}
	}
}