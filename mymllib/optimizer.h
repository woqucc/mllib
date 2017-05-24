#ifndef OPTIMIZER_H
#define OPTIMIZER_H
#include"classifier.h"
namespace myml
{

	template<class feature_type, class label_type, class calc_param_type ,class class_param_type>
	class optimizer
	{
	public:


	private:

	};
	/*
	设计意图：避免重复实施梯度下降系列算法，例如停止条件（未实施），学习速率计算等
	*/
	
	
	/*模板：计算过程中使用的参数类型，传递的参数类型*/
	template<class feature_type, class label_type, class calc_param_type, class class_param_type>
	class grad_desc_optimizer :optimizer<feature_type, label_type, calc_param_type, class_param_type>
	{
	public:
		grad_desc_optimizer(size_t feature_size, size_t label_size);
		calc_param_type learning_rate = 1E-2;

		/*
		随机梯度下降，计算单独样本的梯度后更新
		*/
		void sgd(class_param_type & cparam, const classifier<feature_type, label_type, calc_param_type> &cf, const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix);
		/*
		批量梯度下降，累加本次传入所有样本的梯度后更新
		*/
		void batch_gd(class_param_type & cparam, const classifier<feature_type, label_type, calc_param_type> &cf, const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix);
		/*
		随机梯度下降，动量法更新梯度
		*/
		void sgd_momentum(class_param_type & cparam, const classifier<feature_type, label_type, calc_param_type> &cf, const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix, calc_param_type rho, calc_param_type eit);
		/*
		随机梯度下降，adadelta方式计算更新速率
		*/
		void sgd_adadelta(class_param_type & cparam, const classifier<feature_type, label_type, calc_param_type> &cf, const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix, calc_param_type epsilon, calc_param_type rho );
	private:
		matrix<calc_param_type> _last_grad;/*上一次计算出的梯度矩阵*/
		matrix<calc_param_type> _grad;/*本次计算出的梯度矩阵*/

		matrix<calc_param_type> _error;/*本次计算出的系数误差，通常为梯度乘以系数*/
		matrix<calc_param_type> _last_error;/*上次计算出的系数误差*/

		matrix<calc_param_type> _grad_square_ewma;/*梯度平方的移动平均值*/
		matrix<calc_param_type> _error_square_ewma;/*每次更新误差的平方的移动平均值*/
	};



	template<class feature_type, class label_type, class calc_param_type, class class_param_type>
	inline grad_desc_optimizer<feature_type, label_type, calc_param_type, class_param_type>::grad_desc_optimizer(size_t feature_size, size_t label_size)
	{
		_grad.resize(label_size, feature_size + 1);
		_grad.fill(0);
		_last_grad = _grad;

		_error = _grad;
		_last_error = _grad;

		_grad_square_ewma = _grad;
		_error_square_ewma = _grad;
	}

	template<class feature_type, class label_type, class calc_param_type, class class_param_type>
	inline void grad_desc_optimizer<feature_type, label_type, calc_param_type, class_param_type>::sgd(class_param_type & cparam, const classifier<feature_type, label_type, calc_param_type>& cf, const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix)
	{
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			_grad = cf.gradient(feature_matrix.row(row_i), label_matrix.row(row_i));
			cparam -= _grad * learning_rate;
		}
	}
	
	template<class feature_type, class label_type, class calc_param_type, class class_param_type>
	inline void grad_desc_optimizer<feature_type, label_type, calc_param_type, class_param_type>::batch_gd(class_param_type & cparam, const classifier<feature_type, label_type, calc_param_type>& cf, const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix)
	{
		_grad = cf.gradient(feature_matrix, label_matrix);
		cparam -= _grad * learning_rate;
	}

	template<class feature_type, class label_type, class calc_param_type, class class_param_type>
	inline void grad_desc_optimizer<feature_type, label_type, calc_param_type, class_param_type>::sgd_momentum(class_param_type & cparam, const classifier<feature_type, label_type, calc_param_type>& cf, const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix, calc_param_type rho, calc_param_type eit)
	{
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			_last_error = _error;
			_grad = cf.gradient(feature_matrix.row(row_i), label_matrix.row(row_i));
			//思想：本次梯度是本次计算出的梯度和上一次梯度的向量和,待考证
			_error = _last_error * rho + _grad * (1 - rho);
			cparam -= _error * learning_rate;
		}
	}

	template<class feature_type, class label_type, class calc_param_type, class class_param_type>
	inline void grad_desc_optimizer<feature_type, label_type, calc_param_type, class_param_type>::sgd_adadelta(class_param_type & cparam, const classifier<feature_type, label_type, calc_param_type>& cf, const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix, calc_param_type epsilon = 1E-6, calc_param_type rho = 0.95)
	{
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			matrix<calc_param_type> _grad = cf.gradient(feature_matrix.row(row_i), label_matrix.row(row_i));

			_grad_square_ewma = _grad_square_ewma * rho + dot(_grad, _grad) * (1 - rho);

			_error = sqrt((_error_square_ewma + epsilon) / (_grad_square_ewma + epsilon));
			_error = dot(_error, _grad);

			cparam -= _error;
			_error_square_ewma = _error_square_ewma * rho + dot(_error, _error) * (1 - rho);
		}
	}

}
#endif // !OPTIMIZER_H

