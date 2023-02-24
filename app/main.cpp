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
	tree.insert(18, "sna");
    tree.insert(20, "foo");
    tree.remove(2);

/*
	tree.insert(1, "foo");
	tree.insert(2, "sna");
	tree.insert(3, "bar");
    tree.insert(4, "bar");
	tree.insert(5, "foo");
	tree.insert(6, "sna");
    tree.insert(7, "foo");
	tree.insert(8, "sna");
    tree.insert(9, "foo");
	tree.remove(1);
	tree.remove(2);
	tree.remove(3);
	tree.remove(4);
	tree.remove(5);
	tree.remove(6);
	tree.remove(7);
	tree.remove(8);
	tree.remove(9);
    */


    return 0;
}

