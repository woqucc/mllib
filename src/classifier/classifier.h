#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include"../data/matrix.h"
#include<iostream>
#include<cassert>
namespace myml
{
	using namespace std;
	/*特征类型,标签类型,分类器使用的参数类型*/
	template<class feature_type_t, class label_type_t>
	class classifier
	{
	public:
		using feature_type = feature_type_t;
		using label_type = label_type_t;
		size_t feature_size;/*特征个数*/
		size_t label_size;/*类别个数*/
		/*
		@brief 预测
		@param in feature_matrix特征矩阵，其中每一行为一个样本
		@param out 输出每个样本对应类别的概率
		*/
		virtual const matrix<feature_type_t> probabilities(const matrix<feature_type_t> & feature_matrix) const = 0;
		/*
		@brief 预测
		@param in feature_matrix特征矩阵，其中每一行为一个样本
		@param out 每个样本对应类别，输出一个仅有类别组成的、行数与输入样本数量相同、列数为1的矩阵
		*/
		virtual const matrix<label_type_t> predict(const matrix<feature_type_t> & feature_matrix) const = 0;
		/*
		@brief 保存模型
		@param in 文件
		*/
		virtual bool load(istream &in) = 0;
		/*
		@brief 读取模型
		@param in 文件
		*/
		virtual bool save(ostream &out) = 0;
		/*
		@brief 模型的目标函数
		@param in feature_matrix 特征矩阵
		@param in label_matrix 类别矩阵
		@param out 返回目标函数值
		*/
		virtual feature_type_t objective_function(const matrix<feature_type_t> &feature_matrix, const matrix<label_type_t> &label_matrix) const  = 0;

		/*
		@brief 获取输入样本的准确率
		*/
		virtual feature_type_t accuracy(const matrix<feature_type_t> &feature_matrix, const matrix<label_type_t> &label_matrix) const = 0;

		/*
		@brief 输出分类器信息
		*/
		virtual void print(ostream & out) const = 0 ;
		/*
		@brief 构造函数，初始化特征个数和类标个数
		*/
		classifier(size_t feature_size, size_t label_size);

		/*
		计算梯度，需要使用梯度的优化方法的分类器需要覆盖该函数
		否则直接报错
		*/
		virtual matrix<feature_type_t> gradient(const matrix<feature_type_t> &feature_matrix, const matrix<label_type_t> &label_matrix) const { assert(false); return matrix<feature_type_t>(); }
		/*
		返回海森矩阵，需要使用海森矩阵的优化方法的分类器需要覆盖该函数
		否则直接报错
		*/
		virtual matrix<feature_type_t> hessian(const matrix<feature_type_t> &feature_matrix, const matrix<label_type_t> &label_matrix) const { assert(false); return matrix<feature_type_t>(); }
	};

	template<class feature_type_t, class label_type_t>
	inline classifier<feature_type_t, label_type_t>::classifier(size_t feature_size, size_t label_size) :feature_size(feature_size), label_size(label_size) {}



	/*
	@brief 计算混淆矩阵
	行为实际列标，列为预测出的类标
	*/
	template<class feature_type_t, class label_type_t>
	matrix<size_t> confusion_matrix(const classifier<feature_type_t, label_type_t>& sr, const matrix<feature_type_t> &feature_matrix, const matrix<label_type_t> &label_matrix)
	{
		matrix<label_type_t> p = sr.predict(feature_matrix);
		matrix<size_t> cm(sr.label_size, sr.label_size);
		for (size_t i = 0; i < p.row_size(); ++i)
		{
			cm.at(label_matrix.at(i, 0), p.at(i, 0))++;
		}
		return cm;
	}





}
#endif // !CLASSIFIER_H