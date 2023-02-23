#include <fstream>
#include <iostream>
#include "LevelBalancedTree.hpp"


int main()
{
LevelBalancedTree<int, std::string> tree;
	tree.insert(19, "foo");
	tree.insert(18, "sna");
	tree.insert(20, "bar");
    tree.insert(12, "bar");
	tree.insert(9, "foo");
	tree.insert(17, "sna");
    tree.insert(7, "foo");
	tree.insert(5, "sna");
    tree.insert(13, "foo");
	tree.insert(15, "sna");
    tree.insert(6, "foo");
	tree.insert(16, "sna");
    tree.insert(16, "sna");
	

    return 0;
}

