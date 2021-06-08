#pragma once
#include <iostream>
#include <assert.h>

template<typename TypeOfKey, typename TypeOfValue>
class Node {
public:
	std::pair<const TypeOfKey, TypeOfValue> data;
	Node<TypeOfKey, TypeOfValue>* left;
	Node<TypeOfKey, TypeOfValue>* right;
	Node(const TypeOfKey& key, TypeOfValue value, Node<TypeOfKey, TypeOfValue>* left, Node<TypeOfKey, TypeOfValue>* right) :
		data(key, value), right(right), left(left)
	{};
	Node(const Node<const TypeOfKey, TypeOfValue>& obj);
	Node<TypeOfKey, TypeOfValue>& operator= (const Node<TypeOfKey, TypeOfValue>& NodeObj);
	~Node();
};

template<typename TypeOfKey, typename TypeOfValue>
Node<TypeOfKey, TypeOfValue>& Node<TypeOfKey, TypeOfValue>::operator=(const Node<TypeOfKey, TypeOfValue>& NodeObj) {
	this.data.first = NodeObj->data.first;
	this.data.second = NodeObj->data.second;
	this.left = NodeObj->left;
	this.right = NodeObj->right;
	return *this;
}

template<typename TypeOfKey, typename TypeOfValue>
Node<TypeOfKey, TypeOfValue>::Node(const Node<const TypeOfKey, TypeOfValue>& obj) {
	data.first = obj.data.first;
	data.second = obj.data.second;
	left = obj.left;
	right = obj.right;
}

template<typename TypeOfKey, typename TypeOfValue>
Node<TypeOfKey,TypeOfValue>::~Node() {
	left = nullptr;
	right = nullptr;
}