// avoid error C4996: 'strerror': This function or variable may be unsafe
#define _CRT_SECURE_NO_WARNINGS

#include "SafeArith.h"
#include <sstream>
#include <cassert>

FloatError::FloatError(std::fexcept_t code, const char* op, double arg1, double arg2)
	: _code{ code }
{
	assert(op);
	set_message(op, arg1, arg2);
}

const char* FloatError::what() const
{
	return _msg.data();
}

FloatError::~FloatError()
{
	std::feclearexcept(_code);
}

void FloatError::set_message(const char* op, double arg1, double arg2)
{
	// priority matters
	// when overflow occurs both FE_OVERFLOW and FE_INEXACT are set
	std::ostringstream buffer;
	if (_code & FE_DIVBYZERO)
	{
		buffer << "Division by zero";
	}
	else if (_code & FE_OVERFLOW)
	{
		buffer << "Overflow";
	}
	else if (_code & FE_UNDERFLOW)
	{
		buffer << "Underflow";
	}
	else if (_code & FE_INVALID)
	{
		buffer << "Domain error, argument is invalid";
	}
	else if (_code & FE_INEXACT)
	{
		buffer << "Inexact result, rounding was necessary";
	}
	else if (_code)
	{
		buffer << "Unknown float error";
	}
	buffer << " for " << op << " with " << arg1 << ", " << arg2;
	_msg = buffer.str();
}

void check_float(const char* operation, double res, double arg1, double arg2)
{
	if (math_errhandling & MATH_ERREXCEPT)
	{
		// float except code handling
		std::fexcept_t flag = 0;
		const int ret = std::fegetexceptflag(&flag, FE_ALL_EXCEPT);
		assert(ret == 0);
		if (flag)
			throw FloatError{ flag, operation, arg1, arg2 };
	}
	else
	{
		//assert(!"FP error codes are unavailable!");
		// try to analyze result
		switch (std::fpclassify(res))
		{
		case FP_INFINITE:
			throw FloatError{ FE_OVERFLOW, operation, arg1, arg2 };
		case FP_NAN:
			throw FloatError{ FE_INVALID, operation, arg1, arg2 };
		default:
			break;
		}
	}
}

double add(double a, double b)
{
	double res = a + b;
	check_float(__FUNCTION__, res, a, b);
	return res;
}

double subtract(double a, double b)
{
	double res = a - b;
	check_float(__FUNCTION__, res, a, b);
	return res;
}

double multiply(double a, double b)
{
	double res = a * b;
	check_float(__FUNCTION__, res, a, b);
	return res;
}

double divide(double a, double b)
{
	double res = a / b;
	check_float(__FUNCTION__, res, a, b);
	return res;
}