/*
[4] (∗2.5) Take the basic operations for opening, closing, reading, and writing
from the C interface to your operating system and provide equivalent C++
functions that call the C functions but throw exceptions in case of errors.
*/

#ifdef _MSC_VER
// define this to avoid MSVC error: fopen may be unsafe
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include <cstdio>
#include <exception>
#include <iostream>
#include <sstream>

struct IOException
{
	const std::string message;
};

FILE* open_file(const char* file_name, const char* mode)
{
    auto fp = fopen(file_name, mode);
	if (!fp)
	{
		std::ostringstream buffer;
		buffer << "failed to open file '" << file_name
                        << "' with mode '" << mode << "'";
		throw IOException{ buffer.str() };
	}
    return fp;
}

void close_file(FILE* fp)
{
	if (fclose(fp) != 0)
		throw IOException{ "error while closing a file" };
}

char read_char(FILE* fp)
{
	int c = fgetc(fp);
	if (c == EOF)
	{
		if (feof(fp))
			throw IOException{ "end of file reached while reading" };
		else
			throw IOException{ "failed to read" };
	}
	if ((c > CHAR_MAX) || (c < CHAR_MIN))
	{
		std::ostringstream buffer;
		buffer << c << " character is out of range";
		throw IOException{ buffer.str() };
	}
	return static_cast<char>(c);
}

void write_char(FILE* fp, char ch)
{
	auto res = fputc(ch, fp);
	if (res != ch)
	{
		if (res == EOF)
			throw IOException{ "failed to write" };
		else
			throw IOException{ "unkown error while writing" };
	}
}

int main()
{
	// NOTE: it is better to use RAII solution like File_ptr
    try
    {
        auto fp = open_file("a.tmp", "r");
        close_file(fp); // unreachable
    }
    catch (IOException& e)
    {
        std::cerr << "I/O Error: " << e.message << "\n";
    }

	FILE* fp = nullptr;
	try
	{
		fp = open_file("a.tmp", "w+");
		auto c = read_char(fp);
		std::cout << "Read: " << c << "\n"; // unreachable
	}
	catch (IOException& e)
	{
		std::cerr << "I/O Error: " << e.message << "\n";
	}
	if (fp)
		close_file(fp);
    return 0;
}

