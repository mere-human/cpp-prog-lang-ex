/*
[3] (∗3) Define a class Int that acts exactly like the built-in type int,
except that it throws exceptions rather than overflowing or underflowing.
*/

#include <iostream>
#include <exception>

enum class ErrorType
{
    Unknown,
    Overflow,
    Underflow
};

struct IntError
{
    const ErrorType type;
};

class Int
{
public:
    using Type = int;

    // avoid any implicit conversion
    explicit Int(Type value = {}) : _value{value}
    {}

    Int operator-() const
    {
        if (_value == MaxValue) throw IntError{ErrorType::Underflow};
        return Int(-_value);
    }

    Int operator+(const Int& other) const
    {
        // here is max/min value is analyzed before any computations
        if (_value > 0)
        {
            if (other._value > 0)
            {
                if ((MaxValue - _value - other._value) < 0)
                    throw IntError{ErrorType::Overflow};
            }
        }
        else if (_value < 0)
        {
            if (other._value < 0)
            {
                if ((MinValue - _value - other._value) > 0)
                    throw IntError{ErrorType::Underflow};
            }
        }
        return Int(_value + other._value);
    }

    Int operator-(const Int& other) const
    {
        // just reuse
        return operator+(-other);
    }

    Int operator*(const Int& other) const
    {
        // a*b > c if and only if a > c/b
        if ((_value == 0) || (other._value == 0)) return Int{0};
        if (_value > (MaxValue / other._value)) throw IntError{ErrorType::Overflow};
        if (_value < (MinValue / other._value)) throw IntError{ErrorType::Underflow};
        return Int{_value * other._value};
    }

    // avoid any implicit conversion
    const Type& get() const
    {
        return _value;
    }

    static const Type MaxValue = std::numeric_limits<Type>::max();
    static const Type MinValue = std::numeric_limits<Type>::min();
private:
    Type _value;
};

std::ostream& operator<<(std::ostream& os, const Int& i)
{
    os << i.get();
    return os;
}

int main()
{
    try
    {
        // unary minus
        std::cout << -Int{1} << "\n";
        try
        {
            std::cout << -Int{Int::MaxValue} << "\n";
        }
        catch (IntError& e)
        {
            if (e.type != ErrorType::Underflow) throw;
        }

        // binary plus
        std::cout << Int{0} + Int{0} << "\n";
        std::cout << Int{1} + Int{0} << "\n";
        std::cout << Int{0} + Int{1} << "\n";
        std::cout << Int{1} + Int{2} << "\n";
        std::cout << Int{-1} + Int{2} << "\n";
        std::cout << Int{-1} + Int{-2} << "\n";
        try
        {
            std::cout << Int{Int::MaxValue} + Int{2} << "\n";
            std::cout << "Should not get there\n";
        }
        catch (IntError& e)
        {
            if (e.type != ErrorType::Overflow) throw;
        }
        try
        {
            std::cout << Int{Int::MinValue} + Int{-2} << "\n";
            std::cout << "Should not get there\n";
        }
        catch (IntError& e)
        {
            if (e.type != ErrorType::Underflow) throw;
        }

        // binary minus
        std::cout << Int{2} - Int{1} << "\n";
        try
        {
            std::cout << Int{Int::MinValue} - Int{2} << "\n";
            std::cout << "Should not get there\n";
        }
        catch (IntError& e)
        {
            if (e.type != ErrorType::Underflow) throw;
        }
        try
        {
            std::cout << Int{0} - Int{Int::MaxValue} << "\n";
            std::cout << "Should not get there\n";
        }
        catch (IntError& e)
        {
            if (e.type != ErrorType::Underflow) throw;
        }

        // multiplication
        std::cout << Int{2} * Int{2} << "\n";
        try
        {
            std::cout << Int{Int::MaxValue} * Int{2} << "\n";
            std::cout << "Should not get there\n";
        }
        catch (IntError& e)
        {
            if (e.type != ErrorType::Overflow) throw;
        }

        try
        {
            std::cout << Int{Int::MaxValue} * Int{Int::MaxValue} << "\n";
            std::cout << "Should not get there\n";
        }
        catch (IntError& e)
        {
            if (e.type != ErrorType::Overflow) throw;
        }

        std::cout << Int{-1} * Int{Int::MaxValue} << "\n";
    }
    catch (...)
    {
        std::cout << "Unexpected error\n";
    }
    return 0;
}