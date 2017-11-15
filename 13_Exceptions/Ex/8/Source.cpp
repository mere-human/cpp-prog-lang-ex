/*
[8] (*1) Given:
int main() { / * ... * / }
Change it so that it catches all exceptions thrown from the ..., turns them
into error messages, and abort()s.
*/
#include <exception>
#include <cstdlib>
#include <iostream>
#include <vector>

//T he body of a function can be a try-block (13.5.2.4)
int main()
try
{
	std::vector<int> v;
	v.at(1);
	return 0;
}
catch (std::exception& e)
{
	std::cerr << "Error: " << e.what() << "\n";
	std::abort();
}
catch (...)
{
	std::cerr << "Unknown error\n";
	std::abort();
}