#ifndef SOFTMAX_REGRESSION
#define SOFTMAX_REGRESSION
#include"data.h"
namespace myml
{
	/*设置数据类型，不想用template*/
	using feature_type = long double;
	using label_type = long double;
	class softmax_regression
	{
	public:
		softmax_regression() = default;
		void import_data(const matrix<feature_type> &feature_matrix, const matrix<label_type> &label_matrix);
	private:
		matrix<long double> _theta;
		matrix<long double> _pre_theta;
		matrix<feature_type> _feature_matrix;
		matrix<label_type> _label_matrix;
	};
}
#endif // !SOFTMAX_REGRESSION
