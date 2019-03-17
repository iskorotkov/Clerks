#pragma once
#include "vector.h"

namespace clerks
{
	class clerk
	{
	public:
		clerk() = default;

		void add_subordinate(clerk* subordinate);
		void set_chief(clerk* chief);

		int number() const;
		int chief() const;

		clerk* find_best_path() const;
		clerk* chief_ptr() const;

		vector<clerk*> subordinates() const;

	private:
		int bribe_money_ = 0;
		int number_ = 0;
		int chief_ = 0;
		clerk* chief_ptr_ = nullptr;
		vector<clerk*> subordinates_;
	};

	bool operator==(const clerk& lhs, const clerk& rhs);
	bool operator!=(const clerk& lhs, const clerk& rhs);
}
