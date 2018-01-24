/*
17.5.1.4 Slicing
*/

#include <iostream>

struct Base
{
  int b;
  Base()
  {
    std::cout << "Base()\n";
  }

  //// 1. Prohibit copying of the base
  //// Error	C2280	'Base::Base(const Base &)': attempting to reference a deleted function
  //Base(const Base& b) = delete;

  Base(const Base& b)
    : b{ b.b }
  {
    std::cout << "Base(const Base& b)\n";
  }
};

struct Derived
  : Base
  //// 2. Prevent conversion derived => base
  //// Error	C2243	'type cast' : conversion from 'Derived *' to 'Base *' exists, but is inaccessible
  //: protected Base
{
  int d;
  Derived()
  {
    std::cout << "Derived()\n";
  }
  Derived(const Derived& d)
    : Base(d),
    d{ d.d }
  {
    std::cout << "Derived(const Derived& d)\n";
  }
};

void naive(Base* p)
{
  Base b2 = *p; // may slice
}

/*
output:
Base()
Derived()
Base(const Base& b)
Base(const Base& b)
*/
int main()
{
  Derived d;
  naive(&d);
  Base bb = d; // slices
  return 0;
}