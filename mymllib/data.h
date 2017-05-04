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

namespace myml
{
	using namespace std;

	/*��������*/
	template<class T>
	class pseudo_matrix;
	/*
	@brief �����࣬ʹ������ʵ��
	*/

	template <class T>
	class matrix
	{
	public:
		//��valarray��Ϊ����push_back��һ����ʽ
		using index_array = valarray<size_t>;
		/*����Ԫ��,row_i,col_iΪ��������*/
#define each_ele(op) for (size_t row_i = 0; row_i < _row_size; row_i++) {for (size_t col_i = 0; col_i < _col_size; col_i++){op;}}
		class iterator
		{
		private:
			matrix<T>& _matrix;/*< �洢����*/
			size_t _index;/*< �洢����*/
		public:
			iterator(matrix<T>& matrix, size_t index);
			/*
			@brief ���ص�ǰindex
			*/
			virtual size_t index() const;
			/*
			@brief ������ȡַ������
			@return T& Ԫ������
			*/
			virtual  T& operator * () const;
			/*
			@brief �������Ƚϲ�����
			@param i ����������
			@return true ����
			@return false ���
			*/
			virtual bool operator != (iterator& i) const;
			/*
			@brief ����������������
			@return ����ǰ�ĵ���������
			*/
			virtual typename matrix<T>::iterator& operator ++();
			/*
			@brief �������Լ�������
			@return �Լ�ǰ�ĵ���������
			*/
			virtual typename matrix<T>::iterator& operator --();
			/*
			@brief  �ӺŲ�����
			@return �Լ�ǰ�ĵ���������
			*/
			virtual typename matrix<T>::iterator& operator +(size_t iv);
			/*
			@brief  ���Ų�����
			@return �Լ�ǰ�ĵ���������
			*/
			virtual size_t operator -(const iterator& i);
		};
		/*
		@brief �е�����
		���з���Ԫ��
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
		/*Ĭ�Ϲ��캯��������վ����޷�ʹ��*/
		matrix() = default;
		/*
		@brief ��ӡ�����е�����Ԫ��
		*/
		virtual void print(char split = ',', ostream& out = cout);
		/*
		@brief ����ĳ������
		@param column_num ����
		*/
		virtual void sort_by(size_t column_num);

		/*
		@brief ��ȡԪ�ظ���
		*/
		virtual size_t row_size() const;
		/*
		@brief ��ȡԪ��ά��
		*/
		virtual size_t col_size() const;
		/*
		@brief ������
		@param row Ԫ���е��׵�ַָ��
		@param size Ԫ��ά��
		*/
		virtual void push_back(T *row, size_t size);
		/*
		@brief ��������ÿ�����������Ƿ���ͬ,�������Ƿ�Ϸ�
		@return true ÿ������������ͬ���Ϸ�
		@return false ÿ������������ͬ���Ƿ�;����Ϊ��
		*/
		virtual bool rect_check() const;
		/*
		@brief ��������
		@param row1 ����������1
		@param row2 ����������2
		*/
		virtual void swap_row(size_t row1, size_t row2);
		/*
		@brief ��ȡĳһԪ��
		@param row_num ����
		@param col_num ����
		*/
		virtual T& at(size_t row_num, size_t col_num);
		/*
		@brief ��ȡĳһԪ��
		@param row_num ����
		@param col_num ����
		*/
		virtual const T at(size_t row_num, size_t col_num) const;
		/*
		@brief ���ص�һ������Ԫ�ص�����
		*/
		virtual iterator begin();
		/*
		@brief �������һ������Ԫ�ص�����
		*/
		virtual iterator end();
		/*
		@brief ����ĳһ�е�һ��Ԫ�صĵ�����
		*/
		virtual column_iterator cbegin(size_t column);
		/*
		@brief ����ĳһ�еĽ�β��������ָ��null��
		*/
		virtual column_iterator cend(size_t column);

		/*
		@brief ��������
		@param row_begin	��һ��Ԫ�غ����꣬��0��ʼ
		@param column_begin	��һ��Ԫ�������꣬��0��ʼ
		@param row_end	���һ��Ԫ�غ����꣬��0��ʼ
		@param column_end	���һ��Ԫ�������꣬��0��ʼ
		@return ָ���������ָ�루shared_ptr��
		*/
		virtual pseudo_matrix<T> sub_matrix(size_t row_begin, size_t column_begin, size_t row_end, size_t column_end);
		/*
		@brief ��ֵ������
		*/
		matrix& operator =(const matrix& rn);
		/*
		@brief �ӺŲ�����
		*/
		matrix& operator +=(const T t);
		/*
		@brief ���Ų�����
		*/
		matrix& operator -=(const T t);
		/*
		@brief �˷�������
		*/
		matrix& operator *=(const T t);
		/*
		@brief ���Ų�����
		*/
		matrix& operator /=(const T t);
		/*
		@brief ȡ�������
		*/
		matrix& operator %=(const T t);

		/*
		@brief �������
		*/
		matrix<T> operator +(const matrix<T>& t) const;

		/*
		@brief �������
		*/
		matrix<T> operator -(const matrix<T>& t) const;

		/*
		@brief �������
		*/
		matrix<T> operator *(const matrix<T>& t) const;

		/*
		@brief ������ֻ��һ��Ԫ��ʱ�ɽ���ֱ��ת��Ϊ������T���ͱ���
		*/
		operator const T&() const;
		/*
		@brief ������ֻ��һ��Ԫ��ʱ�ɽ���ֱ��ת��Ϊ������T���ͱ���
		*/
		operator T&();
		/*
		@brief �������
		*/
		matrix<T> operator +=(const matrix<T>& t);

		/*
		@brief �������
		*/
		matrix<T> operator -=(const matrix<T>& t);


		/*
		@brief ѡȡ�����е�ָ����
		*/
		virtual pseudo_matrix<T> fetch_row(const index_array& row_indexs) const;

		/*
		@brief ��ȡ����ָ����������
		*/
		virtual pseudo_matrix<T> fetch_row(function<bool(const T* val, size_t col_size)> condition) const;

		/*
		@brief ��ȡָ���г�Ϊ�µľ���
		*/
		//virtual matrix<T> fetch_column(const index_array& column_indexs) const;

		/*
		@brief ɾ����������ָ������
		*/
		virtual void remove_row(const index_array& row_indexs);

		/*
		@brief �����򣬽�����ȡ��˳��
		*/
		virtual index_array get_order(size_t column_num);

		/*��ʼ���б���ʽ��ʼ��*/
		void push_back(valarray<T> && row);
		void push_back(const valarray<T>& row);
		/*������ָ������*/
		T** raw_data();
		/*������ָ������*/
		T** raw_data() const;
		/*�������캯��*/
		matrix<T>(size_t row_size, size_t col_size);
		/*ת�ƹ��캯��*/
		matrix<T>(matrix&& m);
		/*���ƹ��캯��*/
		matrix<T>(const matrix& m);
		/*��������*/
		virtual ~matrix<T>();

		/*��ȡĳһ�����ݣ������ڶ�ȡ*/
		pseudo_matrix<T> row(size_t row_index) const;
		/*��ȡĳ�����ݣ������ڶ�ȡ*/
		pseudo_matrix<T> col(size_t col_index) const;
		/*��ȡĳһ�����ݣ������ڶ�ȡ*/
		pseudo_matrix<T> rows(size_t begin, size_t end) const;
		/*��ȡĳ�����ݣ������ڶ�ȡ*/
		pseudo_matrix<T> cols(size_t begin, size_t end) const;

		/*���·����С*/
		void resize(size_t row_size, size_t col_size);
		/*��������Ԫ��Ϊָ��ֵ*/
		void fill(const T &t);
		/*�Ƿ�������*/
		bool has_data();
		/*��ת������*/
		void transpose();
		/*�����µľ���*/
		matrix<T> t();
	protected:
		T* _memory = nullptr;
		T** _data = nullptr;
		size_t _row_size = 0;
		size_t _col_size = 0;
		size_t _cur_row_pos = 0;
	};

	template<class T>
	inline void matrix<T>::print(char split, ostream& out)
	{
		out.precision(10);
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
	inline matrix<T>& matrix<T>::operator = (const matrix & rn)
	{
		//�Ѿ���ʵ������ˣ��������⸳ֵ
		if (_data != nullptr && _memory != nullptr)
		{
			assert(rn.row_size() == _row_size && rn.col_size() == _col_size);
		}
		//������δʵ�廯
		else
		{
			if(rn.row_size() > 0 && rn.col_size() > 0)
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
		each_ele(_data[row_i][col_i] += t);
		return *this;
	}
	template<class T>
	inline matrix<T> & matrix<T>::operator-=(const T t)
	{
		each_ele(_data[row_i][col_i] -= t);
		return *this;
	}
	template<class T>
	inline matrix<T> & matrix<T>::operator*=(const T t)
	{
		each_ele(_data[row_i][col_i] *= t);
		return *this;
	}
	template<class T>
	inline matrix<T> & matrix<T>::operator/=(const T t)
	{
		assert(t != 0);
		each_ele(_data[row_i][col_i] /= t);
		return *this;
	}
	template<class T>
	inline matrix<T> & matrix<T>::operator%=(const T t)
	{
		each_ele(_data[row_i][col_i] %= t);
		return *this;
	}
	template<class T>
	inline matrix<T> matrix<T>::operator+(const matrix<T>& t) const
	{
		assert(_col_size == t.col_size() && _row_size == t.row_size());
		matrix<T> temp = *this;
		for (size_t row_i = 0; row_i < _row_size; row_i++)
		{
			for (size_t col_i = 0; col_i < _col_size; col_i++)
			{
				temp.at(row_i, col_i) += t.at(row_i, col_i);
			}
		}
		/*�ڴ˵���ת�ƹ��캯����move��move������*/
		return move(temp);
	}
	template<class T>
	inline matrix<T> matrix<T>::operator-(const matrix<T>& t) const
	{
		assert(_col_size == t.col_size() && _row_size == t.row_size());
		matrix<T> temp = *this;
		for (size_t row_i = 0; row_i < _row_size; row_i++)
		{
			for (size_t col_i = 0; col_i < _col_size; col_i++)
			{
				temp.at(row_i, col_i) -= t.at(row_i, col_i);
			}
		}
		/*�ڴ˵���ת�ƹ��캯����move��move������*/
		return move(temp);
	}
	template<class T>
	inline matrix<T> matrix<T>::operator*(const matrix<T>& t) const
	{
		/*���Գ�*/
		assert(_col_size == t.row_size());
		matrix<T> temp(_row_size, t.col_size());
		for (size_t row_i = 0; row_i < temp.row_size(); row_i++)
		{
			for (size_t col_i = 0; col_i < temp.col_size(); col_i++)
			{
				/* temp = ������ĵ�row_i�� * t����ĵ�col_i�� */
				temp.at(row_i, col_i) = 0;
				for (size_t i = 0; i < _col_size; i++)
				{
					temp.at(row_i, col_i) += this->_data[row_i][i] * t.at(i, col_i);
				}
			}
		}
		/*�ڴ˵���ת�ƹ��캯����move��move������*/
		return move(temp);
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
		each_ele(_data[row_i][col_i] += t.at(row_i, col_i));
		return *this;
	}
	template<class T>
	inline matrix<T> matrix<T>::operator-=(const matrix<T>& t)
	{
		each_ele(_data[row_i][col_i] -= t.at(row_i, col_i));
		return *this;
	}
	//TODO :�Ż��߼�
	template<class T>
	inline typename matrix<T>::index_array matrix<T>::get_order(size_t column_num)
	{
		index_array&& ia = index_array(row_size());
		for (size_t i = 0; i < ia.size(); i++)
		{
			ia[i] = i;
		}
		auto temp = col(column_num);
		/*ʹ��ջ����ݹ飬ִ�п���*/
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
				//�Ӻ���ǰ�ҵ�С��key��Ԫ��j����j���浽i��
				//�״ν���ʱiΪbegin
				while (i < j && temp.at(j, 0) >= key)
				{
					j--;
				}
				//����
				std::swap(ia[i], ia[j]);
				temp.swap_row(i, j);
				//��ǰ����ҵ���һ������key��Ԫ��i����j�����������浽j����beginԪ�ؽ�����i��
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
		/*ʹ��ջ����ݹ飬ִ�п���*/
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
				//�Ӻ���ǰ�ҵ�С��key��Ԫ��j����j���浽i��
				//�״ν���ʱiΪbegin
				while (i < j && at(j, column_num) >= key)
				{
					j--;
				}
				//����
				swap_row(i, j);
				//��ǰ����ҵ���һ������key��Ԫ��i����j�����������浽j����beginԪ�ؽ�����i��
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
	inline void matrix<T>::push_back(valarray<T>&& row)
	{
		assert(_row_size > _cur_row_pos);
		for (size_t i = 0; i < row.size(); ++i)
		{
			_data[_cur_row_pos][i] = row[i];
		}
		++_cur_row_pos;
	}
	template<class T>
	inline void matrix<T>::push_back(const valarray<T>& row)
	{
		assert(_row_size > _cur_row_pos);
		for (size_t i = 0; i < row.size(); ++i)
		{
			_data[_cur_row_pos][i] = row[i];
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
	inline matrix<T> matrix<T>::t()
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
	inline bool matrix<T>::rect_check() const
	{
		return true;
	}

	template<class T>
	pseudo_matrix<T> matrix<T>::sub_matrix(size_t row_begin, size_t col_begin, size_t row_end, size_t col_end)
	{
		/*��Χ��ȷ*/
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
		//��α�����п���
		if (_memory == nullptr)
		{
			//�������ڴ�
			_memory = new T[_row_size*_col_size]();
			for (size_t row_i = 0; row_i < _row_size; row_i++)
			{
				T* origin_row = _data[row_i];
				//���¸�index����ֵ
				_data[row_i] = _memory + row_i * _col_size;
				//��������
				memcpy(_data[row_i], origin_row, sizeof(T) / sizeof(char) * _col_size);
			}
		}
		m._data = nullptr;
		m._memory = nullptr;
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
	/*α���󣬽�����ʱ��ȡʹ��*/
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
		pseudo_matrix() = default;
		pseudo_matrix(const matrix<T>& m, size_t row_size, size_t col_size);
		pseudo_matrix(const matrix<T>& m, size_t row_begin, size_t col_begin, size_t row_size, size_t col_size);
		~pseudo_matrix();
		/*��δ��ʵ�����ڴ�ľ�����������ݣ�������Ϊ��֪����ɶ*/
		void push_back(valarray<T> && row) { assert(false); }
		void push_back(const valarray<T>& row) { assert(false); }
		void push_back(T *row, size_t size) { assert(false); }

	private:
		//T **_data;
	};
	template<class T>
	inline pseudo_matrix<T> & pseudo_matrix<T>::operator=(const pseudo_matrix & rn)
	{
		for (size_t row_i = 0; row_i < _row_size; row_i++)
		{
			memcpy(_data[row_i], rn._data[row_i], sizeof(T) / sizeof(char) * _col_size);
		}
		return *this;
		// TODO: �ڴ˴����� return ���
	}
	template<class T>
	inline pseudo_matrix<T>::pseudo_matrix(const matrix<T>& m, size_t row_size, size_t col_size)
	{
		_row_size = row_size;
		_col_size = col_size;
		//����index�ڴ棬������ʵ���ڴ�
		_data = new T*[_row_size]();
		memcpy(_data, m.raw_data(), sizeof(T*) / sizeof(char)*_row_size);
	}
	template<class T>
	inline pseudo_matrix<T>::pseudo_matrix(const matrix<T>& m, size_t row_begin, size_t col_begin, size_t row_size, size_t col_size)
	{
		//����index�ڴ棬������ʵ���ڴ�
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
		/*���ͷ�����������ڴ�*/
		_memory = nullptr;
	}
	/*�������ݲ��ֵ�ȫ�ֺ���*/
	template<class T>
	bool import_matrix_data(matrix<T>& matrix, ifstream& in, char split = ',', int line_width = 2048)
	{
		if (in.bad() || in.fail()) {
			cerr << "Can not open file!" << endl;
			return false;
		}
		/*��ȡ����*/
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
		/*���ļ�ָ�����õ��ļ��ײ�*/
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
		in.close();
		return true;
	};

	/*����������*/
	namespace matrix_operate
	{
		template<class T>
		void exp(matrix<T>& matrix)
		{
			for (auto& i : matrix)
			{
				i = std::exp(i);
			}
		}
		/*���*/
		template<class T>
		T sum(matrix<T>& matrix)
		{
			T sum = 0;
			for (auto& i : matrix)
			{
				sum += i;
			}
			return sum;
		}
		/*�����f����*/
		template<class T>
		long double norm_f(matrix<T>& matrix)
		{
			long double sum = 0;
			for (auto& i : matrix)
			{
				sum += i * i;
			}
			return sqrt(sum);
		}
		template<class T>
		matrix<T> operator* (const matrix<T> a, const T& b)
		{
			matrix<T> temp = a;
			for (auto& i : temp)
			{
				i *=b;
			}
			return move(temp);
		}
	}
	/*�������ݱ�׼��*/
	namespace matrix_normalized {
		/*����Ԫ��ֵ�ķ�Χ������������upper_bound��Ԫ������Ϊ���ֵ����С������lower_bound��Ԫ������Ϊ��Сֵ*/
		template<class T>
		void set_range(matrix<T>& matrix, size_t column_num, T lower_bound, T upper_bound) {
			for (auto i = matrix.cbegin(column_num); i != matrix.cend(column_num); ++i)
			{
				if (*i < lower_bound)
					*i = lower_bound;
				else if (*i > upper_bound)
					*i = upper_bound;
			}
		}
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
		/*�����ݵ�labelת��Ϊ����������*/
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
				E(serialized_label.row(row_i)) = label_map[label_matrix.row(row_i)];
			}
			return label_map;
		}
	};

}
#endif