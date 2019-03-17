#include "forest.h"

void clerks::forest::add_node(clerk* c)
{
	auto related = find_related(c);
	if (!related.empty())
	{
		connect_related(c, related);
	}
	else
	{
		trees_.push_back(c);
	}
}

clerks::tree* clerks::forest::get_tree() const
{
	return nullptr; // TODO:
}

void clerks::forest::connect_related(clerk* c, vector<clerk*> related)
{
	for (auto r : related)
	{
		if (c->number() == r->chief())
		{
			c->add_subordinate(r);
			r->set_chief(c);
			r = c;
		}
	}
}

clerks::vector<clerks::clerk*> clerks::forest::find_related(const clerk* c) const
{
	vector<clerk*> result;
	for (auto c : trees_)
	{
		if (c->chief() == c->number())
		{
			result.push_back(c);
		}
		else if (auto chief = find_by_number(c->chief()))
		{
			result.push_back(chief);
		}
	}
	return result;
}

clerks::clerk* clerks::forest::find_by_number(int chief) const
{
	throw nullptr;
}
