#include <fstream>
#include <iostream>
#include "LevelBalancedTree.hpp"


int main()
{
LevelBalancedTree<int, std::string> tree;
/*
	tree.insert(44, "foo");
	tree.insert(78, "sna");
	tree.insert(17, "bar");
    tree.insert(32, "bar");
	tree.insert(50, "foo");
	tree.insert(87, "sna");
    tree.insert(48, "foo");
	tree.insert(62, "sna");
    tree.remove(62);
    tree.remove(87);
*/

    tree.insert(10, "foo");
	tree.insert(5, "sna");
	tree.insert(15, "bar");
    tree.insert(2, "bar");
	tree.insert(12, "foo");
	tree.insert(20, "sna");
    tree.insert(11, "foo");
    tree.insert(13, "foo");
    tree.remove(2);



    return 0;
}

