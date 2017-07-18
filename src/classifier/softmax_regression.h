#ifndef SOFTMAX_REGRESSION
#define SOFTMAX_REGRESSION
#include"../data/matrix.h"
#include"classifier.h"
#include"../optimizer/optimizer.h"
#include<map>
#include<iostream>
namespace myml
{
	/*设置数据类型，不想用template*/

	class softmax_regression : public classifier<long double, size_t>
	{
	public:

		using label_class_map = map<label_type, long double>;

		friend class grad_desc_optimizer<softmax_regression, feature_type,label_type>;
		friend class newton_raphson_optimizer<softmax_regression, feature_type, label_type>;
		softmax_regression(size_t feature_count, size_t label_count);

		/*实现分类器标准接口*/
		const matrix<feature_type> probabilities(const matrix<feature_type> & feature_matrix) const override;
		bool load(istream &in) override;
		bool save(ostream &out) override;
		feature_type objective_function(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const override;
		const matrix<label_type> predict(const matrix<feature_type> & feature_matrix) const override;
		void print(ostream & out = cout) const override;
		
		
		/*实现特有方法*/
		void load(const matrix<feature_type>& theta);



		/*
			计算误差矩阵（正确结果-预测结果）* 对应的特征向量
			@param in feature_matrix 输入特征矩阵，矩阵的每一行为一个特征向量
			@param in label_matrix 与特征矩阵每一行相对应的具体类标，用来计算误差
			@param out 输出误差矩阵，矩阵大小与_theta大小相同
		*/
		virtual matrix<feature_type> gradient(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const;

		virtual matrix<feature_type> hessian(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const override;
	protected:
		matrix<feature_type> _theta;
		//newton_raphson_optimizer<feature_type, label_type, feature_type, matrix<feature_type>> _nopt;
		//grad_desc_optimizer<softmax_regression,feature_type,label_type> _opt;
	};

	class softmax_regression_ridge : public softmax_regression
	{
	public:
		feature_type _lambda = static_cast<feature_type>(1E-8L);
		softmax_regression_ridge(size_t feature_count, size_t label_count);
		virtual matrix<feature_type> gradient(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const override;
		feature_type objective_function(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const override;
		virtual matrix<feature_type> hessian(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const override;
	};

}
#endif // !SOFTMAX_REGRESSION
