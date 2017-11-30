/*
[4] (*1.5) Write a program that reads an arbitrary number (possibly limited to some maximum
number) of files whose names are given as command-line arguments and writes them one
after another on cout. Because this program concatenates its arguments to produce its output,
you might call it cat
*/

// Sample launch:
// Test E:\Development\cpp\edu\Cpp_PL_Stroustrup_4ed\Test\12_Funcs\Constexpr.cpp E:\Development\cpp\edu\Cpp_PL_Stroustrup_4ed\Test\12_Funcs\Ptrs.cpp

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv)
{
  for (int i = 1; i != argc; ++i)
  {
    std::string buf;
    std::ifstream file(argv[i]);
    while (std::getline(file, buf))
      std::cout << buf << "\n";
  }
}