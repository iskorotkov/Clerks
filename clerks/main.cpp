#include <vector>
#include <fstream>
#include <algorithm>

using clerk_ptr = std::vector<struct clerk>::iterator;

struct clerk
{
	int bribe = 0;
	int number = 1;
	std::vector<clerk_ptr> subordinates;
};

struct path
{
	int spent = 0;
	std::vector<clerk_ptr> clerks;
};

path best_path(clerk_ptr chief)
{
	path result;
	if (!chief->subordinates.empty())
	{
		for (const auto& c : chief->subordinates)
		{
			const auto p = best_path(c);
			if (result.spent == 0 || p.spent < result.spent)
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
		clerks.at(number - 1).number = number;
		clerks.at(number - 1).bribe = bribe;
		if (chief > 0)
		{
			clerks.at(chief - 1).subordinates.push_back(clerks.begin() + number - 1);
		}
		else
		{
			clerks_chief = clerks.begin() + number - 1;
		}
	}
	auto p = best_path(clerks_chief);
	output << p.spent << '\n';
	std::for_each(p.clerks.cbegin(), p.clerks.cend(), [&output](const auto& c) { output << c->number << ' '; });
}
