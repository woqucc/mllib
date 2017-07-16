#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include"classifier.h"
#include"matrix.h"
namespace myml
{
	class perceptron : public classifier<long double, size_t>
	{
	protected:
		matrix<feature_type> _theta;
	public:
		virtual const matrix<feature_type> probabilities(const matrix<feature_type> & feature_matrix) const override;
		virtual const matrix<label_type> predict(const matrix<feature_type> & feature_matrix) const  override;
		virtual bool load(istream &in)  override;
		virtual bool save(ostream &out)  override;
		virtual feature_type objective_function(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const  override;
		virtual feature_type accuracy(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const  override;
		virtual void print(ostream & out) const  override;
		perceptron(size_t feature_size);
	};
}

#endif // !PERCEPTRON_H

