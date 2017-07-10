#ifndef RANGE_H
#define RANGE_H
#include<iostream>
#include<algorithm>
#include<cmath>

/*
@brief 表示区间的类
可以表示开闭区间(a,b]，重载了比较操作符
*/
namespace myml
{
	template<class T>
	class range
	{
	private:
		T _lower_bound;
		T _upper_bound_eq;
	public:
		range(T lower_bound, T upper_bound);
		range(const range&r);
		range() = default;
		range(std::initializer_list<T> list);
		~range() = default;
		/*
		@brief 赋值操作符
		*/
		range & operator=(const range &r);
		bool operator ==(const range & r) const;
		bool operator >(const range & r) const;
		bool operator <(const range & r) const;
		bool operator !=(const range & r) const;
		bool operator ==(T data) const;
		bool operator >(T data)const;
		bool operator <(T data)const;
		bool operator !=(T data)const;
		void reset_to(const range &r);
		void print(std::ostream &o) const;
		T get_hash() const;
	};

	template<class T>
	range<T>::range(const range&r)
	{
		_upper_bound_eq = r._upper_bound_eq;
		_lower_bound = r._lower_bound;
	}

	template<class T>
	inline range<T>::range(std::initializer_list<T> list)
	{
		_lower_bound = *(list.begin());
		_upper_bound_eq = *(list.begin() + 1);
	}

	template<class T>
	range<T>::range(T lower_bound, T upper_bound)
	{
		_upper_bound_eq = std::max<T>(upper_bound, lower_bound);
		_lower_bound = std::min<T>(upper_bound, lower_bound);
	}

	template<class T>
	bool range<T>::operator==(const range & r)const
	{
		return r._lower_bound == _lower_bound && r._upper_bound_eq == _upper_bound_eq;
	}

	template<class T>
	bool range<T>::operator==(T value)const
	{
		return value > _lower_bound && value <= _upper_bound_eq;
	}

	template<class T>
	bool range<T>::operator>(T value)const
	{
		return value <= _lower_bound;
	}

	template<class T>
	bool range<T>::operator<(T data)const
	{
		return data > _upper_bound_eq;
	}

	template<class T>
	inline bool range<T>::operator!=(T data) const
	{
		return !*this == data;
	}

	template<class T>
	void range<T>::reset_to(const range & r)
	{
		_upper_bound_eq = r._upper_bound_eq;
		_lower_bound = r._lower_bound;
	}

	template<class T>
	void range<T>::print(std::ostream & o) const
	{
		o << "(" << _lower_bound << "," << _upper_bound_eq << "]";
	}

	template<class T>
	T range<T>::get_hash() const
	{
		return std::hash<T>()(_upper_bound_eq + _lower_bound);
	}

	template<class T>
	range<T> & range<T>::operator=(const range & r)
	{
		_upper_bound_eq = r._upper_bound_eq;
		_lower_bound = r._lower_bound;
		return *this;
	}

	template<class T>
	bool range<T>::operator>(const range & r)const
	{
		return _lower_bound >= r._upper_bound_eq && _upper_bound_eq > r._upper_bound_eq && _lower_bound > r._lower_bound;
	}

	template<class T>
	bool range<T>::operator<(const range & r)const
	{
		return _upper_bound_eq <= r._lower_bound && _upper_bound_eq < r._upper_bound_eq && _lower_bound < r._lower_bound;
	}

	template<class T>
	inline bool range<T>::operator!=(const range & r) const
	{
		return _upper_bound_eq != r._upper_bound_eq || _lower_bound != r._lower_bound;
	}
}
#endif // !RANGE_H

