#include <iostream>
#include <string>
#include <vector>

struct throw_type {
	int pins;
	struct throw_type* next_throw;
	throw_type() {
		pins = 0;
		next_throw = nullptr;
	}
	throw_type(int m_pins) {
		pins = m_pins;
		next_throw = nullptr;
	}
};

struct round {
	std::vector<struct throw_type> throws;
	int points;
	round() {
		throws.resize(2);
		points = 0;
	}
};

void create_rounds(std::vector<int>& throws, std::vector<struct round>& rounds, int round) {

	if (throws.size() == 1) {
		rounds[round].throws[0].pins = throws[0];
		throws.erase(throws.begin());
		return;
	}

	// strike
	if (throws[0] == 10)
	{
		rounds[round].throws[0].pins = throws[0];
		rounds[round].throws[0].next_throw = &rounds[round + 1].throws[0];
		throws.erase(throws.begin());
		return;
	}
	// spare / nothing
	else if (throws[0] + throws[1] <= 10) {
		rounds[round].throws[0].pins = throws[0];
		rounds[round].throws[1].pins = throws[1];
		rounds[round].throws[0].next_throw = &rounds[round].throws[1];
		rounds[round].throws[1].next_throw = &rounds[round + 1].throws[0];
		throws.erase(throws.begin());
		throws.erase(throws.begin());
		return;
	}
	else
		throw std::exception::exception();
}

void calculate_points_per_round(std::vector<struct round>& rounds, int round) {
	struct round& current_round = rounds[round];
	if (current_round.throws[0].pins == 10) {
		current_round.points = 10 + current_round.throws[0].next_throw->pins + current_round.throws[0].next_throw->next_throw->pins;
	}
	else if (current_round.throws[0].pins + current_round.throws[1].pins == 10) {
		current_round.points = 10 + current_round.throws[1].next_throw->pins;
	}
	else if (current_round.throws[0].pins + current_round.throws[1].pins < 10) {
		current_round.points = current_round.throws[0].pins + current_round.throws[1].pins;
	}
	else
		throw std::exception::exception();
}
void sum_up_points(std::vector<struct round>& rounds, int round) {
	struct round& current_round = rounds[round];
	if (round > 0)
		current_round.points += rounds[round - 1].points;
}

int main() {
	std::string input = "10:7,2,1,9,6,4,5,5,10,3,7,7,3,6,4,10,2,8,6";
	std::string delimiter = ":";
	std::string string_of_rounds = input.substr(0, input.find(delimiter));
	input.erase(0, input.find(delimiter) + delimiter.length());
	int number_of_rounds = std::stoi(string_of_rounds);

	std::vector<int> throws;
	delimiter = ",";
	size_t pos = 0;
	std::string token;
	while ((pos = input.find(delimiter)) != std::string::npos) {
		token = input.substr(0, pos);
		throws.push_back(std::stoi(token));
		input.erase(0, pos + delimiter.length());
	}
	throws.push_back(std::stoi(input));

	std::vector<int> output;
	std::vector<struct round> rounds;
	rounds.resize(number_of_rounds + 2);

	for (int i = 0; !throws.empty(); i++) {
		create_rounds(throws, rounds, i);
	}
	for (int i = 0; i < number_of_rounds; i++) { 
		calculate_points_per_round(rounds, i);
	}
	for (int i = 0; i < number_of_rounds; i++) {
		sum_up_points(rounds, i);
	}
	std::cout << rounds[0].points;
	for (int i = 1; i < number_of_rounds; i++) {
		std::cout << "," << rounds[i].points;
	}
}