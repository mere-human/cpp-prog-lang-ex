/*
[1] (*2) Implement the functions of the "cannonical complete class" X from
ch.17.1 to do noting but print out their name and the address of their object
(and of their argument where applicable). Now test X by defining variables,
members, objects on the free store, passing arguments, etc.
*/

#include <iostream>

#if defined(_WIN32) && defined(__FUNCSIG__)
#define FUNCNAME __FUNCSIG__
#elif defined(__PRETTY_FUNCTION__)
#define FUNCNAME __PRETTY_FUNCTION__
#else
#define FUNCNAME __FUNCTION__
#endif

#define PRINT_INFO\
  printf("%s %p\n", FUNCNAME, this)

class X
{
public:
  X()
  {
    PRINT_INFO;
  }
  X(int)
  {
    PRINT_INFO;
  }
  X(const X&)
  {
    PRINT_INFO;
  }
  X(X&&)
  {
    PRINT_INFO;
  }
  X& operator=(const X&)
  {
    PRINT_INFO;
    return *this;
  }
  X& operator=(X&&)
  {
    PRINT_INFO;
    return *this;
  }
  ~X()
  {
    PRINT_INFO;
  }
};

X f1()
{
  return X{};
}

void f2(const X&)
{

}

void f3(X)
{

}

int main()
{
  X x; // default ctor
  X x2{ 1 }; // int ctor
  X x3{ x }; // copy ctor
  X x4 = std::move(x2); // move ctor
  x3 = x4; // copy assign
  x4 = std::move(x3); // move assign
  X x5 = f1(); // default ctor (move is optimized)
  f2(x4); // nothing
  f3(x5); // copy ctor
  X* p1 = new X{ 2 }; // int ctor
  X* p2 = new X{ *p1 }; // copy ctor
  delete p1; // dtor
  //delete p2; // no dtor for this object will be called
  // dtors are called here in reverse definition order
}