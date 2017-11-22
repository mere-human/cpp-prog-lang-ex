#ifndef _SAFE_ARITH_H_
#define _SAFE_ARITH_H_
#pragma once

#include <exception>
#include <iostream>
#include <cfenv>

class FloatError : std::exception
{
public:
	FloatError(std::fexcept_t code, const char* op, double arg1, double arg2);
	const char* what() const override;
	~FloatError() override;
private:
	void set_message(const char* op, double arg1, double arg2);
	std::string _msg;
	std::fexcept_t _code;
};

double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);

#endif // _SAFE_ARITH_H_