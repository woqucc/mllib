#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include"../data/matrix.h"
#include<iostream>
#include<cassert>
namespace myml
{
	using namespace std;

	/**
	 * @class	classifier.
	 *
	 * @brief	分类器抽象类。
	 *
	 * @author	woqucc.
	 * @date	2017/7/22.
	 *
	 * @tparam	feature_type_t	特征类型.
	 * @tparam	label_type_t  	类标类型.
	 *
	 */


	class classifier
	{
	public:
		using feature_t = double;
		using label_t = int;
		/** @brief	特征维数. */
		size_t feature_size;
		/** @brief	类标种类. */
		size_t label_size;

		/**
		 * @fn	virtual const matrix<feature_type_t> classifier::probabilities(const matrix<feature_type_t> & feature_matrix) const = 0;
		 *
		 * @brief	求出输入样本属于每种类别的概率.
		 *
		 * @author	woqucc.
		 * @date	2017/7/22.
		 *
		 * @param	feature_matrix	输入样本矩阵.
		 *
		 * @return	概率矩阵，行对应样本，列对应样本属于每一类的概率;
		 *
		 */

		virtual const matrix<feature_t> probabilities(const matrix<feature_t> & feature_matrix) const = 0;

		/**
		 * @fn	virtual const matrix<label_type_t> classifier::predict(const matrix<feature_type_t> & feature_matrix) const = 0;
		 *
		 * @brief	预测输入样本所属类别
		 *
		 * @author	Woqucc.
		 * @date	2017/7/22.
		 *
		 * @param	输入样本矩阵.
		 *
		 * @return	输出一个列向量，维数与输入样本数量相等，其中元素为输入样本对应的类标.
		 *
		 * @seealso	.
		 */

		virtual const matrix<label_t> predict(const matrix<feature_t> & feature_matrix) const = 0;

		/**
		 * @fn	virtual bool classifier::load(istream &in) = 0;
		 *
		 * @brief	从输入流中读取保存的模型.
		 *
		 * @author	Woqucc.
		 * @date	2017/7/22.
		 *
		 * @param	保存着参数的输入流
		 *
		 * @return	true if it succeeds, false if it fails.
		 */

		virtual bool load(istream &in) = 0;

		/**
		 * @fn	virtual bool classifier::save(ostream &out) = 0;
		 *
		 * @brief	将模型保存到输出流
		 *
		 * @author	woqucc.
		 * @date	2017/7/22.
		 *
		 * @param	输出流
		 *
		 * @return	true if it succeeds, false if it fails.
		 */

		virtual bool save(ostream &out) = 0;

		/**
		 * @fn	virtual feature_type_t classifier::objective_function(const matrix<feature_type_t> &feature_matrix, const matrix<label_type_t> &label_matrix) const = 0;
		 *
		 * @brief	返回该分类器目标函数值
		 * 			目标函数就是分类器的优化目标
		 *
		 * @author	woqucc
		 * @date	2017/7/24
		 *
		 * @param	feature_matrix	样本
		 * @param	label_matrix  	类别
		 *
		 * @return	目标函数的值
		 */

		virtual double objective_function(const matrix<feature_t> &feature_matrix, const matrix<label_t> &label_matrix) const = 0;


		/**
		 * @fn	virtual void classifier::print(ostream & out) const = 0;
		 *
		 * @brief	输出分类器相关信息。
		 *
		 * @author	woqucc
		 * @date	2017/7/24
		 *
		 * @param [in]	out	输出流
		 */

		virtual void print(ostream & out) const = 0;

		/**
		 * @fn	classifier::classifier(size_t feature_size, size_t label_size);
		 *
		 * @brief	构造函数，初始化特征个数和类标个数
		 *
		 * @author	Woqucc
		 * @date	2017/7/24
		 *
		 * @param	feature_size	Size of the feature.
		 * @param	label_size  	Size of the label.
		 */

		classifier(size_t feature_size, size_t label_size);

		/**
		 * @fn	virtual matrix<feature_type_t> classifier::gradient(const matrix<feature_type_t> &feature_matrix, const matrix<label_type_t> &label_matrix) const
		 *
		 * @brief			计算梯度，需要使用梯度的优化方法训练的分类器需要覆盖该函数
		 * 					否则报错
		 *
		 * @author	woqucc
		 * @date	2017/7/24
		 *
		 * @param	feature_matrix	The feature matrix.
		 * @param	label_matrix  	The label matrix.
		 *
		 * @return	A matrix&lt;feature_type_t&gt;
		 */

		virtual matrix<feature_t> gradient(const matrix<feature_t> &feature_matrix, const matrix<label_t> &label_matrix) const { assert(false); return matrix<feature_t>(); }

		/**
		 * @fn	virtual matrix<feature_type_t> classifier::hessian(const matrix<feature_type_t> &feature_matrix, const matrix<label_type_t> &label_matrix) const
		 *
		 * @brief	返回海森矩阵，需要使用牛顿法进行训练的分类器需要重写该函数。
		 * 			否则报错
		 *
		 * @author	woqucc
		 * @date	2017/7/24
		 *
		 * @param	feature_matrix	The feature matrix.
		 * @param	label_matrix  	The label matrix.
		 *
		 * @return	A matrix&lt;feature_type_t&gt;
		 */

		virtual matrix<feature_t> hessian(const matrix<feature_t> &feature_matrix, const matrix<label_t> &label_matrix) const { assert(false); return matrix<feature_t>(); }
		/*获取分类错误的样本*/
		const pseudo_matrix<feature_t> error_sample(const matrix<feature_t> &feature_matrix, const matrix<label_t> &label_matrix);
	};


	inline classifier::classifier(size_t feature_size, size_t label_size) :feature_size(feature_size), label_size(label_size) {}


	inline const pseudo_matrix<classifier::feature_t> classifier::error_sample(const matrix<feature_t>& feature_matrix, const matrix<label_t>& label_matrix)
	{
		matrix<feature_t> pr = probabilities(feature_matrix);
		size_t row_i = 0;
		return feature_matrix.fetch_row([&pr, &label_matrix, &row_i](feature_t* data, size_t col_size) {
			if (pr.row(row_i).max_position().second != label_matrix(row_i))
			{
				row_i++;
				return true;
			}
			else
			{
				row_i++;
				return false;
			}
		});
	}


	/*
	@brief 计算混淆矩阵
	行为实际类标，列为预测出的类标
	*/
	template<class feature_t, class label_t>
	matrix<size_t> confusion_matrix(const classifier& cf, const matrix<feature_t> &feature_matrix, const matrix<label_t> &label_matrix)
	{
		matrix<label_t> p = cf.predict(feature_matrix);
		matrix<size_t> cm(cf.label_size, cf.label_size);
		for (size_t i = 0; i < p.row_size(); ++i)
		{
			cm.at(label_matrix.at(i, 0), p.at(i, 0))++;
		}
		return cm;
	}

	/**
	 * @fn	template<class feature_t, class label_t> double accuracy(const classifier& cf, const matrix<feature_t> &feature_matrix, const matrix<label_t> &label_matrix)
	 *
	 * @brief	计算分类器模型在测试数据上的准确率
	 *
	 * @author	Woqucc
	 * @date	2018/6/22
	 *
	 * @tparam	feature_t	Type of the feature t.
	 * @tparam	label_t  	Type of the label t.
	 * @param	cf				分类器模型
	 * @param	feature_matrix	样本.
	 * @param	label_matrix  	类标.
	 *
	 * @return	准确率.
	 */

	template<class feature_t, class label_t>
	double accuracy(const classifier& cf, const matrix<feature_t> &feature_matrix, const matrix<label_t> &label_matrix)
	{
		auto p = cf.predict(feature_matrix);
		matrix<size_t> cm(cf.label_size, cf.label_size);
		size_t correct = 0;
		for (size_t i = 0; i < p.size(); ++i)
		{
			correct += p(i) == label_matrix(i) ? 1 : 0;
		}
		return (correct + .0) / label_matrix.size();
	}

	/**
	 * @fn	inline double accuracy(const matrix<size_t>& confusion_matrix)
	 *
	 * @brief	根据混淆矩阵计算准确率
	 *
	 * @author	Woqucc
	 * @date	2018/6/22
	 *
	 * @param	confusion_matrix	The confusion matrix.
	 *
	 * @return	A double.
	 */
	 //TODO: inline问题，是否建立一个新的源文件？
	inline double accuracy(const matrix<size_t>& confusion_matrix)
	{
		assert(confusion_matrix.row_size() == confusion_matrix.col_size());
		size_t total = matrix_operate::sum(confusion_matrix);
		size_t correct = 0;
		for (size_t diag_i = 0; diag_i < confusion_matrix.row_size(); ++diag_i)
		{
			correct += confusion_matrix(diag_i, diag_i);
		}
		return (correct + .0) / total;
	}
	//被预测为某一类中正确的比例
	inline matrix<double> precision(const matrix<size_t>& confusion_matrix)
	{
		matrix<double> result(confusion_matrix.row_size(), 1);
		double col_sum = 0;
		for (size_t col_i = 0; col_i < confusion_matrix.row_size(); ++col_i)
		{
			col_sum = matrix_operate::sum(confusion_matrix.col(col_i));
			if (col_sum == 0)
				result(col_i) = 0;
			else
				result(col_i) = (confusion_matrix(col_i, col_i) + .0) / col_sum;
		}
		return result;
	};
	//某一类中被预测出的比例
	inline matrix<double> recall(const matrix<size_t>& confusion_matrix)
	{
		matrix<double> result(confusion_matrix.row_size(), 1);
		double row_sum = 0;
		for (size_t row_i = 0; row_i < confusion_matrix.row_size(); ++row_i)
		{
			row_sum = matrix_operate::sum(confusion_matrix.col(row_i));
			if (row_sum == 0)
				result(row_i) = 0;
			else
				result(row_i) = (confusion_matrix(row_i, row_i) + .0) / row_sum;
		}
		return result;
	};
}
#endif // !CLASSIFIER_H