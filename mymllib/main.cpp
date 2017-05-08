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
int main()
{
	matrix<long double> m;
	//ifstream f(R"(binary_classification.txt)", ios::in);
	ifstream f(R"(multi_classification.txt)", ios::in);
	//ifstream f(R"(E:\paper\feature\compound-10Mb-10ms-r1-q1000pa1\feature\feature1.txt)",ios::in);
	//ifstream f(R"(D:\paper\features实验\cubic-10Mb-10ms-r1-q1000pa1\feature\feature0.txt)", ios::in);
	import_matrix_data(m, f, ' ');
	matrix<long double> t;
	import_matrix_data<long double>(t, {
	{4148.70218613171,4418.51180136410,6747.88382180219,4435.69589664134,2550.80386972897,0},
	{-1565.84783857894,-1399.69502209318,-2935.82459826157,-1455.37181730943,-1383.35204023056,0},
	{-17.9242142682373,-22.5493452016841,-21.1482830839771,-23.0005658649597,-2.80998947108530,0 },
	{-11.5217174992796,-18.2172477333245,-14.3057005704548,-19.9734725020512,-2.00223135001052,0 },
	{-24.5779228306577,-25.3983423032451,-27.2762002432028,-18.6447471879729,-2.86534958565167,0 },
	{-18.4297837070852,-23.7748660862561,-24.6598587957338,-22.9518109990376,-5.29095552241851,0 },
	{-16.7934901576758,-21.4348635660293,-23.1251184221200,-19.5986564962285,-52.4129766710766,0 },
	{-12.5067898919877,-17.8307591554491,-13.6138942491149,-17.4530299302615,-1.22230958471246,0 },
	{-15.0739171244252,-21.1914098639516,-19.6500754008747,-22.6241333107264,-22.9144791087634,0 },
	{4.53877358265719,6.41437703177692,2.97872411765876,0.319983008163472,5.95320802451181,0 }
});
	matrix<size_t> label;
	auto label_map = matrix_normalized::serialize_label<long double, size_t>(m.col(m.col_size() - 1), label);
	softmax_regression sr(m.col_size() - 1, label_map.size());
	sr.set_theta(t.t());
	t.t().print();
	sr.predict(m.cols(0, m.col_size() - 2)).print();
	cerr << sr.accuracy(m.cols(0, m.col_size() - 2), label) << endl;
//	t.print();
	//t.transpose();
	/*for (size_t row_i = 0; row_i < m.row_size(); ++row_i)
	{
		matrix<long double> sample = m.row(row_i);
		static_cast<long double>(sample.col(sample.col_size()- 1)) = 1.0L;
		sample.print();
		matrix<long double> predict = sample * t;
		matrix<long double> prob(6,1);
		predict.print();
		int m_NumClasses = 6;
		for (int m = 0; m < m_NumClasses; m++) {
			long double sum = 0;
			for (int n = 0; n < m_NumClasses - 1; n++) {
				//cerr << static_cast<long double>(predict.col(n)) - static_cast<long double>(predict.col(m)) << '\t' << std::exp(static_cast<long double>(predict.col(n)) - static_cast<long double>(predict.col(m))) << endl;
				//sum += std::exp(static_cast<long double>(predict.col(n)) - static_cast<long double>(predict.col(m)));
			}
			static_cast<long double&>(prob.col(m)) = 1 / (sum + std::exp(-static_cast<long double>(predict.col(m))));
		}

		//log(predict);
		prob.print();
	}*/
	//matrix_normalized::set_range<long double>(m, m.col_size() - 1, 0, 3);
	cerr << m.row_size() << '\t' << m.col_size() << endl;
	//matrix<long double> m1 = m;
	//m.transpose();
//	m.print();
	//auto x = m.sub_matrix(0, 0, m.row_size(), m.col_size());
	//c45_tree tree(x);
	//tree.train();
	/*matrix<long double> c = m.row(1);
	matrix<int> cpp = matrix_normalized::convert_matrix_type<long double,int>(c);
	cpp.print();*/


	/*
	matrix<size_t> label;
	auto label_map = matrix_normalized::serialize_label<long double, size_t>(m.col(m.col_size() - 1), label);
	softmax_regression sr(m.col_size() - 1, label_map.size());
	int n = 10000000;
	int p = 0;
	int out_count = 0;
	srand(time(nullptr));
	while (n--)
	{
		p = rand() % m.row_size();

		//sr.sgd(m.cols(0, m.col_size() - 2).row(p), label.row(p));
	//	sr.sgd_momentum(m.cols(0, m.col_size() - 2).row(p), label.row(p));
		//sr.batch_sgd(m.cols(0, m.col_size() - 2), label);
		//sr.update_learning_rate_bd();
		//sr.adadelta(m.cols(0, m.col_size() - 2).row(p), label.row(p));
		sr.adadelta(m.cols(0, m.col_size() - 2), label);
		if (out_count++ % 100 == 0)
		{
			cerr << "error:" << sr.error(m.cols(0, m.col_size() - 2).row(p), label.row(p)) << "\tacc:" << sr.accuracy(m.cols(0, m.col_size() - 2), label) << endl;
			//cerr << "theta" << endl;
			//sr.print();
		}
		//cerr << sr.accuracy(m.cols(0, m.col_size() - 2), label) << endl;
	}
	cerr << sr.accuracy(m.cols(0, m.col_size() - 2), label) << endl;
	sr.print();

	*/

	//sr.predict(m.cols(0, m.col_size() - 2)).print();
//	sr.print();
	//sr.import_data(m.cols(0, m.col_size() - 2), m.col( m.col_size() - 1));

	//auto c = m.row(4);
	//c.print();
	//auto p = m.fetch_column({1,2});
	//p->print();
	//cerr << m.row_size() << "," << m.col_size() << endl;
	//tree<string> tr;
	//auto root = tr.insert(tr.begin(),"ccc");
	//tr.append_child(root, "hello");
	//tr.append_child(root, "hello1");
	//tr.append_child(root, "hello2");
	//for (auto i = tr.begin_leaf(); i != tr.end_leaf(); i++)
	//{
	//	cerr << *i << endl;
	//}
	system("pause");
	return 0;
}