#include "tree.h"
namespace myml
{
	tree_node_v::tree_node_v(int depth)
	{
		_depth = depth;
	}
	size_t tree_node_v::children_size()
	{
		return _children.size();
	}

	tree_node & tree_node_v::child(size_t cn)
	{
		return _children[cn];
	}
	void tree_node_v::remove_child(size_t cn)
	{
		_children.erase(_children.begin() + cn);
	}
	size_t tree_node_v::append_child()
	{
		_children.push_back(tree_node_v());
		return _children.size() - 1;
	}
	inline tree_node & tree_node_v::operator[](size_t cn)
	{
		return child(cn);
	}
}