#include"svm.h"
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
				y += dot_product(_support_vectors_feature.row(sv_row_i), feature_matrix.row(f_row_i)) * _support_vectors_label(sv_row_i)*_lagrange_multiplier(sv_row_i);
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
	svm::svm(size_t feature_size) : classifier(feature_size, 2)
	{
	}

	void svm::train(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix)
	{
		//拉格朗日算子
		matrix<feature_type> lm(feature_matrix.row_size(), 1);
		lm.fill(0);

		matrix<int> label = label_matrix;
		label.replace(0, -1);
		feature_type error_i = 0, error_j = 0;
		feature_type tol = 1E-8;
		feature_type old_lm_i, old_lm_j;
		feature_type eta;

		for (size_t i = 0; i < feature_matrix.row_size(); ++i)
		{

			//error_i = b - label_matrix(i) == 1 ? 1 : -1;
			//for (size_t distance_i = 0; distance_i < feature_matrix.row_size(); ++distance_i)
			//{
			//	if (label_matrix(distance_i) == 1)
			//		error_i += lm(distance_i) * dot_product(feature_matrix.row(distance_i), feature_matrix.row(i));
			//	else
			//		error_i -= lm(distance_i) * dot_product(feature_matrix.row(distance_i), feature_matrix.row(i));
			//}
			// 计算样本i的距离,error_i = f(xi)-yi
			// 这里直接计算 yi*error_i = yi(f(xi))-1
			error_i = b - label(i);
			for (size_t distance_i = 0; distance_i < feature_matrix.row_size(); ++distance_i)
			{
				error_i += lm(distance_i) * dot_product(feature_matrix.row(distance_i), feature_matrix.row(i)) * label(distance_i);
			}
			//检测i是否需要调节
			if (lm(i) < C &&  error_i * label(i) < -tol || error_i * label(i) > tol && lm(i) > 0)
			{
				//选择与i不同的j
				for (size_t j = 0; j < feature_matrix.row_size(); ++j)
				{
					if (i != j)
					{
						//计算样本j的误差
						error_j = b - label(j);
						for (size_t distance_i = 0; distance_i < feature_matrix.row_size(); ++distance_i)
						{
							error_j += lm(distance_i) * dot_product(feature_matrix.row(distance_i), feature_matrix.row(j)) * label(distance_i);
						}
						//计算调整范围
						feature_type L, H;
						if (label_matrix(i) != label_matrix(j))
						{
							L = std::max(static_cast<feature_type>(0), lm(j) - lm(i));
							H = std::min(static_cast<feature_type>(C), C + lm(j) - lm(i));
						}
						else
						{
							L = std::max(static_cast<feature_type>(0), lm(i) + lm(j) - C);
							H = std::min(static_cast<feature_type>(C), lm(i) + lm(j));
						}

						if (L == H)
							break;
						eta = dot_product(feature_matrix.row(i), feature_matrix.row(j)) * 2 - dot_product(feature_matrix.row(i), feature_matrix.row(i)) - dot_product(feature_matrix.row(j), feature_matrix.row(j));
						//选择下个i
						if (eta > 0)
							break;

						//保存修改前的值
						old_lm_i = lm(i), old_lm_j = lm(j);

						lm(j) -= label(j) * (error_i - error_j) / eta;
						//限制范围
						lm(j) = lm(j) > H ? H : lm(j);
						lm(j) = lm(j) < L ? L : lm(j);

						//选择下个i
						if (std::abs(lm(j) - old_lm_j) < 1E-5)
							break;
						lm(i) += (old_lm_j - lm(j)) * label(i)* label(j);
						feature_type b1 = b - error_i - label(i) * (lm(i) - old_lm_i) * dot_product(feature_matrix.row(i), feature_matrix.row(i)) - label(j) * (lm(j) - old_lm_j) * dot_product(feature_matrix.row(i), feature_matrix.row(j));
						feature_type b2 = b - error_j - label(i) * (lm(i) - old_lm_i) * dot_product(feature_matrix.row(i), feature_matrix.row(j)) - label(j) * (lm(j) - old_lm_j) * dot_product(feature_matrix.row(j), feature_matrix.row(j));
						if (lm(i) > 0 && lm(i) < C)
							b = b1;
						if (lm(j) > 0 && lm(j) < C)
							b = b2;
						if (lm(i) > 0 && lm(i) < C && lm(i) > 0 && lm(i) < C)
							b = (b1 + b2) / 2;
					}
				}
			}
		}
		size_t sv_size = feature_matrix.row_size() - lm.count(0);
		_support_vectors_feature.resize(sv_size, feature_matrix.col_size());
		_support_vectors_label.resize(sv_size, 1);
		_lagrange_multiplier.resize(sv_size, 1);
		sv_size = 0;
		for (size_t i = 0; i < lm.size(); i++)
		{
			if (lm(i) != 0)
			{
				_support_vectors_feature.row(sv_size) = feature_matrix.row(i);
				_support_vectors_label(sv_size) = label(i);
				_lagrange_multiplier(sv_size) = lm(i);
				++sv_size;
			}
		}
	}

}