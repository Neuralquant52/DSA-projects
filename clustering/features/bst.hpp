#include <cstddef>
#include <queue>
#include <stdexcept>


template <typename T>
struct TreeNode{
	TreeNode (T key_, TreeNode* left_ = nullptr, TreeNode* right_ = nullptr) : 
		key(key_),  left(left_), right(right_) {}
	T key;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;
};

template <typename T>
class BST {
	using Node = TreeNode<T>;
public:
	void insert(T key){
		
		Node* newNode = new Node(key);
		if (!root){
			root = newNode;
			return;
		}
		
		Node* curr = root;
		Node* parent = nullptr;
		while (curr){
			parent = curr;
			if (newNode->key < curr->key)
			   curr = curr->left;
			else 
			   curr = curr->right;
		}
		
		if (newNode->key < parent->key)
		   parent->left = newNode;
		else 
		   parent->right = newNode;
	}

	void remove(T key){ root = remove(root, key); }	

	Node* search(T key){
		Node* curr = root;
		while (curr){
			if (key < curr->key)
			   curr = curr->left;
			else if (key > curr->key) 
			   curr = curr->right;
			else 
			   return curr;
		}
		throw std::logic_error("(search) Couldn't find key in the BST\n");
	}

	std::size_t height(){
		std::queue<Node*> q;
		if (root)
		   q.push(root);

		std::size_t lvl{};
		while (!q.empty()){
		    std::size_t sz = q.size();
		    for (int i{}; i < sz; i++){
			Node* curr = q.front(); q.pop();
			if (curr->left)
			   q.push(curr->left);
			if (curr->right)
			   q.push(curr->right);
	 	    }
	 	    lvl++;	    
		}
		return lvl;
	}
	
	Node* data(){
		return root;
	}

	void clear(){
		*this = BST<T>{};
	}

	~BST(){
		destructor(root);
	}
private:

	void destructor(Node* root){
		if (!root)
		   return;

		destructor(root->left);
		destructor(root->right);
		delete root;
	}

	Node* remove(Node* n, T key){
	    if (!n) return nullptr;
	    if (key < n->key) n->left = remove(n->left, key);
	    else if (n->key < key) n->right = remove(n->right, key);
	    else if (!n->left || !n->right){
		Node* c = n->left ? n->left : n->right;
		delete n;
		return c;
	    } else {
		Node* m = findMin(n->right);
		n->key = m->key;
		n->right = remove(n->right, m->key);
	    }
	    return n;
	}

	Node* findMin(Node* node){
		while (node && node->left){
			node = node->left;
		}
		return node;
	}
	Node* root = nullptr;
};
