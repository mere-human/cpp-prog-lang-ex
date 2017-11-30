/*
[20] (*1) Write a factorial function that does not use recursion.
*/

#include <iostream>

int fact_iter(int n)
{
  int res = 1;
  for (int i = 2; i <= n; ++i)
  {
    res *= i;
  }
  return res;
}

int fact_recr(int n)
{
  return n <= 1 ? 1 : n * fact_recr(n - 1);
}

int main()
{
  for (int i = 0; i <= 10; ++i)
  {
    std::cout << fact_recr(i) << " " << fact_iter(i) << "\n";
  }
  return 0;
}