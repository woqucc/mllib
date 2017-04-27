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

namespace myml
{
	using namespace std;
	template <class T>
	class matrix
	{
	public:
		class iterator
		{
		private:
			matrix<T>& _matrix;/*< 存储矩阵*/
			size_t _index;/*< 存储索引*/
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
		virtual void print(char split = ',', ostream& out = cout);
		/*
		@brief 按照某列排序
		@param column_num 列数
		*/
		virtual void sort_by(size_t column_num);

		/*
		@brief 获取元素个数
		*/
		virtual size_t size() const;
		/*
		@brief 获取元素维数
		*/
		virtual size_t dimension() const;
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
		virtual shared_ptr<matrix<T>> sub_matrix(size_t row_begin, size_t column_begin, size_t row_end, size_t column_end);
		/*
		@brief 赋值操作符
		*/
		matrix& operator =(matrix& rn);

		using index_array = valarray<size_t>;//将valarray作为暂定的存储下标的数据结构
		/*
		@brief 提取指定行成为新的矩阵
		*/
		virtual shared_ptr<matrix<T>> fetch_row(const index_array& row_indexs) const;

		/*
		@brief 提取满足指定条件的行
		*/
		virtual shared_ptr<matrix<T>> fetch_row(function<bool(const valarray<T> &va)> condition) const;

		/*
		@brief 提取指定行成为新的矩阵
		*/
		virtual shared_ptr<matrix<T>> fetch_column(const index_array& column_indexs) const;

		/*
		@brief 删除指定行
		*/
		virtual void remove_row(const index_array& column_indexs);

		/*
		@brief 删除指定列
		*/
		virtual void remove_column(const index_array& column_indexs);

		/*
		@brief 删除指定列
		*/
		//virtual void cfetch_row(const index_array& column_indexs) = 0;

		/*
		@brief 不排序，仅仅获取其顺序
		*/
		virtual index_array get_order(size_t column_num);

		/*初始化列表形式初始化*/
		void push_back(valarray<T> && row);
		void push_back(const valarray<T>& row);

		/*真正构造函数*/
		matrix<T>(size_t row_size, size_t col_size);
		/*转移构造函数*/
		matrix<T>(matrix&& m);
		/*复制构造函数*/
		matrix<T>(const matrix& m);
		/*析构函数*/
		~matrix<T>();
		/*获取只读row*/
		const matrix<T> row(size_t row_index);
		/*重新分配大小*/
		void resize(size_t row_size, size_t col_size);
	private:
		T* _data = nullptr;
		size_t _row_size = 0;
		size_t _col_size = 0;
		size_t _cur_row_pos = 0;
		size_t _cur_col_pos = 0;
	};

	template<class T>
	inline void matrix<T>::print(char split, ostream& out)
	{
		out.precision(6);
		out << fixed;
		for (size_t row = 0; row < size(); row++)
		{
			for (size_t column = 0; column < dimension() - 1; column++)
			{
				out << at(row, column) << split;
			}
			out << at(row, dimension() - 1) << endl;
		}
	}

	template<class T>
	inline matrix<T>& matrix<T>::operator= (matrix & m)
	{
		matrix(m);
		return *this;
	}
	//TODO :优化逻辑
	template<class T>
	inline typename matrix<T>::index_array matrix<T>::get_order(size_t column_num)
	{
		index_array&& ia = index_array(size());
		for (size_t i = 0; i < ia.size(); i++)
		{
			ia[i] = i;
		}
		auto temp = sub_matrix(0, column_num, size(), column_num);
		/*使用栈代替递归，执行快排*/
		stack<pair<size_t, size_t>> qs_stack;
		qs_stack.push({ 0,size() - 1 });
		while (!qs_stack.empty())
		{
			auto begin = qs_stack.top().first;
			auto end = qs_stack.top().second;
			qs_stack.pop();
			auto i = begin, j = end;
			T key = temp->at(i, column_num);
			while (i < j)
			{
				//从后向前找到小于key的元素j，将j缓存到i处
				//首次交换时i为begin
				while (i < j && temp->at(j, column_num) >= key)
				{
					j--;
				}
				//交换
				std::swap(ia[i], ia[j]);
				temp->swap_row(i, j);
				//从前向后找到第一个大于key的元素i，与j交换，将缓存到j出的begin元素交换至i处
				while (i < j && temp->at(i, column_num) <= key)
				{
					i++;
				}
				temp->swap_row(i, j);
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
		return _matrix.at(_index / _matrix.dimension(), _index % _matrix.dimension());
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
		return _data[row_num * _col_size + col_num];
	}
	template<class T>
	typename matrix<T>::iterator matrix<T>::begin()
	{
		return iterator(*this, 0);
	}

	template<class T>
	typename matrix<T>::iterator matrix<T>::end()
	{
		return iterator(*this, size()*dimension());
	}

	template<class T>
	typename matrix<T>::column_iterator matrix<T>::cbegin(size_t column)
	{
		return column_iterator(*this, 0, column);
	}

	template<class T>
	typename matrix<T>::column_iterator matrix<T>::cend(size_t column)
	{
		return column_iterator(*this, size(), column);
	}

	template<class T>
	inline void matrix<T>::sort_by(size_t column_num)
	{
		/*使用栈代替递归，执行快排*/
		stack<pair<size_t, size_t>> qs_stack;
		qs_stack.push({ 0,size() - 1 });
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
		assert(_col_size > _cur_col_pos);
		for (size_t i = 0; i < size; ++i)
		{
			_data[_cur_row_pos * _col_size] = row[i];
		}
		++_cur_row_pos;
	}
	template<class T>
	inline void matrix<T>::push_back(valarray<T>&& row)
	{
		for (size_t i = 0; i < row.size(); ++i)
		{
			_data[_cur_row_pos * _col_size] = row[i];
		}
		++_cur_row_pos;
	}
	template<class T>
	inline void matrix<T>::push_back(const valarray<T>& row)
	{
		for (size_t i = 0; i < row.size(); ++i)
		{
			_data[_cur_row_pos * _col_size] = row[i];
		}
		++_cur_row_pos;
	}
	template<class T>
	inline void matrix<T>::resize(size_t row_size, size_t col_size)
	{
		delete[]_data;
		_data = new T[row_size * col_size]();
		_row_size = row_size;
		_col_size = col_size;
	}
	template<class T>
	inline bool matrix<T>::rect_check() const
	{
		return true;
	}

	template<class T>
	shared_ptr<matrix<T>> matrix<T>::sub_matrix(size_t row_begin, size_t column_begin, size_t row_end, size_t column_end)
	{
		shared_ptr<matrix<T>> m(new matrix<T>(row_end - row_begin, column_end - column_begin));
		for (auto row_i = row_begin; row_i < row_end; row_i++)
		{
			m->push_back(_data + row_begin * _col_size + column_begin, column_end - column_begin);
		}
		return m;
	}

	template<class T>
	inline shared_ptr<matrix<T>> matrix<T>::fetch_row(const index_array & row_indexs) const
	{
		shared_ptr<matrix<T>> m(new matrix<T>(row_indexs.size(),dimension()));
		for (auto row_i : row_indexs)
		{
			m->push_back(_data + row_i * _col_size, dimension());
		}
		return m;
	}

	template<class T>
	inline shared_ptr<matrix<T>> matrix<T>::fetch_row(function<bool(const valarray<T> &va)> condition) const
	{
		auto temp = shared_ptr<matrix<T>>(new matrix());
		//TODO finish it
		static_assert(true);
		return temp;
	}

	template<class T>
	inline shared_ptr<matrix<T>>  matrix<T>::fetch_column(const index_array & fetch_column) const
	{
		auto temp = shared_ptr<matrix<T>>(new matrix());
		//TODO finish it
		static_assert(true);
		return temp;
	}

	template<class T>
	inline void matrix<T>::remove_column(const index_array & column_indexs)
	{
		//TODO finish it
		static_assert(true);
	}

	template<class T>
	inline void matrix<T>::remove_row(const index_array & column_indexs)
	{
		//TODO finish it
		static_assert(true);
	}

	template<class T>
	inline size_t matrix<T>::size() const
	{
		return _row_size;
	}

	template<class T>
	inline size_t matrix<T>::dimension() const
	{
		return _col_size;
	}

	template<class T>
	inline void matrix<T>::swap_row(size_t row1, size_t row2)
	{
		T * temp_line = new T[_col_size]();
		//row1 2 temp
		memcpy(temp_line, _data + row1 * _col_size, sizeof(T) / sizeof(char) *  _col_size);
		//row 2 to row1
		memcpy(_data + row1 * _col_size, _data + row2 * _col_size, sizeof(T) / sizeof(char) *  _col_size);
		//temp to row2
		memcpy(_data + row2 * _col_size, temp_line, sizeof(T) / sizeof(char) *  _col_size);
	}

	template<class T>
	T& matrix<T>::at(size_t row_num, size_t col_num)
	{
		return _data[row_num * _col_size + col_num];
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
		_col_size = m._col_size;
		_row_size = m._row_size;
		m._data = nullptr;
	}
	template<class T>
	inline matrix<T>::matrix(const matrix<T>& m)
	{
		this->matrix(m._row_size, m._col_size);
		memcpy(_data, m._data, sizeof(T) / sizeof(char) *_row_size* _col_size);
	}

	template<class T>
	inline matrix<T>::~matrix()
	{
		delete[] _data;
	}

	/*
	单列类
	*/
	template<class T>
	class column:matrix<T>
	{
	public:
		column(size_t row_size);
		~column();
	private:

	};
	template<class T>
	column::column(size_t row_size)
	{
		resize(row_size, 1);
	}
	template<class T>
	column::~column()
	{
	}
	/*导入数据部分的全局函数*/
	template<class T>
	bool import_matrix_data(matrix<T>& matrix, ifstream& in, char split = ',', int line_width = 2048)
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
		matrix.resize(row_size, col_size);

		/*将文件指针重置到文件首部*/
		in.seekg(ios::beg);
		for (size_t row_index = 0; row_index < row_size; ++row_index)
		{
			for (size_t col_index = 0; col_index < col_size - 1; ++col_index)
			{
				in >> matrix.at(row_index, col_index) >> split;
			}
			in >> matrix.at(row_index, col_size - 1);
		}
		delete[] line;
		return true;
	};
	/*
	标准化数据类
	*/
	template<class T>
	class normalized {
	public:
		static void set_range(matrix<T>& matrix, size_t column_num, T lower_bound, T upper_bound) {
			for (auto i = matrix.cbegin(column_num); i != matrix.cend(column_num); ++i)
			{
				if (*i < lower_bound)
					*i = lower_bound;
				else if (*i > upper_bound)
					*i = upper_bound;
			}
		}
	};
}
#endif