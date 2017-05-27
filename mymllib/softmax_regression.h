#ifndef SOFTMAX_REGRESSION
#define SOFTMAX_REGRESSION
#include"data.h"
#include"classifier.h"
#include"optimizer.h"
#include<map>
#include<iostream>
namespace myml
{
	/*设置数据类型，不想用template*/
	using feature_type = long double;
	using label_type = size_t;
	using calc_param_type = long double;
	using label_class_map = map<label_type, long double>;
	class softmax_regression : public classifier<feature_type, label_type, calc_param_type>
	{
	public:
		softmax_regression(size_t feature_count, size_t label_count);

		/*实现分类器标准接口*/
		const matrix<calc_param_type> probabilities(const matrix<feature_type> & feature_matrix) const override;
		void train(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) override;
		bool load(istream &in) override;
		bool save(ostream &out) override;
		calc_param_type objective_function(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const override;
		calc_param_type accuracy(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const override;
		const matrix<label_type> predict(const matrix<feature_type> & feature_matrix) const override;
		void print(ostream & out = cout) const override;
		
		
		/*实现特有方法*/
		void load(const matrix<calc_param_type>& theta);


		/*随机梯度下降，可以一次传入多个样本*/
		void sgd(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix,const calc_param_type & learning_rate = 1E-5);
		/*随机梯度下降，动量法调节学习速率，可以一次传入多个样本*/
		void sgd_momentum(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix,calc_param_type rho = 0.9 ,calc_param_type eit = 0.3);
		/*随机梯度下降，adadelta方法调节学习速率*/
		void adadelta(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix, calc_param_type epsilon = 1E-6, calc_param_type rho = 0.95);

		/*批量梯度下降，如果传入的样本的batch为全部样本，则为正常的梯度下降*/
		void batch_gd(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix);


		/*
			计算误差矩阵（正确结果-预测结果）* 对应的特征向量
			@param in feature_matrix 输入特征矩阵，矩阵的每一行为一个特征向量
			@param in label_matrix 与特征矩阵每一行相对应的具体类标，用来计算误差
			@param out 输出误差矩阵，矩阵大小与_theta大小相同
		*/
		virtual matrix<calc_param_type> gradient(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const;

	protected:
		matrix<calc_param_type> _theta;

		grad_desc_optimizer<feature_type, label_type, calc_param_type,matrix<calc_param_type>> _opt;
	};

	class softmax_regression_ridge : public softmax_regression
	{
	public:
		calc_param_type _lambda = 1E-8L;
		softmax_regression_ridge(size_t feature_count, size_t label_count);
		virtual matrix<calc_param_type> gradient(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const override;
		calc_param_type objective_function(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const override;
	};

}
#endif // !SOFTMAX_REGRESSION
