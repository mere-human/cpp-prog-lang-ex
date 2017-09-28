/*
[1] (∗1) Define a struct with a member of each of the types bool, char, int, long, double, and long
double. Order the members so as to get the largest size of the struct and the smallest size of
the struct.
*/

#include <iostream>

int main()
{
	struct S1
	{
		bool b;
		char c;
		int i;
		long l;
		double d;
		long double ld;
	};
	std::cout << "S1: " << sizeof(S1) << "\n";

	struct S2
	{
		long double ld;
		double d;
		long l;
		int i;
		char c;
		bool b;
	};
	std::cout << "S2: " << sizeof(S2) << "\n";

	struct S3
	{
		long double ld;
		double d;
		long l;
		char c;
		bool b;
		int i;
	};
	std::cout << "S3: " << sizeof(S3) << "\n";
}