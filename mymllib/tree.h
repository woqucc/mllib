#ifndef TREE_H
#define TREE_H
#include<vector>
#include"data.h"
namespace myml
{
	using namespace std;
	class tree_node
	{
	public:
		virtual size_t children_size() = 0;
		virtual tree_node& child(size_t cn) = 0;
		virtual void remove_child(size_t cn) = 0;
		virtual size_t append_child() = 0;
		virtual tree_node& operator[](size_t cn) = 0;
	protected:
		int _depth;
	};
	class tree_node_v:public tree_node
	{
	private:
		vector<tree_node_v> _children;
	public:
		tree_node_v(int depth = 0);
		size_t children_size() override;
		tree_node& child(size_t cn) override;
		void remove_child(size_t cn) override;
		size_t append_child() override;
		tree_node& operator[](size_t cn) override;
	};
}
#endif // !TREE_H
