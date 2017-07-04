﻿#ifndef DATA_H
#define DATA_H
#include<vector>
#include<algorithm>
#include<stack>
#include<iostream>
#include<memory>
#include<valarray>
#include<functional>
#include<cassert>
#include<map>
#include <type_traits>
/*g++*/
#include<cfloat>
#include<fstream>
#include<cstring>


namespace myml
{
	using namespace std;

	/**
	 * @class	pseudo_matrix
	 *
	 * @brief	伪矩阵，并不存储实体数据
	 *
	 * @author	woqucc
	 * @date	2017/6/20
	 *
	 * @tparam	T	Generic type parameter
	 */

	template<class T>
	class pseudo_matrix;

	/**
	 * @class	matrix
	 *
	 * @brief	A matrix.
	 *
	 * @author	woqucc
	 * @date	2017/6/20
	 *
	 * @tparam	T	Generic type parameter.
	 */

	template <class T>
	class matrix
	{
	public:

		/**
		* @def	matrix::each_ele(op);
		*
		* @brief	用于在矩阵类内遍历元素时使用。
		* 			因为遍历的代码有点多，懒得一遍遍复制了。
		*
		* @author	Woqucc
		* @date	2017/6/20
		*
		* @param	op	The operation.
		*/

#define each_ele(op) for (size_t row_i = 0; row_i < _row_size; ++row_i) {for (size_t col_i = 0; col_i < _col_size; ++col_i){op;}}

		/**
		* @def	matrix::ele
		*
		* @brief	matrix::each_ele(op)宏中的被遍历的元素的定义。
		*
		* @author	Woqucc
		* @date	2017/6/20
		*/

#define ele _data[row_i][col_i]

		/**
		 * @class	iterator
		 *
		 * @brief	迭代器，遍历整个矩阵.
		 *
		 * @author	Woqucc
		 * @date	2017/6/20
		 */

		class iterator : public std::iterator<std::random_access_iterator_tag, T, ptrdiff_t, T*, T&>
		{
		private:
			/** @brief	矩阵内数据内存的指针 */
			T** _data;
			/** @brief	迭代器指向元素在矩阵内的位置，一行行挨排数 */
			size_t _index;
			/** @brief	矩阵行数*/
			size_t _row_size;
			/** @brief	矩阵列数*/
			size_t _col_size;
		public:
			/**
			 * @fn	iterator::iterator(T** data, size_t row_size, size_t column_size, size_t _index);
			 *
			 * @brief	迭代器构造函数。
			 * 			这玩意主要是matrix类内使用。
			 *
			 * @author	woqucc
			 * @date	2017/6/20
			 *
			 * @param [in,out]	data	   	矩阵内数据内存的指针
			 * @param 		  	row_size   	矩阵行数.
			 * @param 		  	column_size	矩阵列数
			 * @param 		  	_index	   	迭代器指向元素在矩阵内的位置，一行行挨排数.
			 */

			iterator(T** data, size_t row_size, size_t column_size, size_t _index);

			iterator(const iterator& i);

			/**
			 * @fn	virtual size_t iterator::index() const;
			 *
			 * @brief	获取当前index.
			 *
			 * @author	Woqucc
			 * @date	2017/6/20
			 *
			 * @return	A size_t.
			 */

			virtual size_t index() const;

			/**
			 * @fn	virtual T& iterator::operator* () const;
			 *
			 * @brief	迭代器的取址操作符
			 *
			 * @author	Woqucc
			 * @date	2017/6/20
			 *
			 * @return	The result of the operation.
			 */

			virtual  T& operator * () const;

			/**
			 * @fn	virtual bool iterator::operator!= (const iterator& i) const;
			 *
			 * @brief	比较操作符.
			 *
			 * @author	Woqucc
			 * @date	2017/6/20
			 *
			 * @param	i	比较对象.
			 *
			 * @return	不等于的返回真.
			 */

			virtual bool operator != (const iterator& i) const;
			/*
			@brief 迭代器自增操作符
			@return 自增前的迭代器副本
			*/
			virtual typename matrix<T>::iterator& operator ++();
			/*
			@brief 迭代器自减操作符
			@return 自减前的迭代器副本
			*/
			virtual typename matrix<T>::iterator& operator --();
			/*
			@brief  加号操作符
			@return 自减前的迭代器副本
			*/
			virtual typename matrix<T>::iterator operator +(size_t iv) const;
			/*
			@brief  减号操作符
			@return 自减前的迭代器副本
			*/
			virtual size_t operator -(const iterator& i) const;
		};
		/*
		@brief 列迭代器
		按列访问元素
		*/
		class column_iterator
		{
		private:
			T** _data;
			size_t _index;
			size_t _column;
		public:
			column_iterator(T** data, size_t index, size_t column);
			column_iterator(const column_iterator& i);
			virtual size_t index() const;
			virtual T& operator * () const;
			virtual bool operator != (const column_iterator& i) const;
			virtual typename matrix<T>::column_iterator& operator ++();
			virtual typename matrix<T>::column_iterator& operator --();
			virtual typename matrix<T>::column_iterator operator +(size_t iv) const;
			virtual size_t operator -(const column_iterator& i) const;
		};
		/*默认构造函数，构造空矩阵，无法使用*/
		matrix() = default;
		/*
		@brief 打印矩阵中的所有元素
		*/
		virtual void print(ostream& out = cout, char split = ',') const;
		/*
		@brief 按照某列排序
		@param column_num 列数
		*/
		virtual void sort_by(size_t column_num);

		/*
		@brief 获取元素个数
		*/
		virtual size_t row_size() const;
		/*
		@brief 获取元素维数
		*/
		virtual size_t col_size() const;
		/*
		@brief 增加行
		@param row 元素行的首地址指针
		@param size 元素维数
		*/
		virtual void push_back(T *row, size_t size);
		/*
		@brief 检查矩阵中每行数据列数是否相同,即数据是否合法
		@return true 每行数据列数相同，合法
		@return false 每行数据列数不同，非法;矩阵为空
		*/
		virtual bool rect_check() const;
		/*
		@brief 交换两行
		@param row1 待交换的行1
		@param row2 待交换的行2
		*/
		virtual void swap_row(size_t row1, size_t row2);
		/*
		@brief 交换两行
		@param row1 待交换的行1
		@param row2 待交换的行2
		*/
		virtual void swap_col(size_t col1, size_t col2);
		/*
		@brief 获取某一元素
		@param row_num 行数
		@param col_num 列数
		*/
		virtual T& at(size_t row_num, size_t col_num);
		/*
		@brief 获取某一元素
		@param row_num 行数
		@param col_num 列数
		*/
		virtual const T at(size_t row_num, size_t col_num) const;
		/*
		@brief 返回第一个矩阵元素迭代器
		*/
		virtual iterator begin() const;
		/*
		@brief 返回最后一个矩阵元素迭代器
		*/
		virtual iterator end() const;

		/*
		@brief 返回某一列第一个元素的迭代器
		*/
		virtual column_iterator col_begin(size_t column) const;
		/*
		@brief 返回某一列的结尾迭代器（指向null）
		*/
		virtual column_iterator col_end(size_t column) const;

		/*
		@brief 返回子阵
		@param row_begin	第一个元素横坐标，由0开始
		@param column_begin	第一个元素纵坐标，由0开始
		@param row_end	最后一个元素横坐标，由0开始
		@param column_end	最后一个元素纵坐标，由0开始
		@return 指向新子阵的指针（shared_ptr）
		*/
		virtual pseudo_matrix<T> sub_matrix(size_t row_begin, size_t column_begin, size_t row_end, size_t column_end) const;
		/*
		@brief 赋值操作符
		*/
		matrix& operator =(const matrix & rn);
		/*
		@brief 加号操作符
		*/
		matrix& operator +=(const T t);
		/*
		@brief 减号操作符
		*/
		matrix& operator -=(const T t);
		/*
		@brief 乘法操作符
		*/
		matrix& operator *=(const T t);
		/*
		@brief 除号操作符
		*/
		matrix& operator /=(const T t);
		/*
		@brief 取余操作符
		*/
		matrix& operator %=(const T t);
		/*
		@brief 矩阵相加
		*/
		matrix<T> operator +=(const matrix<T>& t);

		/*
		@brief 矩阵相减
		*/
		matrix<T> operator -=(const matrix<T>& t);

		/*
		括号操作符，用来访问元素
		*/
		T& operator ()(size_t row, size_t col);
		/*
		括号操作符，用来访问元素
		*/
		T operator ()(size_t row, size_t col) const;

		/*
		括号操作符，用来访问元素，从前到后访问
		*/
		T& operator ()(size_t index);
		/*
		括号操作符，用来访问元素，从前到后访问
		*/
		T operator ()(size_t index) const;

		/*
		@brief 本矩阵每个元素都exp
		*/
		matrix& exp();




		/*
		@brief 选取矩阵中的指定行
		*/
		virtual pseudo_matrix<T> fetch_row(const initializer_list<size_t>& row_indexs) const;

		/*
		@brief 提取满足指定条件的行
		*/
		virtual pseudo_matrix<T> fetch_row(function<bool(const T* val, size_t col_size)> condition) const;

		/*
		@brief 提取指定行成为新的矩阵
		*/
		//virtual matrix<T> fetch_column(const index_array& column_indexs) const;

		/*
		@brief 删除本矩阵中指定的行
		*/
		virtual void remove_row(const initializer_list<size_t>& row_indexs);

		/*
		@brief 不排序，仅仅获取其顺序
		*/
		virtual valarray<size_t> get_order(size_t column_num) const;

		/*初始化列表形式初始化*/
		void push_back(const initializer_list<T>& row);
		/*返回行指针数组*/
		T** raw_data();
		/*返回行指针数组*/
		T** raw_data() const;
		/*真正构造函数*/
		matrix<T>(size_t row_size, size_t col_size);
		/*转移构造函数*/
		matrix<T>(matrix&& m);
		/*初始化列表*/
		matrix<T>(const initializer_list<initializer_list<T>>&);
		/*复制构造函数*/
		matrix<T>(const matrix& m);
		/*析构函数*/
		virtual ~matrix<T>();

		/*获取某一行数据，仅用于读取*/
		pseudo_matrix<T> row(size_t row_index);
		/*获取某列数据，仅用于读取*/
		pseudo_matrix<T> col(size_t col_index);
		/*获取某一行数据，仅用于读取*/
		pseudo_matrix<T> rows(size_t begin, size_t end);
		/*获取某列数据，仅用于读取*/
		pseudo_matrix<T> cols(size_t begin, size_t end);


		/*获取某一行数据，仅用于读取*/
		const pseudo_matrix<T> row(size_t row_index) const;
		/*获取某列数据，仅用于读取*/
		const pseudo_matrix<T> col(size_t col_index) const;
		/*获取某一行数据，仅用于读取*/
		const pseudo_matrix<T> rows(size_t begin, size_t end) const;
		/*获取某列数据，仅用于读取*/
		const pseudo_matrix<T> cols(size_t begin, size_t end) const;

		/*重新分配大小*/
		void resize(size_t row_size, size_t col_size);
		/*设置所有元素为指定值*/
		void fill(const T &t);
		/*是否有数据*/
		bool has_data();
		/*转置本矩阵*/
		matrix<T>& transpose();
		/*将本矩阵变为本矩阵的逆*/
		matrix<T>& inverse();
		/*改变大小*/
		matrix<T>& reshape(size_t row_size, size_t col_size);
		/*最大元素的位置*/
		pair<size_t, size_t> max_position() const;
		/*交换两个矩阵的内容*/
		void swap(matrix sm);
		/*最大元素*/
		T max() const;
		/*获取某一元素个数*/
		size_t count(const T& t) const;
		/*判断是否是向量*/
		bool is_vector() const;
		/*元素个数*/
		size_t size() const;
	protected:
		T* _memory = nullptr;
		T** _data = nullptr;
		size_t _row_size = 0;
		size_t _col_size = 0;
		size_t _cur_row_pos = 0;
	};

	template<class T>
	inline void matrix<T>::print(ostream& out, char split) const
	{
		//out.precision(std::numeric_limits<T>::digits10);
		out << fixed;
		for (size_t row = 0; row < row_size(); row++)
		{
			for (size_t column = 0; column < col_size() - 1; column++)
			{
				out << at(row, column) << split;
			}
			out << at(row, col_size() - 1) << endl;
		}
	}

	template<class T>
	inline matrix<T>& matrix<T>::operator = (const matrix<T> & rn)
	{
		//已经是实体矩阵了，不能随意赋值
		if (_data != nullptr && _memory != nullptr)
		{
			assert(rn.row_size() == _row_size && rn.col_size() == _col_size);
		}
		//矩阵尚未实体化
		else
		{
			if (rn.row_size() > 0 && rn.col_size() > 0)
				resize(rn.row_size(), rn.col_size());
		}
		for (size_t row_i = 0; row_i < _row_size; row_i++)
		{
			memcpy(_data[row_i], rn._data[row_i], sizeof(T) / sizeof(char) * _col_size);
		}
		_cur_row_pos = rn._cur_row_pos;
		return *this;
	}
	template<class T>
	inline matrix<T> & matrix<T>::operator+=(const T t)
	{
		each_ele(ele += t);
		return *this;
	}
	template<class T>
	inline matrix<T> & matrix<T>::operator-=(const T t)
	{
		each_ele(ele -= t);
		return *this;
	}
	template<class T>
	inline matrix<T> & matrix<T>::operator*=(const T t)
	{
		each_ele(ele *= t);
		return *this;
	}
	template<class T>
	inline matrix<T> & matrix<T>::operator/=(const T t)
	{
		assert(t != 0);
		each_ele(ele /= t);
		return *this;
	}
	template<class T>
	inline matrix<T> & matrix<T>::operator%=(const T t)
	{
		each_ele(ele %= t);
		return *this;
	}
	template<class T>
	inline T & matrix<T>::operator()(size_t row, size_t col)
	{
		return _data[row][col];
	}
	template<class T>
	inline T matrix<T>::operator()(size_t row, size_t col) const
	{
		return _data[row][col];
	}
	template<class T>
	inline T & matrix<T>::operator()(size_t index)
	{
		return _data[index / _col_size][index % _col_size];
	}
	template<class T>
	inline T matrix<T>::operator()(size_t index) const
	{
		return _data[index / _col_size][index % _col_size];
	}
	template<class T>
	inline matrix<T> & matrix<T>::exp()
	{
		each_ele(ele = std::exp(ele));
		return *this;
	}

	template<class T>
	inline matrix<T> matrix<T>::operator+=(const matrix<T>& t)
	{
		assert(_row_size == t.row_size() && _col_size == t.col_size());
		each_ele(_data[row_i][col_i] += t.at(row_i, col_i));
		return *this;
	}
	template<class T>
	inline matrix<T> matrix<T>::operator-=(const matrix<T>& t)
	{
		assert(_row_size == t.row_size() && _col_size == t.col_size());
		each_ele(_data[row_i][col_i] -= t.at(row_i, col_i));
		return *this;
	}
	//TODO :优化逻辑
	template<class T>
	inline valarray<size_t> matrix<T>::get_order(size_t column_num) const
	{
		valarray<size_t>&& ia = valarray<size_t>(row_size());
		for (size_t i = 0; i < ia.size(); i++)
		{
			ia[i] = i;
		}
		auto temp = col(column_num);
		/*使用栈代替递归，执行快排*/
		stack<pair<size_t, size_t>> qs_stack;
		assert(_col_size > 0 && _row_size > 0);
		qs_stack.push({ 0,row_size() - 1 });
		while (!qs_stack.empty())
		{
			auto begin = qs_stack.top().first;
			auto end = qs_stack.top().second;
			qs_stack.pop();
			auto i = begin, j = end;
			T key = temp.at(i, 0);
			while (i < j)
			{
				//从后向前找到小于key的元素j，将j缓存到i处
				//首次交换时i为begin
				while (i < j && temp.at(j, 0) >= key)
				{
					j--;
				}
				//交换
				std::swap(ia[i], ia[j]);
				temp.swap_row(i, j);
				//从前向后找到第一个大于key的元素i，与j交换，将缓存到j出的begin元素交换至i处
				while (i < j && temp.at(i, 0) <= key)
				{
					i++;
				}
				temp.swap_row(i, j);
				std::swap(ia[i], ia[j]);
			}
			if (i >= begin + 1)
				qs_stack.push({ begin, i - 1 });
			if (i + 1 <= end)
				qs_stack.push({ i + 1, end });
		}
		return move(ia);
	}



	template<class T>
	inline matrix<T>::iterator::iterator(T ** data, size_t row_size, size_t column_size, size_t index) :
		_data(data), _row_size(row_size), _col_size(column_size), _index(index)
	{
	}

	template<class T>
	inline matrix<T>::iterator::iterator(const iterator & i)
	{
		_data = i._data;
		_index = i._index;
		_row_size = i._row_size;
		_col_size = i._col_size;
	}

	template<class T>
	inline size_t matrix<T>::iterator::index() const
	{
		return _index;
	}

	template<class T>
	inline bool matrix<T>::iterator::operator!=(const iterator& i) const
	{
		return this->_index != i._index;
	}

	template<class T>
	typename matrix<T>::iterator& matrix<T>::iterator::operator++()
	{
		_index++;
		return *this;
	}

	template<class T>
	typename matrix<T>::iterator& matrix<T>::iterator::operator--()
	{
		_index--;
		return *this;
	}

	template<class T>
	inline typename matrix<T>::iterator matrix<T>::iterator::operator+(size_t iv) const
	{
		return matrix<T>::iterator(_data, _row_size, _col_size, _index + iv);
	}

	template<class T>
	inline size_t matrix<T>::iterator::operator-(const iterator & i) const
	{
		return _index - i._index;
	}

	template<class T>
	inline T & matrix<T>::iterator::operator*() const
	{
		return _data[_index / _col_size][_index % _col_size];
	}

	template<class T>
	matrix<T>::column_iterator::column_iterator(T**data, size_t index, size_t column) :_data(data), _index(index), _column(column)
	{
	}
	template<class T>
	inline matrix<T>::column_iterator::column_iterator(const column_iterator& i)
	{
		_data = i._data;
		_index = i._index;
		_column = i._column;
	}
	template<class T>
	inline T & matrix<T>::column_iterator::operator*() const
	{
		return _data[_index][_column];
	}

	template<class T>
	inline bool matrix<T>::column_iterator::operator!=(const column_iterator & i) const
	{
		return _index != i._index || _column != i._column;
	}

	template<class T>
	inline typename matrix<T>::column_iterator & matrix<T>::column_iterator::operator++()
	{
		++_index;
		return *this;
	}

	template<class T>
	inline typename matrix<T>::column_iterator & matrix<T>::column_iterator::operator--()
	{
		--_index;
		return *this;
	}

	template<class T>
	inline typename matrix<T>::column_iterator matrix<T>::column_iterator::operator+(size_t iv) const
	{
		return matrix<T>::column_iterator(_data, _index + iv, _column);
	}

	template<class T>
	inline size_t matrix<T>::column_iterator::operator-(const column_iterator & i) const
	{
		return _index - i._index;
	}

	template<class T>
	inline size_t matrix<T>::column_iterator::index() const
	{
		return _index;
	}
	template<class T>
	inline const T  matrix<T>::at(size_t row_num, size_t col_num) const
	{
		return _data[row_num][col_num];
	}
	template<class T>
	typename matrix<T>::iterator matrix<T>::begin() const
	{
		return matrix<T>::iterator(_data, _row_size, _col_size, 0);
	}

	template<class T>
	typename matrix<T>::iterator matrix<T>::end() const
	{
		return matrix<T>::iterator(_data, _row_size, _col_size, row_size()*col_size());
	}

	template<class T>
	typename matrix<T>::column_iterator matrix<T>::col_begin(size_t column) const
	{
		return column_iterator(_data, 0, column);
	}

	template<class T>
	typename matrix<T>::column_iterator matrix<T>::col_end(size_t column) const
	{
		return column_iterator(_data, _row_size, column);
	}


	template<class T>
	inline void matrix<T>::sort_by(size_t column_num)
	{
		/*使用栈代替递归，执行快排*/
		stack<pair<size_t, size_t>> qs_stack;
		qs_stack.push({ 0,row_size() - 1 });
		while (!qs_stack.empty())
		{
			auto begin = qs_stack.top().first;
			auto end = qs_stack.top().second;
			qs_stack.pop();
			auto i = begin, j = end;
			T key = at(i, column_num);
			while (i < j)
			{
				//从后向前找到小于key的元素j，将j缓存到i处
				//首次交换时i为begin
				while (i < j && at(j, column_num) >= key)
				{
					j--;
				}
				//交换
				swap_row(i, j);
				//从前向后找到第一个大于key的元素i，与j交换，将缓存到j出的begin元素交换至i处
				while (i < j && at(i, column_num) <= key)
				{
					i++;
				}
				swap_row(i, j);
			}
			if (i >= begin + 1)
				qs_stack.push({ begin, i - 1 });
			if (i + 1 <= end)
				qs_stack.push({ i + 1, end });
		}
	}
	template<class T>
	inline void matrix<T>::push_back(T * row, size_t size)
	{
		assert(_data != nullptr);
		assert(_row_size > 0);
		assert(_col_size > 0);
		assert(_row_size > _cur_row_pos);
		for (size_t i = 0; i < size; ++i)
		{
			_data[_cur_row_pos][i] = row[i];
		}
		++_cur_row_pos;
	}
	template<class T>
	inline void matrix<T>::push_back(const initializer_list<T>& row)
	{
		assert(_row_size > _cur_row_pos);
		assert(_col_size == row.size());
		for (size_t i = 0; i < row.size(); ++i)
		{
			_data[_cur_row_pos][i] = *(row.begin() + i);
		}
		++_cur_row_pos;
	}
	template<class T>
	inline T ** matrix<T>::raw_data()
	{
		return _data;
	}
	template<class T>
	inline T ** matrix<T>::raw_data() const
	{
		return _data;
	}
	template<class T>
	inline pseudo_matrix<T> matrix<T>::row(size_t row_index)
	{
		assert(row_index < _row_size);
		return pseudo_matrix<T>(*this, row_index, 0, 1, _col_size);
	}
	template<class T>
	inline pseudo_matrix<T> matrix<T>::col(size_t col_index)
	{
		assert(col_index < _col_size);
		return pseudo_matrix<T>(*this, 0, col_index, _row_size, 1);
	}
	template<class T>
	inline pseudo_matrix<T> matrix<T>::rows(size_t begin, size_t end)
	{
		assert(begin < _row_size && end < _row_size);
		return pseudo_matrix<T>(*this, begin, 0, end - begin + 1, _col_size);
	}
	template<class T>
	inline pseudo_matrix<T> matrix<T>::cols(size_t begin, size_t end)
	{
		assert(begin < _col_size && end < _col_size);
		return pseudo_matrix<T>(*this, 0, begin, _row_size, end - begin + 1);
	}

	template<class T>
	inline const pseudo_matrix<T> matrix<T>::row(size_t row_index) const
	{
		assert(row_index < _row_size);
		return pseudo_matrix<T>(*this, row_index, 0, 1, _col_size);
	}
	template<class T>
	inline const pseudo_matrix<T> matrix<T>::col(size_t col_index) const
	{
		assert(col_index < _col_size);
		return pseudo_matrix<T>(*this, 0, col_index, _row_size, 1);
	}
	template<class T>
	inline const pseudo_matrix<T> matrix<T>::rows(size_t begin, size_t end) const
	{
		assert(begin < _row_size && end < _row_size);
		return pseudo_matrix<T>(*this, begin, 0, end - begin + 1, _col_size);
	}
	template<class T>
	inline const pseudo_matrix<T> matrix<T>::cols(size_t begin, size_t end) const
	{
		assert(begin < _col_size && end < _col_size);
		return pseudo_matrix<T>(*this, 0, begin, _row_size, end - begin + 1);
	}
	template<class T>
	inline void matrix<T>::resize(size_t row_size, size_t col_size)
	{
		delete[]_data;
		delete[]_memory;
		_data = new T*[row_size]();
		_memory = new T[row_size*col_size]();
		for (size_t row_i = 0; row_i < row_size; row_i++)
		{
			_data[row_i] = _memory + row_i * col_size;
		}
		_row_size = row_size;
		_col_size = col_size;
	}
	template<class T>
	inline void matrix<T>::fill(const T & t)
	{
		each_ele(ele = t);
	}
	template<class T>
	inline bool matrix<T>::has_data()
	{
		return _data != nullptr && _col_size > 0 && _row_size > 0;
	}
	template<class T>
	inline matrix<T>& matrix<T>::transpose()
	{
		size_t trow_size = _col_size;
		size_t tcol_size = _row_size;
		T** t_data = new T*[trow_size]();
		T* t_memory = new T[_col_size * _row_size]();
		for (size_t row_i = 0; row_i < trow_size; ++row_i)
		{
			t_data[row_i] = t_memory + row_i * tcol_size;
		}
		for (size_t row_i = 0; row_i < trow_size; ++row_i)
		{
			for (size_t col_i = 0; col_i < tcol_size; ++col_i)
			{
				t_data[row_i][col_i] = _data[col_i][row_i];
			}
		}
		_row_size = trow_size;
		_col_size = tcol_size;
		delete[] _data;
		delete[] _memory;
		_data = t_data;
		_memory = t_memory;
		return *this;
	}

	template<class T>
	inline matrix<T>& matrix<T>::inverse()
	{
		assert(_col_size == _row_size);
		//方阵检查
		matrix<T> inv = identity_matrix<T>(_col_size);
		T factor = 0;
		for (size_t i = 0; i < _col_size; ++i)
		{
			if (_data[i][i] == 0)
			{
				for (size_t row_i = i; row_i < _col_size; ++row_i)
				{
					if (_data[row_i][i] != T(0))
					{
						swap_row(row_i, i);
						inv.swap_row(row_i, i);
					}
				}
				//不可逆
				//assert(input_copy(i, i) != 0);
				assert(_data[i][i] > 1E-10L);
			}
			for (size_t row_i = 0; row_i < _col_size; ++row_i)
			{
				if (i == row_i)continue;
				if (_data[row_i][i] == 0)continue;
				factor = _data[row_i][i] / _data[i][i];
				row(row_i) -= row(i) * factor;
				inv.row(row_i) -= inv.row(i) * factor;
			}
		}

		for (size_t i = 0; i < _col_size; ++i)
		{
			inv.row(i) /= _data[i][i];
		}
		swap(inv);
		return *this;
	}

	template<class T>
	inline matrix<T>& matrix<T>::reshape(size_t row_size, size_t col_size)
	{
		assert(row_size * col_size == _row_size * _col_size);
		delete[]_data;
		_data = new T*[row_size]();
		for (size_t row_i = 0; row_i < row_size; ++row_i)
		{
			_data[row_i] = _memory + row_i * col_size;
		}
		_row_size = row_size;
		_col_size = col_size;
		return *this;
	}

	template<class T>
	inline pair<size_t, size_t> matrix<T>::max_position() const
	{
		T max = _data[0][0];
		size_t max_row = 0;
		size_t max_col = 0;
		each_ele(
			if (max < ele)
			{
				max_row = row_i;
				max_col = col_i;
				max = ele;
			}
		);
		return { max_row ,max_col };
	}
	template<class T>
	inline void matrix<T>::swap(matrix<T> sm)
	{
		std::swap(_row_size, sm._row_size);
		std::swap(_col_size, sm._col_size);
		std::swap(_cur_row_pos, sm._cur_row_pos);
		std::swap(_data, sm._data);
		std::swap(_memory, sm._memory);
	}
	template<class T>
	inline T matrix<T>::max() const
	{
		T max = _data[0][0];
		each_ele(
			if (max < ele)
			{
				max = ele;
			}
		);
		return max;
	}
	template<class T>
	inline size_t matrix<T>::count(const T & t) const
	{
		size_t c = 0;
		each_ele(
			if (ele == t)
				++c;
		);
		return c;
	}
	template<class T>
	inline size_t matrix<T>::size() const
	{
		return _col_size * _row_size;
	}
	template<class T>
	inline bool matrix<T>::is_vector() const
	{
		return _row_size == 1 || _col_size == 1;
	}
	template<class T>
	inline bool matrix<T>::rect_check() const
	{
		return true;
	}

	template<class T>
	pseudo_matrix<T> matrix<T>::sub_matrix(size_t row_begin, size_t col_begin, size_t row_end, size_t col_end) const
	{
		/*范围正确*/
		assert(row_begin <= row_end && col_begin <= col_end);
		assert(row_end - row_begin < _row_size && col_end - col_begin < _col_size);
		assert(row_end < _row_size && col_end < _col_size);
		return pseudo_matrix<T>(*this, row_begin, col_begin, row_end - row_begin + 1, col_end - col_begin + 1);
	}

	template<class T>
	inline pseudo_matrix<T> matrix<T>::fetch_row(const initializer_list<size_t>& row_indexs) const
	{
		pseudo_matrix<T> temp(*this, row_indexs.size(), _col_size);
		size_t pi = 0;
		for (auto row_i : row_indexs)
		{
			assert(row_i < _row_size);
			temp.raw_data()[pi++] = _data[row_i];
		}
		return move(temp);
	}

	template<class T>
	inline pseudo_matrix<T> matrix<T>::fetch_row(function<bool(const T* val, size_t col_size)> condition) const
	{
		/*matrix<T> temp(_row_size, _col_size);
		for (size_t row_i = 0; row_i < row_size(); row_i++)
		{
			if (condition(_data[row_i], _col_size))
				temp.push_back(_data[row_i], col_size());
		}*/
		return pseudo_matrix<T>();
	}


	template<class T>
	inline void matrix<T>::remove_row(const initializer_list<size_t>& row_indexs)
	{
		for (auto & ri : row_indexs)
		{
			_data[ri] = nullptr;
		}
		size_t d = 0;
		for (size_t row_i = 0; row_i < _row_size; ++row_i)
		{
			if (_data[row_i] != nullptr)
				_data[d++] = _data[row_i];
		}
		_row_size -= row_indexs.size();
	}

	template<class T>
	inline size_t matrix<T>::row_size() const
	{
		return _row_size;
	}

	template<class T>
	inline size_t matrix<T>::col_size() const
	{
		return _col_size;
	}

	template<class T>
	inline void matrix<T>::swap_row(size_t row1, size_t row2)
	{
		T * temp_row = _data[row1];
		_data[row1] = _data[row2];
		_data[row2] = temp_row;
	}

	template<class T>
	inline void matrix<T>::swap_col(size_t col1, size_t col2)
	{
		for (size_t row_i = 0; row_i < _row_size; ++row_i)
		{
			std::swap(_data[row_i][col1], _data[row_i][col2]);
		}
	}

	template<class T>
	T& matrix<T>::at(size_t row_num, size_t col_num)
	{
		return _data[row_num][col_num];
	}



	template<class T>
	inline matrix<T>::matrix(size_t row_size, size_t col_size)
	{
		resize(row_size, col_size);
	}

	template<class T>
	inline matrix<T>::matrix(matrix<T> && m)
	{
		_data = m._data;
		_memory = m._memory;
		_col_size = m._col_size;
		_row_size = m._row_size;
		_cur_row_pos = m._cur_row_pos;
		//从伪矩阵中拷贝
		if (_memory == nullptr)
		{
			//分配新内存
			_memory = new T[_row_size*_col_size]();
			for (size_t row_i = 0; row_i < _row_size; row_i++)
			{
				T* origin_row = _data[row_i];
				//重新给index矩阵赋值
				_data[row_i] = _memory + row_i * _col_size;
				//拷贝数据
				memcpy(_data[row_i], origin_row, sizeof(T) / sizeof(char) * _col_size);
			}
		}
		m._data = nullptr;
		m._memory = nullptr;
	}
	template<class T>
	inline matrix<T>::matrix(const initializer_list<initializer_list<T>> &data)
	{
		resize(data.size(), data.begin()->size());
		for (auto & row : data)
		{
			push_back(row);
		}
	}
	template<class T>
	inline matrix<T>::matrix(const matrix<T>& m)
	{
		resize(m._row_size, m._col_size);
		for (size_t row_i = 0; row_i < _row_size; row_i++)
		{
			memcpy(_data[row_i], m._data[row_i], sizeof(T) / sizeof(char) * _col_size);
		}
	}
	template<class T>
	inline matrix<T>::~matrix()
	{
		delete[] _data;
		delete[] _memory;
	}
	/*伪矩阵，仅供临时读取使用*/
	template<class T>
	class pseudo_matrix :public matrix<T>
	{
		/*g++*/
		using matrix<T>::_memory;
		using matrix<T>::_data;
		using matrix<T>::_row_size;
		using matrix<T>::_col_size;
		using matrix<T>::_cur_row_pos;
	public:
		pseudo_matrix& operator =(const pseudo_matrix& rn);
		pseudo_matrix& operator =(const matrix<T>& rn);
		pseudo_matrix() = default;
		pseudo_matrix(const matrix<T>& m, size_t row_size, size_t col_size);
		pseudo_matrix(const matrix<T>& m, size_t row_begin, size_t col_begin, size_t row_size, size_t col_size);
		~pseudo_matrix();
		/*向未真实分配内存的矩阵中添加数据，具体行为不知道是啥*/
		void push_back(const initializer_list<T>& row) { assert(false); };
		void push_back(T *row, size_t size) { assert(false); }

	private:
	};
	template<class T>
	inline pseudo_matrix<T> & pseudo_matrix<T>::operator=(const pseudo_matrix & rn)
	{
		for (size_t row_i = 0; row_i < _row_size; row_i++)
		{
			memcpy(_data[row_i], rn._data[row_i], sizeof(T) / sizeof(char) * _col_size);
		}
		return *this;
	}
	template<class T>
	inline pseudo_matrix<T> & pseudo_matrix<T>::operator=(const matrix<T> & rn)
	{
		assert(_row_size == rn.row_size() && _col_size == rn.col_size());
		for (size_t row_i = 0; row_i < _row_size; row_i++)
		{
			memcpy(_data[row_i], rn.raw_data()[row_i], sizeof(T) / sizeof(char) * _col_size);
		}
		return *this;
	}
	template<class T>
	inline pseudo_matrix<T>::pseudo_matrix(const matrix<T>& m, size_t row_size, size_t col_size)
	{
		_row_size = row_size;
		_col_size = col_size;
		//分配index内存，不分配实际内存
		_data = new T*[_row_size]();
		memcpy(_data, m.raw_data(), sizeof(T*) / sizeof(char)*_row_size);
	}
	template<class T>
	inline pseudo_matrix<T>::pseudo_matrix(const matrix<T>& m, size_t row_begin, size_t col_begin, size_t row_size, size_t col_size)
	{
		//分配index内存，不分配实际内存
		_data = new T*[row_size]();
		for (size_t row_i = 0; row_i < row_size; ++row_i)
		{
			_data[row_i] = m.raw_data()[row_i + row_begin] + col_begin;
		}
		_row_size = row_size;
		_col_size = col_size;
	}
	template<class T>
	inline pseudo_matrix<T>::~pseudo_matrix()
	{
		/*不释放真正矩阵的内存*/
		_memory = nullptr;
	}
	/*导入数据部分的全局函数*/
	template<class T>
	bool import_matrix_data(matrix<T>& matrix, istream& in, char split = ',', int line_width = 2048)
	{
		if (in.bad() || in.fail()) {
			cerr << "Can not open file!" << endl;
			return false;
		}
		/*获取列数*/
		char *line = new char[line_width]();
		in.getline(line, line_width);
		size_t col_size = count(line, line + strlen(line), split) + 1;
		size_t row_size = 1;

		if (col_size == 0)
			return false;

		while (!in.eof())
		{
			in.getline(line, line_width);
			row_size++;
		}
		if (strlen(line) == 0)
			row_size--;
		matrix.resize(row_size, col_size);
		/*将文件指针重置到文件首部*/
		in.clear();
		in.seekg(ios::beg);
		for (size_t row_index = 0; row_index < row_size; ++row_index)
		{
			for (size_t col_index = 0; col_index < col_size - 1; ++col_index)
			{
				in >> matrix.at(row_index, col_index);
				split = in.get();
			}
			in >> matrix.at(row_index, col_size - 1);
		}
		delete[] line;
		//in.close();
		return true;
	};
	template<class T>
	bool import_matrix_data(matrix<T>& matrix, initializer_list<initializer_list<T>> data)
	{
		matrix.resize(data.size(), data.begin()->size());
		for (auto & row : data)
		{
			matrix.push_back(row);
		}
		return true;
	}

	/**
	 * @namespace	matrix_operate
	 *
	 * @brief	将需要返回新矩阵的矩阵运算操作放到这个命名空间里啦
	 * 			都写在类里面不得劲
	 */

	namespace matrix_operate
	{
		template<class T>
		matrix<T> exp(const matrix<T>& input)
		{
			matrix<T>&& result = matrix<T>(input.row_size(), input.col_size());
			for (size_t row_i = 0; row_i < input.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < input.col_size(); col_i++)
				{
					result.at(row_i, col_i) = std::exp(input.at(row_i, col_i));
				}
			}
			return move(result);
		}

		/**
		 * @fn	template<class T> T sum(const matrix<T>& input)
		 *
		 * @brief	求矩阵的中元素的和
		 *
		 * @author	Woqucc
		 * @date	2017/6/23
		 *
		 * @tparam	T		Generic type parameter.
		 * @param	input	输入矩阵
		 *
		 * @return	和
		 */

		template<class T>
		T sum(const matrix<T>& input)
		{
			T sum = 0;
			for (const auto& i : input)
			{
				sum += i;
			}
			return sum;
		}

		/**
		 * @fn	template<class T> long double norm_f(const matrix<T>& matrix)
		 *
		 * @brief	矩阵的F范数。
		 * 			矩阵中元素的平方和的开方。
		 *
		 * @author	Woqucc
		 * @date	2017/6/21
		 *
		 * @tparam	T	Generic type parameter.
		 * @param	matrix	The matrix.
		 *
		 * @return	A double.
		 */
		 //TODO:容易溢出，待完善。迭代器效率有点低？
		template<class T>
		T norm_f(const matrix<T>& input)
		{
			T sum = 0;
			for (const auto& i : input)
			{
				sum += i * i;
			}
			return std::sqrt(sum);
		}

		template<class T>
		T v_norm_euclidean(const matrix<T>& input)
		{
			T n = 0;
			for (size_t row_i = 0; row_i < input.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < input.col_size(); col_i++)
				{
					n += input(row_i, col_i) * input(row_i, col_i);
				}
			}
			return std::sqrt(n);
		}
		/**
		* @fn	template<class T> inline matrix<T> operator*(const matrix<T>& op1, const matrix<T>& op2)
		*
		* @brief	矩阵相乘
		*
		* @author	Woqucc
		* @date	2017/6/21
		*
		* @tparam	T	Generic type parameter.
		* @param	op1	The first operation.
		* @param	op2	The second operation.
		*
		* @return	The result of the operation.
		*/

		template<class T>
		inline matrix<T> operator*(const matrix<T>& op1, const matrix<T>& op2)
		{
			/*可以乘*/
			assert(op1.col_size() == op2.row_size());
			matrix<T> result(op1.row_size(), op2.col_size());
			for (size_t row_i = 0; row_i < result.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < result.col_size(); col_i++)
				{
					/* temp = 本矩阵的第row_i行 * t矩阵的地col_i列 */
					result.at(row_i, col_i) = 0;
					for (size_t i = 0; i < op1.col_size(); i++)
					{
						result.at(row_i, col_i) += op1.at(row_i, i) * op2.at(i, col_i);
					}
				}
			}
			return result;
		}

		/**
		 * @fn	template<class T,class E, class = std::enable_if<std::is_fundamental<E>::value>::type> matrix<T> value>::operator* (const matrix<T>& op1, const E& op2)
		 *
		 * @brief	矩阵乘元素。 矩阵的每个元素乘以同一个元素。
		 *
		 * @author	Woqucc
		 * @date	2017/6/21
		 *
		 * @tparam	T	Generic type parameter.
		 * @tparam	E	Type of the e.
		 * @tparam	E	Type of the e.
		 * @param	op1	乘数矩阵。
		 * @param	op2	乘数元素。
		 *
		 * @return	The result of the operation.
		 *
		 * ### tparam	T	Generic type parameter.
		 */

		template<class T, class E, class = std::enable_if<std::is_fundamental<E>::value>::type>
		matrix<T> operator* (const matrix<T>& op1, const E& op2)
		{
			matrix<T> temp(op1.row_size(), op1.col_size());
			for (size_t row_i = 0; row_i < op1.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < op1.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = op1.at(row_i, col_i) * op2;
				}
			}
			return move(temp);
		}

		/**
		 * @fn	template<class T, class E, class = std::enable_if<std::is_fundamental<E>::value>::type> matrix<T> value>::operator* (const E& op1, const matrix<T>& op2)
		 *
		 * @brief	矩阵乘元素。 矩阵的每个元素乘以同一个元素。
		 *
		 * @author	Woqucc
		 * @date	2017/6/23
		 *
		 * @tparam	T	Generic type parameter.
		 * @tparam	E	Type of the e.
		 * @tparam	E	Type of the e.
		 * @param	op1	乘数
		 * @param	op2	乘数矩阵
		 *
		 * @return	The result of the operation.
		 */

		template<class T, class E, class = std::enable_if<std::is_fundamental<E>::value>::type>
		matrix<T> operator* (const E& op1, const matrix<T>& op2)
		{
			matrix<T> temp(op2.row_size(), op2.col_size());
			for (size_t row_i = 0; row_i < op2.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < op2.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = op2.at(row_i, col_i) * op1;
				}
			}
			return move(temp);
		}
		/**
		* @fn	template<class T> matrix<T> operator/ (const matrix<T>& op1, const matrix<T>& op2)
		*
		* @brief	矩阵与矩阵相除
		* 			相同大小的矩阵对应位置相除
		*
		* @author	Woqucc
		* @date	2017/6/21
		*
		* @tparam	T	Generic type parameter.
		* @param	op1	作为除数的矩阵。
		* @param	op2	作为被除数的矩阵。
		*
		* @return	相除后的结果矩阵。
		*/

		template<class T>
		matrix<T> operator/ (const matrix<T>& op1, const matrix<T>& op2)
		{
			assert(op1.row_size() == op2.row_size() && op1.col_size() == op2.col_size());
			matrix<T> temp(op1.row_size(), op1.col_size());
			for (size_t row_i = 0; row_i < op1.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < op1.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = op1.at(row_i, col_i) / op2.at(row_i, col_i);
				}
			}
			return move(temp);
		}
		template<class T, class E, class = std::enable_if<std::is_fundamental<E>::value>::type>
		matrix<T> operator/ (const matrix<T>& op1, const E& op2)
		{
			matrix<T> temp(op1.row_size(), op1.col_size());
			for (size_t row_i = 0; row_i < op1.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < op1.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = op1.at(row_i, col_i) / op2;
				}
			}
			return move(temp);
		}
		template<class T, class E, class = std::enable_if<std::is_fundamental<E>::value>::type>
		matrix<T> operator/ (const E& op1, const matrix<T>& op2)
		{
			matrix<T> temp(op2.row_size(), op2.col_size());
			for (size_t row_i = 0; row_i < op2.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < op2.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = op1 / op2.at(row_i, col_i);
				}
			}
			return move(temp);
		}

		/**
		* @fn	template<class T> inline matrix<T> operator+(const matrix<T>& op1, const matrix<T>& op2)
		*
		* @brief	矩阵相加。
		* 			对应位置元素相加。
		*
		* @author	Woqucc
		* @date	2017/6/21
		*
		* @tparam	T	Generic type parameter.
		* @param	op1	加数矩阵
		* @param	op2	加数矩阵
		*
		* @return	结果矩阵
		*/

		template<class T>
		inline matrix<T> operator+(const matrix<T>& op1, const matrix<T>& op2)
		{
			assert(op1.col_size() == op2.col_size() && op1.row_size() == op2.row_size());
			matrix<T> temp(op1.row_size(), op1.col_size());
			for (size_t row_i = 0; row_i < temp.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < temp.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = op1.at(row_i, col_i) + op2.at(row_i, col_i);
				}
			}
			return move(temp);
		}

		template<class T, class E, class = std::enable_if<std::is_fundamental<E>::value>::type>
		matrix<T> operator+ (const matrix<T>& op1, const E& op2)
		{
			matrix<T> temp(op1.row_size(), op1.col_size());
			for (size_t row_i = 0; row_i < op1.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < op1.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = op1.at(row_i, col_i) + op2;
				}
			}
			return move(temp);
		}

		template<class T, class E, class = std::enable_if<std::is_fundamental<E>::value>::type>
		matrix<T> operator+ (const E& op1, const matrix<T>& op2)
		{
			matrix<T> temp(op2.row_size(), op2.col_size());
			for (size_t row_i = 0; row_i < op2.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < op2.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = op2.at(row_i, col_i) + op1;
				}
			}
			return move(temp);
		}

		template<class T, class E, class = std::enable_if<std::is_fundamental<E>::value>::type>
		matrix<T> operator- (const matrix<T>& op1, const E& op2)
		{
			matrix<T> temp(op1.row_size(), op1.col_size());
			for (size_t row_i = 0; row_i < op1.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < op1.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = op1.at(row_i, col_i) - op2;
				}
			}
			return move(temp);
		}

		template<class T, class E, class = std::enable_if<std::is_fundamental<E>::value>::type>
		matrix<T> operator- (const E& op1, const matrix<T>& op2)
		{
			matrix<T> temp(op2.row_size(), op2.col_size());
			for (size_t row_i = 0; row_i < op2.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < op2.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = op1 - op2.at(row_i, col_i);
				}
			}
			return move(temp);
		}

		/**
		 * @fn	template<class T> matrix<T> operator- (const matrix<T>& input)
		 *
		 * @brief	负号操作符。
		 * 			对矩阵中每个元素取负
		 *
		 * @author	Woqucc
		 * @date	2017/6/21
		 *
		 * @tparam	T		Generic type parameter.
		 * @param	input	输入矩阵
		 *
		 * @return	结果
		 */

		template<class T>
		matrix<T> operator- (const matrix<T>& input)
		{
			matrix<T> output(input.row_size(), input.col_size());
			for (size_t row_i = 0; row_i < input.row_size(); ++row_i)
			{
				for (size_t col_i = 0; col_i < input.col_size(); ++col_i)
				{
					output.at(row_i, col_i) = -input.at(row_i, col_i);
				}
			}
			return output;
		}

		/**
		* @fn	template<class T> inline matrix<T> operator-(const matrix<T>& op1, const matrix<T>& op2)
		*
		* @brief	矩阵相减。
		* 			对应位置元素相减。
		*
		* @author	Woqucc
		* @date	2017/6/21
		*
		* @tparam	T	Generic type parameter.
		* @param	op1	被减数
		* @param	op2	减数
		*
		* @return	矩阵相减结果
		*/

		template<class T>
		inline matrix<T> operator-(const matrix<T>& op1, const matrix<T>& op2)
		{
			assert(op1.col_size() == op2.col_size() && op1.row_size() == op2.row_size());
			matrix<T> temp(op1.row_size(), op1.col_size());
			for (size_t row_i = 0; row_i < temp.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < temp.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = op1.at(row_i, col_i) - op2.at(row_i, col_i);
				}
			}
			return move(temp);
		}
		template<class T>
		bool operator ==(const matrix<T>& op1, const matrix<T>& op2)
		{
			if (op1.col_size() != op2.col_size() || op1.row_size() != op2.row_size())
				return false;
			for (size_t row_i = 0; row_i < op1.row_size(); ++row_i)
			{
				for (size_t col_i = 0; col_i < op1.col_size(); ++col_i)
				{
					if (op1(row_i, col_i) != op2(row_i, col_i))
						return false;
				}
			}
			return true;
		}

		template<class T, class E, class = std::enable_if<std::is_fundamental<E>::value>::type>
		bool operator ==(const matrix<T>& op1, const E& op2)
		{
			if (op1.col_size() != 1 || op1.row_size() != 1)
				return false;
			return op1(0, 0) == op2;
		}

		template<class T, class E, class = std::enable_if<std::is_fundamental<E>::value>::type>
		bool operator ==(const E& op2, const matrix<T>& op1)
		{
			if (op1.col_size() != 1 || op1.row_size() != 1)
				return false;
			return op1(0, 0) == op2;
		}

		/**
		 * @fn	template<class T> matrix<T> dot(const matrix<T>& op1, const matrix<T>& op2)
		 *
		 * @brief	矩阵点乘
		 * 			矩阵中对应位置的元素相乘。
		 *
		 * @author	Woqucc
		 * @date	2017/6/21
		 *
		 * @tparam	T	Generic type parameter.
		 * @param	op1	乘数
		 * @param	op2	乘数
		 *
		 * @return	点乘后的矩阵
		 */

		template<class T>
		matrix<T> dot(const matrix<T>& op1, const matrix<T>& op2)
		{
			assert(op1.row_size() == op2.row_size() && op1.col_size() == op2.col_size());
			matrix<T> temp(op1.row_size(), op1.col_size());
			for (size_t row_i = 0; row_i < op1.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < op1.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = op1.at(row_i, col_i) * op2.at(row_i, col_i);
				}
			}
			return move(temp);
		}
		template<class T>
		T dot_product(matrix<T> op1, matrix<T> op2)
		{
			assert(op1.size() == op2.size());
			T sum = 0;
			for (size_t i = 0; i < op1.size(); ++i)
			{
				sum += op1(i) * op2(i);
			}
			return sum;
		}
		/**
		 * @fn	template<class T> matrix<T> transpose(const matrix<T>& input)
		 *
		 * @brief	转置一个矩阵
		 *
		 * @author	Woqucc
		 * @date	2017/6/21
		 *
		 * @tparam	T		Generic type parameter.
		 * @param	input	输入矩阵
		 *
		 * @return	转置后的矩阵
		 */

		template<class T>
		matrix<T> transpose(const matrix<T>& input)
		{
			matrix<T> temp(input.col_size(), input.row_size());
			for (size_t row_i = 0; row_i < input.col_size(); ++row_i)
			{
				for (size_t col_i = 0; col_i < input.row_size(); ++col_i)
				{
					temp.at(row_i, col_i) = input.at(col_i, row_i);
				}
			}
			return temp;
		}



		template<class T>
		matrix<T> pow(const matrix<T>& input, const T& index)
		{
			matrix<T> temp(input.row_size(), input.col_size());
			for (size_t row_i = 0; row_i < input.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < input.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = std::pow(input.at(row_i, col_i), index);
				}
			}
			return move(temp);
		}

		template<class T>
		matrix<T> sqrt(const matrix<T>& input)
		{
			matrix<T> temp(input.row_size(), input.col_size());
			for (size_t row_i = 0; row_i < input.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < input.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = std::sqrt(input.at(row_i, col_i));
				}
			}
			return move(temp);
		}

		template<class T>
		matrix<T> log(const matrix<T>& input)
		{
			matrix<T> temp(input.row_size(), input.col_size());
			for (size_t row_i = 0; row_i < input.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < input.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = std::log(input.at(row_i, col_i));
				}
			}
			return move(temp);
		}

		/**
		 * @fn	template<class T> T max(const matrix<T>& input)
		 *
		 * @brief	获取矩阵中的最大值
		 *
		 * @author	Woqucc
		 * @date	2017/6/21
		 *
		 * @tparam	T	Generic type parameter.
		 * @param	input	输入矩阵
		 *
		 * @return	矩阵中的最大值
		 */

		template<class T>
		T max(const matrix<T>& input)
		{
			T max = -LDBL_MAX;
			for (size_t row_i = 0; row_i < input.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < input.col_size(); col_i++)
				{
					max = max > input.at(row_i, col_i) ? max : input.at(row_i, col_i);
				}
			}
			return max;
		}

		/**
		 * @fn	template<class T> T average(const matrix<T>& input)
		 *
		 * @brief	求矩阵中元素的平均值。
		 *
		 * @author	Woqucc
		 * @date	2017/6/21
		 *
		 * @tparam	T		Generic type parameter.
		 * @param	input	输入矩阵
		 *
		 * @return	平均值
		 */

		template<class T>
		T average(const matrix<T>& input)
		{
			T sum = 0;
			for (size_t row_i = 0; row_i < input.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < input.col_size(); col_i++)
				{
					sum += input.at(row_i, col_i);
				}
			}
			return sum / (input.row_size() * input.col_size());
		}

		/**
		 * @fn	template<class T> T variance(const matrix<T>& input)
		 *
		 * @brief	求矩阵中元素的方差
		 *
		 * @author	Woqucc
		 * @date	2017/6/21
		 *
		 * @tparam	T		Generic type parameter.
		 * @param	input	输入矩阵.
		 *
		 * @return	方差值
		 */

		template<class T>
		T variance(const matrix<T>& input)
		{
			//DX =  E(X^2) - (EX)^2
			T aver = 0;
			T aver_square = 0;
			for (size_t row_i = 0; row_i < input.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < input.col_size(); col_i++)
				{
					aver_square += input.at(row_i, col_i) * input.at(row_i, col_i);
					aver += input.at(row_i, col_i);
				}
			}
			/*防止上溢*/
			//(EX)^2
			aver /= input.row_size() * input.col_size();
			aver *= aver;
			//E(X^2)
			aver_square /= input.row_size() * input.col_size();
			return aver_square - aver;
		}

		/**
		 * @fn	template<class T> matrix<T> diag(const matrix<T>& input)
		 *
		 * @brief	生成对角阵。
		 * 			将输入矩阵的每个元素放置到主对角线上，生成一个对角阵。
		 *
		 * @author	Woqucc
		 * @date	2017/6/20
		 *
		 * @tparam	T	Generic type parameter.
		 * @param	input	输入矩阵。
		 *
		 * @return	对角阵
		 */

		template<class T>
		matrix<T> diag(const matrix<T>& input)
		{
			matrix<T> d(input.row_size() * input.col_size(), input.row_size() * input.col_size());
			d.fill(T(0));
			size_t index = 0;
			for (const auto& i : input)
			{
				d.at(index, index) = i;
				++index;
			}
			return d;
		}
		/*克罗内克积*/
		template<class T>
		matrix<T> kronecker_product(const matrix<T>& op1, const matrix<T>& op2)
		{
			matrix<T> result(op1.row_size() * op2.row_size(), op1.col_size() * op2.col_size());
			for (size_t row_i = 0; row_i < result.row_size(); ++row_i)
			{
				for (size_t col_i = 0; col_i < result.col_size(); ++col_i)
				{
					result(row_i, col_i) = op1(row_i / op1.row_size(), col_i / op1.col_size()) * op2(row_i % op2.row_size(), col_i % op2.col_size());
				}
			}
			return result;
		}

		/*生成单位矩阵*/
		template<class T>
		matrix<T> identity_matrix(size_t size)
		{
			matrix<T> result(size, size);
			for (size_t i = 0; i < size; i++)
			{
				result.at(i, i) = T(1);
			}
			return result;
		}

		template<class T>
		void identity_matrix(matrix<T>& input)
		{
			for (size_t row_i = 0; row_i < input.row_size(); ++row_i)
			{
				for (size_t col_i = 0; col_i < input.col_size(); ++col_i)
				{
					input(row_i, col_i) = row_i == col_i ? 1 : 0;
				}
			}
		}
		/**
		 * @fn	template<class T> matrix<T> reshape(const matrix<T> &input, size_t row_size, size_t col_size)
		 *
		 * @brief	改变矩阵形状.
		 *			方式为从左到右取按行取每一行的元素，并按照从左到右的顺序放到新形状的矩阵中。
		 * @author	Woqucc
		 * @date	2017/6/21
		 *
		 * @tparam	T	Generic type parameter.
		 * @param	input		输入矩阵
		 * @param	row_size	新矩阵的行数。
		 * @param	col_size	新矩阵的列数。
		 *
		 * @return	新矩阵
		 */

		template<class T>
		matrix<T> reshape(const matrix<T> &input, size_t row_size, size_t col_size)
		{
			assert(input.row_size() * input.col_size() == row_size * col_size);
			matrix<T> result = input;
			result.reshape(row_size, col_size);
			return result;
		}

		/**
		 * @fn	template<class T> matrix<T> inverse(const matrix<T> &input)
		 *
		 * @brief	求矩阵的逆矩阵。
		 * 			初等行变换（gauss-jordan），不行啊。
		 *
		 * @author	woqucc
		 * @date	2017/6/20
		 *
		 * @tparam	T	    矩阵的模版参数.
		 * @param	input	输入矩阵
		 *
		 * @return	矩阵的逆;
		 */

		template<class T>
		matrix<T> inverse(const matrix<T> &input)
		{
			//方阵检查
			assert(input.row_size() == input.col_size());
			matrix<T> inv = input;
			inv.inverse();
			return inv;
		}

		template<class T>
		void swap(matrix<T>& s1, matrix<T>& s2)
		{
			s1.swap(s2);
		}

		/**
		 * @fn	template<class T> tuple<matrix<T>,T> householder(const matrix<T> &vector_x, const matrix<T> &vector_y)
		 *
		 * @brief	Householder变换
		 * 			求出可以将向量x变换为y的矩阵H和洗漱rho
		 * 			即在等式 H * x = rho * y中，输入向量x，y 求出矩阵H和系数rho
		 *
		 * @author	Woqucc
		 * @date	2017/6/28
		 *
		 * @tparam	T	Generic type parameter.
		 * @param	vector_x	向量x
		 * @param	vector_y	向量y.
		 *
		 * @return	HouseHolder矩阵，rho;
		 */

		template<class T>
		tuple<matrix<T>, T> householder(const matrix<T> &vector_x, const matrix<T> &vector_y)
		{
			assert(vector_x.is_vector() && vector_y.is_vector());
			assert(vector_x.size() == vector_y.size());
			T rho = vector_x(0, 0) > 0 ? -v_norm_euclidean(vector_x) / v_norm_euclidean(vector_y) : v_norm_euclidean(vector_x) / v_norm_euclidean(vector_y);
			// v = x - y
			matrix<T> vetcor_v = vector_x;
			vetcor_v -= rho * vector_y;
			// v = v / ||v||
			vetcor_v /= v_norm_euclidean(vetcor_v);
			// h = I - 2 * v * v'
			matrix<T> h_matrix = identity_matrix<T>(vector_x.size());
			//TODO:是否需要对列还是行进行判断？应该不需要吧
			//if (vetcor_v.row_size() == 1)
			//	h_matrix -= 2 * transpose(vetcor_v) * vetcor_v;
			//else
			h_matrix -= 2 * vetcor_v * transpose(vetcor_v);
			return { move(h_matrix), rho };
		}

		/**
		 * @fn	template<class T> tuple<matrix<T>, matrix<T>> qr(const matrix<T> &input)
		 *
		 * @brief	将矩阵进行QR分解。
		 * 			A = QR，其中Q为正交阵，R为三角阵。
		 *			householder变换法。
		 * @author	Woqucc
		 * @date	2017/6/28
		 *
		 * @tparam	T	Generic type parameter.
		 * @param	input	输入矩阵
		 *
		 * @return	{Q,R};
		 */

		template<class T>
		tuple<matrix<T>, matrix<T>> qr(const matrix<T> &input)
		{
			size_t n = input.row_size();
			size_t min_size = min(n - 1, input.col_size());
			matrix<T> r = input;
			matrix<T> q = identity_matrix<T>(n);
			//householder变换基
			matrix<T> y(n, 1);
			matrix<T> h(n, n);
			y(0, 0) = T(1);
			for (size_t i = 0; i < min_size; ++i)
			{
				//TODO:等待一个优化
				//进行变换
				identity_matrix(h);
				//使用householder变换将Q变换成正交阵，householder矩阵代表变换方法
				h.sub_matrix(i, i, n - 1, n - 1) = get<0>(householder(r.sub_matrix(i, i, n - 1, i), y.rows(0, n - i - 1)));
				//TODO 编写*=矩阵操作符，可以节省一部分内存
				q = q * h;
				r = h * r;
			}
			//input: m x n ;
			//q: m x n;
			//r: n x n
			/*
			size_t m = input.row_size(), n = input.col_size();

			//Gram-Schmidt正交化，上三角矩阵R记录下变换过程
			//数值不稳定，弃了
			r(0, 0) = v_norm_euclidean(input.col(0));
			q.col(0) = input.col(0) / r(0, 0);
			for (size_t j = 1; j < n; ++j)
			{
				q.col(j) = input.col(j);
				for (size_t i = 0; i < j; ++i)
				{
					//(transpose(q.col(i)) * input.col(j)).print();
					r(i, j) = (transpose(q.col(i)) * input.col(j))(0,0);
					q.col(j) -= r(i, j) * q.col(i);
				}
				r(j, j) = v_norm_euclidean(q.col(j));
				q.col(j) /= r(j, j);
			}
			*/
			return { move(q), move(r) };
		}

		/**
		 * @fn	template<class T> tuple<matrix<T>, matrix<T>, matrix<T>> svd(const matrix<T> &input)
		 *
		 * @brief	对矩阵进行SVD分解
		 *			将矩阵分解为： U * S * V'
		 * @author	Woqucc
		 * @date	2017/6/29
		 *
		 * @tparam	T	Generic type parameter.
		 * @param	input	The input.
		 *
		 * @return	｛U,S,V｝;
		 */

		template<class T>
		tuple<matrix<T>, matrix<T>, matrix<T>> svd_qr(const matrix<T> &input)
		{
			size_t m = input.row_size();
			size_t n = input.col_size();
			matrix<T> u = identity_matrix<T>(m);
			matrix<T> s = transpose(input);
			matrix<T> st = transpose(s);
			matrix<T> v = identity_matrix<T>(n);
			matrix<T> q(m, m);
			matrix<T> qn(n, n);
			size_t iter_count = 26;
			while (iter_count--)
			{
				std::tie(q, st) = qr(transpose(s));
				u = u * q;
				s = transpose(st);
				std::tie(qn, s) = qr(s);
				v = v * qn;
			}
			s.transpose();
			for (size_t i = 0; i < min(m.n); ++i)
			{
				if (s(i, i) < 0)
				{
					u.col(i) *= -1;
					s(i, i) = -s(i, i);
				}
			}

			return { move(u),move(s) ,move(v) };
		}
		template<class T>
		matrix<T> pseudo_inverse(const matrix<T>& input)
		{
			matrix<T> pinv(input.col_size(), input.row_size());
			matrix<T> u(input.row_size(), input.row_size());
			matrix<T> s(input.row_size(), input.col_size());
			matrix<T> v(input.col_size(), input.col_size());
			//TODO :: 这个svd也不行
			std::tie(u, s, v) = svd_hestenes(input, std::numeric_limits<T>::epsilon() * 1024 * 16);
			u.transpose();
			s.transpose();
			for (size_t i = 0; i < std::min(input.col_size(), input.row_size()); ++i)
			{
				s(i, i) = T(1) / s(i, i);
			}
			return v *s *u;

		}

		/**
		 * @fn	template<class T> tuple<matrix<T>, matrix<T>, matrix<T>> svd_hestenes(const matrix<T> &input, T epsilon = T(1E-10))
		 *
		 * @brief	单边jacobi旋转求svd
		 * 
		 *
		 * @author	Woqucc
		 * @date	2017/7/4
		 *
		 * @tparam	T	Generic type parameter.
		 * @param	input  	The input.
		 * @param	epsilon	(Optional) The epsilon.
		 *
		 * @return	A tuple&lt;matrix&lt;T&gt;,matrix&lt;T&gt;,matrix&lt;T&gt;&gt;
		 */

		template<class T>
		tuple<matrix<T>, matrix<T>, matrix<T>> svd_hestenes(const matrix<T> &input, T epsilon = T(1E-10))
		{
			size_t m = input.row_size();
			size_t n = input.col_size();
			matrix<T> temp_input = input;
			matrix<T> u = identity_matrix<T>(m);
			matrix<T> s(input.row_size(), input.col_size());
			matrix<T> v = identity_matrix<T>(n);

			while (orth_precision_column(temp_input) > epsilon)
			{
				for (size_t i = 0; i < n; i++)
				{
					for (size_t j = i + 1; j < n; ++j)
					{
						auto gm = orth_givens<T>(temp_input, i, j);
						givens_rotate(v, gm, i, j);
					}
				}
			}
			std::tie(u, s) = qr(temp_input);
			return { move(u),move(s) ,move(v) };
		}
		template<class T>
		T orth_precision_column(const matrix<T> &input)
		{
			T orth_pre = 0;
			for (size_t i = 0; i < input.col_size(); i++)
			{
				for (size_t j = i + 1; j < input.col_size(); j++)
				{
					orth_pre = std::max(orth_pre, abs(dot_product(input.col(i), input.col(j))));
				}
			}
			return orth_pre;
		}
		template<class T>
		matrix<T> orth_givens(matrix<T> &input, size_t i, size_t j)
		{
			matrix<T> givens_matrix(2, 2);
			T p = dot_product(input.col(i), input.col(j)), q, v;
			q = dot_product(input.col(i), input.col(i)) - dot_product(input.col(j), input.col(j));
			v = std::sqrt(4 * p * p + q * q);
			if (q >= 0)
			{
				givens_matrix(0, 0) = std::sqrt((v + q) / (2 * v));//c 
				givens_matrix(1, 0) = p / (v * givens_matrix(0, 0));//s
			}
			else
			{
				givens_matrix(1, 0) = p > 0 ? std::sqrt((v - q) / (2 * v)) : -std::sqrt((v - q) / (2 * v));//s
				givens_matrix(0, 0) = p / (v * givens_matrix(1, 0));//c
			}
			T temp_i, temp_j;
			for (size_t row_i = 0; row_i < input.row_size(); ++row_i)
			{
				temp_i = input(row_i, i) * givens_matrix(0, 0) + input(row_i, j) * givens_matrix(1, 0);
				temp_j = -input(row_i, i) * givens_matrix(1, 0) + input(row_i, j) * givens_matrix(0, 0);
				input(row_i, i) = temp_i;
				input(row_i, j) = temp_j;
			}
			givens_matrix(1, 1) = givens_matrix(0, 0);
			givens_matrix(0, 1) = -givens_matrix(1, 0);
			return givens_matrix;
		}
		template<class T>
		void givens_rotate(matrix<T> &input, const matrix<T> &tiny_givens_matrix, size_t i, size_t j)
		{
			T temp_i, temp_j;
			for (size_t row_i = 0; row_i < input.row_size(); ++row_i)
			{
				temp_i = input(row_i, i) * tiny_givens_matrix(0, 0) + input(row_i, j) * tiny_givens_matrix(1, 0);
				temp_j = -input(row_i, i) * tiny_givens_matrix(1, 0) + input(row_i, j) * tiny_givens_matrix(0, 0);
				input(row_i, i) = temp_i;
				input(row_i, j) = temp_j;
			}
		}
	}
	/*矩阵数据标准化*/
	namespace matrix_normalization
	{

		/*设置元素值的范围，*/

		/**
		 * @fn	template<class T> void set_range(matrix<T>& input,T lower_bound, T upper_bound)
		 *
		 * @brief	设置矩阵中元素值的取值范围.
		 * 			将大于上限的元素设置为上限，将小于下限的元素设置为下限
		 *
		 * @author	Woqucc
		 * @date	2017/6/20
		 *
		 * @tparam	T	Generic type parameter.
		 * @param [in,out]	input		目标矩阵
		 * @param 		  	lower_bound	下限
		 * @param 		  	upper_bound	上限
		 */

		template<class T>
		void set_range(matrix<T>& input, T lower_bound, T upper_bound)
		{
			for (auto &i : input)
			{
				if (i < lower_bound)
					i = lower_bound;
				else if (i > upper_bound)
					i = upper_bound;
			}
		}

		/**
		 * @fn	template<class src, class dst> matrix<dst> convert_matrix_type(const matrix<src>& input)
		 *
		 * @brief	转换矩阵类型.
		 *
		 * @author	Woqucc
		 * @date	2017/6/20
		 *
		 * @tparam	src	原矩阵类型
		 * @tparam	dst	目标矩阵类型
		 * @param	input	输入矩阵
		 *
		 * @return	转换完成的矩阵类型.
		 */

		template<class src, class dst>
		matrix<dst> convert_matrix_type(const matrix<src>& input)
		{
			matrix<dst> temp(input.row_size(), input.col_size());
			for (size_t row_i = 0; row_i < input.row_size(); ++row_i)
			{
				for (size_t col_i = 0; col_i < input.col_size(); ++col_i)
				{
					temp.at(row_i, col_i) = dst(input.at(row_i, col_i));
				}
			}
			return move(temp);
		}
		/*将数据的label转换为连续的整数*/
		template<class T, class E>
		map<T, E> serialize_label(const matrix<T>& label_matrix, matrix<E>& serialized_label)
		{
			map<T, E> label_map;
			for (auto &i : label_matrix)
			{
				if (label_map.count(i) == 0)
					label_map.insert({ i,0 });
			}
			E map_i = 0;
			for (auto &l : label_map)
			{
				l.second = map_i++;
			}
			serialized_label.resize(label_matrix.row_size(), 1);
			for (size_t row_i = 0; row_i < label_matrix.row_size(); ++row_i)
			{
				static_cast<E&>(serialized_label.at(row_i, 0)) = label_map[label_matrix.at(row_i, 0)];
			}
			return label_map;
		}
		/*
		一列为一个
		z-score 正则化：减去均值除以方差
		*/
		template<class T>
		void zero_mean_by_col(matrix<T>&& m)//注意这里的参数类型为右值引用，这样写可以使函数可以绑定到右值上，相当于把右值当作左值使用
		{
			for (size_t col_i = 0; col_i < m.col_size(); ++col_i)
			{
				//DX =  E(X^2) - (EX)^2
				T aver = 0;
				T variance = 0;
				for (size_t row_i = 0; row_i < m.row_size(); ++row_i)
				{
					aver += m.at(row_i, col_i);
					variance += m.at(row_i, col_i) * m.at(row_i, col_i);
				}
				aver /= m.row_size();
				variance /= m.row_size();
				variance -= aver * aver;
				for (size_t row_i = 0; row_i < m.row_size(); ++row_i)
				{
					m.at(row_i, col_i) = (m.at(row_i, col_i) - aver) / variance;
				}
			}

		}
	};

};
#endif