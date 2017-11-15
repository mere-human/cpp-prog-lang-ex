/*
[5] (*2.5) Write a complete Vector template with Range and Size exceptions
*/
#include "Vector.h"

#include <iostream>

int main()
{
	vector<int> v(2, 1);
	v.resize(3);
	v.push_back(2);
	try
	{
		v.at(1) = 5;
		v.at(5) = 1;
	}
	catch (RangeException& e)
	{
		std::cerr << "Error: " << e.msg << "\n";
	}
	for (size_t i = 0; i != v.size(); ++i)
		std::cout << v.at(i) << " ";
	std::cout << "\n";
	try
	{
		while (true)
			v.pop_back();
	}
	catch (SizeException& e)
	{
		std::cerr << "Error: " << e.msg << "\n";
	}
	return 0;
}
