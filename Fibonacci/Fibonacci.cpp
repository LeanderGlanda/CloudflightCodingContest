#include <iostream>

int main()
{
	int number1 = 0;
	int number2 = 1;
	int n = 38;


	for (int i = 2; i <= n; i++)
	{
		int temp = number1;
		number1 = number2;
		number2 = number1 + temp;
	}

	std::cout << number2;
}