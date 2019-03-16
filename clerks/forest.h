#pragma once
#include "vector.h"
#include "tree.h"

namespace clerks
{
	class forest
	{
	public:
		using type = clerk *;

		void add_node(const type node);

		tree* get_tree() const;

	private:
		vector<tree*> trees_;
	};
}
