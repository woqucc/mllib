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