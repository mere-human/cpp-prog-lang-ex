/*
[9] (*2) Write a class or template suitable for implementing callbacks
*/

#include <iostream>
#include <vector>

template<typename F>
class Callback
{
public:
	Callback(F f) : call{ f }
	{}

	// simple version w/o args
	void operator()()
	{
		call();
	}

	// more complex version with variadic template
	// actually, can be called even w/o args
	template<typename... Args>
	void operator()(Args... args)
	{
		call(args...);
	}
private:
	F call;
};

template<typename F>
Callback<F> callback(F f)
{
	return Callback<F>(f);
}

void f()
{
	std::cout << "f()\n";
}

void g(int n)
{
	std::cout << "g(" << n << ")\n";
}

int main()
{
	// function w/o args
	auto cb1 = callback(&f);
	cb1();

	// function with arg
	auto cb2 = callback(&g);
	cb2(3);

	std::vector<int> v(2, 1);
	std::cout << "size: " << v.size() << "\n";
	// lambda function
	auto cb3 = callback([&v]() { return v.pop_back(); });
	cb3();
	std::cout << "size: " << v.size() << "\n";

	return 0;
}