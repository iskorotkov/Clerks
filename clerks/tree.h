#pragma once
#include "clerk.h"

namespace clerks
{
	class tree
	{
		friend class forest;
	public:
		using iterator = clerk *;

		tree();
		tree(clerk* c);
		virtual ~tree();

		virtual void emplace(clerk* value);

	private:
		iterator root_ = nullptr;
		bool manages_memory_ = false;

		iterator find_by_number(int n);
	};
}
