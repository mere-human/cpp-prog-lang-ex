#include <iostream>

enum Weekday { sun, mon, tue, wed, thu, fri, sat };

Weekday& operator++(Weekday& wd)
{
  return wd = (wd == sat) ? sun : static_cast<Weekday>(wd + 1);
}

int main()
{
  Weekday wd = mon;
  int n = 8;
  while (--n)
    std::cout << static_cast<int>(++wd) << "\n";
}