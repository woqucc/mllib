#ifndef SVM_H
#define SVM_H
#include"perceptron.h"
namespace myml
{
	class svm : public classifier<long double, size_t>
	{
	protected:
		matrix<feature_type> _support_vectors_feature;
		matrix<feature_type> _support_vectors_label;
		matrix<feature_type> _lagrange_multiplier;
		feature_type b = 0;
		feature_type C = 10;
	public:
		virtual const matrix<feature_type> probabilities(const matrix<feature_type> & feature_matrix) const override;
		virtual const matrix<label_type> predict(const matrix<feature_type> & feature_matrix) const  override;
		virtual bool load(istream &in)  override;
		virtual bool save(ostream &out)  override;
		virtual feature_type objective_function(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const  override;
		virtual void print(ostream & out) const  override;
		svm(size_t feature_size);
		void train(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix);
	};
}
#endif // !SVM

