/*
17.4.5 static Member Initialization
*/

#include <cmath>

class Curious
{
public:
  static const int c1 = 7; // OK
  //static int c2 = 11; // error : not const
  const int c3 = 13; // OK, but not static (§17.4.4)
  //static const int c4 = std::sqrt(9); // error : in-class initializer not constant
  //static const float c5 = 7.0; // error : in-class not integral (use constexpr rather than const)
  static constexpr float c5 = 7.0;
};

int main()
{
  Curious c;
}