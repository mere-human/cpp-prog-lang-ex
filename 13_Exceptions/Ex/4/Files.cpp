/*
[4] (∗2.5) Take the basic operations for opening, closing, reading, and writing
from the C interface to your operating system and provide equivalent C++
functions that call the C functions but throw exceptions in case of errors.
*/

#include <cstdio>
#include <exception>
#include <iostream>

struct IOException : public std::exception
{
    IOException(const char* const message) : std::exception{message}
    {}
};

FILE* open_file(const char* file_name, const char* mode)
{
    auto fp = fopen(file_name, mode);
    if (!fp) throw IOException{"failed to open file"};
    return fp;
}

void close_file(FILE* fp)
{
    if (ferror(fp)) throw IOException{"file contains errors"};
    if (fclose(fp) != 0) throw IOException{"failed to close file"};
}

int main()
{
    try
    {
        auto fp = open_file("foo", "r");
        close_file(fp);
    }
    catch (IOException& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}

