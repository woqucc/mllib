#ifndef DATA_H
#define DATA_H
#include<vector>
#include<algorithm>
#include<stack>
#include<iostream>
#include<memory>
#include<valarray>
#include<functional>

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
		matrix() = default;
		matrix(matrix & m);
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
		virtual size_t size() const = 0;
		/*
		@brief ��ȡԪ��ά��
		*/
		virtual size_t dimension() const = 0;
		/*
		@brief ������
		@param row Ԫ���е��׵�ַָ��
		@param size Ԫ��ά��
		*/
		virtual void push_back(T *row, size_t size) = 0;
		/*
		@brief ��������ÿ�����������Ƿ���ͬ,�������Ƿ�Ϸ�
		@return true ÿ������������ͬ���Ϸ�
		@return false ÿ������������ͬ���Ƿ�;����Ϊ��
		*/
		virtual bool rect_check() const = 0;
		/*
		@brief ��������
		@param row1 ����������1
		@param row2 ����������2
		*/
		virtual void swap_row(size_t row1, size_t row2) = 0;
		/*
		@brief ��ȡĳһԪ��
		@param row_num ����
		@param col_num ����
		*/
		virtual T& at(size_t row_num, size_t col_num) = 0;
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
		virtual shared_ptr<matrix<T>> sub_matrix(size_t row_begin, size_t column_begin, size_t row_end, size_t column_end) = 0;
		/*
		@brief ��ֵ������
		*/
		matrix& operator =(matrix& rn);

		using index_array = valarray<size_t>;//��valarray��Ϊ�ݶ��Ĵ洢�±�����ݽṹ
		/*
		@brief ��ȡָ���г�Ϊ�µľ���
		*/
		virtual shared_ptr<matrix<T>> fetch_row(const index_array& row_indexs) const = 0;

		/*
		@brief ��ȡ����ָ����������
		*/
		virtual shared_ptr<matrix<T>> fetch_row(function<bool(const valarray<T> &va)> condition) const = 0;

		/*
		@brief ��ȡָ���г�Ϊ�µľ���
		*/
		virtual shared_ptr<matrix<T>> fetch_column(const index_array& column_indexs) const = 0;

		/*
		@brief ɾ��ָ����
		*/
		virtual void remove_row(const index_array& column_indexs) = 0;

		/*
		@brief ɾ��ָ����
		*/
		virtual void remove_column(const index_array& column_indexs) = 0;

		/*
		@brief ɾ��ָ����
		*/
		//virtual void cfetch_row(const index_array& column_indexs) = 0;

		/*
		@brief �����򣬽�����ȡ��˳��
		*/
		virtual index_array get_order(size_t column_num);
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
	inline matrix<T>::matrix(matrix & m)
	{
		*this = m;
	}

	template<class T>
	inline matrix<T>& matrix<T>::operator= (matrix & m)
	{
		size_t dms = m.dimension();
		auto *row = new T[dms]();
		for (size_t row_num = 0; row_num < m.size(); row_num++)
		{
			for (size_t column_count = 0; column_count < dms; column_count++)
			{
				row[i] = m.at(i);
				push_back(row, dms);
			}
		}
		delete[] row;
		return *this;
	}
	//TODO :�Ż��߼�
	template<class T>
	inline typename matrix<T>::index_array matrix<T>::get_order(size_t column_num)
	{
		index_array&& ia = index_array(size());
		for (size_t i = 0; i < ia.size(); i++)
		{
			ia[i] = i;
		}
		auto temp = sub_matrix(0, column_num, size(), column_num);
		/*ʹ��ջ����ݹ飬ִ�п���*/
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
				//�Ӻ���ǰ�ҵ�С��key��Ԫ��j����j���浽i��
				//�״ν���ʱiΪbegin
				while (i < j && temp->at(j, column_num) >= key)
				{
					j--;
				}
				//����
				std::swap(ia[i], ia[j]);
				temp->swap_row(i, j);
				//��ǰ����ҵ���һ������key��Ԫ��i����j�����������浽j����beginԪ�ؽ�����i��
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
		/*ʹ��ջ����ݹ飬ִ�п���*/
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

	/*
	@brief �����࣬ͨ��vector�洢valarrayʵ��
	*/
	template <class T>
	class matrix_va :public matrix<T>
	{
	public:
		void push_back(T *row, size_t size);
		void push_back(valarray<T> && row);
		void push_back(const valarray<T>& row);
		bool rect_check() const;
		shared_ptr<matrix<T>> sub_matrix(size_t row_begin, size_t column_begin, size_t row_end, size_t column_end);
		shared_ptr<matrix<T>> fetch_row(const index_array& row_indexs) const override;
		shared_ptr<matrix<T>> fetch_row(function<bool(const valarray<T> &va)> condition) const override;
		shared_ptr<matrix<T>> fetch_column(const index_array& fetch_column)const override;
		void remove_column(const index_array& column_indexs) override;
		void remove_row(const index_array& column_indexs) override;
		matrix_va<T>() = default;
		matrix_va<T>(matrix_va&& m);
		matrix_va<T>(const matrix_va& m);
		size_t size() const override;
		size_t dimension() const override;
		void swap_row(size_t row1, size_t row2) override;
		T& at(size_t row_num, size_t col_num) override;
	private:
		vector<valarray<T>> _data;
	};
	template<class T>
	inline void matrix_va<T>::push_back(T * row, size_t size)
	{
		auto&& temp = valarray<T>(size);
		for (size_t i = 0; i < size; i++)
		{
			temp[i] = row[i];
		}
		_data.push_back(move(temp));
	}
	template<class T>
	inline void matrix_va<T>::push_back(valarray<T>&& row)
	{
		_data.push_back(forward<valarray<T>>(row));
	}
	template<class T>
	inline void matrix_va<T>::push_back(const valarray<T>& row)
	{
		_data.push_back(row);
	}
	template<class T>
	inline bool matrix_va<T>::rect_check() const
	{
		if (_data.size() == 0)return false;
		auto column_size = (_data.begin())->size();
		for (auto row = _data.begin()++; row != _data.end(); row++)
		{
			if (row->size() != column_size)
				return false;
		}
		return true;
	}

	template<class T>
	shared_ptr<matrix<T>> matrix_va<T>::sub_matrix(size_t row_begin, size_t column_begin, size_t row_end, size_t column_end)
	{
		shared_ptr<matrix_va<T>> m(new matrix_va<T>());
		for (auto row_i = row_begin; row_i < row_end; row_i++)
		{
			auto row = _data.begin() + row_i;
			m->push_back(
				[column_begin, column_end, row]
			{
				auto&& temp = valarray<T>(column_end - column_begin);
				for (size_t i = column_begin; i < column_end; ++i)
				{
					temp[i - column_begin] = (*row)[i];
				};
				return move(temp);
			}());
		}
		return m;
	}

	template<class T>
	inline shared_ptr<matrix<T>> matrix_va<T>::fetch_row(const index_array & row_indexs) const
	{
		auto temp = shared_ptr<matrix_va<T>>(new matrix_va());
		for (auto i : row_indexs)
		{
			temp->push_back(_data[i]);
		}
		return temp;
	}

	template<class T>
	inline shared_ptr<matrix<T>> matrix_va<T>::fetch_row(function<bool(const valarray<T> &va)> condition) const
	{
		auto temp = shared_ptr<matrix_va<T>>(new matrix_va());
		size_t row_begin = 0;

		for (const auto& row : _data)
		{
			if (condition(row))
				temp->push_back(row);
		}

		return temp;
	}

	template<class T>
	inline shared_ptr<matrix<T>>  matrix_va<T>::fetch_column(const index_array & fetch_column) const
	{
		auto temp = shared_ptr<matrix_va<T>>(new matrix_va());
		valarray<T> temp_row(fetch_column.size());
		for (size_t i = 0; i < _data.size(); ++i)
		{
			for (size_t j = 0; j < fetch_column.size(); ++j)
			{
				temp_row[j] = _data[i][fetch_column[j]];
			}
			temp->push_back(temp_row);
		}
		return temp;
	}

	template<class T>
	inline void matrix_va<T>::remove_column(const index_array & column_indexs)
	{
		if (column_indexs.size() == 0)
			return;
		if (column_indexs.size() == dimension())
		{
			_data.clear();
			return;
		}
		vector<valarray<T>> temp_data;
		valarray<T> temp_row(dimension() - column_indexs.size());
		_data.swap(temp_data);
		for (auto& row : temp_data)
		{
			size_t dn = 0;
			for (size_t cn = 0; cn < row.size(); ++cn)
			{
				if ([column_indexs, cn] {
					for (auto i : column_indexs)
					{
						if (cn == i)
							return false;
					}
					return true;
				}())
					temp_row[dn++] = row[cn];
			}
			_data.push_back(temp_row);
		}
	}

	template<class T>
	inline void matrix_va<T>::remove_row(const index_array & column_indexs)
	{
		for (size_t i = 0; i < column_indexs.size(); ++i)
		{
			_data.erase(_data.begin() + (column_indexs[i] - i));
		}
	}

	template<class T>
	inline size_t matrix_va<T>::size() const
	{
		return _data.size();
	}

	template<class T>
	inline size_t matrix_va<T>::dimension() const
	{
		if (_data.size() == 0)
			return 0;
		return (_data.begin())->size();
	}

	template<class T>
	inline void matrix_va<T>::swap_row(size_t row1, size_t row2)
	{
		std::swap(_data[row1], _data[row2]);
	}

	template<class T>
	T& matrix_va<T>::at(size_t row_num, size_t col_num)
	{
		return _data[row_num][col_num];
	}

	template<class T>
	inline matrix_va<T>::matrix_va(matrix_va<T> && m)
	{
		_data.swap(forward(m));
		//for (auto &&v : m._data)
		//{
		//	_data.push_back(forward(v));
		//}
	}
	template<class T>
	inline matrix_va<T>::matrix_va(const matrix_va<T>& m)
	{
		for (auto v : m._data)
		{
			_data.push_back(v);
		}
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
		size_t column_num = count(line, line + strlen(line), split) + 1;
		delete[] line;
		if (column_num == 0)
			return false;
		/*���ļ�ָ�����õ��ļ��ײ�*/
		in.seekg(ios::beg);
		T *num_line = new T[line_width]();
		while (!in.eof())
		{
			for (size_t i = 0; i < column_num - 1; i++)
			{
				in >> num_line[i] >> split;
			}
			in >> num_line[column_num - 1];
			matrix.push_back(num_line, column_num);
		}
		delete[] num_line;
		return true;
	};
	/*
	��׼��������
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