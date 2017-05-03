#ifndef SOFTMAX_REGRESSION
#define SOFTMAX_REGRESSION
#include"data.h"
#include<map>
namespace myml
{
	/*�����������ͣ�������template*/
	using feature_type = long double;
	using label_type = size_t;
	using param_type = long double;
	using label_class_map = map<label_type, long double>;
	class softmax_regression
	{
	public:
		softmax_regression(size_t feature_count, size_t label_count);
		void import_data(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix);
		/*����ݶ��½�*/
		void sgd(matrix<feature_type> &feature_matrix, matrix<label_type> &label_matrix);
		/*���½�*/
		void batch_gd(matrix<feature_type> &feature_matrix, matrix<label_type> &label_matrix);
		/*
		Bold Driver��������ѧϰ����
		������ǰerror��С������ѧϰ���ʣ���error�������Сѧϰ����
		�������½���ʽ��Ч
		*/
		void update_learning_rate_bd(param_type increase = 1.05, param_type decrease = 0.5);
		
		/*���׼ȷ��*/
		param_type accuracy(matrix<feature_type> &feature_matrix, matrix<label_type> &label_matrix);
		/*
			������������ȷ���-Ԥ������* ��Ӧ����������
			@param in feature_matrix �����������󣬾����ÿһ��Ϊһ����������
			@param in label_matrix ����������ÿһ�����Ӧ�ľ�����꣬�����������
			@param out ��������󣬾����С��_theta��С��ͬ
		*/
		matrix<param_type> error_matrix(matrix<feature_type> &feature_matrix, matrix<label_type> &label_matrix);
		/*
			ʹ��_thetaԤ����������Ľ��
			@param in �����������󣬾����ÿһ��Ϊһ����������
			@param out ��������Ԥ����������ľ���ÿһ��Ϊһ��Ԥ������ֻ��һ��
		*/
		matrix<label_type> predict(matrix<feature_type> &feature_matrix);

		inline param_type error();
		void print()
		{
			_theta.print();
		}
	private:
		matrix<param_type> _theta;
		matrix<param_type> _pre_theta;
		param_type _cur_error = 0;
		param_type _last_error = 0;
		param_type _learn_rate = 0.01;
	};
	inline void softmax_regression::update_learning_rate_bd(param_type increase, param_type decrease)
	{
		if (_last_error - _cur_error > 10E-10L)
		{
			_learn_rate *= increase;
		}
		else if (_last_error < _cur_error)
		{
			_learn_rate *= decrease;
		}
	}
	inline param_type myml::softmax_regression::error()
	{
		return _cur_error;
	}
}
#endif // !SOFTMAX_REGRESSION
