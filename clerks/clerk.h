#pragma once
#include "vector.h"

namespace clerks
{
	class clerk
	{
	public:
		clerk() = default;

		void add_subordinate(const clerk* subordinate);
		void set_chief(const clerk* chief);

		int number() const;

		clerk* find_best_path() const;

		clerks::vector subordinates() const;

	private:
		int number_ = 0;
		int bribe_money_ = 0;
		clerk* chief_ = nullptr;
		clerks::vector subordinates_;
	};
}
