#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <gtest/gtest.h>
#include <vector>
#include "../treap.hpp"


TEST(TreapTestCases, MinMax){
	Treap<int> treap(100'000);
	
	treap.insert(4), treap.insert(7), treap.insert(10), treap.insert(6), treap.insert(3), treap.insert(1);	
	
	treap.height();
	EXPECT_EQ(treap.min()->key, 1);
	EXPECT_EQ(treap.max()->key, 10);
}

TEST(TreapTestCases, Find){
	Treap<int> treap(100'000);
	
	treap.insert(4), treap.insert(7), treap.insert(10), treap.insert(6), treap.insert(3), treap.insert(1);	
	EXPECT_EQ(treap.find(4)->key, 4);
}

int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
