/*
19.2.5 Allocation and Deallocation
*/
#include <iostream>
#include <vector>
#include <memory>

class Employee
{
public:
  void* operator new(size_t n)
  {
    auto p = malloc(n);
    std::cout << "new " << n << " @ " << p << "\n";
    return p;
  }

  void* operator new[](size_t n)
  {
    auto p = malloc(n);
    std::cout << "new[] " << n << " @ " << p << "\n";
    return p;
  }

  void operator delete(void* p, size_t n)
  {
    std::cout << "delete " << n << " @ " << p << "\n";
    free(p);
  }

  void operator delete[](void* p, size_t n)
  {
    std::cout << "delete[] " << n << " @ " << p << "\n";
    free(p);
  }
};

int main()
{
  auto p = new Employee{};
  delete p;
  std::vector<Employee> v;
  v.push_back({});
  return 0;
}