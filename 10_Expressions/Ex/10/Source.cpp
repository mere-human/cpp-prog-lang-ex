/*
[10] (*2) Write a function rev() that takes a C-style string argument and reverses the characters in
it. That is, after rev(p) the last character of p will be the first, etc.
*/

#include <cstring>
#include <cassert>

void rev(char* p)
{
	auto len = std::strlen(p);
	char* e = p + len - 1;
	int n = len / 2;
	while (n--)
	{
		auto tmp = *e;
		*e-- = *p;
		*p++ = tmp;
	}
}

int main()
{
	{
		char p[] = "a";
		rev(p);
		assert(strcmp(p, "a") == 0);
	}
	{
		char p[] = "ab";
		rev(p);
		assert(strcmp(p, "ba") == 0);
	}
	{
		char p[] = "abc";
		rev(p);
		assert(strcmp(p, "cba") == 0);
	}
	{
		char p[] = "abcd";
		rev(p);
		assert(strcmp(p, "dcba") == 0);
	}
}