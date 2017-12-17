/*
[3] (*2.5) Write a program that reads a source file and writes out the names of files #included.
Indent file names to show files #included by included files. Try this program on some real
source files (to get an idea of the amount of information included).
*/

#include <iostream>
# include <fstream>
#include <string>

// TODO: check #include in comments

enum class Token
{
	end,
	word,
	newline,
	comment_begin,
	multicomment_begin,
	multicomment_end,
	hash
};

Token read_token(std::istream& is, std::string& str)
{
	// skip whitespaces except '\n'
	char ch;
	do
	{
		if (!is.get(ch))
			return Token::end;
	}
	while (ch != '\n' && isspace(ch));

	switch (ch)
	{
	case '\n':
		return Token::newline;
	case '/':
		if (is.get(ch))
		{
			if (ch == '*')
				return Token::multicomment_begin;
			else if (ch == '/')
				return Token::comment_begin;
			str += '/';
			is.putback(ch);
		}
		break;
	case '*':
		if (is.get(ch))
		{
			if (ch == '/')
				return Token::multicomment_end;
			str += '*';
			is.putback(ch);
		}
	case '#':
		return Token::hash;
	default:
		is.putback(ch);
		break;
	}
	is >> str;
	return Token::word;
}

const char* to_string(Token t)
{
	switch (t)
	{
	case Token::word:
		return "<W>";
	case Token::newline:
		return "<NL>";
	case Token::comment_begin:
		return "//";
	case Token::multicomment_begin:
		return "/*";
	case Token::multicomment_end:
		return "*/";
	case Token::hash:
		return "#";
	default:
		return "<unknown>";
	}
}

bool is_comment(Token t)
{
	return (t == Token::comment_begin) || (t == Token::multicomment_begin);
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: expected file name\n";
		return 1;
	}

	std::ifstream is(argv[1]);
	if (!is)
	{
		std::cerr << "Error: failed to read file " << argv[1] << "\n";
		return 1;
	}

	// read
	bool include = false;
	Token state = Token::end;
	while (true)
	{
		std::string str;
		auto t = read_token(is, str);

		//std::cout << to_string(t) << ":" << str;
		//if (t == Token::newline)
		//	std::cout << "\n";

		if (t == Token::end)
		{
			break;
		}
		else if (t == Token::comment_begin)
		{
			if (state != Token::multicomment_begin)
				state = Token::comment_begin;
		}
		else if (t == Token::multicomment_begin)
		{
			if (state != Token::comment_begin)
				state = Token::multicomment_begin;
		}
		else if (t == Token::newline)
		{
			if (state == Token::comment_begin)
				state = Token::end;
		}
		else if (t == Token::hash)
		{
			if ((state != Token::comment_begin) && (state != Token::multicomment_begin))
				state = Token::hash;
		}
		else if (t == Token::multicomment_end)
		{
			if (state == Token::multicomment_begin)
				state = Token::end;
		}
		else if (t == Token::word)
		{
			if (include)
			{
				std::cout << str << "\n";
				include = false;
			}
			else
			{
				if ((state == Token::hash) && (str == "include"))
					include = true;
			}
		}
	}

	return 0;
}