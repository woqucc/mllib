#ifndef SOFTMAX_REGRESSION
#define SOFTMAX_REGRESSION
#include"data.h"
#include<map>
namespace myml
{
	/*设置数据类型，不想用template*/
	using feature_type = long double;
	using label_type = size_t;
	using param_type = long double;
	using label_class_map = map<label_type, long double>;
	class softmax_regression
	{
	public:
		softmax_regression(size_t feature_count, size_t label_count);
		void import_data(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix);
		/*随机梯度下降*/
		void sgd(matrix<feature_type> &feature_matrix, matrix<label_type> &label_matrix);
		/*批下降*/
		void batch_gd(matrix<feature_type> &feature_matrix, matrix<label_type> &label_matrix);
		/*
		Bold Driver方法更新学习速率
		即若当前error减小则增大学习速率，若error增大则减小学习速率
		仅对批下降方式有效
		*/
		void update_learning_rate_bd(param_type increase = 1.05, param_type decrease = 0.5);
		
		/*输出准确率*/
		param_type accuracy(matrix<feature_type> &feature_matrix, matrix<label_type> &label_matrix);
		/*
			计算误差矩阵（正确结果-预测结果）* 对应的特征向量
			@param in feature_matrix 输入特征矩阵，矩阵的每一行为一个特征向量
			@param in label_matrix 与特征矩阵每一行相对应的具体类标，用来计算误差
			@param out 输出误差矩阵，矩阵大小与_theta大小相同
		*/
		matrix<param_type> error_matrix(matrix<feature_type> &feature_matrix, matrix<label_type> &label_matrix);
		/*
			使用_theta预测特征矩阵的结果
			@param in 输入特征矩阵，矩阵的每一行为一个特征向量
			@param out 输入矩阵的预测结果，输出的矩阵每一行为一个预测结果，只有一列
		*/
		matrix<label_type> predict(matrix<feature_type> &feature_matrix);

		inline param_type error();
		void print()
		{
			_theta.print();
		}
	private:
		matrix<param_type> _theta;
		matrix<param_type> _pre_theta;
		param_type _cur_error = 0;
		param_type _last_error = 0;
		param_type _learn_rate = 0.01;
	};
	inline void softmax_regression::update_learning_rate_bd(param_type increase, param_type decrease)
	{
		if (_last_error - _cur_error > 10E-10L)
		{
			_learn_rate *= increase;
		}
		else if (_last_error < _cur_error)
		{
			_learn_rate *= decrease;
		}
	}
	inline param_type myml::softmax_regression::error()
	{
		return _cur_error;
	}
}
#endif // !SOFTMAX_REGRESSION
