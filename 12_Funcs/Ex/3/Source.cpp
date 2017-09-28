/*
[3] (*1.5) Write a program like ‘‘Hello, world!’’ that takes a name as a command-line argument
and writes ‘‘Hello, name !’’. Modify this program to take any number of names as arguments
and to say hello to each.
*/

#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "Hello";
	for (int i = 1; i < argc; ++i) // skip prog name
	{
		std::cout << ", " << argv[i];
	}
	std::cout << "!";
	return 0;
}