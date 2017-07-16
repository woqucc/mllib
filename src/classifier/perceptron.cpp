#include "perceptron.h"
namespace myml
{
	using namespace matrix_operate;

	perceptron::perceptron(size_t feature_size):classifier(feature_size, 2),_theta(feature_size + 1,1)
	{
	}


	const matrix<perceptron::feature_type> perceptron::probabilities(const matrix<feature_type>& feature_matrix) const
	{
		matrix<feature_type> prob(feature_matrix.row_size(),label_size);
		return prob;
	}

	const matrix<perceptron::label_type> perceptron::predict(const matrix<feature_type>& feature_matrix) const
	{
		auto theta_temp = _theta.cols(0, feature_size - 1);
		matrix<label_type> pre(feature_matrix.row_size(), 1);
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			pre(row_i) = dot_product(theta_temp, feature_matrix.row(row_i)) + _theta(feature_size) > 0 ? 1 : 0;
		}
		return pre;
	}

	bool perceptron::load(istream & in)
	{
		return false;
	}

	bool perceptron::save(ostream & out)
	{
		return false;
	}

	perceptron::feature_type perceptron::objective_function(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix) const
	{
		return feature_type();
	}

	perceptron::feature_type perceptron::accuracy(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix) const
	{
		return feature_type();
	}

	void perceptron::print(ostream & out) const
	{
	}

}