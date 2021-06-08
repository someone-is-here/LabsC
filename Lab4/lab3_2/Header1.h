#pragma once
#include <cassert>
#include <iterator>
#include <list>
#include <initializer_list>
#include "Node.h"

template<typename TypeOfKey, typename TypeOfValue>
class Iterator : public std::iterator<std::bidirectional_iterator_tag, std::pair<TypeOfKey, TypeOfValue>> {
private:
	Node<TypeOfKey, TypeOfValue>* obj;
	std::list<Node<TypeOfKey, TypeOfValue>*>* listWithNodes;
public:
	Iterator() : obj(nullptr) {};
	Iterator(Node<TypeOfKey, TypeOfValue>* newObj, std::list<Node<TypeOfKey, TypeOfValue>*>* listWithNodes);
	Iterator(const Iterator<TypeOfKey, TypeOfValue>& newIter) : obj(newIter.obj), listWithNodes(newIter.listWithNodes) {};

	const Node<TypeOfKey, TypeOfValue>* operator->();
	const TypeOfKey& operator*();
	const TypeOfKey operator*() const;

	Iterator<TypeOfKey, TypeOfValue> operator++();
	Iterator<TypeOfKey, TypeOfValue> operator--();

	Iterator<TypeOfKey, TypeOfValue> operator++(int);
	Iterator<TypeOfKey, TypeOfValue> operator--(int);
	
	Iterator<TypeOfKey, TypeOfValue>& operator=(const Iterator<TypeOfKey, TypeOfValue>& newIt);
	bool operator==(const Iterator<TypeOfKey, TypeOfValue>& newIter) const;
	bool operator!=(const Iterator<TypeOfKey, TypeOfValue>& newIter) const;

	~Iterator();
};

template<typename TypeOfKey, typename TypeOfValue>
const Node<TypeOfKey, TypeOfValue>* Iterator<TypeOfKey, TypeOfValue>::operator->() {
	return obj;
}

template<typename TypeOfKey, typename TypeOfValue>
const TypeOfKey& Iterator<TypeOfKey, TypeOfValue>::operator*() {
	auto helpIter = listWithNodes->begin();
	for (auto iter = listWithNodes->begin(); iter != listWithNodes->end(); iter++) {
		if (obj == *iter) {
			return obj->data.first;
		}
		else if (obj->data.first > (*iter)->data.first) {
			helpIter = iter;
		}
	}
	obj = *helpIter;
	return (obj)->data.first;
}

template<typename TypeOfKey, typename TypeOfValue>
const TypeOfKey Iterator<TypeOfKey, TypeOfValue>::operator*() const {
	auto helpIter = listWithNodes->begin();
	for (auto iter = listWithNodes->begin(); iter != listWithNodes->end(); iter++) {
		if (obj == *iter) {
			return obj->data.first;
		}
		else if (obj->data.first > (*iter)->data.first) {
			helpIter = iter;
		}
	}
	obj = *helpIter;
	return (obj)->data.first;
}
template<typename TypeOfKey, typename TypeOfValue>
Iterator<TypeOfKey, TypeOfValue>::Iterator(Node<TypeOfKey, TypeOfValue>* newObj, std::list<Node<TypeOfKey, TypeOfValue>*>* listWithNodes) {
	obj = newObj;
	this->listWithNodes = listWithNodes;
}

template<typename TypeOfKey, typename TypeOfValue>
Iterator<TypeOfKey, TypeOfValue> Iterator<TypeOfKey, TypeOfValue>::operator++() {
	int index = 0;
	for (auto iter = listWithNodes->begin(); iter != listWithNodes->end(); iter++, index++) {
		if (obj == *iter) {
			if (index == listWithNodes->size() - 1) {
				obj = *(listWithNodes->begin());
			}
			else {
				obj = *(++iter);
			}
			break;
		}
	}
	return *this;
}

template<typename TypeOfKey, typename TypeOfValue>
Iterator<TypeOfKey, TypeOfValue> Iterator<TypeOfKey, TypeOfValue>::operator--() {
	int index = 0;
	for (auto iter = listWithNodes->begin(); iter != listWithNodes->end(); iter++, index++) {
		if (obj == *iter) {
			if (index == 0) {
				obj = *(--listWithNodes->end());
			}
			else {
				obj = *(--iter);
			}
			break;
		}
	}
	return *this;
}

template<typename TypeOfKey, typename TypeOfValue>
Iterator<TypeOfKey, TypeOfValue> Iterator<TypeOfKey, TypeOfValue>::operator++(int) {
	Iterator<TypeOfKey, TypeOfValue> temp(obj, listWithNodes);
	++(*this);
	return temp;
}

template<typename TypeOfKey, typename TypeOfValue>
Iterator<TypeOfKey, TypeOfValue> Iterator<TypeOfKey, TypeOfValue>::operator--(int) {
	Iterator<TypeOfKey, TypeOfValue> temp(obj, listWithNodes);
	--(*this);
	return temp;
}

template<typename TypeOfKey, typename TypeOfValue>
Iterator<TypeOfKey, TypeOfValue>& Iterator<TypeOfKey, TypeOfValue>::operator=(const Iterator<TypeOfKey, TypeOfValue>& newIt) {
	if (this == &newIt) {
		return *this;
	}
	obj = newIt.obj;
	listWithNodes = newIt.listWithNodes;
	return *this;
}

template<typename TypeOfKey, typename TypeOfValue>
bool Iterator<TypeOfKey, TypeOfValue>::operator==(const Iterator<TypeOfKey, TypeOfValue>& newIter) const {
	return obj == newIter.obj;
}

template<typename TypeOfKey, typename TypeOfValue>
bool Iterator<TypeOfKey, TypeOfValue>::operator!=(const Iterator<TypeOfKey, TypeOfValue>& newIter) const {
	return obj != newIter.obj;
}

template<typename TypeOfKey, typename TypeOfValue>
Iterator<TypeOfKey, TypeOfValue>::~Iterator() {
	listWithNodes = nullptr;
	obj = nullptr;
}
