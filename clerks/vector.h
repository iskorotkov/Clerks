#pragma once

namespace clerks
{
	class vector
	{
	public:
		using type = clerk *;
		using iterator = type *;
		using const_iterator = const type*;

		vector() = default;
		~vector();

		void push_back(type value);
		void resize(int size);

		iterator begin() const;
		iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;

		int size() const;

		bool empty() const;

	private:
		iterator storage_ = nullptr;
		size_t size_ = 0;

		int new_size() const;
	};
}
