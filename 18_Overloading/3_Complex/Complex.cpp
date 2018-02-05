/*
18.3.2 Mixed-Mode Arithmetic
18.3.3 Conversions
18.3.3.1 Conversions of Operands
18.3.4 Literals
*/
#include <iostream>

class Complex
{
  double re, im;
public:
  constexpr Complex(double r = 0.0, double i = 0.0)
    : re{ r }, im{ i }
  {}

  constexpr double real() const { return re; }
  constexpr double imag() const { return im; }

  void real(double r) { re = r; }
  void imag(double i) { im = i; }

  Complex& operator+=(Complex a)
  {
    re += a.re;
    im += a.im;
    return *this;
  }
  Complex& operator+=(double r)
  {
    re += r;
    return *this;
  }
};

Complex operator+(Complex a, Complex b)
{
  return a += b;
}
Complex operator+(Complex a, double b)
{
  return{ a.real() + b, a.imag() };
}
Complex operator+(double a, Complex b)
{
  return{ a + b.real(), b.imag() };
}

std::ostream& operator<<(std::ostream& os, Complex c)
{
  os << c.real() << "+" << c.imag() << "i";
  return os;
}

inline bool operator==(Complex a, Complex b)
{
  return a.real() == b.real() && a.imag() == b.imag();
}

inline bool operator!=(Complex a, Complex b)
{
  return !(a == b);
}

// Warning	C4455	'operator ""i': literal suffix identifiers that do not start with an underscore are reserved
// user defined literal should have signature like this (not double)
constexpr Complex operator""i(long double d)
{
  return{ 0,static_cast<double>(d) }; // avoid narrowing
}

int main()
{
  // mixed mode
  Complex x{ 2, 2 };
  Complex y{ 1, 3 };
  std::cout << x + y << "\n";
  std::cout << x + 2 << "\n";
  std::cout << 2 + x << "\n";
  std::cout << 2 + 3 << "\n"; // built-in int addition

  // conversion constructor
  x = 4; // means x.re = 4, x.im = 0
  std::cout << x << "\n";
  Complex z;
  z = x;
  std::cout << z << "\n";

  // conversion operator
  std::cout << (x == y) << "\n";
  std::cout << (x == 4) << "\n";
  std::cout << (4 == x) << "\n";

  // literals
  constexpr Complex z2{ 1.2, 12e2 }; // compile-time init
  Complex z3{ 1.2 + 12e2i };
  std::cout << z3 << "\n";

  return 0;
}