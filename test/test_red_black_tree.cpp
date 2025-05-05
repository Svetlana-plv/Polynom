#include <gtest/gtest.h>
#include "red_black_tree.h"


TEST(RBTree, CreateTree) {
	RBTree<std::string, int> tree;
	tree.insert("a", 1);
	tree.insert("b", 2);
	tree.insert("c", 3);
	tree.insert("d", 4);
	tree.insert("f", 5);
	RBTree<std::string, int>::Iterator it(tree.get_root());
	for (int i = 0; i < tree.size()-1; i++) {
		it++;
	}

	for (int i = 0; i < tree.size(); i++) {
		it--;
	}
}
