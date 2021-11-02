#include <iostream>

void level1()
{
	double length = 531441;
	double iterations = 9;

	double current_triangle_size = length;
	double line_count = 3;
	for (int i = 0; i < iterations; i++)
	{
		line_count *= 4;
		current_triangle_size /= 3;
	}

	std::cout << line_count << std::endl;
	printf("%lf", line_count * current_triangle_size);
}

void level2()
{
	double length = 531441;
	double iterations = 9;

	double current_triangle_size = length;
	double line_count = 4;
	for (int i = 0; i < iterations; i++)
	{
		line_count *= 5;
		current_triangle_size /= 3;
	}

	std::cout << line_count << std::endl;
	printf("%lf", line_count * current_triangle_size);
}

int main()
{
	std::cout << "Run Level 1!\n";
	level1();
	std::cout << "Run Level 2!\n";
	level2();
}