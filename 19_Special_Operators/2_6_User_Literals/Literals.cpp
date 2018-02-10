/*
19.2.6 User-defined Literals
*/

#include <iostream>
#include <string>

std::string operator""_str(const char* p)
{
  return p;
}

std::string operator""_str2(const char* p, size_t n)
{
  return std::string{ p, n };
}

template<int n>
constexpr int b3_helper() // terminal
{
  return n;
}

template<int n, char c, char... tail>
constexpr int b3_helper() // peel off one digit
{
  static_assert(c < '3', "not a ternary digit");
  return b3_helper<3 * n + c - '0', tail...>();
}

template<char... chars>
constexpr int operator""_b3() // base 3
{
  return b3_helper<0, chars...>();
}

int main()
{
  std::cout << 123345678901234567890_str << "\n";
  std::cout << 1.5_str << "\n";
  std::cout << "abc"_str2 << "\n";

  std::cout << 201_b3 << "\n"; // 9*2+0*3+1 == 19
}