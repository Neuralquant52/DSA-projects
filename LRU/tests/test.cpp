#include <gtest/gtest.h>
#include "../LRU.hpp"

TEST(LRUTests, Contains){
	LRUCache<char, int> cache(4);
	cache.insert('a', 1);
	cache.insert('b', 2);
	cache.insert('c', 3);
	cache.insert('d', 4);
	cache.insert('e', 5);

	EXPECT_EQ(cache.get('c').value_or(0), 3);
	EXPECT_EQ(cache.get('b').value_or(0), 2);
}

TEST(LRUTests, Eviction){
	LRUCache<char, int> cache(4);
	cache.insert('a', 1);
	cache.insert('b', 2);
	cache.insert('c', 3);
	cache.insert('d', 4);
	cache.insert('e', 5);

	EXPECT_EQ(cache.get('a').value_or(0), 0);
	EXPECT_EQ(cache.get('e').value_or(0), 5);
}

int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
