/*
[14] (*1.5) Define a class Index to hold the index for an exponentiation
function mypow(double,Index). Find a way to have 2**I call mypow(2,I).
*/

#include <iostream>

struct ExpBase
{
  double v;
  ExpBase(double n = 0.0) : v{ n } {}
};

class Index
{
  double v;
public:
  Index(double n = 0.0) : v{ n } {}
  double operator*() const { return v; } // unary dereference operator
};

double operator*(ExpBase x, double y) // at least one user-defined type
{
  return std::pow(x.v, y);
}

int main()
{
  Index i = 2;
  std::cout << 2 ** i;
}