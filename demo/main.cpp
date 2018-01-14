#include<iostream>
#include<fstream>
#include<memory>
#include<unordered_map>
#include<ctime>
#include<cstring>
#include<string>

#include"../src/data/matrix.h"
#include"../src/classifier/perceptron.h"
#include"../src/classifier/softmax_regression.h"
#include<vector>
#include<ctime>
#include<cstdlib>
#include<tuple>
#include<limits>
#include<random>

#include"../src/classifier/svm.h"

//#include"cublas_v2.h"
//#include"cuda_runtime.h"

using namespace std;
using namespace myml;
using namespace myml::matrix_operate;

int main(int argc, char* argv[])
{

	matrix<long double> am;
	//ifstream f(R"(C:\Users\woqucc\Desktop\feature0.txt)", ios::in);
	ifstream f(R"(..\\test_data\\perceptron_test.txt)", ios::in);
	//ifstream f(R"(..\test_data\multi_classification.txt)", ios::in);
	//ifstream f(R"(..\\test_data\\hessian_test.txt)", ios::in);

	//ifstream f(R"(..\test_data\binary_classification.txt)", ios::in);
	//ifstream f(R"(D:\研\ss_project\workspace_20170924\data\20170924.txt)", ios::in);
	//auto x = diag<long double>({ {1,2,3,4,5,6,7,8,9,10} });
	//(-x).print();
	//ifstream f(R"(E:\paper\feature\compound-10Mb-10ms-r1-q1000pa1\feature\feature1.txt)",ios::in);
	//ifstream f(argv[1],ios::in);
//	ifstream f(R"(D:\paper\features实验\cubic-10Mb-10ms-r1-q1000pa1\feature\feature0.txt)", ios::in);

	random_device rd;
	import_matrix_data(am, f, ' ');
	
	//auto m = am.cols(0, am.col_size() - 1);
	auto m = am;
	cout << m.row_size() << endl;
	//matrix_normalization::zero_mean_by_col(m.cols(0, m.col_size() - 2));
	matrix<size_t> label;
	//matrix_normalization::zero_mean_by_col(m.cols(0, m.col_size() - 2));
	//matrix_normalization::set_range<long double>(m.col(m.col_size() - 1), 0, 3);
	matrix<long double> temp = m.col(m.col_size() - 1);
	auto label_map = matrix_normalization::serialize_label<long double, size_t>(temp, label);
	
	
	
	softmax_regression sr(m.col_size() - 1, label_map.size());
	//newton_raphson_optimizer<softmax_regression> nro(sr);
	grad_desc_optimizer<softmax_regression> gdo(sr);
	size_t n = 200000;

	while (n--)
	{
		auto sample_id = rd() % m.row_size();
		//nro.newton_raphson(m.cols(0, m.col_size() - 2),label);
		//gdo.sgd_adadelta(m.cols(0, m.col_size() - 1).row(sample_id), label.row(sample_id));
		gdo.sgd_adadelta(m.cols(0, m.col_size() - 1), label);
		if (n % 10 == 0)
		{
			cout << "of:" << sr.objective_function(m.cols(0, m.col_size() - 1), label) << '\t';
			cout << "acc:" << sr.accuracy(m.cols(0, m.col_size() - 1), label) << endl;
			confusion_matrix(sr, m.cols(0, m.col_size() - 1), label).print();
			sr.print();
		}
	}
	cout << "of:" << sr.objective_function(m.cols(0, m.col_size() - 1), label) << '\t';
	cout << "acc:" << sr.accuracy(m.cols(0, m.col_size() - 1), label) << endl;
	//sr.print();
	//auto cm = confusion_matrix(sr, m.cols(0, m.col_size() - 1), label);

	//s.predict(m.cols(0, m.col_size() - 1)).print();
	
	confusion_matrix(sr, m.cols(0, m.col_size() - 1), label).print();


	/*matrix<long double> m[4];
	ifstream f[4] = { ifstream(R"(cwnd0.txt)", ios::in), ifstream(R"(cwnd1.txt)", ios::in), ifstream(R"(cwnd2.txt)", ios::in), ifstream(R"(cwnd3.txt)", ios::in)};
	for (size_t i = 0; i < 4; i++)
	{
		import_matrix_data(m[i], f[i], '\t');
		cerr << m[i].row_size() << '\t' << m[i].col_size() <<  endl;
	}

	auto result = matrix_normalization::merge_matrices_by_cols<long double>(4, m[0], m[1], m[2], m[3]);
	ofstream out("all.txt", ios::out);
	result.print(out);
	*/
	return 0;
}
