#include<iostream>
#include<fstream>
#include<memory>
#include<unordered_map>
#include<ctime>
#include<cstring>
#include<string>
#include"tree.hh"
#include"data.h"
#include"c4.5.h"
using namespace std;
using namespace myml;
int main()
{
	//matrix_a<long double> m;
	////ifstream f(R"(in.txt)", ios::in);
	////ifstream f(R"(E:\paper\feature\compound-10Mb-10ms-r1-q1000pa1\feature\feature0.txt)",ios::in);
	////ifstream f(R"(D:\paper\features µ—È\cubic-10Mb-10ms-r1-q1000pa1\feature\feature0.txt)", ios::in);
	//import_matrix_data(m, f);
	//auto x = m.sub_matrix(0, 0, m.size(), m.dimension());
	//c45_tree tree(x);
	//tree.train();
	//cerr << m.size() << "," << m.dimension() << endl;
	tree<string> tr;
	auto root = tr.insert(tr.begin(),"ccc");
	tr.append_child(root, "hello");
	tr.append_child(root, "hello1");
	tr.append_child(root, "hello2");
	for (auto i = tr.begin_leaf(); i != tr.end_leaf(); i++)
	{
		cerr << *i << endl;
	}

}