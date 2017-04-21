#include<iostream>
#include<fstream>
#include<memory>
#include<unordered_map>
#include<ctime>
#include"lib/tree.hh"
#include"data.h"
#include"c4.5.h"
using namespace std;
using namespace myml;
int main()
{
	//matrix_va<long double> m;
	////ifstream f(R"(in.txt)", ios::in);
	////ifstream f(R"(E:\paper\feature\compound-10Mb-10ms-r1-q1000pa1\feature\feature0.txt)",ios::in);
	////ifstream f(R"(D:\paper\features µ—È\cubic-10Mb-10ms-r1-q1000pa1\feature\feature0.txt)", ios::in);
	//import_matrix_data(m, f);
	//auto x = m.sub_matrix(0, 0, m.size(), m.dimension());
	//c45_tree tree(x);
	//tree.train();
	//cerr << m.size() << "," << m.dimension() << endl;
	tree<int> tree;
	tree = 1;
	tree.insert_after(tree.begin(), 33);
	tree.append_child(tree.begin_leaf(),3);
	tree.append_child(tree.begin_leaf(), 4);
	tree<int>::fixed_depth_iterator a= tr.begin();
	for (auto i = tree.begin_fixed(tree.) ;i !=tree.end(); ++i)
	{
		cerr << *i << endl;
	}
	
	return 0;
}