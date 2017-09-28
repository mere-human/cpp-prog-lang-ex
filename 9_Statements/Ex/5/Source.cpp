/*
[5] (∗2) Write a function itoa(int i, char b[]) that creates a string representation of i in b and
returns b.
[6] Modify iota() from the previous exercise to take an extra "string length" argument to make
overflow less likely
*/

#include <cassert>
#include <cstring>

char* my_itoa(int i, char b[], size_t len)
{
	// convert digits
	int rank = 0;
	char* p = b;
	do
	{
		int digit = i % 10;
		*p++ = '0' + digit;
		i /= 10;
		++rank;
	} while (i && p != (b + len));
	
	// reverse
	if (rank > 1)
	{
		p = b;
		char* e = p + rank - 1;
		int n = rank / 2;
		while (n--)
		{
			// swap & advance
			auto tmp = *e;
			*e-- = *p;
			*p++ = tmp;
		}
	}
	return b;
}

int main()
{
	char buf[10] = { 0 };
	constexpr auto len = sizeof(buf) / sizeof(*buf);
	assert(std::strcmp(my_itoa(0, buf, len), "0") == 0);
	assert(std::strcmp(my_itoa(1, buf, len), "1") == 0);
	assert(std::strcmp(my_itoa(10, buf, len), "10") == 0);
	assert(std::strcmp(my_itoa(123, buf, len), "123") == 0);
	assert(std::strcmp(my_itoa(42564983, buf, len), "42564983") == 0);
	buf[3] = '\0';
	assert(std::strcmp(my_itoa(12300, buf, 3), "300") == 0);
}