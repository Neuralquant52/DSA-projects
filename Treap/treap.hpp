#include <cstdlib>
#include <cstddef>
#include <queue>
#include <stdexcept>

template <typename T = int>
struct TreapNode {
	TreapNode(T key_, int priority_, TreapNode* parent = nullptr) : 
		parent(parent), key(key_), priority(priority_)
	{}

	TreapNode* parent = nullptr;
	
	T key;
	int priority;
	TreapNode* right = nullptr;
	TreapNode* left = nullptr;
	
	void setRight(TreapNode<T>* node){
		this->right = node;

		if (node)
		   node->parent = this;
	}

	void setLeft(TreapNode<T>* node){
		this->left = node;

		if (node)
		   node->parent = this;
	}
};

template <typename T>
class Treap {
	using Node = TreapNode<T>;
public:
	Treap(int randomizationInterval) : interval(randomizationInterval) {}
	void insert(T key){
		Node* node = root;
		Node* parent = nullptr;		
		int priority = std::rand() % interval;
		
		Node* newNode = new Node(key, priority);

		while (node != nullptr){
			parent = node;
			if (node->key >= key)
				node = node->left;
			else 
				node = node->right;
		}
		if (parent == nullptr){
			root = newNode;
			return;
		}
		else if (key <= parent->key)
			parent->left = newNode;
		else 
			parent->right = newNode;
		
		newNode->parent = parent;
		
		bool rotationSuccessful;
		while (newNode->parent != nullptr && newNode->priority < newNode->parent->priority){
			if (newNode == newNode->parent->left)
			   rotationSuccessful = rightRotate(newNode);
			else 
			   rotationSuccessful = leftRotate(newNode);
			
			if (!rotationSuccessful){
			   throw std::logic_error("(Insert) Couldn't rotate\n");
			   return;
			}
		}
		if (newNode->parent == nullptr)
		    root = newNode;
	}
	

	void remove(T key){
		Node* node = find(key);
		if (!node)
		   throw std::logic_error("(Remove) Node not in the treap\n");

		if (isRoot(node) && isLeaf(node)){
		   delete node;
		   root = nullptr;
		   return;
	  	}	  
		
		while (!isLeaf(node)){
			if (node->left != nullptr && (node->right == nullptr || node->left->priority < node->right->priority)){
			   if (!rightRotate(node->left))
			 	throw std::logic_error("(Remove) Cannot rotate\n");
			}
			else {
			   if (!leftRotate(node->right))
				throw std::logic_error("(Remove) Cannot rotate\n");
			}
		}
		if (isRoot(node))
		    node  = nullptr;
		else if (node == node->parent->right)
		    node->parent->right = nullptr;
		else 
		    node->parent->left = nullptr;
		delete node;
	}

	Node* find(T key){
		Node* curr = root;
		while (curr->key != key){
			if (!curr->left && !curr->right)
			   return nullptr;

			if (key < curr->key)
			   curr = curr->left;
			else if (key > curr->key)
			   curr = curr->right;
		}
		return curr;
	}


	Node* max(){
		Node* curr = root;
		while (curr && curr->right)
		   curr = curr->right;

		return curr;
	}


	Node* min(){
		Node* curr = root;
		while (curr && curr->left)
		   curr = curr->left;

		return curr;
	}

	std::size_t height(){
		std::queue<Node*> q;
		if (root)
		  q.push(root);
		
		std::size_t lvl{};
		while (!q.empty()){
			std::size_t sz = q.size();

			for (std::size_t i{}; i < sz; i++){
				Node* last = q.front(); q.pop();
				if (last->left)
				   q.push(last->left);
				if (last->right)
				   q.push(last->right);
			}
			lvl++;
		}
		return lvl;
	}
	
	void clear(){
		*this = Treap<T>{};
	}

	~Treap(){
		destructor(root);
	}
private:
	bool isRoot(Node* node){ return node->parent == nullptr;}
	bool isLeaf(Node* node){ return !node->left && !node->right;}

	void destructor(Node* root){
		if (!root)
		   return;

		destructor(root->left);
		destructor(root->right);
		delete root;
	}

	[[nodiscard]]
	bool rightRotate(Node* x){
		if (!x || x == root)
			return 0;	
		
		Node* y = x->parent;
		
		if (y->left != x)
			return 0;

		Node* p = y->parent;
		if (p){
		   if (p->left == y)
			p->setLeft(x);
		   else 
			p->setRight(x);
		}
		else {
		   root = x;
		   x->parent = nullptr;
		}

		y->setLeft(x->right);
		x->setRight(y);	
		return 1;
	}

	[[nodiscard]]
	bool leftRotate(Node* x){
		if (!x || x == root)
			return 0;	
		
		Node* y = x->parent;
		
		if (y->right != x)
			return 0;

		Node* p = y->parent;
		if (p){
		   if (p->left == y)
			p->setLeft(x);
		   else 
			p->setRight(x);
		}
		else{ 
		   root = x;
		   root->parent = nullptr;	
		}

		y->setRight(x->left);
		x->setLeft(y);	
		return 1;
	}
	
	int interval;
	Node* root = nullptr;
};
