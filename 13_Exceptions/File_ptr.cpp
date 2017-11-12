// Example of File_ptr from 13.3 Resource Management


#ifdef _MSC_VER
// define this to avoid MSVC error: fopen may be unsafe
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include <cstdio>
#include <stdexcept>
#include <iostream>

class File_ptr
{
	FILE* _fp;
public:
	File_ptr(const char* file_name, const char* mode)
		: _fp{ fopen(file_name, mode) }
	{
		if (_fp == nullptr)
			throw std::runtime_error{ "File_ptr: Can not open file" };
	}

	// assume ownership
	File_ptr(FILE* fp)
		: _fp{ fp }
	{
		if (_fp == nullptr)
			throw std::runtime_error{ "File_ptr: Invalid file passed" };
	}

	// disallow copying - file is not shared
	File_ptr(const File_ptr&) = delete;
	File_ptr& operator=(const File_ptr&) = delete;

	File_ptr(File_ptr&& other)
		: _fp(other._fp)
	{}

	File_ptr& operator=(File_ptr&& other)
	{
		if (_fp)
		{
			fclose(_fp);
			_fp = nullptr;
		}
		std::swap(_fp, other._fp);
	}

	~File_ptr()
	{
		if (_fp)
			fclose(_fp);
	}

	operator FILE*()
	{
		return _fp;
	}
};

int main()
{
	try
	{
		File_ptr fp("a.tmp", "r");
	}
	catch (std::exception& e)
	{
		std::cerr << "I/O Error: " << e.what() << "\n";
	}

	try
	{
		File_ptr fp("a.tmp", "w+");
		auto c = fgetc(fp);
		std::cout << "Read: " << c << "\n";
	}
	catch (std::exception& e)
	{
		std::cerr << "I/O Error: " << e.what() << "\n";
	}
	return 0;
}