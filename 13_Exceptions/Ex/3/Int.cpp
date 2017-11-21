/*
[3] (∗3) Define a class Int that acts exactly like the built-in type int,
except that it throws exceptions rather than overflowing or underflowing.
*/

#include "Int.h"
#include <iostream>
#include <cassert>


// NOTE: Testing with such macros and assert is not very good idea
// However, I wanted to cover some cases and do not want to use other libs

#define SHOULD_THROW(action, message)\
	try\
	{\
		action;\
		assert(!"Exception is expected");\
	}\
	catch (IntError& e)\
	{\
		if (e.what() != std::string{message}) throw;\
	}\

int main()
{
    try
    {
        // unary minus
		assert(-Int{ 1 } == -1);
		assert(-Int{ Int::MaxValue } == Int::MinValue + 1);
		SHOULD_THROW(-Int{ Int::MinValue }, "minus overflow");

        // binary plus
		assert((Int{ 0 } + Int{ 0 }) == 0);
		assert((Int{ 1 } + Int{ 0 }) == 1);
        assert((Int{ 0 } + Int{ 1 }) == 1);
        assert((Int{ 1 } + Int{ 2 }) == 3);
		assert((Int{ -1 } + Int{ 2 }) == 1);
		assert((Int{ -1 } + Int{ -2 }) == -3);
		SHOULD_THROW(Int{ Int::MaxValue } + Int{ 2 }, "add overflow");
		SHOULD_THROW(Int{ Int::MinValue } + Int{ -2 }, "add underflow");

        // binary minus
		assert((Int{ 2 } - Int{ 1 }) == 1);
		SHOULD_THROW(Int{ Int::MinValue } - Int{ 2 }, "add underflow");
		assert((Int{ 0 } - Int{ Int::MaxValue }) == Int::MinValue + 1);

        // multiplication
		assert((Int{ 2 } * Int{ 2 }) == 4);
		SHOULD_THROW(Int{ Int::MaxValue } * Int{ 2 }, "mult overflow");
		SHOULD_THROW(Int{ Int::MaxValue } * Int{ Int::MaxValue }, "mult overflow");
		assert((Int{ Int::MaxValue } * Int{ -1 }) == Int::MinValue + 1);
		assert((Int{ -1 } * Int{ Int::MaxValue }) == Int::MinValue + 1);
		SHOULD_THROW(Int{ 2 } * Int{ Int::MinValue }, "mult overflow");
		SHOULD_THROW(Int{ Int::MinValue } * Int{ -1 }, "minus overflow");

		// division
		assert((Int{ 5 } / Int{ 2 }) == 2);
		SHOULD_THROW(Int{ 1 } / Int{ 0 }, "division by zero");
		SHOULD_THROW(Int{ Int::MinValue } / Int{ -1 }, "division overflow");
    }
    catch (std::exception& e)
    {
        std::cout << "Unexpected error: " << e.what() << "\n";
    }
    return 0;
}
