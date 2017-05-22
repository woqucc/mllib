#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include"data.h"
#include<iostream>
#include<cassert>
namespace myml
{
	using namespace std;
	/*特征类型,标签类型,计算过程中用到的参数的类型,分类器使用的参数类型*/
	template<class feature_type, class label_type, class calc_param_type>
	class classifier
	{
	public:
		/*
		@brief 预测
		@param in feature_matrix特征矩阵，其中每一行为一个样本
		@param out 输出每个样本对应类别的概率
		*/
		virtual const matrix<calc_param_type> probabilities(const matrix<feature_type> & feature_matrix) const = 0;
		/*
		@brief 预测
		@param in feature_matrix特征矩阵，其中每一行为一个样本
		@param out 每个样本对应类别，输出一个仅有类别组成的、行数与输入样本数量相同、列数为1的矩阵
		*/
		virtual const matrix<label_type> predict(const matrix<feature_type> & feature_matrix) const = 0;
		/*
		@brief 训练
		@param in feature_matrix 特征矩阵，其中每一行为一个样本
		@param in label_matrix 每个样本对应的类别
		*/
		virtual void train(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) = 0;
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
		virtual calc_param_type objective_function(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const  = 0;

		/*
		@brief 获取输入样本的准确率
		*/
		virtual calc_param_type accuracy(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const = 0;

		/*
		@brief 输出分类器信息
		*/
		virtual void print(ostream & out) const = 0 ;
		/*
		@brief 构造函数，初始化特征个数和类标个数
		*/
		classifier(size_t feature_size, size_t label_size);

		/*计算梯度，需要使用梯度训练的分类器覆盖该方法*/
		virtual matrix<calc_param_type> gradient(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const { assert(false); return matrix<calc_param_type>(); };
		size_t feature_size;
		size_t label_size;
	};

	template<class feature_type, class label_type, class calc_param_type>
	inline classifier<feature_type, label_type, calc_param_type>::classifier(size_t feature_size, size_t label_size) :feature_size(feature_size), label_size(label_size) {}



	/*
	@brief 计算混淆矩阵
	行为实际列标，列为预测出的类标
	*/
	template<class feature_type, class label_type, class calc_param_type>
	matrix<size_t> confusion_matrix(const classifier<feature_type, label_type, calc_param_type>& sr, const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix)
	{
		matrix<label_type> p = sr.predict(feature_matrix);
		matrix<size_t> cm(sr.label_size, sr.label_size);
		for (size_t i = 0; i < p.row_size(); ++i)
		{
			cm.at(label_matrix.at(i, 0), p.at(i, 0))++;
		}
		return cm;
	}





}
#endif // !CLASSIFIER_H