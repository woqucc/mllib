#ifndef SVM_H
#define SVM_H
#include"perceptron.h"
namespace myml
{
	using std::size_t;
	namespace kernel {
		template<class feature_t,int param_d = 3>
		static feature_t polynomial(const matrix<feature_t>& op1, const matrix<feature_t>& op2)
		{
			feature_t sum = 0;
			for (size_t i = 0; i < op1.size(); ++i)
			{
				sum += op1(i) * op2(i);
			}
			sum *= 0.5;
			return std::pow(sum + static_cast<feature_t>(0), param_d);
		}; 
		template<class feature_t>
		static feature_t gauss(const matrix<feature_t>& op1, const matrix<feature_t>& op2)
		{
			feature_t sum = 0;
			for (size_t i = 0; i < op1.size(); ++i)
			{
				sum += (op1(i) - op2(i)) * (op1(i) - op2(i));
			}
			std::sqrt(sum);
			return std::exp(sum * -0.5);
		};
		template<class feature_t>
		static feature_t linear(const matrix<feature_t>& op1, const matrix<feature_t>& op2)
		{
			feature_t sum = 0;
			for (size_t i = 0; i < op1.size(); ++i)
			{
				sum += op1(i) * op2(i);
			}
			return sum;
		};
		//static feature_t gauss(const matrix<feature_t>&, const matrix<feature_t>&);

	};


	class svm : public classifier
	{
	protected:
		matrix<feature_t> _support_vectors_feature;
		matrix<feature_t> _lagrange_multiplier;
		function<feature_t(const matrix<feature_t>&, const matrix<feature_t>&)> _kernel;
		feature_t b = 0;
		feature_t C = 10;
	public:
		virtual const matrix<feature_t> probabilities(const matrix<feature_t> & feature_matrix) const override;
		virtual const matrix<label_t> predict(const matrix<feature_t> & feature_matrix) const  override;
		virtual bool load(istream &in)  override;
		virtual bool save(ostream &out)  override;
		virtual feature_t objective_function(const matrix<feature_t> &feature_matrix, const matrix<label_t> &label_matrix) const  override;
		virtual void print(ostream & out) const  override;
		svm(size_t feature_size, function<feature_t(const matrix<feature_t>&, const matrix<feature_t>&)> kernel = kernel::linear<feature_t>);
		void train(const matrix<feature_t>& feature_matrix, const matrix<label_t>& label_matrix);



	};
	//template<class feature_t>

	//template<class feature_t, class d>
	//inline feature_t feature_t::polynomial(const matrix<feature_t>&, const matrix<feature_t>&)
	//{

	//}
}
#endif // !SVM