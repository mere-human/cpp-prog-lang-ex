/*
19.2.4 Increment and Decrement
*/
#include <iostream>

template<typename T>
class Ptr
{
  T* ptr;
  T* arr;
  int sz;
public:
  template<int N>
  Ptr(T* p, T(&a)[N]) : ptr{ p }, arr{ a }, sz{ N } // array
  {}
  Ptr(T* p) : ptr{ p }, arr{ p }, sz{ 0 } // single object
  {}
  Ptr& operator++() // prefix
  {
    if ((ptr + 1 - arr) >= sz)
      throw std::out_of_range{ "Ptr is out of range" };
    ++ptr;
    return *this;
  }
  Ptr operator++(int) // postfix
  {
    if ((ptr + 1 - arr) >= sz)
      throw std::out_of_range{ "Ptr is out of range" };
    auto old = *this;
    ++ptr;
    return old;
  }
  Ptr& operator--() // prefix
  {

  }
  Ptr operator--(int) // postfix
  {

  }
  T& operator*() { return *ptr; }
};

int main()
{
  int n1 = 2;
  Ptr<int> p1(&n1);
  try
  {
    while (true)
    {
      std::cout << *p1 << "\n";
      ++p1;
    }
  }
  catch (std::out_of_range& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
  }
}