/*
[19] (*2) Add functions such as sqrt(), log(), and sin() to the desk calculator from §10.2.
Hint: Predefine the names and call the functions through an array of pointers to functions.
Don’t forget to check the arguments in a function call.
*/

/*
program:
	end           // end is end-of-input
	expr_list end

expr_list:
	expression print           // print is newline or semicolon
	expression print expr_list

expression:
	expression + term
	expression ? term
	term

term:
	term / primary
	term ? primary
	primary

primary:
	number            // number is a floating-point literal
	name              // name is an identifier
	name = expression
	- primary
	( expression )

So, function call is "name ( expression )"
*/

#include <iostream> // I/O
#include <sstream>
#include <string>   // strings
#include <map>      // map
#include <cctype>   // isalpha(), etc
#include <cmath>    // sqrt(), log(), and sin()

using namespace std;

enum class Kind : char {
	name, number, end,
	plus = '+', minus = '-', mul = '*', div = '/', print = ';', assign = '=', lp = '(', rp = ')'
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

using func_ptr = double(*)(double);

Token_stream ts{ cin }; // use input from cin
int no_of_errors;
map<string, double> table;
map<string, func_ptr> funcs;

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
		auto it = funcs.find(ts.current().string_value);
		if (it == funcs.end())
		{
			double& v = table[ts.current().string_value]; // find the corresponding
			if (ts.get().kind == Kind::assign) v = expr(true); // '=' seen: assignment
			return v;
		}
		else
		{
			if (ts.get().kind != Kind::lp) return error("function call, '(' expected");
			if (ts.get().kind != Kind::number) return error("function call, number expected");
			auto num = ts.current().number_value;
			if (ts.get().kind != Kind::rp) return error("function call, ')' expected");
			return it->second(num);
		}
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
		"sqrt(4)\n";
	ts.set_input(new istringstream{ text });

	// insert predefined names
	table["pi"] = 3.141592;
	table["e"] = 2.711828;

	// insert predefined funcs
	funcs["sqrt"] = &sqrt;
	funcs["log"] = &log;
	funcs["sin"] = &sin;

	process();

	return no_of_errors;
}