#include "softmax_regression.h"
#include<cmath>
namespace myml
{
	using namespace matrix_operate;
	softmax_regression::softmax_regression(size_t feature_size, size_t label_size) :classifier(feature_size, label_size)
	{
		_theta.resize(label_size, feature_size + 1);
		_theta.fill(0);
	}

	void softmax_regression::load(const matrix<feature_type>& theta)
	{
		_theta = theta;
	}

	const matrix<softmax_regression::feature_type> softmax_regression::probabilities(const matrix<feature_type>& feature_matrix) const
	{
		matrix<feature_type> feature(feature_matrix.row_size(), feature_size + 1);
		/*最后一列填1*/
		feature.cols(0, feature_size - 1) = feature_matrix;
		feature.col(feature_size).fill(1);
		matrix<feature_type> predict_result = feature* transpose(_theta);
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			/*
			* trick: 在线性相乘得到的结果predict_result中，首先获取其中最大的值，随后将每个值都减去该最大值，这样不会造成overflow
			*/
			predict_result.row(row_i) -= predict_result.row(row_i).max();
			predict_result.row(row_i) = exp(predict_result.row(row_i));
			/*正则化，使概率和在0-1之间*/
			predict_result.row(row_i) /= sum(predict_result.row(row_i));
		}

		//label_type(result.row(row_i)) = predict_result.max_position().first;
		return predict_result;
	}


	bool softmax_regression::load(istream & in)
	{
		return import_matrix_data<feature_type>(_theta, in);
	}

	bool softmax_regression::save(ostream & out)
	{
		_theta.print(out);
		return true;
	}

	softmax_regression::feature_type softmax_regression::accuracy(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix) const
	{
		matrix<feature_type> pr = probabilities(feature_matrix);
		size_t total = pr.row_size();
		size_t correct = 0;
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			if (pr.row(row_i).max_position().second == label_matrix.row(row_i))
				correct++;
		}
		return (correct + .0) / total;
	}

	const matrix<softmax_regression::label_type> softmax_regression::predict(const matrix<feature_type>& feature_matrix) const
	{
		matrix<feature_type> feature(feature_matrix.row_size(), feature_size + 1);
		/*最后一列填1*/
		feature.cols(0, feature_size - 1) = feature_matrix;
		feature.col(feature_size).fill(1);
		matrix<feature_type> prob_matrix = feature*transpose(_theta);

		matrix<label_type> predict_result(feature_matrix.row_size(), 1);
		for (size_t i = 0; i < feature_matrix.row_size(); ++i)
		{
			predict_result.at(i, 0) = prob_matrix.row(i).max_position().second;
		}
		return predict_result;
	}

	void softmax_regression::print(ostream & out) const
	{
		_theta.print(out);
	}

	matrix<softmax_regression::feature_type> softmax_regression::gradient(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix) const
	{
		/*误差矩阵大小与_theta大小相同*/
		matrix<feature_type> sum_error(_theta.row_size(), _theta.col_size());
		matrix<feature_type> predict_matrix = probabilities(feature_matrix);
		/*累加每个特征向量的误差，预测减去准确，梯度下降算法
		正常是准确-预测，然后乘以负的系数，这里直接将负号带入
		*/
		for (size_t row_i = 0; row_i < predict_matrix.row_size(); ++row_i)
		{
			for (size_t theta_i = 0; theta_i < predict_matrix.col_size(); ++theta_i)
			{
				predict_matrix.at(row_i, theta_i) = predict_matrix.at(row_i, theta_i) - (theta_i == label_matrix.row(row_i) ? 1 : 0);
			}
		}
		predict_matrix.transpose();
		/*预测结果的每一列误差，乘以对应的特征向量项，*/
		for (size_t col_i = 0; col_i < predict_matrix.col_size(); ++col_i)
		{
			sum_error.cols(0, _theta.col_size() - 2) += predict_matrix.col(col_i) * feature_matrix.row(col_i);
			/*计算常数项误差*/
			sum_error.col(_theta.col_size() - 1) += predict_matrix.col(col_i);
		}
		/*正常为 乘以 -1/m 因为上面将负号带入了，这里不用再加负号*/
		sum_error /= feature_type(feature_matrix.row_size());		
		return sum_error;
	}
	matrix<softmax_regression::feature_type> softmax_regression::hessian(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix) const
	{
		matrix<feature_type> feature(feature_matrix.row_size(), feature_size + 1);
		/*最后一列填1*/
		feature.cols(0, feature_size - 1) = feature_matrix;
		feature.col(feature_size).fill(1);
		size_t theta_size = feature_size + 1;
		//海森矩阵大小 (特征数+1)*类别个数x(特征数+1)*类别个数
		matrix<feature_type> hessian_matrix(theta_size * label_size, theta_size * label_size);
		matrix<feature_type> predict_matrix = probabilities(feature_matrix);
		for (size_t label_i = 0; label_i < label_size; ++label_i)
		{		
			matrix<feature_type> w_diag = dot(predict_matrix.col(label_i),1.0L - predict_matrix.col(label_i));
			hessian_matrix.sub_matrix(label_i * theta_size, label_i * theta_size, label_i * theta_size + theta_size - 1, label_i * theta_size + theta_size - 1) = transpose(feature) * diag(w_diag) * feature;
			for (size_t other_label = label_i + 1; other_label < label_size; ++other_label)
			{
				matrix<feature_type> w_off_diag = -dot(predict_matrix.col(label_i), predict_matrix.col(other_label));
				hessian_matrix.sub_matrix(label_i * theta_size, other_label * theta_size, label_i * theta_size + theta_size - 1, other_label * theta_size + theta_size - 1) = transpose(feature) * diag(w_off_diag) * feature;
				hessian_matrix.sub_matrix(other_label * theta_size, label_i * theta_size, other_label * theta_size + theta_size - 1, label_i * theta_size + theta_size - 1) = transpose(feature) * diag(w_off_diag) * feature;
			}
		}
		return hessian_matrix;
	}
	softmax_regression::feature_type softmax_regression::objective_function(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const
	{
		feature_type of = 0;
		matrix<feature_type> predict_matrix = probabilities(feature_matrix);
		for (size_t row_i = 0; row_i < predict_matrix.row_size(); ++row_i)
		{
			size_t label = label_matrix.at(row_i, 0);
			of += predict_matrix.at(row_i, label);
		}
		return of;
	}


	softmax_regression_ridge::softmax_regression_ridge(size_t feature_count, size_t label_count) :softmax_regression(feature_count, label_count)
	{

	}
	matrix<softmax_regression::feature_type> softmax_regression_ridge::gradient(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix) const
	{
		/*误差矩阵大小与_theta大小相同*/
		matrix<feature_type> sum_error = softmax_regression::gradient(feature_matrix, label_matrix);
		sum_error += _theta * _lambda;
		return sum_error;
	}
	softmax_regression::feature_type softmax_regression_ridge::objective_function(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix) const
	{
		feature_type of = softmax_regression::objective_function(feature_matrix, label_matrix);
		of -= norm_f(_theta)* _lambda;
		return of;
	}
	matrix<softmax_regression::feature_type> softmax_regression_ridge::hessian(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix) const
	{
		matrix<feature_type> hessian_matrix = softmax_regression::hessian(feature_matrix, label_matrix);
		hessian_matrix += identity_matrix<feature_type>(hessian_matrix.row_size()) * _lambda;
		return hessian_matrix;
	}
}