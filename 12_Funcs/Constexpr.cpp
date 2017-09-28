#include <iostream>

int glob = 0;
constexpr void g(int n) {
	//glob = n; // error
}

constexpr int fact(int n) {
	return (n > 1) ? n * fact(n - 1) : 1;
}

void f(int n) {
	int f5 = fact(5);
	int fn = fact(n); // runtime

	constexpr int f6 = fact(6);
	//constexpr int fnn = fact(n); // error

	char a[fact(4)];
	//char a2[fact(n)]; // error
}

constexpr int ftbl[] = { 1, 2, 3, 5, 8, 13 };

constexpr int fib(int n) {
	return (n < sizeof(ftbl) / sizeof(*ftbl)) ? ftbl[n] : fib(n);
}

int main() {
	f(2);
	std::cout << fib(3);
}