/*
17.3.1 Initialization Without Constructors
*/

#include <iostream>

struct Buf
{
  int count;
  char buf[16*1024];
};

void print(const Buf& b)
{
  std::cout << "count: " << b.count << " buf: " << static_cast<int>(b.buf[0]) << "\n";
}

Buf buf0; // statically allocated, so initalized by default

int main()
{
  Buf buf1; // leave elements uninitialized
  Buf buf2{}; // I really want to zero out those elements
  
  print(buf0);
  print(buf1);
  print(buf2);
}