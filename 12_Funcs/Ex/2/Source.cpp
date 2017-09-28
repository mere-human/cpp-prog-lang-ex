/*
[2] (*1) What does the following mean? What would it be good for?
using riffi = int (&) (int, int);
*/

#include <iostream>

// reference to function which returns int and takes two int arguments
using riffi = int(&) (int, int);

int add(int a, int b)
{
	return a + b;
}

int main()
{
	riffi f = add;
	std::cout << f(1, 2);
}