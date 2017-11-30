#include <iostream>

int main() {
  int n = 10000;
  for (int i = 0; ; ++i) {
    int* p = new(std::nothrow) int[n];
    if (!p) {
      std::cout << "no memory at step " << i << "\n";
      operator delete(p, std::nothrow);
      break;
    }
  }
}