/*
[1] (*2) Complete class Ptr from 19.2.4 and test it. To be complete, Ptr must have at least the
operators ∗, −>, =, ++, and −− defined. Do not cause a run-time error until a wild pointer is
actually dereferenced.
*/

#include <iostream>
#include <utility> // pair
#include <string>

template<typename T>
class Ptr
{
	T* base;
	int size;
	int pos;
	void check_bounds(int i)
	{
		if (i < 0 || i >= size)
			throw std::out_of_range{ "Ptr is out of range" };
	}
public:
	Ptr(T* ptr = nullptr)
		: base{ ptr }, size{ 1 }, pos{ 0 }
	{}
	// T* constructor is preferred for single arg, even if it is actually an array
	// so, index arg is mandatory
	template<int N>
	Ptr(T(&arr)[N], int index)
		: base{ arr + index }, size{ N }, pos{ index }
	{}
	T& operator*()
	{
		check_bounds(pos);
		return *(base + pos);
	}
	T* operator->()
	{
		check_bounds(pos);
		return base + pos;
	}
	T& operator[](int i)
	{
		check_bounds(pos + i);
		return base[pos + i];
	}
	// no postfix versions - yes, I am lazy
	Ptr& operator++()
	{
		++pos;
		return *this;
	}
	Ptr& operator--()
	{
		--pos;
		return *this;
	}
};

int main()
{
	int i1 = 2;
	Ptr<int> p1 = &i1;
	std::cout << *p1 << "\n";

	using key_value_t = std::pair<int, std::string>;
	key_value_t v2{ 1, "x" };
	Ptr<key_value_t> p2 = &v2;
	std::cout << p2->first << p2->second << "\n";

	int arr[] = { 1, 2, 3 };
	Ptr<int> p3{ arr, 0 };
	std::cout << *p3 << " ";
	++p3;
	--p3;
	std::cout << *(++p3) << " ";
	std::cout << p3[1];
	return 0;
}