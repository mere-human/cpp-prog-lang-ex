#include <iostream>

class Tiny
{
  char v;
  void assign(int i)
  {
    if (i & ~077)
      throw Bad_range{};
    v = i;
  }
public:
  class Bad_range {};

  Tiny(int i) { assign(i); }
  Tiny& operator=(int i) { assign(i); return *this; }
  operator int() const { return v; }
};

int main()
{
  Tiny c1 = 2;
  Tiny c2 = 62;
  Tiny c3 = c2 - c1;
  std::cout << c3 << "\n";
  Tiny c4 = c3;
  int i = c1 + c2;
  std::cout << i << "\n";
  try
  {
    c1 = c1 + c2;
  }
  catch (Tiny::Bad_range&)
  {
    std::cerr << "range error\n";
  }
  i = c3 - 64;
  std::cout << i << "\n";
  try
  {
    c2 = c3 - 64;
  }
  catch (Tiny::Bad_range&)
  {
    std::cerr << "range error\n";
  }

  return 0;
}