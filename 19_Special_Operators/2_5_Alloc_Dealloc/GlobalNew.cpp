/*
19.2.5 Allocation and Deallocation
*/

#include <memory>
#include <iostream>
#include <vector>

void* operator new(size_t n) // individual object
{
  auto p = malloc(n);
  std::cout << "new " << n << " @ " << p << "\n";
  return p;
}

void* operator new[](size_t n) // array
{
  auto p = malloc(n);
  std::cout << "new[] " << n << " @ " << p << "\n";
  return p;
}

void operator delete(void* p, size_t n) // individual object
{
  std::cout << "delete " << n << " @ " << p << "\n";
  free(p);
}

void operator delete[](void* p, size_t n) // array
{
  std::cout << "delete[] " << n << " @ " << p << "\n";
  free(p);
}

void f()
{
  std::vector<char> v(5);
  v[0] = 1;
  std::cout << v.size() << "\n";
}

int main()
{
  f();
  int* n1 = new int{ 3 };
  delete n1;
  double* d = new double[3];
  delete d; // oops
  return 0;
}