#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <array>
#include <algorithm>
#include <fstream>

struct p_sweet
{
	int economist_id;
	std::vector<int> values;

	p_sweet(std::vector<int> p_values, int p_economist_id)
		: values(p_values), economist_id(p_economist_id)
	{

	}
	p_sweet()
	{
		economist_id = 0;
	}
};

void level1(std::string p_filename)
{
	std::stringstream filename;
	filename << "C:\\Users\\Leander\\Downloads\\level1\\";
	filename << p_filename;
	filename << ".in";
	std::ifstream infile(filename.str());

	std::vector<p_sweet> lines;

	std::string line;
	int counter = 0;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		int a, b;
		//if (!(iss >> a >> b)) { break; } // error

		// process pair (a,b)

		lines.emplace_back();

		int temp = 0;
		iss >> temp;
		lines[counter].economist_id = temp;

		for (int j = 1; !(iss.eof()); j++)
		{
			iss >> temp;
			//iss >> lines[counter].values[j];
			lines[counter].values.push_back(temp);
		}
		counter++;
	}

	filename.str("");
	filename << "C:\\Users\\Leander\\Downloads\\level1\\";
	filename << p_filename;
	filename << ".out";

	std::ofstream outfile(filename.str());

	// ignore the first entry, it's the number of economists
	for (int i = 1; i < lines.size(); i++)
	{
		int value = 0;

		for (int j = 0; j < lines[i].values.size(); j++)
		{
			value += lines[i].values[j];
		}
		std::cout << lines[i].economist_id << std::endl;
		outfile << value << std::endl;
	}
}

void level2(std::string p_filename)
{
	std::stringstream filename;
	filename << "C:\\Users\\Leander\\Downloads\\level2\\";
	filename << p_filename;
	filename << ".in";
	std::ifstream infile(filename.str());

	std::vector<p_sweet> lines;

	std::string line;
	int counter = 0;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		int a, b;
		//if (!(iss >> a >> b)) { break; } // error

		// process pair (a,b)

		lines.emplace_back();

		int temp = 0;
		iss >> temp;
		lines[counter].economist_id = temp;

		for (int j = 1; !(iss.eof()); j++)
		{
			iss >> temp;
			//iss >> lines[counter].values[j];
			lines[counter].values.push_back(temp);
		}
		counter++;
	}

	filename.str("");
	filename << "C:\\Users\\Leander\\Downloads\\level2\\";
	filename << p_filename;
	filename << ".out";

	std::ofstream outfile(filename.str());

	// ignore the first entry, it's the number of economists
	for (int i = 1; i < lines.size(); i++)
	{
		/*int highest_sweet_in_line = 0;
		for (int j = 0; j < lines[i].values.size(); j++)
		{
		if (lines[i].values[j] > highest_sweet_in_line)
		highest_sweet_in_line = lines[i].values[j];
		}

		int second_highest_sweet_in_line = 0;
		for (int j = 0; j < lines[i].values.size(); j++)
		{
		if (lines[i].values[j] > second_highest_sweet_in_line && lines[i].values[j] < highest_sweet_in_line)
		second_highest_sweet_in_line = lines[i].values[j];
		}*/

		int lowest_sweet_in_line = 1000000;
		for (int j = 0; j < lines[i].values.size(); j++)
		{
			if (lines[i].values[j] < lowest_sweet_in_line)
				lowest_sweet_in_line = lines[i].values[j];
		}


		int ecoID = 0;
		int value = 0;


		for (int k = 1; k < lines.size(); k++)
		{
			if (k == i)
				continue;
			for (int l = 0; l < lines[k].values.size(); l++)
			{
				if (lines[k].values[l] > value)
				{
					ecoID = lines[k].economist_id;
					value = lines[k].values[l];
				}
			}
		}

		if (value > lowest_sweet_in_line)
		{
			outfile << lines[i].economist_id << " " << lowest_sweet_in_line << " " << ecoID << " " << value << std::endl;
		}
		else
		{
			outfile << "NO TRADE" << std::endl;
		}



		/*int value = 0;

		for (int j = 0; j < lines[i].values.size(); j++)
		{
		value += lines[i].values[j];
		}
		std::cout << lines[i].economist_id << std::endl;
		outfile << value << std::endl;*/
	}
}

void level3(std::string p_filename)
{
	std::stringstream filename;
	filename << "C:\\Users\\Leander\\Downloads\\level3\\";
	filename << p_filename;
	filename << ".in";
	std::ifstream infile(filename.str());

	std::vector<p_sweet> lines;

	int number_ecos = 0;

	//std::vector<std::vector<std::vector<int>>> table;
	std::vector<std::vector<int>> table;

	std::string line;
	int counter = 0;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		lines.emplace_back();
		if (counter - number_ecos - 2 >= 0)
			table.emplace_back();

		int temp = 0;
		/*iss >> temp;
		lines[counter].economist_id = temp;*/

		for (int j = 0; !(iss.eof()); j++)
		{
			if (counter == 0)
			{
				iss >> temp;
				number_ecos = temp;
				break;
			}
			if (counter <= number_ecos)
			{
				if (j == 0)
				{
					iss >> temp;
					lines[counter].economist_id = temp;
					continue;
				}
				iss >> temp;
				lines[counter].values.push_back(temp);
			}
			else
			{
				if (counter == number_ecos + 1)
				{
					std::string temp1;
					iss >> temp1;
					break;
				}
				table[counter - number_ecos - 2].push_back(0);
				iss >> table[counter - number_ecos - 2][j];
				//iss >> temp;
			}
		}
		counter++;
	}


	// comment for the future
	// all data should be alright, but now the according trades need to be found.

	filename.str("");
	filename << "C:\\Users\\Leander\\Downloads\\level3\\";
	filename << p_filename;
	filename << ".out";

	std::ofstream outfile(filename.str());

	// ignore the first entry, it's the number of economists
	for (int i = 1; i < lines.size(); i++)
	{

		int lowest_sweet_in_line = 1000000;
		for (int j = 0; j < lines[i].values.size(); j++)
		{
			if (table[lines[i].values[j]]. < lowest_sweet_in_line)
				lowest_sweet_in_line = lines[i].values[j];
		}


		int ecoID = 0;
		int value = 0;


		for (int k = 1; k < lines.size(); k++)
		{
			if (k == i)
				continue;
			for (int l = 0; l < lines[k].values.size(); l++)
			{
				if (lines[k].values[l] > value)
				{
					ecoID = lines[k].economist_id;
					value = lines[k].values[l];
				}
			}
		}

		if (value > lowest_sweet_in_line)
		{
			outfile << lines[i].economist_id << " " << lowest_sweet_in_line << " " << ecoID << " " << value << std::endl;
		}
		else
		{
			outfile << "NO TRADE" << std::endl;
		}
	}
}

int main()
{
	level3("level3_example");
}