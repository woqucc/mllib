﻿#include<iostream>
#include<fstream>
#include<memory>
#include<unordered_map>
#include<ctime>
#include<cstring>
#include<string>
#include"data/matrix.h"
#include"classifier/perceptron.h"
#include"classifier/softmax_regression.h"
#include<vector>
#include<ctime>
#include<cstdlib>
#include<tuple>
#include<limits>

using namespace std;
using namespace myml;
using namespace myml::matrix_operate;
int main(int argc, char* argv[])
{
	matrix<long double> m;
	ifstream f(R"(..\\test_data\\perceptron_test.txt)", ios::in);
	//ifstream f(R"(multi_classification.txt)", ios::in);
	//ifstream f(R"(..\\test_data\\hessian_test.txt)", ios::in);

	//ifstream f(R"(multi_classification2.txt)", ios::in);
	//auto x = diag<long double>({ {1,2,3,4,5,6,7,8,9,10} });
	//(-x).print();
	//ifstream f(R"(E:\paper\feature\compound-10Mb-10ms-r1-q1000pa1\feature\feature1.txt)",ios::in);
	//ifstream f(argv[1],ios::in);
//	ifstream f(R"(D:\paper\features实验\cubic-10Mb-10ms-r1-q1000pa1\feature\feature0.txt)", ios::in);


	import_matrix_data(m, f, ' ');

	//matrix_normalization::zero_mean_by_col(m.cols(0, m.col_size() - 2));
	matrix<size_t> label;
	//matrix_normalization::zero_mean_by_col(m.cols(0, m.col_size() - 2));
	//matrix_normalization::set_range<long double>(m.col(m.col_size() - 1), 0, 3);
	matrix<long double> temp = m.col(m.col_size() - 1);
	auto label_map = matrix_normalization::serialize_label<long double, size_t>(temp, label);
	vector<size_t> us[6];
	for (size_t row_i = 0; row_i < m.row_size(); row_i++)
	{
		us[label.at(row_i, 0)].push_back(row_i);
	}
	
	/*softmax_regression_ridge sr(m.col_size() - 1, label_map.size());
	newton_raphson_optimizer<softmax_regression> nro(sr);
	grad_desc_optimizer<softmax_regression> gdo(sr);
	size_t n = 20;
	while (n--)
	{
		//nro.newton_raphson(m.cols(0, m.col_size() - 2),label);
		gdo.sgd_adadelta(m.cols(0, m.col_size() - 2), label);
	}

	cout << "of:" << sr.objective_function(m.cols(0, m.col_size() - 2), label) << '\t';
	cout << "acc:" << sr.accuracy(m.cols(0, m.col_size() - 2), label) << endl;
	sr.print();
	confusion_matrix(sr, m.cols(0, m.col_size() - 2), label).print();
	*/
	perceptron p(m.col_size() - 1);
	grad_desc_optimizer<perceptron> gdo(p);
	size_t n = 2;
	while (n--)
	{
		//nro.newton_raphson(m.cols(0, m.col_size() - 2),label);
		//gdo.sgd_adadelta(m.cols(0, m.col_size() - 2), label);
		gdo.sgd(m.cols(0, m.col_size() - 2), label,1E-3);
	}
	p.print(cout);
	cout << "of:" << p.objective_function(m.cols(0, m.col_size() - 2), label) << '\t';
	cout << "acc:" << p.accuracy(m.cols(0, m.col_size() - 2), label) << endl;
	confusion_matrix(p, m.cols(0, m.col_size() - 2), label).print();
	return 0;
}
