#pragma once
#include "vector.h"
#include "tree.h"
#include "clerk.h"

namespace clerks
{
	class forest
	{
	public:
		void add_node(clerk* node);

		tree* get_tree() const;

	private:
		vector<clerk*> trees_;

		void connect_related(clerk* c, vector<clerk*> related);
		clerk* find_by_number(int chief) const;

		vector<clerk*> find_related(const clerk* c) const;
	};
}
