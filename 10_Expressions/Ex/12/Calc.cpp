/*
[13] (*3) Allow a user to define functions in the calculator. Hint: Define a function as a sequence
of operations just as a user would have typed them. Such a sequence can be stored either as a
character string or as a list of tokens. Then read and execute those operations when the function is called.
If you want a user-defined function to take arguments, you will have to invent
a notation for that.
*/
// NOTE: NOT FINISHED
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
	fun name print expr_list
	ret expr print
	- primary
	( expression )
*/

/*
fun a; ret 1
fun a(b, c); ret b * c;
*/

#include <iostream> // I/O
#include <sstream>
#include <string>   // strings
#include <map>      // map
#include <cctype>   // isalpha(), etc
#include <vector>

using namespace std;

enum class Kind : char {
	name, number, fun, ret, end,
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
map<string, double> table;
map<string, vector<Token>> funcs;
int no_of_errors;
int line_no{ 1 };

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
			if (ct.string_value == "fun")
				ct.kind = Kind::fun;
			else if (ct.string_value == "ret")
				ct.kind = Kind::ret;
			else
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
		auto it = table.find(ts.current().string_value); // find the corresponding variable
		if (it != table.end()) {
			if (ts.get().kind == Kind::assign) it->second = expr(true); // '=' seen: assignment
			return it->second;
		}
		else { // function call
			auto it2 = funcs.find(ts.current().string_value); // find the corresponding fun
			if (it2 != funcs.end()) {
				if (ts.get().kind != Kind::lp) return error("'(' expected");
				if (ts.get().kind != Kind::rp) return error("')' expected");
			}
			else {
				return error("unknown id");
			}
		}
	}
	case Kind::fun:
	{
		if (ts.get().kind != Kind::name) return error("name expected");
		const string name = ts.current().string_value;
		if (ts.get().kind != Kind::print) return error("print expected");
		string body;
		do {
			body.push_back(ts.current());
		} while (ts.get().kind != Kind::ret);
		body.push_back(ts.get()); // return value
		if (ts.get().kind != Kind::print) return error("print expected");
		funcs[name] = body;
		return 0; // no value
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

void calculate()
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

	calculate();

	return no_of_errors;
}