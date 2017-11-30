/*
[7](*2) Implement and test these functions : strlen(), which returns the length of a C - style string;
strcpy(), which copies a C - style string into another; and strcmp(), which compares two C - style
strings.Consider what the argument types and return types ought to be.Then compare your
functions with the standard library versions as declared in <cstring>(<string.h>) and as specified in §43.4.
*/

#include <iostream>
#include <cassert>
#include <cstring>

int my_strlen(const char* str)
{
  int len = 0;
  while (str && *str)
  {
    ++str;
    ++len;
  }
  return len;
}

char* my_strcpy(const char* src, char* dst)
{
  auto dst_beg = dst;
  if (src && dst)
    while (*src)
      *dst++ = *src++;
  return dst_beg;
}

int my_strcmp(const char* str1, const char* str2)
{
  auto n1 = my_strlen(str1);
  auto n2 = my_strlen(str2);
  auto diff = n1 - n2;
  if (diff != 0) return diff > 0 ? 1 : -1;
  while (*str1 && *str2)
  {
    if (*str1 > *str2)
      return 1;
    else if (*str1 < *str2)
      return -1;
    ++str1;
    ++str2;
  }
  return 0;
}

void test_strcpy(const char* str)
{
  static char buffer[10];
  if (str)
    assert(strcmp(str, my_strcpy(str, buffer)) == 0);
}

void test_strcmp(const char* str1, const char* str2)
{
  assert(my_strcmp(str1, str2) == strcmp(str1, str2));
}

int main()
{
  assert(my_strlen(nullptr) == 0);
  assert(my_strlen("") == 0);
  assert(my_strlen("1") == 1);
  assert(my_strlen("333") == 3);
  assert(my_strlen("  \n") == 3);

  test_strcpy(nullptr);
  test_strcpy("");
  test_strcpy("1");
  test_strcpy("10");
  test_strcpy("\td");

  test_strcmp("", "");
  test_strcmp("a", "a");
  test_strcmp("A", "a");
  test_strcmp("a", "A");
  test_strcmp("a", "ab");
  test_strcmp("ab", "a");
  return 0;
}