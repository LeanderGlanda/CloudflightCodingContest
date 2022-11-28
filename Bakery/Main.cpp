#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <array>
#include <algorithm>

struct business_day {
	int tag;
	int tagesumsatz;
	int bankeinzahlung;

	business_day(int p_tag, int p_tagesumsatz, int p_bankeinzahlung)
		: tag(p_tag), tagesumsatz(p_tagesumsatz), bankeinzahlung(p_bankeinzahlung)
	{
	}
	business_day()
	{
		tag = 0;
		tagesumsatz = 0;
		bankeinzahlung = 0;
	}

};

std::vector<business_day> parse_input(std::string& p_input)
{
	std::stringstream input(p_input);
	std::vector<std::string> result;

	while (input.good())
	{
		std::string substr;
		std::getline(input, substr, ' ');
		result.push_back(substr);
	}

	std::vector<business_day> umsatz;

	umsatz.resize(result.size() / 3);

	for (int i = 0; i < result.size() / 3; i++)
	{
		if (result[(i * 3)] == "F")
		{
			umsatz[i].tag = std::stoi(result[(i * 3 + 1)]);
			umsatz[i].tagesumsatz = std::stoi(result[i * 3 + 2]);
		}
		else
		{
			umsatz[i - result.size() / 6].bankeinzahlung = std::stoi(result[i * 3 + 2]);
		}
	}

	return umsatz;
}

void level1(std::string input)
{
	std::vector<business_day> umsatz = parse_input(input);

	std::stringstream output;

	for (int i = 0; i < umsatz.size(); i++)
	{
		if (umsatz[i].tagesumsatz != umsatz[i].bankeinzahlung)
			output << umsatz[i].tag << " ";
	}
	
	std::cout << output.str();
}

void level2(std::string input)
{
	level1(input);
}

std::vector<std::string> parse_input2(std::string& p_input)
{
	std::stringstream input(p_input);
	std::vector<std::string> result;

	while (input.good())
	{
		std::string substr;
		std::getline(input, substr, ' ');
		result.push_back(substr);
	}

	return result;
}

void level3(std::string input)
{
	std::vector<std::string> result = parse_input2(input);
	std::vector<business_day> umsatz;

	umsatz.resize(result.size() / 3);

	bool first_time = true;

	for (int i = 0; i < result.size() / 3; i++)
	{
		if (result[(i * 3)] == "F")
		{
			umsatz[i].tag = std::stoi(result[(i * 3 + 1)]);
			umsatz[std::stoi(result[(i * 3 + 1)]) - 1].tagesumsatz = std::stoi(result[i * 3 + 2]);
		}
		else
		{
			if (umsatz[i - 1].tagesumsatz > umsatz[i - 1].bankeinzahlung && first_time == false)
			{
				first_time = false;
				int unterschied = umsatz[i - 1].tagesumsatz - umsatz[i - 1].bankeinzahlung;
				//if (std::stoi(result[i * 3 + 2]) >= unterschied)
				//{
					umsatz[i - 1].bankeinzahlung += unterschied;
					umsatz[std::stoi(result[(i * 3 + 1)]) - 1].bankeinzahlung += std::stoi(result[i * 3 + 2]) - unterschied;
				//}
			}
			else
				umsatz[std::stoi(result[(i * 3 + 1)]) - 1].bankeinzahlung += std::stoi(result[i * 3 + 2]);
		}
	}

	std::stringstream output;

	for (int i = 0; i < umsatz.size(); i++)
	{
		if (umsatz[i].tagesumsatz != umsatz[i].bankeinzahlung)
			output << umsatz[i].tag << " ";
	}

	std::cout << output.str();
}

int main()
{
	/*while (true)
	{
		std::string input;
		std::cin >> input;
		level1(input);
	}*/

	level1("F 1 739 B 1 739");
	level2("");
	//level3("F 1 739 F 2 734 B 1 739 B 2 739");
	level3("F 1 200 F 2 170 B 1 100 B 2 80 B 2 15 B 2 100 B 3 70");
}