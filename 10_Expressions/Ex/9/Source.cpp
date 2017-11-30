/*
[9] (*2) Write a function cat() that takes two C-style string arguments and returns a string that is
the concatenation of the arguments. Use new to find store for the result.
*/

#define _CRT_SECURE_NO_WARNINGS 1

#include <cassert>
#include <cstring>

char* cat(const char* str1, const char* str2)
{
  const auto len1 = std::strlen(str1);
  const auto len2 = std::strlen(str2);
  if (auto new_len = len1 + len2)
  {
    char* new_str = new char[new_len + 1];
    std::strcpy(new_str, str1);
    std::strcpy(new_str + len1, str2);
    return new_str;
  }
  return nullptr;
}

int main()
{
  char* str = cat("", "");
  assert(str == nullptr);

  str = cat("a", "b");
  assert(std::strcmp(str, "ab") == 0);
  delete str;

  str = cat("ab", "cd");
  assert(std::strcmp(str, "abcd") == 0);
  delete str;
}