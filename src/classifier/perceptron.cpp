#include "perceptron.h"
namespace myml
{
	using namespace matrix_operate;

	perceptron::perceptron(size_t feature_size) :classifier(feature_size, 2), _theta(1, feature_size + 1)
	{
	}

	matrix<perceptron::feature_t> perceptron::gradient(const matrix<feature_t>& feature_matrix, const matrix<label_t>& label_matrix) const
	{
		auto partial_theta = _theta.cols(0, feature_size);
		matrix<feature_t> grad(1, feature_size + 1);
		for (auto row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			auto pre = dot_product(partial_theta, feature_matrix.row(row_i)) + _theta(feature_size);
			if (pre < 0 && label_matrix(row_i) == 1)
			{
				grad.cols(0, feature_size) -= feature_matrix.row(row_i);
				grad(feature_size) -= 1;
			}
			else if (pre >= 0 && label_matrix(row_i) == 0)
			{
				grad.cols(0, feature_size) += feature_matrix.row(row_i);
				grad(feature_size) += 1;
			}
		}
		return grad;
	}


	const matrix<perceptron::feature_t> perceptron::probabilities(const matrix<feature_t>& feature_matrix) const
	{
		matrix<feature_t> prob(feature_matrix.row_size(), label_size);
		auto partial_theta = _theta.cols(0, feature_size);
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			if (dot_product(partial_theta, feature_matrix.row(row_i)) + _theta(feature_size) > 0)
			{
				prob(row_i, 0) = 0;
				prob(row_i, 1) = 1;
			}
			else
			{
				prob(row_i, 0) = 1;
				prob(row_i, 1) = 0;
			}
		}
		return prob;
	}

	const matrix<perceptron::label_t> perceptron::predict(const matrix<feature_t>& feature_matrix) const
	{
		auto partial_theta = _theta.cols(0, feature_size);
		matrix<label_t> pre(feature_matrix.row_size(), 1);
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			pre(row_i) = dot_product(partial_theta, feature_matrix.row(row_i)) + _theta(feature_size) > 0 ? 1 : 0;
		}
		return pre;
	}

	bool perceptron::load(istream & in)
	{
		return import_matrix_data<feature_t>(_theta, in);
	}

	bool perceptron::save(ostream & out)
	{
		_theta.print(out);
		return true;
	}
	//感知机目标函数，是误分类点到分类平面的距离最大？
	perceptron::feature_t perceptron::objective_function(const matrix<feature_t>& feature_matrix, const matrix<label_t>& label_matrix) const
	{
		feature_t of = 0;
		auto partial_theta = _theta.cols(0, feature_size);
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			auto pre = dot_product(partial_theta, feature_matrix.row(row_i)) + _theta(feature_size);
			if (pre < 0 && label_matrix(row_i) == 1)
			{
				of += std::abs(dot_product(partial_theta, feature_matrix.row(row_i)) + _theta(feature_size));
			}
			else if (pre >= 0 && label_matrix(row_i) == 0)
			{
				of -= std::abs(dot_product(partial_theta, feature_matrix.row(row_i)) + _theta(feature_size));
			}
				
		}
		return of;
	}


	void perceptron::print(ostream & out) const
	{
		_theta.print();
	}

}