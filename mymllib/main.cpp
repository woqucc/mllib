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
using namespace std;
using namespace myml;
using namespace myml::matrix_operate;
int main()
{
	matrix<long double> m;
	//ifstream f(R"(binary_classification.txt)", ios::in);
	//ifstream f(R"(multi_classification.txt)", ios::in);
	//ifstream f(R"(E:\paper\feature\compound-10Mb-10ms-r1-q1000pa1\feature\feature1.txt)",ios::in);
	ifstream f(R"(D:\paper\features实验\cubic-10Mb-10ms-r1-q1000pa1\feature\feature0.txt)", ios::in);
	import_matrix_data(m, f);
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
	matrix<size_t> label;
	auto label_map = matrix_normalized::serialize_label<long double, size_t>(m.col(m.col_size() - 1), label);
	softmax_regression sr(m.col_size() - 1, label_map.size());
	int n = 1000000;
	int p = 0;
	int out_count = 0;

	while (n--)
	{
		p = rand() % m.row_size();

		//sr.sgd(m.cols(0, m.col_size() - 2).row(p), label.row(p));
		//sr.sgd_momentum(m.cols(0, m.col_size() - 2).row(p), label.row(p));
		//sr.batch_sgd(m.cols(0, m.col_size() - 2), label);
		//sr.update_learning_rate_bd();
		sr.adadelta(m.cols(0, m.col_size() - 2), label);
		//sr.adadelta(m.cols(0, m.col_size() - 2), label);
		if (out_count++ % 100 == 0)
		{
			cerr << "error:" << sr.error() << "\tacc:" << sr.accuracy(m.cols(0, m.col_size() - 2), label) << endl;
			//cerr << "theta" << endl;
			//sr.print();
		}
		//cerr << sr.accuracy(m.cols(0, m.col_size() - 2), label) << endl;
	}
	cerr << sr.accuracy(m.cols(0, m.col_size() - 2), label) << endl;
	sr.print();
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