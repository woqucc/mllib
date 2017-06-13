#include<iostream>
#include<fstream>
#include<memory>
#include<unordered_map>
#include<ctime>
#include<cstring>
#include<string>
#include"data.h"
#include"softmax_regression.h"
#include<vector>
#include<ctime>
#include<cstdlib>

using namespace std;
using namespace myml;
using namespace myml::matrix_operate;
int main(int argc, char* argv[])
{
	matrix<long double> m;
	//ifstream f(R"(binary_classification.txt)", ios::in);
	//ifstream f(R"(multi_classification.txt)", ios::in);
	ifstream f(R"(hessian_test.txt)", ios::in);
	//ifstream f(R"(multi_classification2.txt)", ios::in);
	//ifstream f(R"(E:\paper\feature\compound-10Mb-10ms-r1-q1000pa1\feature\feature1.txt)",ios::in);

	//ifstream f(argv[1],ios::in);
//	ifstream f(R"(D:\paper\features实验\cubic-10Mb-10ms-r1-q1000pa1\feature\feature0.txt)", ios::in);
	import_matrix_data(m, f, ' ');
	//matrix_normalization::zero_mean_by_col(m.cols(0, m.col_size() - 2));
	matrix<size_t> label;
	matrix_normalization::zero_mean_by_col(m.cols(0, m.col_size() - 2));
	//matrix_normalization::set_range<long double>(m, m.col_size() - 1, 0, 3);
	matrix<long double> temp = m.col(m.col_size() - 1);
	auto label_map = matrix_normalization::serialize_label<long double, size_t>(temp, label);
	vector<size_t> us[6];
	for (size_t row_i = 0; row_i < m.row_size(); row_i++)
	{
		us[label.at(row_i, 0)].push_back(row_i);
	}
	softmax_regression sr(m.col_size() - 1, label_map.size());
	//sr.load({ { 0.4709,0.5486,0.1839 },{ -2.5932,6.0889,-2.3215 },{ 3.2777,-1.2836,0.0483 } });
	matrix<long double> h = sr.hessian(m.cols(0, m.col_size() - 2), label);
	matrix<long double> g = temp - sr.probabilities(m.cols(0, m.col_size() - 2));
	h.print();
	cerr << endl;
	g.print();
	cerr << endl;
	auto hi = inverse(h);
	hi.print();
	(h * hi).print();
	int n = 2000;
	/*size_t r = 0;
	int out_count = 0;
	srand(time(nullptr));
	long double e = 0;
	long double acc = 0;
	while (n-- > 0)
	{


		r = rand() % m.row_size();

		sr.adadelta(m.cols(0, m.col_size() - 2), label);
		//sr.adadelta(m.cols(0, m.col_size() - 2).row(r), label.row(r));
		//e = sr.error(m.cols(0, m.col_size() - 2), label);
		//sr.sgd(m.cols(0, m.col_size() - 2).row(r), label.row(r));
		//sr.sgd(m.cols(0, m.col_size() - 2), label);
		//sr.sgd_momentum(m.cols(0, m.col_size() - 2).row(r), label.row(r));
		//sr.sgd_momentum(m.cols(0, m.col_size() - 2), label);
		//sr.batch_gd(m.cols(0, m.col_size() - 2), label);
		//sr.update_learning_rate_bd();
		//
		if (out_count++ % 200 == 0)
		{
			acc = sr.accuracy(m.cols(0, m.col_size() - 2), label);
			e = sr.objective_function(m.cols(0, m.col_size() - 2), label);
			cout << "objective function:" << e << "\tacc:" << acc << endl;
			cout << "theta:" << endl;
			sr.print();
			cout << "c ma:" << endl;
			confusion_matrix(sr, m.cols(0, m.col_size() - 2), label).print();
		
			//sr.predict(m.cols(0, m.col_size() - 2)).print();

		}
		//cerr << sr.accuracy(m.cols(0, m.col_size() - 2), label) << endl;
	}
	cout << "of:" << sr.objective_function(m.cols(0, m.col_size() - 2), label) << '\t';
	cout << "acc:" << sr.accuracy(m.cols(0, m.col_size() - 2), label) << endl;
	sr.print();
	confusion_matrix(sr, m.cols(0, m.col_size() - 2), label);*/
	return 0;
}
