// [7] (*2.5) Write a program that strips comments out of a C++ program. That is, read from cin,
// remove both // comments and /* */ comments, and write the result to cout. Do not worry
// about making the layout of the output look nice (that would be another, and much harder,
// exercise). Do not worry about incorrect programs. Beware of //, /*, and */ in comments,
// strings, and character constants.

#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <input_file>\n";
		return 1;
	}

	const char* in_file_name = argv[1];
	std::ifstream in_stream(in_file_name);
	if (!in_stream)
	{
		std::cerr << "Error: Failed to open " << in_file_name << "\n";
		return 1;
	}

	auto& out_stream = std::cout;

	enum class state_type
	{
		text,
		comment,
		multi_comment,
		string
	};
	auto state = state_type::text;

	char ch = 0, prev_ch = 0;
	while (in_stream.get(ch))
	{
		// change state
		switch (ch)
		{
		case '/':
			if (prev_ch == '/')
			{
				if (state == state_type::text)
					state = state_type::comment;
			}
			else if (prev_ch == '*')
			{
				if (state == state_type::multi_comment)
				{
					state = state_type::text;
					ch = 0;
					prev_ch = 0;
				}
			}
			break;

		case '*':
			if (prev_ch == '/')
			{
				if (state == state_type::text)
					state = state_type::multi_comment;
			}
			break;

		case '"':
			switch (state)
			{
			case state_type::comment:
			case state_type::multi_comment:
				break;
			case state_type::string:
				state = state_type::text;
				break;
			default:
				state = state_type::string;
				break;
			}
			break;

		case '\n':
			if (state == state_type::comment)
			{
				state = state_type::text;
				prev_ch = 0;
			}
			break;

		default:
			break;
		}

		// write output
		switch (state)
		{
		case state_type::string:
		case state_type::text:
			if (prev_ch)
				out_stream << prev_ch;
			break;
		default:
			break;
		}

		prev_ch = ch;
	}

	// write last character
	if ((state != state_type::comment) && (state != state_type::multi_comment))
		if (prev_ch)
			out_stream << prev_ch;

	return 0;
}