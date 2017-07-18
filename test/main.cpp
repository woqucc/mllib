#include"../src/data/matrix.h"
#include"../src/classifier/softmax_regression.h"
#define CATCH_CONFIG_MAIN
#include"catch.hpp"
using namespace myml;
using namespace myml::matrix_operate;
TEST_CASE("Matrix Operate Test 1")
{
	matrix<int> a = { { 1,2,3,4},{ 5,6,7,8 },{ 9,10,11,12 },{ 13,14,15,16 } };
	matrix<int> b = { { 1,2,3,4 },{ 5,6,7,8 },{ 5,6,7,8 },{ 5,6,7,8 } };
	matrix<int> c = { { 2,4,6,8 },{ 10,12,14,16 },{ 14,16,18,20 },{ 18,20,22,24 } };
	matrix<int> d = { { 0,0,0,0 },{ 0,0,0,0 },{ 4,4,4,4 },{ 8,8,8,8 } };
	REQUIRE(a + b == c);
	REQUIRE(a - b == d);
}
TEST_CASE("Pesudo inverse Test")
{
	matrix<long double> b = { { 4,5,6 },{ 1,2,3 } };
	auto c = pseudo_inverse(b);
	//精度
	REQUIRE((c * b * c) == c);
	REQUIRE((b * c * b) == b);
}
TEST_CASE("Softmax Test")
{
	/*ifstream f(R"(..\\test_data\\perceptron_test.txt)", ios::in);
	matrix<long double> m;
	import_matrix_data(m, f, ' ');
	matrix<size_t> label;
	auto label_map = matrix_normalization::serialize_label<long double, size_t>(m.cols(0, m.col_size() - 2), label);
	softmax_regression sr(m.col_size() - 1, label_map.size());
	newton_raphson_optimizer<softmax_regression> nro(sr);
	grad_desc_optimizer<softmax_regression> gdo(sr);
	size_t n = 20;
	while (n--)
	{
		gdo.sgd_adadelta(m.cols(0, m.col_size() - 2), label);
	}
	REQUIRE(sr.accuracy(m.cols(0, m.col_size() - 2), label) == 1.0);*/
}