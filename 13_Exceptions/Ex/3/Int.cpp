/*
[3] (∗3) Define a class Int that acts exactly like the built-in type int,
except that it throws exceptions rather than overflowing or underflowing.
*/

#include <iostream>

class Int
{
public:
    Int(int value = {}) : _value{value}
    {}

    operator int() const
    {
        return _value;
    }
private:
    int _value;
};

int main()
{
    Int n = 2;
    std::cout << n;
    return 0;
}