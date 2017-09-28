#include <iostream>

[[noreturn]] int f() { // warning
	return 2;
}

int main() {
	std::cout << f();
	std::cout << "\nafter noreturn\n";
}