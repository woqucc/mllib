#ifndef DATA_H
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
/*g++*/
#include<cfloat>
#include<fstream>
#include<cstring>


namespace myml
{
	using namespace std;

	/*声明子类*/
	template<class T>
	class pseudo_matrix;
	/*
	@brief 矩阵类，使用数组实现
	*/

	template <class T>
	class matrix
	{
	public:
		//将valarray作为可以push_back的一种形式
		using index_array = valarray<size_t>;
		/*遍历元素,row_i,col_i为迭代坐标*/
#define each_ele(op) for (size_t row_i = 0; row_i < _row_size; row_i++) {for (size_t col_i = 0; col_i < _col_size; col_i++){op;}}
#define ele _data[row_i][col_i]
		class iterator : public std::iterator<std::random_access_iterator_tag,T,ptrdiff_t,T*,T&>
		{
		private:
			T** _data;
			matrix<T>& _matrix;/*< 存储矩阵*/
			size_t _index;/*< 存储索引*/
			size_t _column_size;
			size_t _row_size;
		public:
			iterator(matrix<T>& matrix, size_t index);
			/*
			@brief 返回当前index
			*/
			virtual size_t index() const;
			/*
			@brief 迭代器取址操作符
			@return T& 元素引用
			*/
			virtual  T& operator * () const;
			/*
			@brief 迭代器比较操作符
			@param i 其他迭代器
			@return true 不等
			@return false 相等
			*/
			virtual bool operator != (iterator& i) const;
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
			virtual typename matrix<T>::iterator& operator +(size_t iv);
			/*
			@brief  减号操作符
			@return 自减前的迭代器副本
			*/
			virtual size_t operator -(const iterator& i);
		};
		/*
		@brief 列迭代器
		按列访问元素
		*/
		class column_iterator
		{
		private:
			matrix<T>& _matrix;
			size_t _index;
			size_t _column;
		public:
			column_iterator(matrix<T>& matrix, size_t index, size_t column);
			virtual size_t index() const;
			virtual T& operator * () const;
			virtual bool operator != (column_iterator& i);
			virtual typename matrix<T>::column_iterator& operator ++();
			virtual typename matrix<T>::column_iterator& operator --();
			virtual typename matrix<T>::column_iterator& operator +(size_t iv);
			virtual size_t operator -(const column_iterator& i);
		};
		/*默认构造函数，构造空矩阵，无法使用*/
		matrix() = default;
		/*
		@brief 打印矩阵中的所有元素
		*/
		virtual void print(ostream& out = cout,char split = ',' ) const;
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
		virtual iterator begin();
		/*
		@brief 返回最后一个矩阵元素迭代器
		*/
		virtual iterator end();

		/*
		@brief 返回某一列第一个元素的迭代器
		*/
		virtual column_iterator cbegin(size_t column);
		/*
		@brief 返回某一列的结尾迭代器（指向null）
		*/
		virtual column_iterator cend(size_t column);

		/*
		@brief 返回子阵
		@param row_begin	第一个元素横坐标，由0开始
		@param column_begin	第一个元素纵坐标，由0开始
		@param row_end	最后一个元素横坐标，由0开始
		@param column_end	最后一个元素纵坐标，由0开始
		@return 指向新子阵的指针（shared_ptr）
		*/
		virtual pseudo_matrix<T> sub_matrix(size_t row_begin, size_t column_begin, size_t row_end, size_t column_end);
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
		@brief 本矩阵每个元素都exp
		*/
		matrix& exp();

		/*
		@brief 矩阵中只有一个元素时可将其直接转换为单个的T类型变量
		*/
		operator const T&() const;
		/*
		@brief 矩阵中只有一个元素时可将其直接转换为单个的T类型变量
		*/
		operator T&();
		/*
		@brief 矩阵相加
		*/
		matrix<T> operator +=(const matrix<T>& t);

		/*
		@brief 矩阵相减
		*/
		matrix<T> operator -=(const matrix<T>& t);


		/*
		@brief 选取矩阵中的指定行
		*/
		virtual pseudo_matrix<T> fetch_row(const index_array& row_indexs) const;

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
		virtual void remove_row(const index_array& row_indexs);

		/*
		@brief 不排序，仅仅获取其顺序
		*/
		virtual index_array get_order(size_t column_num);

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
		pseudo_matrix<T> row(size_t row_index) const;
		/*获取某列数据，仅用于读取*/
		pseudo_matrix<T> col(size_t col_index) const;
		/*获取某一行数据，仅用于读取*/
		pseudo_matrix<T> rows(size_t begin, size_t end) const;
		/*获取某列数据，仅用于读取*/
		pseudo_matrix<T> cols(size_t begin, size_t end) const;

		/*重新分配大小*/
		void resize(size_t row_size, size_t col_size);
		/*设置所有元素为指定值*/
		void fill(const T &t);
		/*是否有数据*/
		bool has_data();
		/*转置本矩阵*/
		void transpose();
		/*生成新的转置过的矩阵*/
		matrix<T> t() const;
		/*最大元素的位置*/
		pair<size_t, size_t> max_position() const;
		/*最大元素*/
		T max() const;
		/*获取某一元素个数*/
		size_t count(const T& t);

	protected:
		T* _memory = nullptr;
		T** _data = nullptr;
		size_t _row_size = 0;
		size_t _col_size = 0;
		size_t _cur_row_pos = 0;
	};

	template<class T>
	inline void matrix<T>::print(ostream& out,char split) const
	{
		out.precision(4);
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
	inline matrix<T> & matrix<T>::exp()
	{
		each_ele(ele = std::exp(ele));
		return *this;
	}

	template<class T>
	inline matrix<T>::operator const T&() const
	{
		assert(_row_size == 1 && _col_size == 1);
		return _data[0][0];
	}
	template<class T>
	inline matrix<T>::operator T&()
	{
		assert(_row_size == 1 && _col_size == 1);
		return _data[0][0];
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
		each_ele(_data[row_i][col_i] -= t.at(row_i, col_i));
		return *this;
	}
	//TODO :优化逻辑
	template<class T>
	inline typename matrix<T>::index_array matrix<T>::get_order(size_t column_num)
	{
		index_array&& ia = index_array(row_size());
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
	inline matrix<T>::iterator::iterator(matrix<T>& matrix, size_t index) :_matrix(matrix), _index(index) {}

	template<class T>
	inline size_t matrix<T>::iterator::index() const
	{
		return _index;
	}

	template<class T>
	inline bool matrix<T>::iterator::operator!=(iterator& i) const
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
	inline typename matrix<T>::iterator & matrix<T>::iterator::operator+(size_t iv)
	{
		_index += iv;
		return *this;
	}

	template<class T>
	inline size_t matrix<T>::iterator::operator-(const iterator & i)
	{
		return _index - i._index;
	}

	template<class T>
	inline T & matrix<T>::iterator::operator*() const
	{
		return _matrix.at(_index / _matrix.col_size(), _index % _matrix.col_size());
	}

	template<class T>
	matrix<T>::column_iterator::column_iterator(matrix<T>& matrix, size_t index, size_t column) :_matrix(matrix), _index(index), _column(column)
	{
	}
	template<class T>
	inline T & matrix<T>::column_iterator::operator*() const
	{
		return _matrix.at(_index, _column);
	}

	template<class T>
	inline bool matrix<T>::column_iterator::operator!=(column_iterator & i)
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
	inline typename matrix<T>::column_iterator & matrix<T>::column_iterator::operator+(size_t iv)
	{
		_index += iv;
		return *this;
	}

	template<class T>
	inline size_t matrix<T>::column_iterator::operator-(const column_iterator & i)
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
	typename matrix<T>::iterator matrix<T>::begin()
	{
		return iterator(*this, 0);
	}

	template<class T>
	typename matrix<T>::iterator matrix<T>::end()
	{
		return iterator(*this, row_size()*col_size());
	}

	template<class T>
	typename matrix<T>::column_iterator matrix<T>::cbegin(size_t column)
	{
		return column_iterator(*this, 0, column);
	}

	template<class T>
	typename matrix<T>::column_iterator matrix<T>::cend(size_t column)
	{
		return column_iterator(*this, row_size(), column);
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
			_data[_cur_row_pos][i] = *(row.begin()+i);
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
	inline pseudo_matrix<T> matrix<T>::row(size_t row_index) const
	{
		assert(row_index < _row_size);
		return pseudo_matrix<T>(*this, row_index, 0, 1, _col_size);
	}
	template<class T>
	inline pseudo_matrix<T> matrix<T>::col(size_t col_index) const
	{
		assert(col_index < _col_size);
		return pseudo_matrix<T>(*this, 0, col_index, _row_size, 1);
	}
	template<class T>
	inline pseudo_matrix<T> matrix<T>::rows(size_t begin, size_t end) const
	{
		assert(begin < _row_size && end < _row_size);
		return pseudo_matrix<T>(*this, begin, 0, end - begin + 1, _col_size);
	}
	template<class T>
	inline pseudo_matrix<T> matrix<T>::cols(size_t begin, size_t end) const
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
		each_ele(_data[row_i][col_i] = t);
	}
	template<class T>
	inline bool matrix<T>::has_data()
	{
		return _data != nullptr && _col_size > 0 && _row_size > 0;
	}
	template<class T>
	inline void matrix<T>::transpose()
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
	}
	template<class T>
	inline matrix<T> matrix<T>::t() const
	{
		matrix<T> temp(_col_size, _row_size);
		for (size_t row_i = 0; row_i < _col_size; ++row_i)
		{
			for (size_t col_i = 0; col_i < _row_size; ++col_i)
			{
				temp.at(row_i, col_i) = _data[col_i][row_i];
			}
		}
		return temp;
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
	inline size_t matrix<T>::count(const T & t)
	{
		size_t c = 0;
		each_ele(
			if (ele == t)
				++c;
		);
		return c;
	}
	template<class T>
	inline bool matrix<T>::rect_check() const
	{
		return true;
	}

	template<class T>
	pseudo_matrix<T> matrix<T>::sub_matrix(size_t row_begin, size_t col_begin, size_t row_end, size_t col_end)
	{
		/*范围正确*/
		assert(row_begin <= row_end && col_begin <= col_end);
		assert(row_end - row_begin < _row_size && col_end - col_begin < _col_size);
		assert(row_end < _row_size && col_end < _col_size);
		return pseudo_matrix<T>(*this, row_begin, col_begin, row_end - row_begin + 1, col_end - col_begin + 1);
	}

	template<class T>
	inline pseudo_matrix<T> matrix<T>::fetch_row(const index_array & row_indexs) const
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
	inline void matrix<T>::remove_row(const index_array & row_indexs)
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
	bool import_matrix_data(matrix<T>& matrix,istream& in, char split = ',', int line_width = 2048)
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
	/*矩阵运算类*/
	namespace matrix_operate
	{
		template<class T>
		matrix<T> exp(const matrix<T>& a)
		{
			matrix<T> temp(a.row_size(), a.col_size());
			for (size_t row_i = 0; row_i < a.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < a.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = std::exp(a.at(row_i, col_i));
				}
			}
			return move(temp);
		}
		/*求和*/
		template<class T>
		T sum(const matrix<T>& matrix)
		{
			T sum = 0;
			for (size_t row_i = 0; row_i < matrix.row_size(); ++row_i)
			{
				for (size_t col_i = 0; col_i < matrix.col_size(); ++col_i)
				{
					sum += matrix.at(row_i, col_i);
				}
			}
			return sum;
		}
		/*矩阵的f范数*/
		template<class T>
		long double norm_f(matrix<T>& matrix)
		{
			long double sum = 0;
			for (auto& i : matrix)
			{
				sum += i * i;
			}
			return std::sqrt(sum);
		}
		template<class T>
		matrix<T> operator* (const matrix<T>& a, const T& b)
		{
			matrix<T> temp(a.row_size(), a.col_size());
			for (size_t row_i = 0; row_i < a.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < a.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = a.at(row_i, col_i) * b;
				}
			}
			return move(temp);
		}
		template<class T>
		matrix<T> operator/ (const matrix<T>& a, const T& b)
		{
			matrix<T> temp(a.row_size(), a.col_size());
			for (size_t row_i = 0; row_i < a.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < a.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = a.at(row_i, col_i) / b;
				}
			}
			return move(temp);
		}
		template<class T>
		matrix<T> operator+ (const matrix<T>& a, const T& b)
		{
			matrix<T> temp(a.row_size(), a.col_size());
			for (size_t row_i = 0; row_i < a.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < a.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = a.at(row_i, col_i) + b;
				}
			}
			return move(temp);
		}

		template<class T>
		matrix<T> operator- (const matrix<T>& a, const T& b)
		{
			matrix<T> temp(a.row_size(), a.col_size());
			for (size_t row_i = 0; row_i < a.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < a.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = a.at(row_i, col_i) - b;
				}
			}
			return move(temp);
		}
		template<class T>
		inline matrix<T> operator+(const matrix<T>& a, const matrix<T>& b)
		{
			assert(a.col_size() == b.col_size() && a.row_size() == b.row_size());
			matrix<T> temp(a.row_size(), a.col_size());
			for (size_t row_i = 0; row_i < temp.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < temp.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = a.at(row_i, col_i) + b.at(row_i, col_i);
				}
			}
			return move(temp);
		}
		template<class T>
		inline matrix<T> operator-(const matrix<T>& a, const matrix<T>& b)
		{
			assert(a.col_size() == b.col_size() && a.row_size() == b.row_size());
			matrix<T> temp(a.row_size(), a.col_size());
			for (size_t row_i = 0; row_i < temp.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < temp.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = a.at(row_i, col_i) - b.at(row_i, col_i);
				}
			}
			return move(temp);
		}
		template<class T>
		inline matrix<T> operator*(const matrix<T>& a, const matrix<T>& b)
		{
			/*可以乘*/
			assert(a.col_size() == b.row_size());
			matrix<T> temp(a.row_size(), b.col_size());
			for (size_t row_i = 0; row_i < temp.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < temp.col_size(); col_i++)
				{
					/* temp = 本矩阵的第row_i行 * t矩阵的地col_i列 */
					temp.at(row_i, col_i) = 0;
					for (size_t i = 0; i < a.col_size(); i++)
					{
						temp.at(row_i, col_i) += a.at(row_i, i) * b.at(i, col_i);
					}
				}
			}
			return move(temp);
		}
		/*
		两个矩阵点乘：对应位置的元素相乘
		*/
		template<class T>
		matrix<T> dot(const matrix<T>& a, const matrix<T>& b)
		{
			assert(a.row_size() == b.row_size() && a.col_size() == b.col_size());
			matrix<T> temp(a.row_size(), a.col_size());
			for (size_t row_i = 0; row_i < a.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < a.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = a.at(row_i, col_i) * b.at(row_i, col_i);
				}
			}
			return move(temp);
		}
		/*
		矩阵相除：相同大小的矩阵对应位置相除
		*/
		template<class T>
		matrix<T> operator/ (const matrix<T>& a, const matrix<T>& b)
		{
			assert(a.row_size() == b.row_size() && a.col_size() == b.col_size());
			matrix<T> temp(a.row_size(), a.col_size());
			for (size_t row_i = 0; row_i < a.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < a.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = a.at(row_i, col_i) / b.at(row_i, col_i);
				}
			}
			return move(temp);
		}

		template<class T>
		matrix<T> pow(const matrix<T>& a, const T& b)
		{
			matrix<T> temp(a.row_size(), a.col_size());
			for (size_t row_i = 0; row_i < a.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < a.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = std::pow(a.at(row_i, col_i), b);
				}
			}
			return move(temp);
		}
		template<class T>
		matrix<T> sqrt(const matrix<T>& a)
		{
			matrix<T> temp(a.row_size(), a.col_size());
			for (size_t row_i = 0; row_i < a.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < a.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = std::sqrt(a.at(row_i, col_i));
				}
			}
			return move(temp);
		}
		template<class T>
		matrix<T> log(const matrix<T>& a)
		{
			matrix<T> temp(a.row_size(), a.col_size());
			for (size_t row_i = 0; row_i < a.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < a.col_size(); col_i++)
				{
					temp.at(row_i, col_i) = std::log(a.at(row_i, col_i));
				}
			}
			return move(temp);
		}
		template<class T>
		T max(const matrix<T>& a)
		{
			T max = -LDBL_MAX;
			for (size_t row_i = 0; row_i < a.row_size(); row_i++)
			{
				for (size_t col_i = 0; col_i < a.col_size(); col_i++)
				{
					max = max > a.at(row_i, col_i) ? max : a.at(row_i, col_i);
				}
			}
			return max;
		}
	}
	/*矩阵数据标准化*/
	namespace matrix_normalized {
		/*设置元素值的范围，将大于上限upper_bound的元素设置为最大值，将小于下限lower_bound的元素设置为最小值*/
		template<class T>
		void set_range(matrix<T>& m, size_t column_num, T lower_bound, T upper_bound) {
			for (matrix<T>::column_iterator i = m.cbegin(column_num); i != m.cend(column_num); ++i)
			{
				if (*i < lower_bound)
					*i = lower_bound;
				else if (*i > upper_bound)
					*i = upper_bound;
			}
		}
		/*转换矩阵中数据的类型*/
		template<class SRC, class DST>
		matrix<DST> convert_matrix_type(const matrix<SRC>& m)
		{
			matrix<DST> temp(m.row_size(), m.col_size());
			for (size_t row_i = 0; row_i < m.row_size(); ++row_i)
			{
				for (size_t col_i = 0; col_i < m.col_size(); ++col_i)
				{
					temp.at(row_i, col_i) = DST(m.at(row_i, col_i));
				}
			}
			return move(temp);
		}
		/*将数据的label转换为连续的整数*/
		template<class T, class E>
		map<T, E> serialize_label(matrix<T>& label_matrix, matrix<E>& serialized_label)
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
				static_cast<E&>(serialized_label.row(row_i)) = label_map[label_matrix.row(row_i)];
			}
			return label_map;
		}
	};

}
#endif