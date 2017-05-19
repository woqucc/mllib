#ifndef C45_H
#define C45_H
#include"range.h"
#include"data.h"
#include"tree.hh"
#include"classifier.h"
#include<unordered_map>
#include<memory>
namespace myml
{
	using namespace std;
	using count_result = unordered_map<long double, int>;
	using matrix_p = shared_ptr<matrix<long double>>;
	using feature_type = long double;
	using label_type = size_t;
	using param_type = long double;
	class c45_tree_node
	{

	public:

		c45_tree_node(matrix_p data);
		/*
		@breif 计算离散属性的gain
			计算信息使用属性an（第an个属性），对样本进行分类的信息增益
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
		@breif 计算信息增熵
		@param cr <类名,该类个数>
		@return 熵
		*/
		long double _calc_ent(const count_result& cr);
		long double _ent = 0;/*< 本节点熵值*/
		long double _gain = 0;/*<本节点最大信息增益*/
		long double _gain_ratio = 0;/*<本节点最大信息增益率*/
		bool _finish_node = false;
		long double _label = .0L;
		size_t _gain_ratio_attr = 0;
		size_t _gain_attr = 0;

		matrix_p _data;
		count_result _labels_count;
		//获取每类属性的个数
		count_result _get_column_classes_count(size_t column_num, matrix_p data);
		//获取某一类的值为
		count_result _get_specified_value_labels_count(long double value, matrix_p data, size_t column_num);
		//计算count_result 中value的和
		long double _count_value_sum(const count_result& cr);
		//根据数据中较多项判断类标
		void _set_finish_node();
		/*
		@brief 获取数据按照指定离散属性分隔获取的信息增益
		@param data 数据
		@param column_num 属性列数
		*/
		long double _calc_gain(matrix_p data, size_t column_num,const count_result& cr);
		
		/*
			@brief 根据count_result<类别,类数>，计算intrinsic value(分裂信息)
			@param count_result 类名，类数量
		*/
		long double _calc_intrinsic_value(const count_result& cr);
	};
	class c45 : public classifier<feature_type, label_type, param_type>
	{
	public:
		/*实现分类器标准接口*/
		const matrix<param_type> probabilities(const matrix<feature_type> & feature_matrix) const override;
		void train(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) override;
		bool load(istream &in) override;
		bool save(ostream &out) override;
		param_type objective_function(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) override;
		param_type accuracy(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const override;
		const matrix<label_type> predict(const matrix<feature_type> & feature_matrix) const override;
		void print(ostream & out = cout) override;
	protected:
		tree<c45_tree_node> tr;

		c45_tree_node _root;
	};
}
#endif // !C45_H
