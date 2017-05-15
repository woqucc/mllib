#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include"data.h"
#include<fstream>
namespace myml
{
	using namespace std;
	/*特征类型,标签类型,计算过程中用到的参数的类型*/
	template<class feature_type, class label_type, class param_type>
	class classifier
	{
	public:
		/*
		@brief 预测
		@param in feature_matrix特征矩阵，其中每一行为一个样本
		@param out 输出每个样本对应类别的概率
		*/
		virtual const matrix<param_type> probabilities(const matrix<feature_type> & feature_matrix) const = 0 ;
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
		virtual bool load(ifstream &in) = 0;
		/*
		@brief 读取模型
		@param in 文件
		*/
		virtual bool save(ofstream &out) = 0;
		/*
		@brief 模型的目标函数
		@param in feature_matrix 特征矩阵
		@param in label_matrix 类别矩阵
		@param out 返回目标函数值
		*/
		virtual param_type objective_function(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) = 0;

		/*
		@brief 获取输入样本的准确率
		*/
	    virtual param_type accuracy(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix) const = 0 ;
	};
}
#endif // !CLASSIFIER_H