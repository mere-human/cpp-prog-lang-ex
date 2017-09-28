/*
[8] (∗1.5) What is the size of the array str in the following example:
char str[] = "a short string";
What is the length of the string "a short string"?
*/

#include <iostream>
#include <cstring>

int main()
{
	char str[] = "a short string";
	std::cout << "size: " << sizeof(str) / sizeof(*str)
		<< "\nlen: " << std::strlen(str) << "\n";
}