/*
[4] (*1.5) Define a struct Date to keep track of dates. Provide functions that read Dates from
input, write Dates to output, and initialize a Date with a date.
*/

#include <iostream>

struct Date
{
	int day;
	int month;
	int year;
};

Date get_date(int day, int month, int year)
{
	return { day, month, year };
}

void read_date(Date& d)
{
	std::cin >> d.day;
	std::cin >> d.month;
	std::cin >> d.year;
}

void print_date(const Date& d)
{
	std::cout << d.day << "/" << d.month << "/" << d.year;
}

int main()
{
	auto d = get_date(1, 1, 1980);
	print_date(d);
}