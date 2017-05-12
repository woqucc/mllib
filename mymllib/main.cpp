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
	//ifstream f(R"(multi_classification.txt)", ios::in);
	//ifstream f(R"(E:\paper\feature\compound-10Mb-10ms-r1-q1000pa1\feature\feature1.txt)",ios::in);
	
	
	ifstream f(R"(D:\paper\features实验\cubic-10Mb-10ms-r1-q1000pa1\feature\feature0.txt)", ios::in);
	import_matrix_data(m, f, ',');
	
	/*matrix<long double> t;
	ifstream tf("multiclass_theta.txt");
	import_matrix_data(t, tf, ' ');
	softmax_regression sr(10,4);
	sr.set_theta(t.t());
	sr.predict({ {0.001,0.004,1.7579,0.000,0.0004,0.0352,0.0004,0.0200,0.1217,10000.0000} }).print();*/
//	t.print();
	/*import_matrix_data<long double>(t, {
	{-1565.84783857894,-1399.69502209318,-2935.82459826157,-1455.37181730943,-1383.35204023056,0},
	{-17.9242142682373,-22.5493452016841,-21.1482830839771,-23.0005658649597,-2.80998947108530,0 },
	{-11.5217174992796,-18.2172477333245,-14.3057005704548,-19.9734725020512,-2.00223135001052,0 },
	{-24.5779228306577,-25.3983423032451,-27.2762002432028,-18.6447471879729,-2.86534958565167,0 },
	{-18.4297837070852,-23.7748660862561,-24.6598587957338,-22.9518109990376,-5.29095552241851,0 },
	{-16.7934901576758,-21.4348635660293,-23.1251184221200,-19.5986564962285,-52.4129766710766,0 },
	{-12.5067898919877,-17.8307591554491,-13.6138942491149,-17.4530299302615,-1.22230958471246,0 },
	{-15.0739171244252,-21.1914098639516,-19.6500754008747,-22.6241333107264,-22.9144791087634,0 },
	{4.53877358265719,6.41437703177692,2.97872411765876,0.319983008163472,5.95320802451181,0 },
	{ 4148.70218613171,4418.51180136410,6747.88382180219,4435.69589664134,2550.80386972897,0 }
	});
	*/
	/*import_matrix_data<long double>(t, {
		{-62350.5546,-62110.0811,-63833.2558,0,-62050.7227,-24259.7617},
	{	-298.0831,-302.5437,-301.1813,0,-298.4696,72.918 },
	{-5.6469,-12.5772,-8.2891,0,-11.683,100.0922 },
	{	-154.2791,-154.9827,-156.7956,0,-137.8718,164.9297 },
	{	-232.816,-238.0395,-239.0855,0,-230.1669,42.1609 },
	{	-104.2868,-109.2243,-110.8647,0,-107.0903,-467.3525 },
	{	60.2174,54.6576,59.4585,0,58.7135,100.365 },
	{	-98.0534,-105.1555,-102.7717,0,-101.3799,-441.1214 },
	{	1809.2638,1811.3267,1808.1922,0,1803.6084,-1993.7788 },
	{ 115514.7318,115663.5619,118282.5192,0,114875.5643,31500.2471}
	});
	auto abc = t.max_position();

*/
/*	matrix<size_t> label;
	matrix_normalized::set_range<long double>(m, m.col_size() - 1, 0, 3);
	auto label_map = matrix_normalized::serialize_label<long double, size_t>(m.col(m.col_size() - 1), label);
	softmax_regression sr(m.col_size() - 1, label_map.size());
	sr.set_theta(t.t());
	//label += size_t(1);

	cerr << sr.accuracy(m.cols(0, m.col_size() - 2), label) << endl;
	cerr << sr.error(m.cols(0, m.col_size() - 2), label) << endl;
	*/

    matrix<size_t> label;
	matrix_normalized::set_range<long double>(m, m.col_size() - 1, 0, 3);
	auto label_map = matrix_normalized::serialize_label<long double, size_t>(m.col(m.col_size() - 1), label);
	vector<size_t> us[4];
	for (size_t row_i = 0; row_i < m.row_size(); row_i++)
	{
		us[label.at(row_i, 0)].push_back(row_i);
	}
	softmax_regression sr(m.col_size() - 1, label_map.size());
	int n = 50000;
	int r = 0;
	int out_count = 0;
	srand(time(nullptr));
	long double e = 0;
	long double acc = 0;
	while (acc < 0.85 || n-- > 0)
	{
		
		size_t tr = rand() % 4;
		r = us[tr][rand()% us[tr].size()];
		//sr.adadelta(m.cols(0, m.col_size() - 2), label);
		sr.adadelta(m.cols(0, m.col_size() - 2).row(r), label.row(r));
		//e = sr.error(m.cols(0, m.col_size() - 2), label);
		//sr.sgd(m.cols(0, m.col_size() - 2).row(p), label.row(p));
		//sr.sgd_momentum(m.cols(0, m.col_size() - 2).row(p), label.row(p));
		//sr.batch_sgd(m.cols(0, m.col_size() - 2), label);
		//sr.update_learning_rate_bd();
		acc = sr.accuracy(m.cols(0, m.col_size() - 2), label);
		if (out_count++ % 100 == 0)
		{
			
			e = sr.error(m.cols(0, m.col_size() - 2), label);
			cerr << "error:" << e << "\tacc:" << acc << endl;
			cerr << "theta:" << endl;
			sr.print();
			//cerr << "theta" << endl;
			//sr.print();

		}
		//cerr << sr.accuracy(m.cols(0, m.col_size() - 2), label) << endl;
	}
	cerr << "error" << sr.error(m.cols(0, m.col_size() - 2), label) << endl;
	cerr << sr.accuracy(m.cols(0, m.col_size() - 2), label) << endl;
	sr.print();
	matrix<long double> p = sr.predict(m.cols(0, m.col_size() - 2));
	matrix<long double> cm(label_map.size(), label_map.size());
	for (size_t row_i = 0; row_i < p.row_size(); row_i++)
	{
		cm.at(p.row(row_i).max_position().second, label.at(row_i, 0))++;
	}
	cm.print('\t');
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
	return 0;
}