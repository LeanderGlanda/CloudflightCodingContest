#include "pch.h"

void readfile(std::stringstream& output, std::string m_filename) {
	std::stringstream filename;
	filename << "C:\\Users\\Leander\\Documents\\Development\\CloudflightCodingContest\\ccc2022\\angabe\\level2\\";
	filename << m_filename;
	std::ifstream infile(filename.str());
	output << infile.rdbuf();
	infile.close();
}

void savefile(std::string input, std::string m_filename) {
	std::stringstream filename;
	filename << "C:\\Users\\Leander\\Documents\\Development\\CloudflightCodingContest\\ccc2022\\angabe\\level2\\";
	filename << m_filename;
	std::ofstream ofile(filename.str());
	ofile << input;
	ofile.close();
}

void level1() {

	std::string filename = "level1_5";

	std::string input;
	//readfile(input, filename + ".in");
	std::cout << input;
	std::string::difference_type n = std::count(input.begin(), input.end(), 'B');

	std::stringstream output;
	output << n;

	savefile(output.str(), filename + ".outa");

}

std::string possible_characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!#%&()[]{}*+-/.?:<>=_|";

void level2(std::stringstream& input, std::stringstream& output) {

	std::vector<char> alphabet;
	std::vector<int> occurences;

	int number_of_rounds = 0;

	std::string line;
	int counter = 0;
	while (std::getline(input, line)) {
		if (counter == 0) {
			number_of_rounds = std::stoi(line);
			counter++;
			continue;
		}

		char& first_char = line[0];

		bool skip = false;
		for (int i = 0; i < alphabet.size(); i++)
		{
			if (first_char == alphabet[i])
				skip = true;
		}

		if (!skip) {
			alphabet.push_back(first_char);
		}

		counter++;
	}

	std::string input_string = input.str();

	for (char c : alphabet) {
		std::string::difference_type m = std::count(possible_characters.begin(), possible_characters.end(), c);
		if (m == 0)
			throw std::exception::exception();
		std::string::difference_type n = std::count(input_string.begin(), input_string.end(), c);

		occurences.push_back(n);
	}

	for(int value : occurences)
		output << value << "\n";
}

void level() {
	std::string filename = "level2_5";

	std::stringstream input;
	readfile(input, filename + ".in");

	std::stringstream output;

	level2(input, output);

	savefile(output.str(), filename + ".outa");
}

int main()
{
	level();
}