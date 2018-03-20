#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

// Treap
template<class T>
class Treap {

public:
	Treap() {
		this->treapRoot = NULL;
	}

	void insert(T val) {
		this->treapRoot = __insert(this->treapRoot, val);
	}
	void erase(T val) {
		this->treapRoot = __erase(this->treapRoot, val);
	}
	// TODO: How return Node type here ??
	bool find(T val) {
		return this->__find(this->treapRoot, val) != NULL;
	}
	// 1-based indexes
	int findKth(int kth) {
		return this->__findKth(this->treapRoot, kth);
	}
	// Upper bound of val
	int countLessThanEq(T val) {
		return this->__countLessThanEq(this->treapRoot, val);
	}	

private:
	template<typename U>
	struct Node {
		U val; 
		int priority, size;
		Node<U> *left, *right;

		Node() {}
		Node(U v) {
			val = v; size = 1;
			priority = rand();			
			left = right = NULL;
		}
		void updateSize() {
			int lsize = left != NULL ? left->size : 0;
			int rsize = right != NULL ? right->size : 0;			
			size = lsize + rsize + 1;
		}
	};
	Node<T>* treapRoot;

	// Return 2 treaps, where nodes in the left are less-than-equal & nodes in the right are greater than val
	pair<Node<T>*, Node<T>*> split(Node<T>* root, T val) {

		if(root == NULL) return make_pair((Node<T>*)NULL, (Node<T>*)NULL);

		if(val > root->val) {
			pair<Node<T>*, Node<T>*> rightSplit = split(root->right, val);
			root->right = rightSplit.first;
			root->updateSize();
			return make_pair(root, rightSplit.second);
		}
		pair<Node<T>*, Node<T>*> leftSplit = split(root->left, val);
		root->left = leftSplit.second;
		root->updateSize();
		return make_pair(leftSplit.first, root);
	}
	// Merges 2 treaps in one, always keeping treap constrains. Values in T1 are all smaller than values in T2
	Node<T>* merge(Node<T>* T1, Node<T>* T2) {

		if(T1 == NULL) return T2;
		if(T2 == NULL) return T1;
		
		if(T1->priority > T2->priority) {
			T1->right = merge(T1->right, T2);
			T1->updateSize();
			return T1;
		}
		T2->left = merge(T1, T2->left);
		T2->updateSize();
		return T2;
	}
	Node<T>* __find(Node<T>* root, T val) {

		if(root == NULL) return NULL;

		if(val < root->val) return __find(root->left, val);
		if(val > root->val) return __find(root->right, val);
		return root;
	}
	Node<T>* __insert(Node<T>* root, T val) {
		// Make split to the Treap
		pair<Node<T>*, Node<T>*> splitTreap = split(root, val);
		// Merge T1 with the merge of new Node and T2. 
		// As merge() selects the root based on node priorities, it assures the new Treap preserves both of its constrains
		return merge(splitTreap.first, merge(new Node<T>(val), splitTreap.second));
	}
	Node<T>* __erase(Node<T>* root, T val) {

		if(root == NULL) return NULL;

		if(val > root->val) {
			root->right = __erase(root->right, val);
		}
		else if(val < root->val) {
			root->left = __erase(root->left, val);
		}
		else {
			// Split and delete root, then merge both children
			Node<T>* eraseNode = root;
			root = merge(root->left, root->right);
			delete eraseNode;
		}
		if(root != NULL) root->updateSize();
		return root;
	}
	// 1-based indexes
	int __findKth(Node<T>* root, int kth) {
		// Out of bounds
		if(root == NULL) return -1;

		int leftSize = root->left != NULL ? root->left->size : 0;		
		if (leftSize >= kth) return __findKth(root->left, kth);
		if (leftSize + 1 == kth) return root->val;
		return __findKth(root->right, kth - leftSize - 1);
	}
	// Upper bound of val
	int __countLessThanEq(Node<T>* root, T val) {

		if(root == NULL) return 0;

		if(val >= root->val) {
			int lessThanEq = root->left != NULL ? root->left->size : 0;
			return __countLessThanEq(root->right, val) + lessThanEq + 1;
		}
		return __countLessThanEq(root->left, val);
	}
};

Treap<int> T;

