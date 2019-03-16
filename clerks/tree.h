#pragma once
#include "clerk.h"

namespace clerks
{
	class tree
	{
	public:
		using type = clerk *;
		using iterator = type *;

		tree(bool manages_memory);
		virtual ~tree();

		virtual void emplace(type value);

	private:
		iterator root_ = nullptr;
		bool manages_memory_ = false;
	};
}
