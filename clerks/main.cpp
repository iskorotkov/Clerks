#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <fstream>
#include <stack>

struct clerk;
using clerk_ptr = std::vector<clerk>::iterator;

struct clerk
{
	int bribe = 0;
	int number;
	std::vector<clerk_ptr> subordinates;
};

struct path
{
	std::vector<clerk_ptr> clerks;
	int spent = 0;
};

path best_path(clerk_ptr chief)
{
	path result;
	if (!chief->subordinates.empty())
	{
		for (const auto& c : chief->subordinates)
		{
			const auto p = best_path(c);
			if (p.spent < result.spent || result.spent == 0)
			{
				result = p;
			}
		}
	}
	result.spent += chief->bribe;
	result.clerks.push_back(chief);
	return result;
}

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");
	int n;
	input >> n;
	std::vector<clerk> clerks(n);
	clerk_ptr clerks_chief;
	for (auto i = 0; i < n; ++i)
	{
		int number, chief, bribe;
		input >> number >> chief >> bribe;
		--number;
		--chief;
		clerks.at(number).number = number + 1;
		clerks.at(number).bribe = bribe;
		if (chief >= 0)
		{
			clerks.at(chief).subordinates.push_back(clerks.begin() + number);
		}
		else
		{
			clerks_chief = clerks.begin() + number;
		}
	}
	auto p = best_path(clerks_chief);
	output << p.spent << '\n';
	for (auto c : p.clerks)
	{
		output << c->number << ' ';
	}
}
