#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>

struct clerk
{
	int bribe = 0;
	int number = 1;
	std::vector<const clerk*> subordinates;
};

struct path
{
	int spent = 0;
	std::vector<const clerk*> clerks;
};

struct clerk_data
{
	int bribe = 0;
	int number = 1;
	std::vector<int> subordinates;
};

struct parse_data
{
	int chief_index = 0;
	std::vector<clerk_data> clerks;
};

path best_path(const clerk* chief)
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

void print_result(const path& p)
{
	std::ofstream output("output.txt");
	output << p.spent << '\n';
	std::for_each(p.clerks.cbegin(), p.clerks.cend(), [&output](const auto& c) { output << c->number << ' '; });
}

parse_data parse_input()
{
	std::ifstream input("input.txt");
	int n;
	input >> n;
	parse_data data;
	data.clerks.resize(n);
	for (auto i = 0; i < n; ++i)
	{
		int number, chief, bribe;
		input >> number >> chief >> bribe;
		data.clerks.at(number - 1).number = number;
		data.clerks.at(number - 1).bribe = bribe;
		if (chief > 0)
		{
			data.clerks.at(chief - 1).subordinates.emplace_back(number - 1);
		}
		else
		{
			data.chief_index = number - 1;
		}
	}
	return data;
}

clerk* create_clerk(const clerk_data& data)
{
	const auto cl = new clerk;
	cl->number = data.number;
	cl->bribe = data.bribe;
	return cl;
}

clerk* create_subtree(const std::vector<clerk_data>& data, const int index)
{
	const auto& chief_data = data[index];
	const auto chief = create_clerk(chief_data);
	for (const auto subordinate : chief_data.subordinates)
	{
		chief->subordinates.emplace_back(create_subtree(data, subordinate));
	}
	return chief;
}

clerk* create_tree(const parse_data& data)
{
	return create_subtree(data.clerks, data.chief_index);
}

void clear_tree(const clerk* chief)
{
	if (chief)
	{
		for (const auto& cl : chief->subordinates)
		{
			clear_tree(cl);
		}
		delete chief;
	}
}

void log_error(const std::exception& e)
{
	std::ofstream output("output.txt");
	output << e.what();
	std::cout << e.what();
}

int main()
{
	try
	{
		const auto data = parse_input();
		const auto clerks_tree = create_tree(data);
		const auto p = best_path(clerks_tree);
		print_result(p);
		clear_tree(clerks_tree);
	}
	catch (const std::exception& e)
	{
		log_error(e);
	}
}
