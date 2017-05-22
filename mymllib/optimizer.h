#ifndef OPTIMIZER_H
#define OPTIMIZER_H
#include"classifier.h"
namespace myml
{
	template<class feature_type, class label_type, class calc_param_type ,class class_param_type>
	class optimizer
	{
	public:


	private:

	};
	/*计算过程中使用的参数类型，传递的参数类型*/
	template<class feature_type, class label_type, class calc_param_type, class class_param_type>
	class grad_desc_optimizer :optimizer<feature_type, label_type, calc_param_type, class_param_type>
	{
	public:
		void sgd(class_param_type & cparam, const classifier<feature_type, label_type, calc_param_type> &cf, const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix);
		calc_param_type learning_rate = 1E-5;
		//void adadelta(class_param_type& c, const class_param_type &grad, const calc_param_type learning_rate);
	private:

	};




	template<class feature_type, class label_type, class calc_param_type, class class_param_type>
	inline void grad_desc_optimizer<feature_type, label_type, calc_param_type, class_param_type>::sgd(class_param_type & cparam, const classifier<feature_type, label_type, calc_param_type>& cf, const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix)
	{
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			matrix<calc_param_type> grad = cf.gradient(feature_matrix.row(row_i), label_matrix.row(row_i));
			cparam -= grad * learning_rate;
		}
	}

}
#endif // !OPTIMIZER_H

