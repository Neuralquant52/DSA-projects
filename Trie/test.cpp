#include <ios>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct TrieNode {
	std::unordered_map<char, TrieNode*> childrens;
	bool word = false;
};


class Trie {
public: 
	void insert(std::string word){
		TrieNode* curr = &root;
		for (const char& c : word){
			if (!curr->childrens.contains(c))
			   curr->childrens[c] = new TrieNode;

			curr = curr->childrens[c];
		}
		curr->word = true;
	}

	bool contains(std::string word){
		TrieNode* curr = &root;
		for (const char& c : word){
			if (!curr->childrens.contains(c))
				return false;

			curr = curr->childrens[c];
		}
		return curr->word;
	}

	bool startsWith(std::string prefix){
		TrieNode* curr = &root;
		for (const char& c : prefix){
			if (!curr->childrens.contains(c))
				return false;

			curr = curr->childrens[c];
		}
		return true;
	}

	std::vector<std::string> wordsWith(std::string prefix){
		TrieNode* curr = &root;
		std::vector<std::string> res;	
		
		for (const char& c : prefix){
			if (!curr->childrens.contains(c))
				return {};

			curr = curr->childrens[c];
		}

		return wordsWith(prefix, curr, res);
	}

private:
	std::vector<std::string> wordsWith(std::string prefix, TrieNode* node, std::vector<std::string>& words){

		if (node->word)
			words.emplace_back(prefix);

		for (auto& [c, child] : node->childrens)
			wordsWith(prefix + c, child, words);
		

		return words;
	}

	TrieNode root;
};


int main(){
	Trie trie;
	trie.insert("abcd");
	trie.insert("aabda");

	std::vector<std::string> words = trie.wordsWith("ab");
	for (std::string& word : words)
		std::cout << word << '\n';

	return 0;
}
