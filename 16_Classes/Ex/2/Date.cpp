/*
[2] (*2.5) Complete and test Date.
Reimplement it with "number of days after 1/1/1970" representation.
*/

#include <iostream>

namespace Chrono
{
  enum class Month
  {
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
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
    int d, y;
    Month m;
  };

  bool is_date(int d, int m, int y);
  bool is_leapyear(int y);

  const Date& default_date();

  bool operator==(const Date& a, const Date& b);
  bool operator!=(const Date& a, const Date& b);

  std::ostream& operator<<(std::ostream& os, const Date& d);
  std::istream& operator>>(std::istream& is, Date& d);
}

Chrono::Date::Date(int dd, Month mm, int yy)
  : d{ dd }, m{ mm }, y{ yy }
{
  if (d == 0) d = default_date().day();
  if (m == Month{}) m = default_date().month();
  if (y == 0) y = default_date().year();

  if (!is_valid()) throw Bad_date{};
}

inline int Chrono::Date::day() const
{
  return d;
}

inline Chrono::Month Chrono::Date::month() const
{
  return m;
}

inline int Chrono::Date::year() const
{
  return y;
}

Chrono::Date& Chrono::Date::add_day(int n)
{
  // TODO: provide proper implementation
  d += n;
  return *this;
}

Chrono::Date& Chrono::Date::add_month(int n)
{
  if (n == 0)
    return *this;

  if (n > 0)
  {
    int delta_y = n / 12; // number of full years
    int mm = static_cast<int>(m) + n % 12; // number of months ahead
    if (mm > 12) // note: dec is represented as 12
    {
      ++delta_y;
      mm -= 12;
    }
    // TODO: handle cases when the month mm does not have a day d
    y += delta_y;
    m = static_cast<Month>(mm);
  }
  // TODO: handle negative n
  return *this;
}

Chrono::Date& Chrono::Date::add_year(int n)
{
  int yy = y + n;
  if (d == 29 && m == Month::feb && !is_leapyear(yy))
  {
    d = 1;
    m = Month::mar;
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
  return *this;
}

bool Chrono::Date::is_valid()
{
  return is_date(d, static_cast<int>(m), y);
}

bool Chrono::is_date(int d, int m, int y)
{
  if (m < 1 || m > 12)
    return false;

  int ndays;
  switch (static_cast<Month>(m))
  {
  case Month::feb:
    ndays = 28 + is_leapyear(y);
    break;
  case Month::jan: case Month::mar: case Month::may: case Month::jul:
  case Month::oct: case Month::aug: case Month::nov:
    ndays = 31;
    break;
  default:
    ndays = 30;
    break;
  }
  return 1 <= d && d <= ndays;
}

bool Chrono::is_leapyear(int y)
{
  if (y % 4 != 0) return false;
  else if (y % 100 != 0) return true;
  else if (y % 400 != 0) return false;
  return true;
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

std::istream& Chrono::operator>>(std::istream& is, Date& x)
{
  int d, m, y;
  is >> d >> m >> y;
  x = Date{ d, static_cast<Month>(m), y };
  return is;
}

int main()
{
  Chrono::Date d;
  std::cout << d << "\n";
  d.add_day(30).add_month(1).add_year(2);
  if (d != Chrono::default_date())
    std::cout << "new date: " << d << "\n";
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