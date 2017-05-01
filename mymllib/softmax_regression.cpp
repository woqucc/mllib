#include "softmax_regression.h"

void myml::softmax_regression::import_data(const matrix<feature_type>& feature_matrix, const matrix<label_type>& label_matrix)
{
	_feature_matrix = feature_matrix;
	_label_matrix = label_matrix;
}
