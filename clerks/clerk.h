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
		clerk* chief() const;

		vector<clerk*> subordinates() const;

	private:
		int number_ = 0;
		int bribe_money_ = 0;
		clerk* chief_ = nullptr;
		vector<clerk*> subordinates_;
	};
}
