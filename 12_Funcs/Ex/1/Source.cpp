/*
[1] (*1) Write declarations for the following: a function taking arguments of type pointer to character and reference to integer and returning no value; a pointer to such a function; a function
taking such a pointer as an argument; and a function returning such a pointer. Write the definition of a function that takes such a pointer as an argument and returns its argument as the
return value. Hint: Use a type alias (using).
*/

#include <iostream>

void f1(char* p, int& n)
{
  std::cout << __FUNCTION__ << " " << p[n] << "\n";
}

using pf1 = void(*)(char*, int&);

void f2(pf1 f)
{
}

pf1 f3()
{
  return f1;
}

pf1 f4(pf1 f)
{
  return f;
}

int main()
{
  char p[] = "abcd";
  int n = 1;
  f4(&f1)(p, n);

  return 0;
}