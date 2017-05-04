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
		//����ʹ��������
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
		/*�������С��_theta��С��ͬ*/
		matrix<feature_type> sum_error(_theta.row_size(), _theta.col_size());
		/*�ۼ�ÿ���������������*/
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			/*��ʱ������������������������ά�������㳣����*/
			matrix<feature_type> row = matrix<feature_type>(1, feature_matrix.col_size() + 1);
			/*��ʱ�������������һά�볣����ϵ����ˣ�����Ϊ1*/
			row.col(feature_matrix.col_size()).fill(1);
			/*��ʱ����������ֵ*/
			row.cols(0, feature_matrix.col_size() - 1) = feature_matrix.row(row_i);
			/*ת����ʱ����*/
			row.transpose();

			/*
			����������Ԥ����predict_result�����������������ͬ
			��i�м�����������Ϊ��i��ĸ���
			*/
			/*ϵ����������е����Խ��*/
			matrix<feature_type> predict_result = (_theta * row);
			for (auto &i : predict_result)
			{
				if (i > 709.783)
				{
					i = 709;
				}
			}
			/*softmax��������*/
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
			/*׼ȷ���Ϊ����������������������һ��Ӧ��Ϊ1��������Ӧ��Ϊ0
			ʹ��׼ȷ�����ȥ�������
			*/
			for (size_t theta_i = 0; theta_i < predict_result.row_size(); ++theta_i)
			{
				//׼ȷ�����ȥԤ����Ϊ���
				feature_type(predict_result.row(theta_i)) = (theta_i == label_matrix.row(row_i) ? 1 - predict_result.row(theta_i) : 0 - predict_result.row(theta_i));
			}
			/*Ԥ������ÿһ�������Ե����е�����������*/
			sum_error += predict_result * row.t();
		}
		sum_error /= -param_type(feature_matrix.row_size());
		return sum_error;
	}

}