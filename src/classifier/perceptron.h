#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include"classifier.h"
namespace myml
{
	class perceptron : public classifier<long double, size_t>
	{
	public:
		virtual const matrix<feature_type> probabilities(const matrix<feature_type> & feature_matrix) const;
		virtual const matrix<label_type> predict(const matrix<feature_type> & feature_matrix) const;
		virtual void train(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix);
		virtual bool load(istream &in);
		virtual bool save(ostream &out);
		virtual feature_type objective_function(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const;
		virtual feature_type accuracy(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const;
		virtual void print(ostream & out) const;
	};
}

#endif // !PERCEPTRON_H

