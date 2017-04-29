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
int main()
{
	matrix<long double> m;
	ifstream f(R"(in.txt)", ios::in);
	////ifstream f(R"(E:\paper\feature\compound-10Mb-10ms-r1-q1000pa1\feature\feature0.txt)",ios::in);
	////ifstream f(R"(D:\paper\features µ—È\cubic-10Mb-10ms-r1-q1000pa1\feature\feature0.txt)", ios::in);
	import_matrix_data(m, f);
	//auto x = m.sub_matrix(0, 0, m.row_size(), m.col_size());
	//c45_tree tree(x);
	//tree.train();
	matrix<long double> c = m.row(1);
	matrix<int> cpp = matrix_normalized::convert_matrix_type<long double,int>(c);
	cpp.print();
	softmax_regression sr;
	sr.import_data(m.sub_matrix(0, 0, m.row_size() - 1, m.col_size() - 2), m.col( m.col_size() - 1));
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
	return 0;
}