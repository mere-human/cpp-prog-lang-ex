/*
[6] (*1) Write a loop that computes the sum of a Vector as defined in 13-5
without examining the size of the Vector. Why is this a bad idea?
*/

#include "../5/Vector.h"
#include <iostream>

int main()
{
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(5);
  // This is inefficient.
  // Exception handling is error handling.
  // Exception handling is an alternative flow to a normal one
  // and imposes performance overhead.
  int sum = 0;
  try
  {
    int i = 0;
    while (true)
      sum += v.at(i++);
  }
  catch (RangeException&)
  {
    std::cout << "sum is " << sum;
  }
  return 0;
}