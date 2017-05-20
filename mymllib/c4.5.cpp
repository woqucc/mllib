#include "c4.5.h"
#include<cmath>
#include<valarray>
namespace myml
{
	c45_tree_node::c45_tree_node(matrix_p data) :_data(data)
	{
		calc_discrete_gain();
	}

	inline long double c45_tree_node::_calc_ent(const count_result& cr)
	{
		auto element_sum = _count_value_sum(cr);
		long double ent = 0;
		for (auto i = cr.begin(); i != cr.end(); ++i)
		{
			long double proportion = (.0L + i->second) / element_sum;
			ent += proportion * log(proportion) / log(2.0L);
		}
		return -ent;
	}
	void c45_tree_node::calc_discrete_gain()
	{
		//类标位置
		size_t label_pos = _data->col_size() - 1;
		//获取类标的<类别，该类个数>
		_labels_count = _get_column_classes_count(label_pos, _data);
		if (_labels_count.size() == 1)
		{
			_set_finish_node();
			return;
		}
		_ent = _calc_ent(_labels_count);
		//使用哪一个属性进行分隔
		long double max_gain_ratio = -LDBL_MAX;
		long double max_gain = -LDBL_MAX;
		for (size_t attr_num = 0; attr_num < label_pos; attr_num++)
		{
			/*获取该属性的<种类,该类元素个数>*/
			auto attr_count_result = _get_column_classes_count(attr_num, _data);
			//只有一类，不用算了，换下一个
			if (attr_count_result.size() < 2)
			{
				continue;
			}
			//根据使用该属性分隔后的每一类中真实类标的<种类,该类元素个数>
			_gain = _ent - _calc_gain(_data, attr_num, attr_count_result);
			//计算iv
			_gain_ratio = _gain / _calc_intrinsic_value(attr_count_result);
			if (max_gain_ratio < _gain_ratio)
			{
				max_gain_ratio = _gain_ratio;
				_gain_ratio_attr = attr_num;
			}
			if (max_gain < _gain)
			{
				max_gain = _gain;
				_gain_attr = attr_num;
			}
			cerr << "数据大小:" << _data->row_size() << endl;
			cerr << "信息增益：" << _gain << '\t';
			cerr << "当前节点熵：" << _ent << endl;
			cerr << "信息增益率：" << _gain_ratio << endl;
		}
		//如果未找到可进行分隔的属性（属性只有一种）,将该节点设置为终结节点
		if (max_gain_ratio == -LDBL_MAX && max_gain == -LDBL_MAX)
		{
			_set_finish_node();
		}
		//保存最大信息增益和最大信息增益率
		_gain = max_gain;
		_gain_ratio = max_gain_ratio;
	}

	size_t c45_tree_node::split_by_gain_ratio()
	{
		//如果不是终结节点
		if (_finish_node)
			return 1;
		//获取信息增益率最大的属性
		auto selected_attr_counts = _get_column_classes_count(_gain_ratio_attr, _data);
		//定义与子节点个数相对应的区间
		_children_range.resize(selected_attr_counts.size());
		cerr << "最大信息增益率的属性：" << _gain_ratio_attr << "\t" << _gain_ratio << endl;
		//使用信息增益率最大的属性进行分割
		//cerr << "print"; 
		for (const auto& attr : selected_attr_counts)
		{
			auto temp_gr = _gain_ratio_attr;
			matrix_p temp_matrix(&(_data->fetch_row([attr, temp_gr](const long double* val, size_t col_size) ->bool {
				if (val[temp_gr] == attr.first)
					return true;
				return false;
			})));
		//	temp_matrix->remove_column({ _gain_ratio_attr });
			append_child(c45_tree_node(temp_matrix));
			_children_range[_children.size() - 1].reset_to({ attr.first,attr.first });
		}
		size_t total_node = 0;
		for (auto& c : _children)
		{
			total_node += c.split_by_gain_ratio();
		}
		//this->print(cout);
		return total_node;
	}

	void c45_tree_node::append_child(c45_tree_node && tn)
	{
		_children.push_back(forward<c45_tree_node>(tn));
	}

	void c45_tree_node::append_child(const c45_tree_node & tn)
	{
		_children.push_back(tn);
	}

	void c45_tree_node::print(ostream &out)
	{
		out << "depth:" << depth;
		out << "\tgain_ratio" << _gain_ratio << endl;
		out << "data:" << endl;
		_data->print(out);
		for (auto& c : _children)
		{
			c.print(out);
		}
	}

	inline count_result c45_tree_node::_get_column_classes_count(size_t column_num, matrix_p data)
	{
		count_result&& cr = count_result();
		for (auto i = data->col_begin(column_num); i != data->col_end(column_num); ++i)
		{
			auto lable_pair = cr.find(*i);
			if (lable_pair == cr.end())
			{
				cr.insert({ *i, 1 });
			}
			else
			{
				lable_pair->second++;
			}
		}
		return move(cr);
	}

	long double c45_tree_node::_calc_gain(matrix_p data, size_t column_num, const count_result& cr)
	{
		//获取类标位置
		size_t lable_pos = data->col_size() - 1;
		auto index_map = unordered_map<long double, count_result>(cr.size());
		for (const auto& i : cr)
		{
			index_map.insert({ i.first, unordered_map<long double,int>() });
		}

		for (size_t i = 0; i < data->row_size(); ++i)
		{
			auto column_i = data->at(i, column_num);
			auto label = data->at(i, lable_pos);
			auto lable_i = index_map[column_i].find(label);
			if (lable_i == index_map[column_i].end())
			{
				index_map[column_i].insert({ label,1 });
			}
			else
			{
				lable_i->second++;
			}
		}

		long double gain = 0;
		long double total = _count_value_sum(cr);
		for (const auto& i : index_map)
		{
			gain += _calc_ent(i.second) * _count_value_sum(i.second) / total;
		}
		return gain;
	}

	long double c45_tree_node::_calc_intrinsic_value(const count_result& cr)
	{
		auto total = _count_value_sum(cr);
		long double ivalue = 0;
		for (auto i : cr)
		{
			ivalue += i.second / total * log(i.second / total) / log(2);
		}
		return -ivalue;
	}

	count_result c45_tree_node::_get_specified_value_labels_count(long double value, matrix_p data, size_t column_num)
	{
		auto label_pos = data->col_size() - 1;
		count_result&& cr = count_result();
		for (auto i = data->col_begin(column_num); i != data->col_end(column_num); ++i)
		{
			if (*i != value)
				continue;
			auto lable_pair = cr.find(*i);
			if (lable_pair == cr.end())
			{
				cr.insert({ *i, 1 });
			}
			else
			{
				lable_pair->second++;
			}
		}
		return move(cr);
	}

	long double c45_tree_node::_count_value_sum(const count_result & cr)
	{
		long double sum = 0;
		for (const auto &i : cr)
		{
			sum += i.second;
		}
		return sum;
	}

	void c45_tree_node::_set_finish_node()
	{
		size_t most_label_count = _labels_count.begin()->second;
		auto most_label = _labels_count.begin()->first;
		for (const auto& i : _labels_count)
		{
			if (i.second > most_label_count)
			{
				most_label_count = i.second;
				most_label = i.first;
			}
		}
		_finish_node = true;
		_label = most_label;
	}

}