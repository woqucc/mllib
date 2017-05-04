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
		_cur_error = rand();
		_last_error = rand();
	}

	void softmax_regression::import_data(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix)
	{

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
		_error_matrix = error_matrix(feature_matrix.row(0), label_matrix.row(0));
		_error_matrix = _last_error_matrix * rho - _error_matrix * eit;
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
		_cur_error = norm_f(_error_matrix);

		_pre_theta = _theta;
		_theta -= ((_error_matrix) *= _learning_rate);

	}

	matrix<label_type> softmax_regression::predict(const matrix<feature_type>& feature_matrix)
	{
		matrix<label_type> result(feature_matrix.row_size(), 1);
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			matrix<feature_type> row = matrix<feature_type>(1, feature_matrix.col_size() + 1);
			row.col(feature_matrix.col_size()).fill(1);
			row.cols(0, feature_matrix.col_size() - 1) = feature_matrix.row(row_i);
			row.transpose();
			matrix<feature_type> predict_result = (_theta * row);

			param_type max = -LDBL_MAX;
			label_type max_i = 0;
			for (size_t row_i = 0; row_i < predict_result.row_size(); ++row_i)
			{
				if (predict_result.row(row_i) > max)
				{
					max = predict_result.row(row_i);
					max_i = row_i;
				}
			}
			label_type(result.row(row_i)) = max_i;
		}
		return result;
	}




	void softmax_regression::adadelta(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix,param_type epsilon, param_type rho)
	{
		_error_matrix = error_matrix(feature_matrix, label_matrix);
	}

	param_type softmax_regression::accuracy(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix)
	{
		matrix<label_type> pr = predict(feature_matrix);
		size_t total = pr.row_size();
		size_t correct = 0;
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			if (pr.row(row_i) == label_matrix.row(row_i))
				correct++;
		}
		return (correct + .0) / total;
	}

	matrix<param_type> softmax_regression::error_matrix(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix)
	{
		/*误差矩阵大小与_theta大小相同*/
		matrix<feature_type> sum_error(_theta.row_size(), _theta.col_size());
		/*累加每个特征向量的误差*/
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			/*临时特征向量，增加特征向量的维数，计算常数项*/
			matrix<feature_type> row = matrix<feature_type>(1, feature_matrix.col_size() + 1);
			/*临时特征向量的最后一维与常数项系数相乘，设置为1*/
			row.col(feature_matrix.col_size()).fill(1);
			/*临时特征向量赋值*/
			row.cols(0, feature_matrix.col_size() - 1) = feature_matrix.row(row_i);
			/*转置临时向量*/
			row.transpose();

			/*
			特征向量的预测结果predict_result，的行数与类标数相同
			第i行即该特征向量为第i类的概率
			*/
			/*系数矩阵乘以行的线性结果*/
			matrix<feature_type> predict_result = (_theta * row);
			for (auto &i : predict_result)
			{
				if (i > 709.783)
				{
					i = 709;
				}
			}
			/*softmax函数处理*/
			exp(predict_result);
			predict_result /= sum(predict_result);
			
			for (auto &i : predict_result)
			{
				if (isnan(i))
				{
					i = 1.0L / predict_result.row_size();
				}
			}
			//predict_result.print();
			/*准确结果为，特征向量的真正类标的那一行应该为1，其他行应该为0
			使用准确结果减去真正结果
			*/
			for (size_t theta_i = 0; theta_i < predict_result.row_size(); ++theta_i)
			{
				//准确结果减去预测结果为误差
				feature_type(predict_result.row(theta_i)) = (theta_i == label_matrix.row(row_i) ? 1 - predict_result.row(theta_i) : 0 - predict_result.row(theta_i));
			}
			/*预测结果的每一行误差，乘以倒数中的特征向量项*/
			sum_error += predict_result * row.t();
		}
		sum_error /= -param_type(feature_matrix.row_size());
		return sum_error;
	}

}