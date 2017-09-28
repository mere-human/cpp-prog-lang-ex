/*
[16] (*3) Write a macro processor that defines and expands simple macros (like the C preprocessor does).
Read from cin and write to cout.
At first, don’t try to handle macros with arguments.
Hint: The desk calculator (§10.2) contains a symbol table and a lexical analyzer that
you could modify.
*/

#include <iostream> // I/O
#include <sstream>
#include <string>   // strings
#include <map>      // map
#include <cctype>   // isalpha(), etc

using namespace std;

enum class Kind : char {
	name, def, print, ws, end
};

struct Token {
	Kind kind;
	string value;
};

class Token_stream {
public:
	Token_stream(istream& s) : ip{ &s }, owns{ false } {}
	Token_stream(istream* p) : ip{ p }, owns{ true } {}

	~Token_stream() { close(); }

	void get();             // read and return next token
	const Token& current()   // most recently read token
	{
		return ct;
	}

	void set_input(istream& s)
	{
		close();
		ip = &s;
		owns = false;
	}

	void set_input(istream* p)
	{
		close();
		ip = p;
		owns = true;
	}

private:
	void close() { if (owns) delete ip; }

	istream* ip;            // pointer to an input stream
	bool owns;              // does the Token_stream own the istream?
	Token ct{ Kind::end };  // current token
};

Token_stream ts{ cin }; // use input from cin
int no_of_errors;
map<string, string> table;

void error(const string& s)
{
	no_of_errors++;
	cerr << "error: " << s << "\n";
}

void Token_stream::get()
{
	ct = { Kind::end };
	char ch;
	while (true)
	{
		if (!ip->get(ch))
			return;
		if (isspace(ch))
			ct.value.push_back(ch);
		else
			break;
	}

	if (!ct.value.empty())
	{
		ip->putback(ch);
		ct.kind = Kind::ws;
		return;
	}

	switch (ch) {
	case '#':
		*ip >> ct.value;
		if (ct.value == "define")
			ct.kind = Kind::def;
		else
			ct.kind = Kind::print;
		ct.value.insert(0, 1, ch);
		break;
	default:
		if (isalpha(ch))
		{
			ct.value = ch;
			while (ip->get(ch) && isalnum(ch))
				ct.value += ch;
			ip->putback(ch);
			ct.kind = Kind::name;
		}
		else
		{
			ip->putback(ch);
			*ip >> ct.value;
			ct.kind = Kind::print;
		}
		break;
	}
}

string prim(bool get)
{
	if (get)
		ts.get();
	switch (ts.current().kind) {
	case Kind::name:
	{
		auto it = table.find(ts.current().value);
		if (it == table.end())
			return ts.current().value;
		else
			return it->second;
	}
	case Kind::def:
	{
		string text = ts.current().value;

		ts.get();
		text += ts.current().value;
		if (ts.current().kind != Kind::ws)
		{
			error("whitespace expected");
			return text;
		}

		ts.get();
		auto name = ts.current().value;
		text += name;
		if (ts.current().kind != Kind::name)
		{
			error("name expected");
			return text;
		}

		ts.get();
		text += ts.current().value;
		if (ts.current().kind != Kind::ws)
		{
			error("whitespace expected");
			return text;
		}

		ts.get();
		text += ts.current().value;
		if (ts.current().kind != Kind::print)
		{
			error("define body expected");
			return text;
		}
		else
		{
			table[name] = ts.current().value;
			return "";
		}
	}
	default:
		error("primary expected");
		return ts.current().value;
	}
	
}

void process()
{
	for (;;) {
		ts.get();
		switch (ts.current().kind)
		{
		case Kind::end:
			return;
		case Kind::ws:
		case Kind::print:
			cout << ts.current().value;
			break;
		default:
			cout << prim(false);
		}
	}
}

int main(int argc, char* argv[])
{
	//switch (argc) {
	//case 1: // read from standard input
	//	break;
	//case 2:
	//	ts.set_input(new istringstream{ argv[1] });
	//	break;
	//default:
	//	error("too many arguments");
	//	return 1;
	//}

	string text =
		"#define A 22\n"
		"#include <stdio.h>\n"
		"int main() {\n"
		"  printf(\"%d\", A);\n"
		"}\n";
	ts.set_input(new istringstream{ text });

	// TODO: insert predefined names

	process();

	return no_of_errors;
}