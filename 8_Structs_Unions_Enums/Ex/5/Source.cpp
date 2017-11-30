/*
[5] (∗2) Implement an enum called Season with enumerators spring, summer, autumn, and winter.
Define operators ++ and −− for Season. Define input (>>) and output (<<) operations for Season, providing string values. 
Provide a way to control the mapping between Season values
and their string representations. For example, I might want the strings to reflect the Danish
names for the seasons. For further study, see Chapter 39.
*/

#include <iostream>
#include <string>

enum class Season
{
  spring, summer, autumn, winter
};

Season operator++(const Season& val)
{
  switch (val)
  {
  case Season::spring: return Season::summer;
  case Season::summer: return Season::autumn;
  case Season::autumn: return Season::winter;
  case Season::winter: return Season::spring;
  }
}

Season operator--(const Season& val)
{
  switch (val)
  {
  case Season::spring: return Season::winter;
  case Season::summer: return Season::spring;
  case Season::autumn: return Season::summer;
  case Season::winter: return Season::autumn;
  }
}

std::ostream& operator<<(std::ostream& os, const Season& s)
{
  switch (s)
  {
  case Season::spring:
    os << "spring";
    break;
  case Season::summer:
    os << "summer";
    break;
  case Season::autumn:
    os << "autumn";
    break;
  case Season::winter:
    os << "winter";
    break;
  }
  return os;
}

std::istream& operator >> (std::istream& is, Season& s)
{
  std::string text;
  is >> text;

  if (text == "spring") s = Season::spring;
  else if (text == "summer") s = Season::summer;
  else if (text == "autumn") s = Season::autumn;
  else if (text == "winter") s = Season::winter;
  else throw std::runtime_error{ "bad value for Season" };

  return is;
}

int main()
{
  Season s;
  std::cout << "Enter a season: ";
  std::cin >> s;
  std::cout << "Next season will be " << ++s << "\n";
}