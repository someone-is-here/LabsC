#pragma once
#include<iostream>
#include <assert.h>
template<typename TypeOfKey, typename TypeOfValue>
struct Node {
	TypeOfKey key;
	TypeOfValue value;
	Node<TypeOfKey, TypeOfValue>* left;
	Node<TypeOfKey, TypeOfValue>* right;
};

template<typename TypeOfKey, typename TypeOfValue>
class BinaryTree {
private:
	Node<TypeOfKey, TypeOfValue>* root;
	size_t size;
public:
	BinaryTree();
	BinaryTree(const BinaryTree<TypeOfKey, TypeOfValue>& obj);
	Node<TypeOfKey, TypeOfValue>* Copy(Node<TypeOfKey, TypeOfValue>* node);
	size_t Size() const;
	bool Empty() const;
	void Clear();
	void HelpClear(Node<TypeOfKey, TypeOfValue>* node);
	void Insert(const TypeOfKey key, TypeOfValue value);
	Node<TypeOfKey, TypeOfValue>* Add(Node<TypeOfKey, TypeOfValue>* node, const TypeOfKey key, TypeOfValue value);
	TypeOfValue& Find(const TypeOfKey key);
	Node<TypeOfKey, TypeOfValue>* Minimum(Node<TypeOfKey, TypeOfValue>* node);
	Node<TypeOfKey, TypeOfValue>* Maximum(Node<TypeOfKey, TypeOfValue>* node);
	Node<TypeOfKey, TypeOfValue>* HelpFind(Node<TypeOfKey, TypeOfValue>* node, const TypeOfKey key);
	void PrintBT(std::ostream& out, Node<TypeOfKey, TypeOfValue>* node) const;
	TypeOfValue& operator[] (const TypeOfKey key);
	TypeOfKey FindNext(const TypeOfKey key);
	TypeOfKey FindPrevious(const TypeOfKey key);  
	Node<TypeOfKey, TypeOfValue>* HelpErase(Node<TypeOfKey, TypeOfValue>* root, const TypeOfKey key);
	void Erase(const TypeOfKey key);
	friend std::ostream& operator<<(std::ostream& out, const BinaryTree<TypeOfKey, TypeOfValue>& obj) {
		out << "Size: " << obj.size << '\n';
		if (obj.Empty()) {
			obj.PrintBT(out,obj.root);
		}
		else {
			out << "Empty\n";
		}
		return out;
	}
	BinaryTree<TypeOfKey, TypeOfValue>& operator=(const BinaryTree<TypeOfKey, TypeOfValue>& BinTreeObj);
	~BinaryTree();
};

template<typename TypeOfKey, typename TypeOfValue>
BinaryTree<TypeOfKey, TypeOfValue>::BinaryTree() {
	root = nullptr;
	size = 0;
}

template<typename TypeOfKey, typename TypeOfValue>
Node<TypeOfKey, TypeOfValue>* BinaryTree<TypeOfKey, TypeOfValue>::Copy(Node<TypeOfKey, TypeOfValue>* node) {
	if (node == nullptr) {
		return nullptr;
	}
	Node<TypeOfKey, TypeOfValue>* n1 = new Node<TypeOfKey, TypeOfValue>;
	n1->key = node->key;
	n1->value = node->value;
	n1->left = Copy(node->left);
	n1->right = Copy(node->right);
	return n1;
}

template<typename TypeOfKey, typename TypeOfValue>
BinaryTree<TypeOfKey, TypeOfValue>::BinaryTree(const BinaryTree<TypeOfKey, TypeOfValue>& obj) {
	size = obj.size;
	root = Copy(obj.root);
}

template<typename TypeOfKey, typename TypeOfValue>
BinaryTree<TypeOfKey, TypeOfValue>& BinaryTree<TypeOfKey, TypeOfValue>::operator=(const BinaryTree<TypeOfKey, TypeOfValue>& BinTreeObj) {
	if (this == &BinTreeObj) {
		return *this;
	}
	size = BinTreeObj.size;
	root = Copy(BinTreeObj.root);
	return *this;
}

template<typename TypeOfKey, typename TypeOfValue>
void BinaryTree<TypeOfKey, TypeOfValue>::PrintBT(std::ostream& out, Node<TypeOfKey, TypeOfValue>* node) const {
	if (node) {
		out << node->key << " - " << node->value << '\n';
		PrintBT(out, node->left);
		PrintBT(out, node->right);
	}
}

template<typename TypeOfKey, typename TypeOfValue>
void BinaryTree<TypeOfKey, TypeOfValue>::HelpClear(Node<TypeOfKey, TypeOfValue>* node) {
	if (node != nullptr) {
		HelpClear(node->left);
		HelpClear(node->right);
		delete node;
	}
}

template<typename TypeOfKey, typename TypeOfValue>
Node<TypeOfKey, TypeOfValue>* BinaryTree<TypeOfKey, TypeOfValue>::HelpFind(Node<TypeOfKey, TypeOfValue>* node, const TypeOfKey key) {
	if (node != nullptr) {
		if (node->key < key) {
			HelpFind(node->right, key);
		}
		else if (node->key > key) {
			HelpFind(node->left, key);
		}
		else {
			return node;
		}
	}
	else {
		return node;
	}
}

template<typename TypeOfKey, typename TypeOfValue>
Node<TypeOfKey, TypeOfValue>* BinaryTree<TypeOfKey, TypeOfValue>::Maximum(Node<TypeOfKey, TypeOfValue>* node) {
	if (node->right == nullptr) {
		return node;
	}
	return Maximum(node->right);
}

template<typename TypeOfKey, typename TypeOfValue>
Node<TypeOfKey, TypeOfValue>* BinaryTree<TypeOfKey, TypeOfValue>::Minimum(Node<TypeOfKey, TypeOfValue>* node) {
	if (node->left == nullptr) {
		return node;
	}
	return Minimum(node->left);
}

template<typename TypeOfKey, typename TypeOfValue>
Node<TypeOfKey, TypeOfValue>* BinaryTree<TypeOfKey, TypeOfValue>::HelpErase(Node<TypeOfKey, TypeOfValue>* root, const TypeOfKey key) {
	if (root == nullptr) {
		return root;
	}
	if (root->key < key) {
		root->right = HelpErase(root->right, key);
	}
	else if (root->key > key) {
		root->left = HelpErase(root->left, key);
	}
	else if (root->right != nullptr && root->left != nullptr) {
		root->key = Minimum(root->right)->key;
		root->right = HelpErase(root->right, root->key);
	}
	else {
		if (root->left != nullptr) {
			root = root->left;
		}
		else if (root->right != nullptr) {
			root = root->right;
		}
		else {
			root = nullptr;
		}
	}
	return root;
}

template<typename TypeOfKey, typename TypeOfValue>
void BinaryTree<TypeOfKey, TypeOfValue>::Erase(const TypeOfKey key) {
	HelpErase(root, key);
}

template<typename TypeOfKey, typename TypeOfValue>
TypeOfKey BinaryTree<TypeOfKey, TypeOfValue>::FindNext(const TypeOfKey key) {
	Node<TypeOfKey, TypeOfValue>* current = root, *node = nullptr;
	while (current != nullptr) {
		if (current->key > key) {
			node = current;
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	return node->key;
}

template<typename TypeOfKey, typename TypeOfValue>
TypeOfKey BinaryTree<TypeOfKey, TypeOfValue>::FindPrevious(const TypeOfKey key) {
	Node<TypeOfKey, TypeOfValue>*current = root, *node = nullptr;
	while (current != nullptr) {
		if (current->key < key) {
			node = current;
			current = current->right;
		}
		else {
			current = current->left;
		}
	}
	return node->key;
}

template<typename TypeOfKey, typename TypeOfValue>
TypeOfValue& BinaryTree<TypeOfKey, TypeOfValue>::Find(const TypeOfKey key) {
	Node<TypeOfKey, TypeOfValue>* res = HelpFind(root,key);
	if (res != nullptr) {
		return res->value;
	}
	TypeOfValue val = -1;
	return val;
}

template<typename TypeOfKey, typename TypeOfValue>
TypeOfValue& BinaryTree<TypeOfKey, TypeOfValue>::operator[] (const TypeOfKey key) {
	TypeOfValue val = Find(key);
	return val;
}

template<typename TypeOfKey, typename TypeOfValue>
Node<TypeOfKey, TypeOfValue>* BinaryTree<TypeOfKey, TypeOfValue>::Add(Node<TypeOfKey, TypeOfValue>* node,const TypeOfKey key, TypeOfValue value) {
	if (node == nullptr) {
		node = new Node<TypeOfKey, TypeOfValue>;
		node->key = key;
		node->value = value;
		node->left = node->right = nullptr;
	}
	else  if (key < node->key) {  
		assert((node->key != key) && "Such a key already exists!");
		node->left = Add(node->left, key, value);
	}
	else { 
		assert(node->key != key && "Such a key already exists!");
		node->right = Add(node->right,key, value);
	}
	return node;
}

template<typename TypeOfKey, typename TypeOfValue>
void BinaryTree<TypeOfKey, TypeOfValue>::Insert(const TypeOfKey key, TypeOfValue value) {
	if (!root) {
		root = Add(root, key, value);
	}
	else {
		Add(root, key, value);
	}
	size++;
	return;
}

template<typename TypeOfKey, typename TypeOfValue>
size_t BinaryTree<TypeOfKey, TypeOfValue>::Size() const {
	return size;
}

template<typename TypeOfKey, typename TypeOfValue>
bool BinaryTree<TypeOfKey, TypeOfValue>::Empty() const {
	return size;
}

template<typename TypeOfKey, typename TypeOfValue>
void BinaryTree<TypeOfKey, TypeOfValue>::Clear() {
	HelpClear(root);
}

template<typename TypeOfKey, typename TypeOfValue>
BinaryTree<TypeOfKey, TypeOfValue>::~BinaryTree() {
	HelpClear(root);
	root = nullptr;
	size = 0;
}