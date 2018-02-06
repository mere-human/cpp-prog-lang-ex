#include <iostream>

struct X { X(const char*) {} };
struct Z { Z(X) {} };
struct XX { XX(int) {} };

void f(Z) {}

void h(double) { std::cout << "double\n"; }
void h(XX) { std::cout << "XX\n"; }

int main()
{
  //f("Mack"); // error: 2 conversions needed

  h(1);
}
