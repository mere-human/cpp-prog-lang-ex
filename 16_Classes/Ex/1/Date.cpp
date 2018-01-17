/*
[1] (*1) Find the error in Date::add_year() in §16.2.3.
Then find two additional errors in the version in §16.2.10.
*/

#include <iostream>

class Date
{
  int d, m, y;
public:
  explicit Date(int dd = 0, int mm = 0, int yy = 0)
  {
    d = dd ? dd : 1;
    m = mm ? mm : 1;
    y = yy ? yy : 1970;
  }

  int day() const { return d; }
  int month() const { return m; }
  int year() const { return y; }

  static bool leap_year(int n)
  {
    if (n % 4 != 0) return false;
    else if (n % 100 != 0) return true;
    else if (n % 400 != 0) return false;
    return true;
  }

  void add_day(int n)
  {
    // TODO: proper implementation which considers year change and leap year
    d += n;
  }
  void add_month(int n)
  {
    // TODO: proper implementation which considers year change and leap year
    m += n;
  }
  void add_year(int n)
  {
    int yy = y + n;
    if (d == 29 && m == 2 && !leap_year(yy))
    {
      d = 1;
      m = 3;
    }
    if (yy == 0)
    {
      // AD 1 immediately follows the year 1 BC
      if (yy > y)
        yy = 1;
      else
        yy = -1;
    }
    y = yy;
  }
};

int main()
{
  Date d{ 1, 1, 100 };
  d.add_year(-100);
  std::cout << "new date: " << d.day() << "." << d.month() << "." << d.year() << "\n";
  Date d2{ 29, 2, 2020 };
  d2.add_year(3);
  std::cout << "new date: " << d2.day() << "." << d2.month() << "." << d2.year() << "\n";
  return 0;
}