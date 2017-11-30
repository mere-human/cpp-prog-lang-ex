/*
[21] (*2) Write functions to add one day, one month, and one year to a Date as defined in §X.9[4].
Write a function that gives the day of the week for a given Date. Write a function that gives
the Date of the first Monday following a given Date.
*/

#include <iostream>
#include <algorithm>

enum Month : int
{
  Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};

enum class WeekDay
{
  Mon, Tue, Wed, Thu, Fri, Sat, Sun
};

const char* to_string(WeekDay wd)
{
  switch (wd)
  {
  case WeekDay::Mon:
    return "mon";
  case WeekDay::Tue:
    return "tue";
  case WeekDay::Wed:
    return "wed";
  case WeekDay::Thu:
    return "thu";
  case WeekDay::Fri:
    return "fri";
  case WeekDay::Sat:
    return "sat";
  case WeekDay::Sun:
    return "sun";
  default:
    return "";
  }
}

struct Date
{
  Month month;
  int day;
  int year;
};

Date get_date(int day, int month, int year)
{
  return{ static_cast<Month>(month), day, year };
}

void print_date(const Date& d)
{
  std::cout << d.day << "/" << static_cast<int>(d.month) << "/" << d.year;
}

bool is_leap_year(int y)
{
  if ((y % 4) == 0)
  {
    if (((y % 100) != 0) || ((y % 400) == 0))
      return true;
  }
  return false;
}

int get_max_days(Month m, int y)
{
  switch (m)
  {
  case Month::Jan:
  case Month::Mar:
  case Month::May:
  case Month::Jul:
  case Month::Aug:
  case Month::Oct:
  case Month::Dec:
    return 31;
  case Month::Feb:
    return is_leap_year(y) ? 29 : 28;
  default:
    return 30;
  }
}

void add_year(Date& d)
{
  ++d.year;
}

Month next_month(const Month month)
{
  return (month == Month::Dec) ?
    Month::Jan :
    static_cast<Month>(static_cast<int>(month) + 1);
}

void add_month(Date& d)
{
  d.month = next_month(d.month);
  if (d.month == Month::Jan)
    add_year(d);
}

int days_from_year_start(const Date d)
{
  int n = 0;
  for (auto i = Month::Jan; i != d.month; i = next_month(i))
    n += get_max_days(i, d.year);
  n += d.day;
  return n;
}

bool is_less(const Date d1, const Date d2)
{
  if (d1.year == d2.year)
  {
    if (d1.month == d2.month)
      return d1.day < d2.day;
    return d1.month < d2.month;
  }
  return d1.year < d2.year;
}

int days_diff(const Date d1, const Date d2)
{
  int n = 0;
  const auto& mind = is_less(d1, d2) ? d1 : d2;
  const auto& maxd = is_less(d1, d2) ? d2 : d1;
  for (int y = maxd.year; y != mind.year; --y)
    n += is_leap_year(y) ? 366 : 365;
  n += days_from_year_start(maxd) - days_from_year_start(mind);
  return n;
}

WeekDay get_week_day(const Date d)
{
  // 5.09.2016 is monday
  // 2016 is a leap year
  static const auto anchor_date = get_date(5, 9, 2016);
  auto diff = days_diff(anchor_date, d);
  return static_cast<WeekDay>((diff + 1)% 7);
}

void add_day(Date& d)
{
  ++d.day;
  if (d.day > get_max_days(d.month, d.year))
    add_month(d);
}

int main()
{
  auto d = get_date(17, 9, 2016); // Fri
  std::cout << is_leap_year(d.year) << "\n" << to_string(get_week_day(d));
  //add_day(d);
  //print_date(d);
}