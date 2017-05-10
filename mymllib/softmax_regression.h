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

		void load(const matrix<param_type>& theta);
		/*随机梯度下降，可以一次传入多个样本*/
		void sgd(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix,const param_type & learning_rate = 1E-5);

		/*随机梯度下降，可以一次传入多个样本*/
		void sgd_momentum(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix,param_type rho = 0.9 ,param_type eit = 0.3);

		/*批量梯度下降，如果传入的样本的batch为全部样本，则为正常的梯度下降*/
		void batch_sgd(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix);
		/*
		Bold Driver方法更新学习速率
		即若当前error减小则增大学习速率，若error增大则减小学习速率
		仅对批下降方式有效
		*/
		void update_learning_rate_bd(param_type increase = 1.05, param_type decrease = 0.5);
		/*
		Bold Driver方法更新学习速率
		即若当前error减小则增大学习速率，若error增大则减小学习速率
		仅对批下降方式有效
		*/
		void adadelta(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix,param_type epsilon = 1E-6, param_type rho = 0.95);

		
		/*输出准确率*/
		param_type accuracy(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix);
		/*
			计算误差矩阵（正确结果-预测结果）* 对应的特征向量
			@param in feature_matrix 输入特征矩阵，矩阵的每一行为一个特征向量
			@param in label_matrix 与特征矩阵每一行相对应的具体类标，用来计算误差
			@param out 输出误差矩阵，矩阵大小与_theta大小相同
		*/
		matrix<param_type> error_matrix(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix);
		/*
			使用_theta预测特征矩阵的结果
			@param in 输入特征矩阵，矩阵的每一行为一个特征向量
			@param out 输入矩阵的预测结果，输出的矩阵每一行为一个预测结果，只有一列
		*/
		matrix<feature_type> predict(const matrix<feature_type> &feature_matrix) const;

		param_type error(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix);
		void print()
		{
			_theta.print();
		}
		void set_theta(const matrix<feature_type> &feature_matrix);
	private:
		matrix<param_type> _theta;
		matrix<param_type> _pre_theta;
		param_type _cur_error = 0;
		param_type _last_error = 0;
		param_type _learning_rate = 1E-3L;

		matrix<param_type> _grad_ewma;
		matrix<param_type> _error_ewma;

		/*仅在使用动量法进行梯度下降时使用*/
		matrix<param_type> _last_error_matrix;/*上一次误差*/
		matrix<param_type> _error_matrix;/*本次误差*/
	};
	inline void softmax_regression::update_learning_rate_bd(param_type increase, param_type decrease)
	{
		if (_last_error - _cur_error > 10E-10L)
		{
			_learning_rate *= increase;
		}
		else if (_last_error < _cur_error)
		{
			_learning_rate *= decrease;
			_theta = _pre_theta;
		}
	}
	template <class T>
	matrix<size_t> confusion_matrix(const softmax_regression& sr, const matrix<T> &feature_matrix)
	{
		matrix<T> p = sr.predict(feature_matrix);
		
	}

}
#endif // !SOFTMAX_REGRESSION
