/*
[2] (*2) Allocate so much memory using new that bad_alloc is thrown.
Report how much memory was allocated and how much time it took.
Do this twice: once not writing to the allocated memory and once writing to each element.
*/

// Debug, no write:     1,928,886 KB
// Debug, write:        1,928,860 KB
// Release, no write:   2,042,067 KB
// Release, write:      2,042,003 KB
// Debug x64, no write: 14,486,643 KB

#include <exception>
#include <iostream>

int main()
{
	int block_size = 1024;
	int n = 0;
	try
	{
		while (true)
		{
			char* p = new char[block_size];
			//// write to the memory
			//for (int i = 0; i != block_size; ++i)
			//	p[i] = 'a' + i;
			n++;
		}
	}
	catch (std::bad_alloc&)
	{
		std::cout << "Mem: " << n << " KB\n";
	}
}