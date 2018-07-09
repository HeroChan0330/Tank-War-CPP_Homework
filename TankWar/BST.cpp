#pragma once
#include <stdlib.h>

template<typename KEY, typename VALUE> class BSTNode;

template<typename KEY, typename VALUE>
class BST {
private:
	VALUE get(BSTNode<KEY, VALUE>*x, KEY key) {
		if (x == NULL) return NULL;
		int cmp = key - x->key;
		if (cmp > 0) return get(x->right, key);
		else if (cmp<0) return get(x->left, key);
		else return x->value;
		return NULL;
	}
	BSTNode<KEY, VALUE>*put(BSTNode<KEY, VALUE>*x, KEY key, VALUE val) {
		if (x == NULL) {
			return new BSTNode<KEY, VALUE>(key, val, 1);
		}
		int cmp = key - x->key;
		if (cmp>0) {
			x->right = put(x->right, key, val);
		}
		else if (cmp < 0) {
			x->left = put(x->left, key, val);
		}
		else {
			x->value = val;
		}
		x->N = size(x->left) + size(x->right) + 1;
		return x;
	}
	int size(BSTNode<KEY, VALUE>*node) {
		if (node == NULL) return 0;
		else return node->N;
	}
	BSTNode<KEY, VALUE>* minKey(BSTNode<KEY, VALUE>*x) {
		if (x->left == NULL) return x;
		return minKey(x->left);
	}
	BSTNode<KEY, VALUE>*removeMin(BSTNode<KEY, VALUE>*x) {
		if (x->left == NULL) return x->right;
		x->left = removeMin(x->left);
		x->N = size(x->left) + size(x->right) + 1;
		return x;
	}

	BSTNode<KEY, VALUE>*remove(BSTNode<KEY, VALUE>*x, KEY key) {
		if (x == NULL) return NULL;
		int cmp = key - x->key;
		if (cmp < 0) x->left = remove(x->left, key);
		else if (cmp>0) x->right = remove(x->right, key);
		else {
			if (x->right == NULL) return x->left;
			if (x->left == NULL) return x->right;
			BSTNode<KEY, VALUE>*t = x;
			x = minKey(t->right);
			x->right = removeMin(t->right);
			x->left = t->left;
		}
		x->N = size(x->left) + size(x->right) + 1;
		return x;
	}
public:
	BSTNode<KEY, VALUE>*root;
	BST() {
		root = NULL;
	}
	int size() {
		return size(root);
	}
	VALUE get(KEY key) {
		return get(root, key);
	}
	void put(KEY key, VALUE val) {
		root = put(root, key, val);
	}
	KEY minKey() {
		return minKey(root)->key;
	}
	void removeMin() {
		root = removeMin(root);
	}
	void remove(KEY key) {
		root = remove(root, key);
	}
};

template<typename KEY, typename VALUE>
class BSTNode {
protected:
public:
	KEY key;
	VALUE value;
	int N;
	BSTNode<KEY, VALUE>*left, *right;
	friend class BST<KEY, VALUE>;
	BSTNode(KEY key, VALUE val, int N) {
		this->key = key;
		this->value = val;
		this->N = N;
		this->left = NULL;
		this->right = NULL;
		//cout << "newNode "<<key<<","<<val<< endl;
	}
};
