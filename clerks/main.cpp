#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <stdexcept>

class clerk
{
public:
	clerk() = default;
	clerk(const int number, const int bribe) : bribe_(bribe), number_(number)
	{
	}

	auto& subordinates() { return subordinates_; }
	auto bribe(const int value) { bribe_ = value; }
	auto number(const int value) { number_ = value; }

	auto& subordinates() const { return subordinates_; }
	auto bribe() const { return bribe_; }
	auto number() const { return number_; }

private:
	int bribe_ = 0;
	int number_ = 1;
	std::vector<const clerk*> subordinates_;
};

class path
{
public:
	auto& clerks() { return clerks_; }
	auto spent(const int value) { return spent_ = value; }

	auto& clerks() const { return clerks_; }
	auto spent() const { return spent_; }
	auto empty() const { return clerks_.empty(); }

private:
	int spent_ = 0;
	std::vector<const clerk*> clerks_;
};

class clerk_data
{
public:
	auto& subordinates() { return subordinates_; }
	auto bribe(const int value) { bribe_ = value; }
	auto number(const int value) { number_ = value; }

	auto& subordinates() const { return subordinates_; }
	auto bribe() const { return bribe_; }
	auto number() const { return number_; }

private:
	int bribe_ = 0;
	int number_ = 1;
	std::vector<int> subordinates_;
};

class parse_data
{
public:
	auto& clerks() { return clerks_; }
	auto chief_index(const int value) { chief_index_ = value; }

	auto& clerks() const { return clerks_; }
	auto chief_index() const { return chief_index_; }
	auto has_chief() const { return chief_index_ >= 0; }

private:
	int chief_index_ = -1;
	std::vector<clerk_data> clerks_;
};

path best_path(const clerk* chief)
{
	path result;
	if (!chief->subordinates().empty())
	{
		for (const auto& c : chief->subordinates())
		{
			const auto p = best_path(c);
			if (result.empty() || p.spent() < result.spent())
			{
				result = p;
			}
		}
	}
	result.spent(result.spent() + chief->bribe());
	result.clerks().emplace_back(chief);
	return result;
}

void print_result(const path& p, const std::string& output_file)
{
	std::ofstream output(output_file);
	output << p.spent() << '\n';
	std::for_each(p.clerks().cbegin(), p.clerks().cend(), [&output](const auto& c) { output << c->number() << ' '; });
}

parse_data parse_input(const std::string& input_file)
{
	const auto max_clerks_number = 100;
	std::ifstream input(input_file);
	int n;
	input >> n;
	parse_data data;
	data.clerks().resize(n);
	for (auto i = 0; i < n; ++i)
	{
		int number, chief, bribe;
		input >> number >> chief >> bribe;
		if (number < 1 || number > n)
		{
			throw std::out_of_range("Некорректный номер чиновника: " + std::to_string(number));
		}
		if (chief < 0 || chief > n)
		{
			throw std::out_of_range("Некорректный номер начальника: " + std::to_string(chief));
		}
		if (bribe < 1 || bribe > max_clerks_number)
		{
			throw std::out_of_range("Некорректная сумма взятки: " + std::to_string(bribe));
		}
		data.clerks().at(number - 1).number(number);
		data.clerks().at(number - 1).bribe(bribe);
		if (chief > 0)
		{
			data.clerks().at(chief - 1).subordinates().emplace_back(number - 1);
		}
		else
		{
			if (data.has_chief())
			{
				throw std::logic_error("Существует несколько главных чиновников");
			}
			data.chief_index(number - 1);
		}
	}
	if (!data.has_chief())
	{
		throw std::logic_error("Нет ни одного главного чиновника");
	}
	return data;
}

clerk* create_clerk(const clerk_data& data)
{
	return new clerk(data.number(), data.bribe());
}

clerk* create_subtree(const std::vector<clerk_data>& data, const int index)
{
	const auto& chief_data = data.at(index);
	const auto chief = create_clerk(chief_data);
	for (const auto subordinate : chief_data.subordinates())
	{
		chief->subordinates().emplace_back(create_subtree(data, subordinate));
	}
	return chief;
}

clerk* create_tree(const parse_data& data)
{
	return create_subtree(data.clerks(), data.chief_index());
}

void clear_tree(const clerk* chief)
{
	if (chief)
	{
		for (const auto& cl : chief->subordinates())
		{
			clear_tree(cl);
		}
		delete chief;
	}
}

int main()
{
	const std::string input_file = "input.txt";
	const std::string output_file = "output.txt";
	try
	{
		const auto data = parse_input(input_file);
		const auto clerks_tree = create_tree(data);
		const auto p = best_path(clerks_tree);
		print_result(p, output_file);
		clear_tree(clerks_tree);
	}
	catch (const std::exception& e)
	{
		std::ofstream output(output_file);
		output << e.what();
	}
}
