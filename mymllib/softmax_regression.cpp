#include "softmax_regression.h"
#include<cmath>
namespace myml
{
	using namespace matrix_operate;
	softmax_regression::softmax_regression(size_t feature_count, size_t label_count)
	{
		_theta.resize(label_count, feature_count + 1);
		_theta.fill(0);
		_pre_theta = _theta;
		
		_error_matrix = _theta;
		
		_grad_ewma = _theta;
		_error_ewma = _theta;

		_cur_error = rand();
		_last_error = rand();
	}

	void softmax_regression::load(const matrix<param_type>& theta)
	{
		_theta = theta;
	}


	void softmax_regression::sgd(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix, const param_type & learning_rate)
	{

		_error_matrix = error_matrix(feature_matrix.row(0), label_matrix.row(0));

		_last_error = _cur_error;
		_cur_error = norm_f(_error_matrix);

		_pre_theta = _theta;
		_theta -= (_error_matrix *= learning_rate);
	}

	void softmax_regression::sgd_momentum(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix, param_type rho, param_type eit)
	{
		//不好使！！！！
		_last_error_matrix = _error_matrix;
		_error_matrix = error_matrix(feature_matrix.row(0), label_matrix.row(0)) * _learning_rate;
		_error_matrix = _last_error_matrix * rho - _error_matrix * (1-rho);
		//_error_matrix.print();

		_pre_theta = _theta;
		_theta += (_error_matrix);
		_last_error = _cur_error;
		_cur_error = norm_f(_error_matrix);
	}

	void softmax_regression::batch_sgd(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix)
	{
		_error_matrix = error_matrix(feature_matrix, label_matrix);

		_last_error = _cur_error;
		_cur_error = error(feature_matrix, label_matrix);

		_pre_theta = _theta;
		_theta -= ((_error_matrix) *= _learning_rate);

	}

	matrix<feature_type> softmax_regression::predict(const matrix<feature_type>& feature_matrix) const
	{
		matrix<feature_type> feature(feature_matrix.row_size(), feature_matrix.col_size() + 1);
		/*最后一列填1*/
		feature.cols(0, feature_matrix.col_size() - 1) = feature_matrix;
		feature.col(feature_matrix.col_size()).fill(1);
		matrix<feature_type> predict_result = feature*_theta.t();
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			/*
			* trick: 在线性相乘得到的结果predict_result中，首先获取其中最大的值，随后将，这样不会造成overflow
			*/
			predict_result.row(row_i) -= predict_result.row(row_i).max();
			predict_result.row(row_i) = exp(predict_result.row(row_i));
			/*正则化，使概率和在0-1之间*/
			predict_result.row(row_i) /= sum(predict_result.row(row_i));
		}
	
		//label_type(result.row(row_i)) = predict_result.max_position().first;
		return predict_result;
	}




	void softmax_regression::adadelta(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix,param_type epsilon, param_type rho)
	{
		matrix<param_type> grad = error_matrix(feature_matrix, label_matrix);
		_cur_error = norm_f(grad);
		_grad_ewma = _grad_ewma * rho + dot(grad, grad) * (1 - rho);


		_last_error_matrix = _error_matrix;

		_error_matrix = sqrt((_error_ewma + epsilon) / (_grad_ewma + epsilon));

		_error_matrix  = dot(_error_matrix, grad);
		
		_pre_theta = _theta;


		_theta -= _error_matrix;
		_error_ewma = _error_ewma * rho + dot(_error_matrix, _error_matrix) * (1 - rho);
		

	}

	param_type softmax_regression::accuracy(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix)
	{
		matrix<param_type> pr = predict(feature_matrix);
		size_t total = pr.row_size();
		size_t correct = 0;
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			if (pr.row(row_i).max_position().second == label_matrix.row(row_i))
				correct++;
		}
		return (correct + .0) / total;
	}

	matrix<param_type> softmax_regression::error_matrix(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix)
	{
		/*误差矩阵大小与_theta大小相同*/
		matrix<feature_type> sum_error(_theta.row_size(), _theta.col_size());
		matrix<feature_type> predict_matrix = predict(feature_matrix);
		/*累加每个特征向量的误差*/
		for (size_t row_i = 0; row_i < predict_matrix.row_size(); ++row_i)
		{
			for (size_t theta_i = 0; theta_i < predict_matrix.col_size(); ++theta_i)
			{
				predict_matrix.at(row_i, theta_i) =  predict_matrix.at(row_i, theta_i) - (theta_i == label_matrix.row(row_i) ? 1 : 0);
			}
			
		}
		predict_matrix.transpose();
		/*预测结果的每一列误差，乘以对应的特征向量项，*/
		for (size_t col_i = 0; col_i < predict_matrix.col_size(); ++col_i)
		{
			sum_error.cols(0, _theta.col_size() - 2) += predict_matrix.col(col_i) * feature_matrix.row(col_i);
			/*补1*/
			sum_error.col(_theta.col_size() - 1) = predict_matrix.col(col_i);
		}	
		sum_error /= param_type(feature_matrix.row_size());
		return sum_error;
	}
	void softmax_regression::set_theta(const matrix<feature_type>& feature_matrix)
	{
		_theta = feature_matrix;
	}
	param_type softmax_regression::error(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix)
	{
		_last_error = _cur_error;
		_cur_error = 0;
		
		matrix<feature_type> predict_matrix = predict(feature_matrix);
		for (size_t row_i = 0; row_i < predict_matrix.row_size(); ++row_i)
		{
			size_t label = label_matrix.at(row_i, 0);
			_cur_error += predict_matrix.at(row_i, label);
		}
		return _cur_error;
	}
}