/*
[1](∗1) Write declarations for the following : a pointer to a character, an array of 10 integers, a
reference to an array of 10 integers, a pointer to an array of character strings, a pointer to a
pointer to a character, a constant integer, a pointer to a constant integer, and a constant
pointer to an integer.Initialize each one.
*/

#include <iostream>
#include <string>

int main()
{
	char c = 'a';
	char* pc = &c; // a pointer to a character
	std::cout << *pc << "\n";
	
	int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // an array of 10 integers
	int(&ra)[10] = a; // a reference to an array of 10 integers
	ra[2] = 3;
	std::cout << a[2] << "\n";
	
	std::string sa[] = { "one", "two" }; // a pointer to an array of character strings
	std::string(*ps)[2] = &sa;
	std::cout << (*ps)[0] << "\n";

	char** ppc = &pc; // a pointer to a pointer to a character
	std::cout << **ppc << "\n";

	const int i = 2;
	const int* pi = &i;
	//*pi = 3; // error
	const int* const cpi = pi;
	//cpi = &a[0]; // error
	std::cout << *cpi << "\n";
}