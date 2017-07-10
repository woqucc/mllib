﻿#ifndef OPTIMIZER_H
#define OPTIMIZER_H
#include"../classifier/classifier.h"
#include"../data/matrix.h"
namespace myml
{
	using namespace matrix_operate;
	template<class classifier_type, class feature_type, class label_type>
	class optimizer
	{
	public:
		optimizer(classifier_type &cf):_classifier(cf) {};
	protected:
		classifier_type & _classifier;
	};
	/*
	设计意图：避免重复实施梯度下降系列算法，例如停止条件（未实施），学习速率计算等
	*/
	
	
	/*模板：计算过程中使用的参数类型，传递的参数类型*/
	template<class classifier_type,class feature_type = classifier_type::feature_type,class label_type= classifier_type::label_type>
	class grad_desc_optimizer :optimizer<classifier_type, feature_type, label_type>
	{
		
	public:
		grad_desc_optimizer(classifier_type& cf);

		/*
		随机梯度下降，计算单独样本的梯度后更新
		*/
		void sgd(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix, feature_type learning_rate = 1E-5);
		/*
		批量梯度下降，累加本次传入所有样本的梯度后更新
		*/
		void batch_gd(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix, feature_type learning_rate=1E-5);
		/*
		随机梯度下降，动量法更新梯度
		*/
		void sgd_momentum(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix, feature_type learning_rate = 1E-5,feature_type rho = 0.9, feature_type eit = 0.3);
		/*
		随机梯度下降，adadelta方式计算更新速率
		*/
		void sgd_adadelta(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix, feature_type epsilon = 1E-6, feature_type rho = 0.95);
	private:
		matrix<feature_type> _last_grad;/*上一次计算出的梯度矩阵*/
		matrix<feature_type> _grad;/*本次计算出的梯度矩阵*/

		matrix<feature_type> _error;/*本次计算出的系数误差，通常为梯度乘以系数*/
		matrix<feature_type> _last_error;/*上次计算出的系数误差*/

		matrix<feature_type> _grad_square_ewma;/*梯度平方的移动平均值*/
		matrix<feature_type> _error_square_ewma;/*每次更新误差的平方的移动平均值*/
	};





	template<class classifier_type, class feature_type, class label_type>
	inline grad_desc_optimizer<classifier_type, feature_type, label_type>::grad_desc_optimizer(classifier_type & cf):optimizer(cf)
	{
		_grad.resize(cf.label_size, cf.feature_size + 1);
		_grad.fill(0);
		_last_grad = _grad;

		_error = _grad;
		_last_error = _grad;

		_grad_square_ewma = _grad;
		_error_square_ewma = _grad;
	}

	template<class classifier_type, class feature_type, class label_type>
	inline void grad_desc_optimizer<classifier_type, feature_type, label_type>::sgd(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix, feature_type learning_rate)
	{
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			_grad = _classifier.gradient(feature_matrix.row(row_i), label_matrix.row(row_i));
			_classifier._theta -= _grad * learning_rate;
		}
	}
	
	template<class classifier_type, class feature_type, class label_type>
	inline void grad_desc_optimizer<classifier_type, feature_type, label_type>::batch_gd(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix, feature_type learning_rate)
	{
		_grad = _classifier.gradient(feature_matrix, label_matrix);
		_classifier._theta -= _grad * learning_rate;
	}

	template<class classifier_type, class feature_type, class label_type>
	inline void grad_desc_optimizer<classifier_type, feature_type, label_type>::sgd_momentum(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix,feature_type learning_rate, feature_type rho, feature_type eit)
	{
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			_last_error = _error;
			_grad = _classifier.gradient(feature_matrix.row(row_i), label_matrix.row(row_i));
			//思想：本次梯度是本次计算出的梯度和上一次梯度的向量和,待考证
			_error = _last_error * rho + _grad * (1 - rho);
			_classifier._theta -= _error * learning_rate;
		}
	}

	template<class classifier_type, class feature_type, class label_type>
	inline void grad_desc_optimizer<classifier_type, feature_type, label_type>::sgd_adadelta(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix, feature_type epsilon, feature_type rho)
	{
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			matrix<feature_type> _grad = _classifier.gradient(feature_matrix.row(row_i), label_matrix.row(row_i));

			_grad_square_ewma = _grad_square_ewma * rho + dot(_grad, _grad) * (1 - rho);

			_error = sqrt((_error_square_ewma + epsilon) / (_grad_square_ewma + epsilon));
			_error = dot(_error, _grad);

			_classifier._theta -= _error;
			_error_square_ewma = _error_square_ewma * rho + dot(_error, _error) * (1 - rho);
		}
	}
	/*模板：计算过程中使用的参数类型，传递的参数类型*/
	template<class classifier_type, class feature_type = classifier_type::feature_type, class label_type = classifier_type::label_type>
	class newton_raphson_optimizer :optimizer<classifier_type, feature_type, label_type>
	{
	public:
		newton_raphson_optimizer(classifier_type &cf) :optimizer(cf) {};
		void newton_raphson (const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix);
	};
	
	
	template<class classifier_type, class feature_type, class label_type>
	inline void newton_raphson_optimizer<classifier_type, feature_type, label_type>::newton_raphson(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix)
	{
		auto hessian = _classifier.hessian(feature_matrix, label_matrix);
		//(get<0>(x) * transpose(get<0>(x))).print();
		//hessian.print();
		//hessian += identity_matrix<feature_type>(hessian.row_size()) * 1E-8;
		auto inverse_hessian = pseudo_inverse(hessian);
		//inverse_hessian.print();
		//(hessian * inverse_hessian).print();
		auto gradient = dynamic_cast<softmax_regression&>(_classifier).gradient(feature_matrix, label_matrix);
		//auto gradient = _classifier.gradient(feature_matrix, label_matrix);
		

		gradient.reshape(_classifier.label_size + _classifier.feature_size * _classifier.label_size, 1);
		auto hg = inverse_hessian * gradient;
		hg.reshape(_classifier.feature_size + 1, _classifier.label_size).transpose();

		//transpose(reshape(inverse(hessian_matrix) * grad, theta_size, label_size));
		//TODO 优化
		//cf.hessian(feature_matrix, label_matrix).print();
		//cparam -= cf.hessian(feature_matrix, label_matrix);
		_classifier._theta -= hg;
	}
}
#endif // !OPTIMIZER_H
