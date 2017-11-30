/*
[9] (*2.5) Write a function to invert a two-dimensional array. Hint: §7.4.2
*/

#include <string>
#include <iostream>

constexpr int n2 = 5;

void invert(int arr[][n2], int n1)
{
  for (int i = 0; i != n1; ++i)
  {
    for (int j = 0; j != n2; ++j)
    {
      arr[i][j] = ~arr[i][j];
    }
  }
}

void print(int arr[][n2], int n1)
{
  for (int i = 0; i != n1; ++i)
  {
    for (int j = 0; j != n2; ++j)
    {
      std::cout << arr[i][j] << " ";
    }
    std::cout << "\n";
  }
}

int main()
{
  constexpr int n1 = 3;

  int v[n1][n2] = {
    { 0,1,2,3,4 },{ 10,11,12,13,14 },{ 20,21,22,23,24 }
  };

  print(v, n1);
  invert(v, n1);
  print(v, n1);
}