#include <type_traits>
#include <iostream>

int main()
{
	std::cout << (std::is_signed<char>::value ? "signed\n" : "unsigned\n");
}