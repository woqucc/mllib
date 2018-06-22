#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include"classifier.h"
#include"../data/matrix.h"
#include"../optimizer/optimizer.h"
namespace myml
{
	using std::size_t;
	class perceptron : public classifier
	{
	protected:
		matrix<feature_t> _theta;
	public:
		friend class grad_desc_optimizer<perceptron>;
		virtual const matrix<feature_t> probabilities(const matrix<feature_t> & feature_matrix) const override;
		virtual const matrix<label_t> predict(const matrix<feature_t> & feature_matrix) const  override;
		virtual bool load(istream &in)  override;
		virtual bool save(ostream &out)  override;
		virtual feature_t objective_function(const matrix<feature_t> &feature_matrix, const matrix<label_t> &label_matrix) const  override;
		virtual void print(ostream & out) const  override;
		perceptron(size_t feature_size);
		virtual matrix<feature_t> gradient(const matrix<feature_t> &feature_matrix, const matrix<label_t> &label_matrix) const override;
	};
}

#endif // !PERCEPTRON_H

