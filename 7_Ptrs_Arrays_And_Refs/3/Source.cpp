/*
[3] (∗1) Use an alias (using) to define the types unsigned char, const unsigned char, pointer to
integer, pointer to pointer to char, pointer to array of char, array of 7 pointers to int, pointer to
an array of 7 pointers to int, and array of 8 arrays of 7 pointers to int.
*/

#include <iostream>

int main()
{
  using uc_t = unsigned char;
  using cuc_t = const unsigned char;
  using pi_t = int*; // pointer to integer
  using ppc_t = char**; // pointer to pointer to char
  using pac_t = char(*)[3]; // pointer to array of char
  using api_t = int*[3]; // array of 7 pointers to int
  using papi_t = int*(*)[3]; // pointer to an array of 7 pointers to int
  using arrr_t = api_t[2]; //  array of 8 arrays of 7 pointers to int

  char ca[] = { 'a', 'b', 'c' };
  pac_t pca = &ca;
  std::cout << (*pca)[1] << "\n";

  int a = 1, b = 2;
  api_t ap = { &a,&b, &b };
  std::cout << *ap[2] << "\n";

  papi_t apa = &ap;
  std::cout << *(*apa)[2] << "\n";

  arrr_t appa = { { &a, &b, &b }, { &b, &b, &a } };
  std::cout << *appa[1][2] << "\n";
}