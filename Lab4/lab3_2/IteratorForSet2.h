#pragma once
#include <cassert>
#include <iterator>
#include <list>
#include <initializer_list>
#include "Node.h"

template<typename TypeOfKey>
class IteratorForSet2 : public std::iterator<std::bidirectional_iterator_tag, std::pair<TypeOfKey, char>> {
private:
	Node<TypeOfKey, char>* obj;
	std::list<Node<TypeOfKey, char>*>* listWithNodes;
public:
	IteratorForSet2() : obj(nullptr) {};
	IteratorForSet2(Node<TypeOfKey, char>* newObj, std::list<Node<TypeOfKey, char>*>* listWithNodes);
	IteratorForSet2(const IteratorForSet2<TypeOfKey>& newIter) : obj(newIter.obj), listWithNodes(newIter.listWithNodes) {};

	const Node<TypeOfKey, char>* operator->();
	const TypeOfKey& operator*();
	const TypeOfKey operator*() const;

	IteratorForSet2<TypeOfKey> operator++();
	IteratorForSet2<TypeOfKey> operator--();

	IteratorForSet2<TypeOfKey> operator++(int);
	IteratorForSet2<TypeOfKey> operator--(int);

	IteratorForSet2<TypeOfKey>& operator=(const IteratorForSet2<TypeOfKey>& newIt);
	bool operator==(const IteratorForSet2<TypeOfKey>& newIter) const;
	bool operator!=(const IteratorForSet2<TypeOfKey>& newIter) const;
	~IteratorForSet2();
};

template<typename TypeOfKey>
const Node<TypeOfKey, char>* IteratorForSet2<TypeOfKey>::operator->() {
	return obj;
}

template<typename TypeOfKey>
const TypeOfKey& IteratorForSet2<TypeOfKey>::operator*() {
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

template<typename TypeOfKey>
const TypeOfKey IteratorForSet2<TypeOfKey>::operator*() const {
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
template<typename TypeOfKey>
IteratorForSet2<TypeOfKey>::IteratorForSet2(Node<TypeOfKey, char>* newObj, std::list<Node<TypeOfKey, char>*>* listWithNodes) {
	obj = newObj;
	this->listWithNodes = listWithNodes;
}

template<typename TypeOfKey>
IteratorForSet2<TypeOfKey> IteratorForSet2<TypeOfKey>::operator++() {
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

template<typename TypeOfKey>
IteratorForSet2<TypeOfKey> IteratorForSet2<TypeOfKey>::operator--() {
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

template<typename TypeOfKey>
IteratorForSet2<TypeOfKey> IteratorForSet2<TypeOfKey>::operator++(int) {
	IteratorForSet2<TypeOfKey> temp(obj, listWithNodes);
	++(*this);
	return temp;
}

template<typename TypeOfKey>
IteratorForSet2<TypeOfKey> IteratorForSet2<TypeOfKey>::operator--(int) {
	IteratorForSet2<TypeOfKey> temp(obj, listWithNodes);
	--(*this);
	return temp;
}

template<typename TypeOfKey>
IteratorForSet2<TypeOfKey>& IteratorForSet2<TypeOfKey>::operator=(const IteratorForSet2<TypeOfKey>& newIt) {
	if (this == &newIt) {
		return *this;
	}
	obj = newIt.obj;
	listWithNodes = newIt.listWithNodes;
	return *this;
}

template<typename TypeOfKey>
bool IteratorForSet2<TypeOfKey>::operator==(const IteratorForSet2<TypeOfKey>& newIter) const {
	return obj == newIter.obj;
}

template<typename TypeOfKey>
bool IteratorForSet2<TypeOfKey>::operator!=(const IteratorForSet2<TypeOfKey>& newIter) const {
	return obj != newIter.obj;
}

template<typename TypeOfKey>
IteratorForSet2<TypeOfKey>::~IteratorForSet2() {
	listWithNodes = nullptr;
	obj = nullptr;
}
