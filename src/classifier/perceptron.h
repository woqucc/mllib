#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include"classifier.h"
#include"../data/matrix.h"
#include"../optimizer/optimizer.h"
namespace myml
{
	using std::size_t;
	class perceptron : public classifier<long double, size_t>
	{
	protected:
		matrix<feature_type> _theta;
	public:
		friend class grad_desc_optimizer<perceptron, feature_type, label_type>;
		virtual const matrix<feature_type> probabilities(const matrix<feature_type> & feature_matrix) const override;
		virtual const matrix<label_type> predict(const matrix<feature_type> & feature_matrix) const  override;
		virtual bool load(istream &in)  override;
		virtual bool save(ostream &out)  override;
		virtual feature_type objective_function(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const  override;
		virtual void print(ostream & out) const  override;
		perceptron(size_t feature_size);
		virtual matrix<feature_type> gradient(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const override;
	};
}

#endif // !PERCEPTRON_H

