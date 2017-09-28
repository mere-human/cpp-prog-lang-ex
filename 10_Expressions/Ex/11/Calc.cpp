/*
[11] (*2) Type in the calculator example and get it to work. Do not "save time" by using an
already entered text. You’ll learn most from finding and correcting "little silly errors".
*/

#include <iostream> // I/O
#include <sstream>
#include <string>   // strings
#include <map>      // map
#include <cctype>   // isalpha(), etc

using namespace std;

enum class Kind : char {
	name, number, end,
	plus = '+', minus = '-', mul = '*', div = '/', print = ';', assign='=', lp='(', rp=')'
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
int no_of_errors;
map<string, double> table;

double error(const string& s)
{
	no_of_errors++;
	cerr << "error: " << s << "\n";
	return 1;
}

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
		error("bad token");
		return ct = { Kind::print };
	}
}

double expr(bool);

double prim(bool get)
{
	if (get) ts.get();
	switch (ts.current().kind) {
	case Kind::number: // floating-point constant
	{
		double v = ts.current().number_value;
		ts.get();
		return v;
	}
	case Kind::name:
	{
		double& v = table[ts.current().string_value]; // find the corresponding
		if (ts.get().kind == Kind::assign) v = expr(true); // '=' seen: assignment
		return v;
	}
	case Kind::minus:
		return -prim(true);
	case Kind::lp:
	{
		auto e = expr(true);
		if (ts.current().kind != Kind::rp) return error("')' expected");
		ts.get(); // eat ')'
		return e;
	}
	default:
		return error("primary expected");
	}
}

double term(bool get)
{
	double left = prim(get);
	for (;;) {
		switch (ts.current().kind) {
		case Kind::mul:
			left *= prim(true);
			break;
		case Kind::div:
			if (auto d = prim(true)) {
				left /= d;
				break;
			}
			return error("divide by 0");
		default:
			return left;
		}
	}
}

double expr(bool get)
{
	double left = term(get);
	for (;;) { // forever
		switch (ts.current().kind) {
		case Kind::plus:
			left += term(true);
			break;
		case Kind::minus:
			left -= term(true);
			break;
		default:
			return left;
		}
	}
	return left;
}

void process()
{
	for (;;) {
		ts.get();
		if (ts.current().kind == Kind::end) break;
		if (ts.current().kind == Kind::print) continue;
		cout << expr(false) << "\n";
	}
}

int main(int argc, char* argv[])
{
	switch (argc) {
	case 1: // read from standard input
		break;
	case 2:
		ts.set_input(new istringstream{ argv[1] });
		break;
	default:
		error("too many arguments");
		return 1;
	}

	table["pi"] = 3.141592; // insert predefined names
	table["e"] = 2.711828;

	process();

	return no_of_errors;
}