#ifndef C45_H
#define C45_H
#include"range.h"
#include"data.h"
#include<unordered_map>
#include<memory>
namespace myml
{
	using namespace std;
	using count_result = unordered_map<long double, int>;
	using matrix_p = shared_ptr<matrix<long double>>;
	class c45_tree_node
	{

	public:

		c45_tree_node(matrix_p data);
		/*
		@breif ������ɢ���Ե�gain
			������Ϣʹ������an����an�����ԣ������������з������Ϣ����
		*/
		void calc_discrete_gain();
		size_t split_by_gain_ratio();
		void append_child(c45_tree_node&& tn);
		void append_child(const c45_tree_node& tn);
		void remove_child(size_t i);
		void print(ostream &out);
		size_t depth = 0;
		valarray<range<long double>> _children_range;
	private:

		vector<c45_tree_node> _children;
		/*
		@breif ������Ϣ����
		@param cr <����,�������>
		@return ��
		*/
		long double _calc_ent(const count_result& cr);
		long double _ent = 0;/*< ���ڵ���ֵ*/
		long double _gain = 0;/*<���ڵ������Ϣ����*/
		long double _gain_ratio = 0;/*<���ڵ������Ϣ������*/
		bool _finish_node = false;
		long double _label = .0L;
		size_t _gain_ratio_attr = 0;
		size_t _gain_attr = 0;

		matrix_p _data;
		count_result _labels_count;
		//��ȡÿ�����Եĸ���
		count_result _get_column_classes_count(size_t column_num, matrix_p data);
		//��ȡĳһ���ֵΪ
		count_result _get_specified_value_labels_count(long double value, matrix_p data, size_t column_num);
		//����count_result ��value�ĺ�
		long double _count_value_sum(const count_result& cr);
		//���������н϶����ж����
		void _set_finish_node();
		/*
		@brief ��ȡ���ݰ���ָ����ɢ���Էָ���ȡ����Ϣ����
		@param data ����
		@param column_num ��������
		*/
		long double _calc_gain(matrix_p data, size_t column_num,const count_result& cr);
		
		/*
			@brief ����count_result<���,����>������intrinsic value(������Ϣ)
			@param count_result ������������
		*/
		long double _calc_intrinsic_value(const count_result& cr);
	};
	class c45_tree
	{
	public:
		c45_tree(matrix_p data);
		void train();
	protected:
		c45_tree_node _root;
	};
}
#endif // !C45_H
