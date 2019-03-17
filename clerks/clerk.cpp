#include "clerk.h"

void clerks::clerk::add_subordinate(clerk* subordinate)
{
	subordinates_.push_back(subordinate);
}

void clerks::clerk::set_chief(clerk* chief)
{
	chief_ptr_ = chief;
}

int clerks::clerk::number() const
{
	return number_;
}

int clerks::clerk::chief() const
{
	return chief_;
}

clerks::clerk* clerks::clerk::find_best_path() const
{
	return nullptr; // TODO:
}

clerks::clerk* clerks::clerk::chief_ptr() const
{
	return chief_ptr_;
}

clerks::vector<clerks::clerk*> clerks::clerk::subordinates() const
{
	return subordinates_;
}

bool clerks::operator==(const clerk& lhs, const clerk& rhs)
{
	return lhs.number() == rhs.number();
}

bool clerks::operator!=(const clerk& lhs, const clerk& rhs)
{
	return !(lhs == rhs);
}
