#include <cstdio>
#include <iostream>

#define perr(...) fprintf(stderr, "error: %s %d\n", __VA_ARGS__)

int main() {
	perr("answer", 42);
	std::cout << __DATE__ << "\n";
	std::cout << __TIME__ << "\n";
	std::cout << __func__ << "\n";
}