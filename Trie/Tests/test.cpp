#include <gtest/gtest.h>
#include "../Trie.hpp"

TEST(Trie, Contains_word){
	Trie trie;

	trie.insert("abcde");
	trie.insert("ghfd");

	EXPECT_EQ(trie.contains("abcde"), true);
	EXPECT_EQ(trie.contains("jkl"), false);
	EXPECT_EQ(trie.contains("ghfd"), true);
}


TEST(Trie, Starts_with){
	Trie trie;

	trie.insert("abcde");
	EXPECT_EQ(trie.startsWith("ab"), true);
	EXPECT_EQ(trie.startsWith("jkl"), false);
	EXPECT_EQ(trie.startsWith("ak"), false);
}



int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
