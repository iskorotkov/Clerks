#pragma once
#include "tree.h"

namespace clerks
{
	class search_tree : tree
	{
	public:
		using tree::tree;
		~search_tree();

		void emplace(type value) override;

		type find(int number) const;
	};
}
