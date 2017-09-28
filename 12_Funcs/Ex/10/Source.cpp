/*
[10] (*2) Write an encryption program that reads from cin and writes the encoded characters to
cout. You might use this simple encryption scheme: the encrypted form of a character c is
c^key[i], where key is a string passed as a command-line argument. The program uses the
characters in key in a cyclic manner until all the input has been read. Re-encrypting encoded
text with the same key produces the original text. If no key (or a null string) is passed
, then no encryption is done.
*/

#include <iostream>
#include <fstream>
#include <string>

// Typical usage:
//  encode: <prog> password lorem_ipsum.txt enc.txt
//  decode: <prog> password enc.txt dec.txt

int main(int argc, char** argv)
{
	std::string key;
	std::string input_file, output_file;
	if (argc == 4)
	{
		key = argv[1];
		input_file = argv[2];
		output_file = argv[3];
	}
	else
	{
		std::cerr << "Error: wrong amount of arguments\n";
		return 1;
	}

	// Streams should use binary mode because encoding produce non-printable characters
	// which can cause troubles while reading.
	std::ifstream input_stream(input_file, std::ios::binary);
	std::ofstream output_stream(output_file, std::ios::binary);

	int i = 0;
	char c;
	while (input_stream.get(c))
	{
		c = key[i++] ^ c;
		if (i == key.length())
			i = 0;
		output_stream.put(c);
	}

	return 0;
}