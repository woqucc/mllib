#include "svm.h"
namespace myml
{
	const matrix<svm::feature_type> svm::probabilities(const matrix<feature_type>& feature_matrix) const
	{
		return matrix<feature_type>();
	}
	const matrix<svm::label_type> svm::predict(const matrix<feature_type>& feature_matrix) const
	{
		matrix<label_type> result(feature_matrix.row_size(), 1);
		feature_type y;
		for (size_t f_row_i = 0; f_row_i < feature_matrix.row_size(); ++f_row_i)
		{
			y = b;
			for (size_t sv_row_i = 0; sv_row_i < _support_vectors_feature.row_size(); ++sv_row_i)
			{
				y += _kernel(_support_vectors_feature.row(sv_row_i), feature_matrix.row(f_row_i)) * _lagrange_multiplier(sv_row_i);
			}
			result(f_row_i) = y > 0 ? 1 : 0;
		}
		return std::move(result);
	}
	bool svm::load(istream & in)
	{
		return false;
	}
	bool svm::save(ostream & out)
	{
		return false;
	}
	svm::feature_type svm::objective_function(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix) const
	{
		return feature_type();
	}
	void svm::print(ostream & out) const
	{
	}
	svm::svm(size_t feature_size, function<feature_type(const matrix<feature_type>&, const matrix<feature_type>&)> kernel) : classifier(feature_size, 2), _kernel(kernel)
	{

	}

	void svm::train(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix)
	{
		// 临时变量：
		// 第0列:temp(i,0),存储拉格朗日算子
		// 第1列:temp(i,1),存储每个样本的的误差
		// 第2列:temp(i,2),存储将label_matrix中0替换为-后的类标,temp(i,0)
		matrix<feature_type> temp(feature_matrix.row_size(), 3);

		temp.fill(0);
		(temp.col(2) = label_matrix).replace(0, -1);


		matrix<feature_type> label = label_matrix;
		label.replace(0, -1);
		//feature_type error_i = 0;
		//feature_type error_j = 0;
		feature_type tol = 1E-8;
		feature_type old_lm_i, old_lm_j;
		feature_type eta;


		//计算Ek=f(xk) -yk
		for (size_t i = 0; i < feature_matrix.row_size(); ++i)
		{
			// 计算样本i的距离,error_i = f(xi)-yi
			temp(i, 1) = b - label(i);
			for (size_t distance_i = 0; distance_i < feature_matrix.row_size(); ++distance_i)
			{
				temp(i, 1) += temp(distance_i, 0) * _kernel(feature_matrix.row(distance_i), feature_matrix.row(i)) * label(distance_i);
			}

		}
		//何时停止优化？当我们遍历一边样本后发现不需要改变任何值之后。
		bool continue_opt = true;
		while (continue_opt)
		{
			continue_opt = false;
			for (size_t i = 0; i < feature_matrix.row_size(); ++i)
			{
				/*
				 *  检测i是否满足KKT条件
				 *  0 < ai < C && f(xi) * yi == 1
				 *  ai == 0 && f(xi) * yi >= 1
				 *  ai == C && f(xi) * yi <= 1
				 */
				if (temp(i, 0) < C &&  temp(i, 1) * label(i) < -tol || temp(i, 1) * label(i) > tol && temp(i, 0) > 0)
				{
					//选择与i不同的j
					for (size_t j = 0; j < feature_matrix.row_size(); ++j)
					{
						if (i != j)
						{
							//计算第j个算子调节的范围，在调节第j个算子时，需要使第i个算子也满足约束条件
							feature_type L, H;
							if (label_matrix(i) != label_matrix(j))
							{
								L = std::max(static_cast<feature_type>(0), temp(j, 0) - temp(i, 0));
								H = std::min(static_cast<feature_type>(C), C + temp(j, 0) - temp(i, 0));
							}
							else
							{
								L = std::max(static_cast<feature_type>(0), temp(i, 0) + temp(j, 0) - C);
								H = std::min(static_cast<feature_type>(C), temp(i, 0) + temp(j, 0));
							}

							if (L == H)
								break;
							//
							eta = _kernel(feature_matrix.row(i), feature_matrix.row(j)) * 2 - _kernel(feature_matrix.row(i), feature_matrix.row(i)) - _kernel(feature_matrix.row(j), feature_matrix.row(j));
							//选择下个i
							if (eta > 0)
								break;

							//保存修改前的值
							old_lm_i = temp(i, 0);
							old_lm_j = temp(j, 0);

							temp(j, 0) -= label(j) * (temp(i, 1) - temp(j, 1)) / eta;
							//限制范围
							temp(j, 0) = temp(j, 0) > H ? H : temp(j, 0);
							temp(j, 0) = temp(j, 0) < L ? L : temp(j, 0);

							//调节范围过小
							if (std::abs(temp(j, 0) - old_lm_j) < 1E-5)
								break;
							temp(i, 0) += (old_lm_j - temp(j, 0)) * label(i) * label(j);

							//计算参数b的值
							feature_type b1 = b - temp(i, 1) - label(i) * (temp(i, 0) - old_lm_i) * _kernel(feature_matrix.row(i), feature_matrix.row(i)) - label(j) * (temp(j, 0) - old_lm_j) * _kernel(feature_matrix.row(i), feature_matrix.row(j));
							feature_type b2 = b - temp(j, 1) - label(i) * (temp(i, 0) - old_lm_i) * _kernel(feature_matrix.row(i), feature_matrix.row(j)) - label(j) * (temp(j, 0) - old_lm_j) * _kernel(feature_matrix.row(j), feature_matrix.row(j));
							if (temp(i, 0) > 0 && temp(i, 0) < C && temp(i, 0) > 0 && temp(i, 0) < C)
								b = (b1 + b2) / 2;
							else if (temp(i, 0) > 0 && temp(i, 0) < C)
								b = b1;
							else if (temp(j, 0) > 0 && temp(j, 0) < C)
								b = b2;

							continue_opt = true;

							//更新两个算子对应的样本误差缓存
							temp(i, 1) = b - label(i);
							temp(j, 1) = b - label(j);
							for (size_t distance_i = 0; distance_i < feature_matrix.row_size(); ++distance_i)
							{
								temp(i, 1) += temp(distance_i, 0) * _kernel(feature_matrix.row(distance_i), feature_matrix.row(i)) * label(distance_i);
								temp(j, 1) += temp(distance_i, 0) * _kernel(feature_matrix.row(distance_i), feature_matrix.row(j)) * label(distance_i);
							}

						}
					}

				}
			}


		}
		size_t sv_size = feature_matrix.row_size() - temp.col(0).count(0);
		_support_vectors_feature.resize(sv_size, feature_matrix.col_size());
		_lagrange_multiplier.resize(sv_size, 1);
		sv_size = 0;
		for (size_t i = 0; i < temp.row_size(); i++)
		{
			if (temp(i, 0) != 0)
			{
				_support_vectors_feature.row(sv_size) = feature_matrix.row(i);
				_lagrange_multiplier(sv_size) = temp(i, 0) * label(i);
				++sv_size;
			}
		}
	}



}