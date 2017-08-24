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

	template<class feature_type_t, class label_type_t>
	class classifier
	{
	public:
		using feature_type = feature_type_t;
		using label_type = label_type_t;
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

		virtual const matrix<feature_type_t> probabilities(const matrix<feature_type_t> & feature_matrix) const = 0;

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

		virtual const matrix<label_type_t> predict(const matrix<feature_type_t> & feature_matrix) const = 0;

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

		virtual feature_type_t objective_function(const matrix<feature_type_t> &feature_matrix, const matrix<label_type_t> &label_matrix) const  = 0;

		/**
		 * @fn	virtual feature_type_t classifier::accuracy(const matrix<feature_type_t> &feature_matrix, const matrix<label_type_t> &label_matrix) const;
		 *
		 * @brief	获取模型在预测样本上的准确率
		 *
		 * @author	woqucc
		 * @date	2017/7/24
		 *
		 * @param	feature_matrix	The feature matrix.
		 * @param	label_matrix  	The label matrix.
		 *
		 * @return	预测准确率
		 */

		virtual feature_type_t accuracy(const matrix<feature_type_t> &feature_matrix, const matrix<label_type_t> &label_matrix) const;

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

		virtual void print(ostream & out) const = 0 ;

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

		virtual matrix<feature_type_t> gradient(const matrix<feature_type_t> &feature_matrix, const matrix<label_type_t> &label_matrix) const { assert(false); return matrix<feature_type_t>(); }

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

		virtual matrix<feature_type_t> hessian(const matrix<feature_type_t> &feature_matrix, const matrix<label_type_t> &label_matrix) const { assert(false); return matrix<feature_type_t>(); }
		/*获取分类错误的样本*/
		const pseudo_matrix<feature_type_t> error_sample(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix);
	};

	template<class feature_type_t, class label_type_t>
	inline feature_type_t classifier<feature_type_t, label_type_t>::accuracy(const matrix<feature_type_t>& feature_matrix, const matrix<label_type_t>& label_matrix) const
	{
		matrix<feature_type_t> pr = probabilities(feature_matrix);
		size_t total = pr.row_size();
		size_t correct = 0;
		for (size_t row_i = 0; row_i < feature_matrix.row_size(); ++row_i)
		{
			if (pr.row(row_i).max_position().second == label_matrix(row_i,0))
				correct++;
		}
		return (correct + .0) / total;
	}

	template<class feature_type_t, class label_type_t>
	inline classifier<feature_type_t, label_type_t>::classifier(size_t feature_size, size_t label_size) :feature_size(feature_size), label_size(label_size) {}


	template<class feature_type_t, class label_type_t>
	inline const pseudo_matrix<feature_type_t> classifier<feature_type_t, label_type_t>::error_sample(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix)
	{
		matrix<feature_type_t> pr = probabilities(feature_matrix);
		size_t row_i = 0;
		return feature_matrix.fetch_row([&pr,&label_matrix,&row_i](feature_type_t* data,size_t col_size) {
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
	行为实际列标，列为预测出的类标
	*/
	template<class feature_type_t, class label_type_t>
	matrix<size_t> confusion_matrix(const classifier<feature_type_t, label_type_t>& cf, const matrix<feature_type_t> &feature_matrix, const matrix<label_type_t> &label_matrix)
	{
		matrix<label_type_t> p = cf.predict(feature_matrix);
		matrix<size_t> cm(cf.label_size, cf.label_size);
		for (size_t i = 0; i < p.row_size(); ++i)
		{
			cm.at(label_matrix.at(i, 0), p.at(i, 0))++;
		}
		return cm;
	}





}
#endif // !CLASSIFIER_H