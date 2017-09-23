#include"../src/data/matrix.h"
#include"../src/classifier/softmax_regression.h"
#define CATCH_CONFIG_MAIN
#include"catch.hpp"
using namespace myml;
using namespace myml::matrix_operate;
TEST_CASE("Matrix Operate Test: Matrix Addition")
{
	matrix<int> a = { {44500, 46483, 29500, 22952},
					  {41667, 15482, 30063, 43385},
					  {61942,  7825, 43381, 27273},
					  {13693, 39800, 50481, 55176} };

	matrix<int> b = { {54586, 35438,  7813, 41898},
					  {16806, 57012, 61592, 35698},
					  {40204, 17353, 42307, 42422},
					  {38158, 20845, 31422, 35644} };

	matrix<int> c = { {99086, 81921, 37313, 64850},
					  {58473, 72494, 91655, 79083},
					  {102146,25178, 85688, 69695},
					  {51851, 60645, 81903, 90820} };

	matrix<int> d = { {198172,163842, 74626,129700},
					  {116946,144988,183310,158166},
					  {204292, 50356,171376,139390},
					  {103702,121290,163806,181640} };
	REQUIRE(a + b == c);
	REQUIRE(a + b + c == d);
}
TEST_CASE("Matrix Operate Test: Matrix Subtract")
{
	matrix<int> a = { { 44500, 46483, 29500, 22952 },
					  { 41667, 15482, 30063, 43385 },
					  { 61942,  7825, 43381, 27273 },
					  { 13693, 39800, 50481, 55176 } };

	matrix<int> b = { { 54586, 35438,  7813, 41898 },
					  { 16806, 57012, 61592, 35698 },
					  { 40204, 17353, 42307, 42422 },
					  { 38158, 20845, 31422, 35644 } };

	matrix<int> c = { {-10086, 11045, 21687,-18946},
					 { 24861, -41530 ,-31529, 7687},
					 { 21738, -9528,  1074, -15149},
					 { -24465, 18955, 19059, 19532} };

	matrix<int> d = { { 0,0,0,0 },
					  { 0,0,0,0 },
					  { 0,0,0,0 },
					  { 0,0,0,0 } };
	REQUIRE(a - b == c);
	REQUIRE(a - b - c == d);
}

TEST_CASE("Matrix Operate Test: Matrix Multiply")
{
	matrix<long long> a = { { 44500, 46483, 29500, 22952 },
					  { 41667, 15482, 30063, 43385 },
					  { 61942,  7825, 43381, 27273 },
					  { 13693, 39800, 50481, 55176 } };

	matrix<long long> b = { { 54586, 35438,  7813, 41898 },
					  { 16806, 57012, 61592, 35698 },
					  { 40204, 17353, 42307, 42422 },
					  { 38158, 20845, 31422, 35644 } };

	matrix<long long> c = { { 5272090714,5217427736,5179913680,5593361222 },
							{ 5398763036,3785298494,3914230426,5120187928 },
							{ 6297445820,3962515674,3658202419,5687010360 },
							{ 5551268830,4780470647,6427784948,6102688040 } };
	REQUIRE(a * b == c);
}
TEST_CASE("Matrix Operate Test: Matrix Transpose")
{
	matrix<int> a = { { 44500, 46483, 29500, 22952 },
					  { 41667, 15482, 30063, 43385 },
					  { 61942,  7825, 43381, 27273 },
					  { 13693, 39800, 50481, 55176 } };
	matrix<int> b = { { 44500, 41667, 61942, 13693 },
					  { 46483, 15482,  7825, 39800 },
					  { 29500, 30063, 43381, 50481 },
					  { 22952, 43385, 27273, 55176 } };
	REQUIRE(a.transpose() == b);
}
TEST_CASE("Pesudo inverse Test")
{
	matrix<long double> b = { { 1,0,0},{ 0,2,0 },{ 0,0,3 } };
	auto c = pseudo_inverse(b);
	REQUIRE((c * b * c) == c);
	REQUIRE((b * c * b) == b);
}
TEST_CASE("Softmax with Grandient")
{
	ifstream f(R"(..\test_data\perceptron_test.txt)", ios::in);
	matrix<long double> m;
	import_matrix_data(m, f, ' ');
	matrix<size_t> label;
	auto label_map = matrix_normalization::serialize_label<long double, size_t>(m.col(m.col_size() - 1), label);
	softmax_regression sr(m.col_size() - 1, label_map.size());
	newton_raphson_optimizer<softmax_regression> nro(sr);
	grad_desc_optimizer<softmax_regression> gdo(sr);
	size_t n = 20;
	while (n--)
	{
		gdo.sgd_adadelta(m.cols(0, m.col_size() - 1), label);
	}
	REQUIRE(sr.accuracy(m.cols(0, m.col_size() - 1), label) == 1.0);
}