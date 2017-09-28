/*
[2] (∗1) See how your compiler reacts to these errors:
void f(int a, int b)
{
if (a = 3) // ...
if (a&077 == 0) // ...
a := b+1;
}
Devise more simple errors and see how the compiler reacts.
*/

#include <iostream>

void f(int a, int b)
{
	if (a = 3) std::cout << __LINE__ << "\n"; // no warning
	//if (a & 077 == 0) std::cout << __LINE__ << "\n"; // Warning	C4554	'&': check operator precedence for possible error; use parentheses to clarify precedence
	//a := b + 1; // syntax error
}

int main()
{
	f(1, 2);
}