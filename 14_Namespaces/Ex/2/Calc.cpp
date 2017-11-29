/*
[2] (*2.5) Modify the desk calculator program into a module with a simple
interface specifying calls and potential errors. Don’t expose implemetation
details to users. Don’t make it easy for users to supply bad data. Don’t use
any global using-directives. Keep a record of the mistakes you made. Suggest
ways of avoiding such mistakes in the future.
*/

/*
Sample output:

1/0
Error: divide by 0
~
Error: bad token
(1
Error: ')' expected
*/

#include <iostream> // I/O
#include <sstream>
#include <string>   // strings
#include <map>      // map
#include <cctype>   // isalpha(), etc

using namespace std;

namespace Error {
	class SyntaxError : public std::exception
	{
	public:
		SyntaxError(const char* msg) : std::exception{ msg }
		{}
	};
} // namespace Error

namespace Lexer {

	enum class Kind : char {
		name, number, end,
		plus = '+', minus = '-', mul = '*', div = '/',
		print = ';', assign = '=', lp = '(', rp = ')'
	};

	struct Token {
		Kind kind;
		string string_value;
		double number_value;
	};

	class Token_stream {
	public:
		Token_stream(istream& s) : ip{ &s }, owns{ false } {}
		Token_stream(istream* p) : ip{ p }, owns{ true } {}

		~Token_stream() { close(); }

		Token get();             // read and return next token
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

	Token Token_stream::get()
	{
		char ch;
		do { // skip whitespace except '\n'
			if (!ip->get(ch)) return ct = { Kind::end };
		} while (ch != '\n' && isspace(ch));

		switch (ch) {
		case ';':
		case '\n':
			return ct = { Kind::print };
		case '*':
		case '/':
		case '+':
		case '-':
		case '(':
		case ')':
		case '=':
			return ct = { static_cast<Kind>(ch) };
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
		case '.':
			ip->putback(ch);        // put the first digit (or .) back into the input stream
			*ip >> ct.number_value; // read the number into ct
			ct.kind = Kind::number;
			return ct;
		default:  // name, name =, or error
			if (isalpha(ch)) {
				ct.string_value = ch;
				while (ip->get(ch) && isalnum(ch))
					ct.string_value += ch; // append ch to end of string_value
				ip->putback(ch);
				ct.kind = Kind::name;
				return ct;
			}
			throw Error::SyntaxError{ "bad token" };
		}
	}

} // namespace Lexer

namespace Table {
	map<string, double> table;
} // namespace Table

namespace Parser {

	double prim(bool get);
	double term(bool get);
	double expr(bool);

} // namespace Parser

double Parser::prim(bool get)
{
	if (get) Lexer::ts.get();
	switch (Lexer::ts.current().kind) {
	case Lexer::Kind::number: // floating-point constant
	{
		double v = Lexer::ts.current().number_value;
		Lexer::ts.get();
		return v;
	}
	case Lexer::Kind::name:
	{
		double& v = Table::table[Lexer::ts.current().string_value]; // find the corresponding
		if (Lexer::ts.get().kind == Lexer::Kind::assign) v = expr(true); // '=' seen: assignment
		return v;
	}
	case Lexer::Kind::minus:
		return -prim(true);
	case Lexer::Kind::lp:
	{
		auto e = expr(true);
		if (Lexer::ts.current().kind != Lexer::Kind::rp) throw Error::SyntaxError{ "')' expected" };
		Lexer::ts.get(); // eat ')'
		return e;
	}
	default:
		throw Error::SyntaxError{ "primary expected" };
	}
}

double Parser::term(bool get)
{
	double left = prim(get);
	for (;;) {
		switch (Lexer::ts.current().kind) {
		case Lexer::Kind::mul:
			left *= prim(true);
			break;
		case Lexer::Kind::div:
			if (auto d = prim(true)) {
				left /= d;
				break;
			}
			throw Error::SyntaxError{ "divide by 0" };
		default:
			return left;
		}
	}
}

double Parser::expr(bool get)
{
	double left = term(get);
	for (;;) { // forever
		switch (Lexer::ts.current().kind) {
		case Lexer::Kind::plus:
			left += term(true);
			break;
		case Lexer::Kind::minus:
			left -= term(true);
			break;
		default:
			return left;
		}
	}
	return left;
}

namespace Driver {

	int process()
	{
		int no_of_errors = 0;
		for (;;) {
			try
			{
				Lexer::ts.get();
				if (Lexer::ts.current().kind == Lexer::Kind::end) break;
				if (Lexer::ts.current().kind == Lexer::Kind::print) continue;
				cout << Parser::expr(false) << "\n";
			}
			catch (Error::SyntaxError& e)
			{
				++no_of_errors;
				std::cerr << "Error: " << e.what() << "\n";
			}
		}
		return no_of_errors;
	}
} // namespace Driver

int main(int argc, char* argv[])
{
	switch (argc) {
	case 1: // read from standard input
		break;
	case 2:
		Lexer::ts.set_input(new istringstream{ argv[1] });
		break;
	default:
		std::cerr << "too many arguments\n";
		return 1;
	}

	Table::table["pi"] = 3.141592; // insert predefined names
	Table::table["e"] = 2.711828;

	return Driver::process();
}
