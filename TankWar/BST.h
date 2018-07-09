#pragma once
#include <stdlib.h>

template<typename KEY,typename VALUE> class BSTNode;

template<typename KEY,typename VALUE>
class BST{
private:
    BSTNode<KEY,VALUE>*root;
	VALUE get(BSTNode<KEY, VALUE>*x, KEY&key) {
		if (x == NULL) return NULL;
		int cmp = key - x->key;
		if (cmp>0) get(x->right, key);
		else if (cmp<0) get(x->left, key);
		else return x.val;
		return NULL;
	}
	BSTNode<KEY, VALUE>*put(BSTNode<KEY, VALUE>*x, KEY&key, VALUE&val) {
		if (x == NULL) return new BSTNode<KEY, VALUE>(key, val, 1);
		int cmp = key - x->key;
		if (cmp>0) put(x->right, key, val);
		else if (cmp<0) put(x->left, key, val);
		else x->val = val;
		x->N = size(x->left) + size(x->right) + 1;
		return x;
	}
	int size(BSTNode<KEY, VALUE>*node) {
		if (node == NULL) return 0;
		else return node.N;
	}
public:
	BST() {
		root = NULL;
	}
	int size() {
		return size(root);
	}
	VALUE get(KEY&key) {
		return get(root, key);
	}
	void put(KEY&key, VALUE&val) {
		root = put(root, key, val);
	}

};

template<typename KEY,typename VALUE>
class BSTNode{
protected:
    KEY key;
    VALUE value;
    int N;
    BSTNode<KEY,VALUE>*left,*right;
public:
    friend class BST<KEY,VALUE>;
    BSTNode(KEY key,VALUE val,int N){
        this->key=key;
        this->value=val;
        this->N=N;
    }
};
