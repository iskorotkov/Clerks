#pragma once

namespace clerks
{
	template <typename T>
	class vector
	{
	public:
		vector() = default;
		~vector();

		void push_back(T value);
		void resize(int size);
		void clear();

		T* begin() const;
		T* end() const;
		const T* cbegin() const;
		const T* cend() const;

		int size() const;

		bool empty() const;

		T* find(const T& value);
		const T* find(const T& value) const;

		T& operator[](int n);
		const T& operator[](int n) const;

	private:
		T* storage_ = nullptr;
		int size_ = 0;
		int buffer_size_ = 0;
		int initial_buffer_size_ = 8;
		int buffer_size_multiplier_ = 2;

		void resize();
	};

	template <typename T>
	const T& clerks::vector<T>::operator[](int n) const
	{
		return storage_[n];
	}

	template <typename T>
	T& clerks::vector<T>::operator[](int n)
	{
		return storage_[n];
	}

	template <typename T>
	void clerks::vector<T>::resize()
	{
		if (buffer_size_ == 0)
		{
			buffer_size_ = initial_buffer_size_;
		}
		else
		{
			buffer_size_ *= buffer_size_multiplier_;
		}
		resize(buffer_size_);
	}

	template <typename T>
	int clerks::vector<T>::size() const
	{
		return size_;
	}

	template <typename T>
	const T* clerks::vector<T>::find(const T& value) const
	{
		for (auto ptr = begin(); ptr != end(); ++ptr)
		{
			if (*ptr == value)
			{
				return ptr;
			}
		}
		return nullptr;
	}

	template <typename T>
	T* clerks::vector<T>::find(const T& value)
	{
		for (auto ptr = begin(); ptr != end(); ++ptr)
		{
			if (*ptr == value)
			{
				return ptr;
			}
		}
		return nullptr;
	}

	template <typename T>
	bool clerks::vector<T>::empty() const
	{
		return size_ == 0;
	}

	template <typename T>
	const T* clerks::vector<T>::cend() const
	{
		return end();
	}

	template <typename T>
	const T* clerks::vector<T>::cbegin() const
	{
		return begin();
	}

	template <typename T>
	T* clerks::vector<T>::end() const
	{
		return empty() ? nullptr : begin() + size_;
	}

	template <typename T>
	T* clerks::vector<T>::begin() const
	{
		return empty() ? nullptr : storage_;
	}

	template <typename T>
	void clerks::vector<T>::clear()
	{
		delete[] storage_;
	}

	template <typename T>
	void clerks::vector<T>::resize(int n)
	{
		if (!empty() && n > size())
		{
			clear();
		}
		storage_ = new T[n];
	}

	template<typename T>
	vector<T>::~vector()
	{
		if (!empty())
		{
			clear();
		}
	}
	template<typename T>
	void vector<T>::push_back(T value)
	{
		if (empty())
		{
			resize();
		}
		storage_[size_] = value;
		++size_;
	}
}
