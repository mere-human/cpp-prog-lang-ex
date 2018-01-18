/*
[2] (*2.5) Complete and test Date.
Reimplement it with "number of days after 1/1/1970" representation.
*/

// NOTE: implementation is incomplete and may contain hidden issues

#include <iostream>

namespace Chrono
{
  enum class Month
  {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
  };

  class Date
  {
  public:
    class Bad_date {};

    explicit Date(int dd = {}, Month mm = {}, int yy = {});

    int day() const;
    Month month() const;
    int year() const;

    std::string string_rep() const;
    void char_rep(char s[], int max) const;

    Date& add_day(int n);
    Date& add_month(int n);
    Date& add_year(int n);

  private:
    bool is_valid();
    void to_dmy(int& d, int& m, int& y) const;

    int nd = 0;
  };

  bool is_date(int d, int m, int y);
  bool is_leapyear(int y);
  int max_days(Month m, int y);

  const Date& default_date();

  bool operator==(const Date& a, const Date& b);
  bool operator!=(const Date& a, const Date& b);

  std::ostream& operator<<(std::ostream& os, const Date& d);
  std::istream& operator >> (std::istream& is, Date& d);
}

Chrono::Date::Date(int dd, Month mm, int yy)
{
  if ((dd != 0) && (mm != Month{}) && (yy != 0))
    if (!is_date(dd, static_cast<int>(mm), yy))
      throw Bad_date{};
  // year
  if (yy > 1970)
  {
    int nleaps = 0;
    int first_leap = 1972;
    if (yy > first_leap)
    {
      int last_leap = yy;
      while (!is_leapyear(last_leap))
        --last_leap;
      nleaps = (last_leap - first_leap) / 4;
    }
    nd = nleaps * 366 + (yy - 1970 - nleaps) * 365;
  }
  else
  {
    // TODO
  }
  // month
  if (mm != Month{})
  {
    auto m = Month::jan;
    while (m != mm)
    {
      nd += max_days(m, yy);
      m = static_cast<Month>(static_cast<int>(m) + 1);
    }
  }
  // day
  nd += dd;
}

inline int Chrono::Date::day() const
{
  int d, m, y;
  to_dmy(d, m, y);
  return d;
}

inline Chrono::Month Chrono::Date::month() const
{
  int d, m, y;
  to_dmy(d, m, y);
  return static_cast<Month>(m);
}

inline int Chrono::Date::year() const
{
  int d, m, y;
  to_dmy(d, m, y);
  return y;
}

Chrono::Date& Chrono::Date::add_day(int n)
{
  nd += n;
  return *this;
}

Chrono::Date& Chrono::Date::add_month(int n)
{
  if (n > 0)
  {
    int d, m, y;
    to_dmy(d, m, y);
    int delta_y = n / 12;
    int nm = n % 12;
    while (nm--)
      nd += max_days(static_cast<Month>(m++), y);
    while (delta_y > 0)
      nd += 365 + is_leapyear(y + delta_y);
  }
  else
  {
    // TODO:
  }
  return *this;
}

Chrono::Date& Chrono::Date::add_year(int n)
{
  if (n > 0)
  {
    int d, m, y;
    to_dmy(d, m, y);
    while (n > 0)
      nd += 365 + is_leapyear(y + n--);
  }
  else
  {
    // TODO:
  }
  return *this;
}

bool Chrono::Date::is_valid()
{
  int d, m, y;
  to_dmy(d, m, y);
  return is_date(d, m, y);
}

void Chrono::Date::to_dmy(int& d, int& m, int& y) const
{
  if (nd >= 0)
  {
    y = 1970;
    d = nd;
    int max_yd = 365 + is_leapyear(y);
    while (d > max_yd)
    {
      d -= max_yd;
      max_yd = 365 + is_leapyear(++y);
    }
    m = 1;
    int max_md = max_days(static_cast<Month>(m), y);
    while (d > max_md)
    {
      d -= max_md;
      ++m;
      max_md = max_days(static_cast<Month>(m), y);
    }
    if (d == 0)
      d = 1;
  }
}

bool Chrono::is_date(int d, int m, int y)
{
  if (m < 1 || m > 12)
    return false;
  return 1 <= d && d <= max_days(static_cast<Month>(m), y);
}

bool Chrono::is_leapyear(int y)
{
  if (y % 4 != 0) return false;
  else if (y % 100 != 0) return true;
  else if (y % 400 != 0) return false;
  return true;
}

int Chrono::max_days(Month m, int y)
{
  switch (m)
  {
  case Month::feb:
    return 28 + is_leapyear(y);
  case Month::jan: case Month::mar: case Month::may: case Month::jul:
  case Month::aug: case Month::oct: case Month::nov:
    return 31;
  case Month::apr: case Month::jun: case Month::sep: case Month::dec:
    return 30;
  default:
    return -1;
  }
}

const Chrono::Date& Chrono::default_date()
{
  static Chrono::Date d{ 1, Chrono::Month::jan, 1970 };
  return d;
}

bool Chrono::operator==(const Date& a, const Date& b)
{
  return (a.day() == b.day()) &&
    (a.month() == b.month()) &&
    (a.year() == b.year());
}

bool Chrono::operator!=(const Date& a, const Date& b)
{
  return !(a == b);
}

std::ostream& Chrono::operator<<(std::ostream& os, const Date& d)
{
  os << d.day() << " " << static_cast<int>(d.month()) << " " << d.year();
  return os;
}

std::istream& Chrono::operator >> (std::istream& is, Date& x)
{
  int d, m, y;
  is >> d >> m >> y;
  x = Date{ d, static_cast<Month>(m), y };
  return is;
}

int main()
{
  Chrono::Date d1(2, Chrono::Month::mar, 1971);
  std::cout << d1 << "\n";
  Chrono::Date d;
  std::cout << d << "\n";
  d.add_day(30).add_month(1).add_year(2);
  if (d != Chrono::default_date())
    std::cout << "new date: " << d << "\n";
  std::cout << "leap: " << Chrono::is_leapyear(d.year()) << "\n";
  try
  {
    Chrono::Date d2{ 30, Chrono::Month::feb, 1990 };
  }
  catch (Chrono::Date::Bad_date&)
  {
    std::cout << "error: bad date\n";
  }
  return 0;
}
