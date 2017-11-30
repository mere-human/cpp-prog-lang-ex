#include <iostream>

int sum(int a, int b) {
  std::cout << a << " + " << b << "\n";
  return a + b;
}

int main() {
  using P1 = int(*)(int, int);
  P1 p1 = &sum;
  p1(1, 2);
}