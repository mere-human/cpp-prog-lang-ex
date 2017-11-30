/*
[9] (∗1) Define functions f(char), g(char&), and h(const char&). Call them with the arguments 'a',
49, 3300, c, uc, and sc, where c is a char, uc is an unsigned char, and sc is a signed char.
Which calls are legal? Which calls cause the compiler to introduce a temporary variable?
*/

#include <iostream>

void f(char)
{
  std::cout << "f(char)\n";
}

void g(char&)
{
  std::cout << "g(char&)\n";
}

void h(const char&)
{
  std::cout << "h(const char&)\n";
}

int main()
{
  f('a');
  //g('a'); // error
  h('a');

  f(49);
  //g(49); // error
  h(49);

  f(3300);
  //g(3300); // error
  h(3300);

  char c = 'r';
  unsigned char uc = 'g';
  signed char sc = 'b';

  f(c);
  g(c);
  h(c);

  f(uc);
  //g(uc); // error
  h(uc);

  f(sc);
  //g(sc); // error
  h(sc);
}