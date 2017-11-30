#ifndef __INT_H__
#define __INT_H__
#pragma once

#include <ostream>
#include <limits>

struct IntError : std::exception
{
  explicit IntError(const char* const msg) : std::exception{ msg }
  {}
};

class Int
{
public:
  using Type = int;

  // avoid any implicit conversions

  explicit Int(Type value = {}) : _value{ value }
  {}

  const Type& get() const
  {
    return _value;
  }

  static const Type MaxValue = std::numeric_limits<Type>::max();
  static const Type MinValue = std::numeric_limits<Type>::min();
private:
  Type _value;
};

Int operator-(const Int& a)
{
  if (a.get() == Int::MinValue) throw IntError{ "minus overflow" };
  return Int(-a.get());
}

Int operator+(const Int& a, const Int& b)
{
  if ((a.get() > 0) && (b.get() > 0))
  {
    // a + b > MAX => MAX - a - b < 0 => error
    if ((Int::MaxValue - a.get() - b.get()) < 0)
      throw IntError{ "add overflow" };
  }
  else if ((a.get() < 0) && (b.get() < 0))
  {
    // a + b < MIN => MIN - a - b > 0 => error
    if ((Int::MinValue - a.get() - b.get()) > 0)
      throw IntError{ "add underflow" };
  }
  return Int(a.get() + b.get());
}

Int operator-(const Int& a, const Int& b)
{
  // just reuse
  return a + (-b);
}

Int operator*(const Int& a, const Int& b)
{
  // check for zero
  if ((a.get() == 0) || (b.get() == 0)) return Int{ 0 };
  // check for negation
  if (a.get() == -1) return -Int{ b.get() };
  if (b.get() == -1) return -Int{ a.get() };
  // a * b > MAX => a > MAX / b => error
  if (a.get() > (Int::MaxValue / b.get())) throw IntError{ "mult overflow" };
  if (a.get() < (Int::MinValue / b.get())) throw IntError{ "mult overflow" };
  return Int(a.get() * b.get());
}

Int operator/(const Int& a, const Int& b)
{
  if (b.get() == 0) throw IntError{ "division by zero" };
  // MIN/-1 => error
  if ((a.get() == Int::MinValue) && (b.get() == -1))
    throw IntError{ "division overflow" };
  return Int(a.get() / b.get());
}

std::ostream& operator<<(std::ostream& os, const Int& i)
{
  os << i.get();
  return os;
}

bool operator==(const Int& a, int b)
{
  return a.get() == b;
}

#endif // __INT_H__
