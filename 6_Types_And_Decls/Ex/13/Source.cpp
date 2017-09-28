/*
[13] (*1.5) Write a loop that prints out the values 4, 5, 9, 17, 12 without using an array or a vector.
*/

#include <iostream>

int main()
{
	for (int i = 0; i <= 4; ++i)
	{
		int val = 0;
		switch (i)
		{
		case 0:
			val = 4;
			break;
		case 1:
			val = 5;
			break;
		case 2:
			val = 9;
			break;
		case 3:
			val = 17;
			break;
		case 4:
			val = 12;
			break;
		default:
			break;
		}
		if (val)
			std::cout << val << "\n";
		else
			break;
	}
}