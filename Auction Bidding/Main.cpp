#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <array>
#include <algorithm>

struct my_bid {
	int bid;
	std::string name;

	my_bid(int p_bid, std::string p_name)
		: bid(p_bid), name(p_name)
	{
	}
	my_bid()
	{
		bid = 0;
		name = "";
	}
};

struct my_current_state {
	struct my_bid bid;
	int price;

	my_current_state(struct my_bid p_bid, int p_price)
		: bid(p_bid), price(p_price)
	{
	}
	my_current_state()
	{
		bid = { 0, "" };
		price = 0;
	}
};

void level1(std::string input)
{
	std::stringstream ss(input);
	std::vector<std::string> result;

	while (ss.good())
	{
		std::string substr;
		std::getline(ss, substr, ',');
		result.push_back(substr);
	}

	result.erase(result.begin());

	std::vector<my_bid> bids;

	for (int i = 0; i < std::ceil(((double)result.size() / 2)); i++)
	{
		bids.emplace_back(std::stoi(result[i * 2 + 1]), result[i * 2]);
	}

	std::sort(std::begin(bids), std::end(bids), [](const my_bid& a, const my_bid& b) {return a.bid < b.bid; });

	struct my_bid bid_result = { bids[bids.size() - 2].bid + 1, bids.back().name };

	std::cout << bid_result.name << "," << bid_result.bid << std::endl;
}

void level2(std::string input)
{
	std::stringstream ss(input);
	std::vector<std::string> result;

	while (ss.good())
	{
		std::string substr;
		std::getline(ss, substr, ',');
		result.push_back(substr);
	}

	int current_price = std::stoi(result[0]);
	result.erase(result.begin());

	std::vector<my_bid> bids;

	for (int i = 0; i < std::ceil(((double)result.size() / 2)); i++)
	{
		bids.emplace_back(std::stoi(result[i * 2 + 1]), result[i * 2]);
	}

	std::sort(std::begin(bids), std::end(bids), [](const my_bid& a, const my_bid& b) {return a.bid < b.bid; });

	struct my_bid bid_result;

	/*for (int i = 0; i < bids.size(); i++)
	{
		for (int j = 0; j < bids.size(); j++)
		{
			if (bids[i].bid == bids[j].bid && j != i)
			{
				bids.erase(bids.begin() + j);
			}
		}
	}*/

	do
	{
		int amount = 0;
		for (int i = 0; i < bids.size(); i++)
		{
			if (bids[i].bid >= current_price)
			{
				amount++;
			}
			else
			{
				bids.erase(bids.begin() + i);
				i--;
			}
		}
		int amount_top = 0;
		for (int i = 0; i < bids.size(); i++)
		{

			if (bids[i].name == bids.back().name/* || bids[i + 1].bid == bids[i].bid && bids[i + 1].name != bids[i].name */)
			{
				amount_top++;
			}
		}

		int counter_bids_bid = 0;
		for (int i = 0; i < bids.size(); i++)
			if (bids[0].bid != bids[i].bid)
				break;
			else
				counter_bids_bid++;

		if (amount_top == amount)
		{
			bid_result = { current_price, bids.back().name };
			break;
		}

		if (bids.size() == counter_bids_bid)
		{
			bid_result = bids[0];
			break;
		}
		
		current_price++;
	} while (true);

	std::cout << bid_result.name << "," << bid_result.bid << std::endl;
}

void level3(std::string input)
{
	std::stringstream ss(input);
	std::vector<std::string> result;

	while (ss.good())
	{
		std::string substr;
		std::getline(ss, substr, ',');
		result.push_back(substr);
	}

	int current_price = std::stoi(result[0]);
	result.erase(result.begin());

	std::vector<my_bid> bids;

	for (int i = 0; i < std::ceil(((double)result.size() / 2)); i++)
	{
		bids.emplace_back(std::stoi(result[i * 2 + 1]), result[i * 2]);
	}

	//std::sort(std::begin(bids), std::end(bids), [](const my_bid& a, const my_bid& b) {return a.bid < b.bid; });

	struct my_bid bid_result;

	/*for (int i = 0; i < bids.size(); i++)
	{
		for (int j = 0; j < bids.size(); j++)
		{
			if (bids[i].bid == bids[j].bid && j != i)
			{
				bids.erase(bids.begin() + j);
			}
		}
	}*/

	/*for (int i = 1; i < bids.size(); i++)
	{
		if (bids[i-1].name == bids[i].name)
		{
			if (bids[i-1].bid < bids[i].bid)
				bids.erase(bids.begin() + i - 1);
			else
				bids.erase(bids.begin() + i);
			i--;
		}
	}*/

	std::stringstream output;
	output << "-," << current_price;

	int start_price = current_price;
	bool first_time = true;

	//int last_highest_bid = current_price;
	struct my_current_state current_state = { {current_price, "-"}, current_price};

	do
	{
		for (int i = 0; i < bids.size(); i++)
		{
			/*if (bids[i].bid > current_state.price)
			{
				if (first_time)
				{
					current_state.bid = bids[i].bid;
					current_state.price = start_price;
					first_time = false;
				}
				else
				{
					current_state.price = current_state.bid + 1;
					current_state.bid = bids[i].bid;
				}
				output << "," << bids[i].name << "," << current_state.price;
				break;
			}*/

			/*if (bids[i].bid >= current_price)
			{
				current_price.price = ;
				current_state.bid = bids[i];
			}*/

			if (bids[i].bid >= current_price && bids[i].bid != current_state.bid.bid && bids[i].name != current_state.bid.name)
			{
				current_state.bid = bids[i];
				current_state.price = current_state.bid.bid;
				output << "," << bids[i].name << "," << bids[i].bid;
				break;
			}
		}

		int amount = 0;
		for (int i = 0; i < bids.size(); i++)
		{
			if (bids[i].bid >= current_price)
			{
				amount++;
			}
			else
			{
				/*//output << "," << bids[i].name << "," << bids[i].bid;
				output << "," << bids[i].name << "," << last_highest_bid;
				last_highest_bid = bids[i].bid;*/
				bids.erase(bids.begin() + i);
				i--;
			}
		}
		int amount_top = 0;
		for (int i = 0; i < bids.size(); i++)
		{

			if (bids[i].name == bids.back().name/* || bids[i + 1].bid == bids[i].bid && bids[i + 1].name != bids[i].name */)
			{
				amount_top++;
			}
		}

		int counter_bids_bid = 0;
		for (int i = 0; i < bids.size(); i++)
			if (bids[0].bid != bids[i].bid)
				break;
			else
				counter_bids_bid++;

		if (amount_top == amount)
		{
			bid_result = { current_price, bids.back().name };
			break;
		}

		if (bids.size() == counter_bids_bid)
		{
			bid_result = bids[0];
			break;
		}

		current_price++;
	} while (true);

	std::cout << output.str() << "," << bid_result.name << "," << bid_result.bid << std::endl;
}

int main()
{
	level1("1,A,5,B,10,A,8,A,17,B,17");
	level2("100,A,100,A,115,A,119,A,144,A,145,A,157,A,158,A,171,A,179,A,194,A,206,A,207,A,227,A,229,A,231,A,234");
	level3("1,A,5,B,10,A,8,A,14,A,17,B,17");
}