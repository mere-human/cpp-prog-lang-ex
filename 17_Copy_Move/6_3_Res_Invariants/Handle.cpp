/*
17.6.3.3 Resource Invariants
*/
#include <iostream>

template<typename T>
class Handle
{
  T* p;
public:
  Handle(T* pp) : p{ pp } {}
  Handle(const Handle& a) : p{ new T{*a.p} } {}
  ~Handle() { delete p; }
  T& operator*() { return *p; }
  Handle& operator=(const Handle& a) { *p = *a.p; }
};

int main()
{
  Handle<int> h(new int{ 3 });
  //Handle<int> h2; // Error	C2512	'Handle<int>': no appropriate default constructor available
  std::cout << *h << "\n";
  Handle<int> h3{ h }; // no error, however, runtime double free corruption occurs
  std::cout << *h3 << "\n";
  return 0;
}