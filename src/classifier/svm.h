#ifndef SVM_H
#define SVM_H
#include"perceptron.h"
namespace myml
{
	using std::size_t;
	namespace kernel {
		template<class feature_type,int param_d = 3>
		static feature_type polynomial(const matrix<feature_type>& op1, const matrix<feature_type>& op2)
		{
			feature_type sum = 0;
			for (size_t i = 0; i < op1.size(); ++i)
			{
				sum += op1(i) * op2(i);
			}
			sum *= 0.5;
			return std::pow(sum + static_cast<feature_type>(0), param_d);
		}; 
		template<class feature_type>
		static feature_type gauss(const matrix<feature_type>& op1, const matrix<feature_type>& op2)
		{
			feature_type sum = 0;
			for (size_t i = 0; i < op1.size(); ++i)
			{
				sum += (op1(i) - op2(i)) * (op1(i) - op2(i));
			}
			std::sqrt(sum);
			return std::exp(sum * -0.5);
		};
		template<class feature_type>
		static feature_type linear(const matrix<feature_type>& op1, const matrix<feature_type>& op2)
		{
			feature_type sum = 0;
			for (size_t i = 0; i < op1.size(); ++i)
			{
				sum += op1(i) * op2(i);
			}
			return sum;
		};
		//static feature_type gauss(const matrix<feature_type>&, const matrix<feature_type>&);

	};


	class svm : public classifier<long double, size_t>
	{
	protected:
		matrix<feature_type> _support_vectors_feature;
		matrix<feature_type> _lagrange_multiplier;
		function<feature_type(const matrix<feature_type>&, const matrix<feature_type>&)> _kernel;
		feature_type b = 0;
		feature_type C = 10;
	public:
		virtual const matrix<feature_type> probabilities(const matrix<feature_type> & feature_matrix) const override;
		virtual const matrix<label_type> predict(const matrix<feature_type> & feature_matrix) const  override;
		virtual bool load(istream &in)  override;
		virtual bool save(ostream &out)  override;
		virtual feature_type objective_function(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const  override;
		virtual void print(ostream & out) const  override;
		svm(size_t feature_size, function<feature_type(const matrix<feature_type>&, const matrix<feature_type>&)> kernel = kernel::linear<feature_type>);
		void train(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix);



	};
	//template<class feature_type>

	//template<class feature_type, class d>
	//inline feature_type feature_type::polynomial(const matrix<feature_type>&, const matrix<feature_type>&)
	//{

	//}
}
#endif // !SVM