#pragma once

namespace clerks
{
	template <typename T>
	class vector
	{
	public:
		using type = T *;
		using iterator = type *;
		using const_iterator = const type*;

		vector() = default;
		~vector();

		void push_back(type value);
		void resize(size_t size);
		void remove(size_t n);
		void remove(const_iterator i);

		iterator begin() const;
		iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;

		int size() const;

		bool empty() const;

		type& operator[](size_t n);

	private:
		iterator storage_ = nullptr;
		size_t size_ = 0;

		int new_size() const;
	};
}
