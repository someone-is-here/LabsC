#pragma once
#include <cassert>
#include <iterator>
#include <list>
#include <initializer_list>
#include "Node.h"
#include "Map.h"

template<typename TypeOfKey>
class IteratorForSet {
private:
	Node<TypeOfKey, char>* obj;
	Map<TypeOfKey, char>* copySet;
public:
	IteratorForSet() : obj(nullptr) {};
	IteratorForSet(Node<TypeOfKey, char>* newObj,Map<TypeOfKey, char>* set) : obj(newObj), copySet(set) {};
	IteratorForSet(const IteratorForSet<TypeOfKey>& newIter) : obj(newIter.obj), copySet(newIter.copySet) {};

	const Node<TypeOfKey, char>* operator->();
	const TypeOfKey& operator*();
	const TypeOfKey operator*() const;

	IteratorForSet<TypeOfKey> operator++();
	IteratorForSet<TypeOfKey> operator--();

	IteratorForSet<TypeOfKey> operator++(int);
	IteratorForSet<TypeOfKey> operator--(int);

	IteratorForSet<TypeOfKey>& operator=(const IteratorForSet<TypeOfKey>& newIt);
	bool operator==(const IteratorForSet<TypeOfKey>& newIter) const;
	bool operator!=(const IteratorForSet<TypeOfKey>& newIter) const;
	~IteratorForSet();
};

template<typename TypeOfKey>
const Node<TypeOfKey, char>* IteratorForSet<TypeOfKey>::operator->() {
	return obj;
}

template<typename TypeOfKey>
const TypeOfKey& IteratorForSet<TypeOfKey>::operator*() {
	return obj->data.first;
}

template<typename TypeOfKey>
const TypeOfKey IteratorForSet<TypeOfKey>::operator*() const {
	return obj->data.first;
}

template<typename TypeOfKey>
IteratorForSet<TypeOfKey> IteratorForSet<TypeOfKey>::operator++() {
	if (obj == copySet->FindNextNode(obj->data.first)){
		obj = copySet->Minimum(copySet->GetRoot());
	}
	else {
		obj = copySet->FindNextNode(obj->data.first);
	}
	
	return *this;
}

template<typename TypeOfKey>
IteratorForSet<TypeOfKey> IteratorForSet<TypeOfKey>::operator--() {
	if (obj == copySet->FindPreviousNode(obj->data.first)) {
		obj = copySet->Maximum(copySet->GetRoot());
	}
	else {
		obj = copySet->FindPreviousNode(obj->data.first);
	}
	return *this;
}

template<typename TypeOfKey>
IteratorForSet<TypeOfKey> IteratorForSet<TypeOfKey>::operator++(int) {
	IteratorForSet<TypeOfKey> temp(obj, copySet);
	++(*this);
	return temp;
}

template<typename TypeOfKey>
IteratorForSet<TypeOfKey> IteratorForSet<TypeOfKey>::operator--(int) {
	IteratorForSet<TypeOfKey> temp(obj, copySet);
	--(*this);
	return temp;
}

template<typename TypeOfKey>
IteratorForSet<TypeOfKey>& IteratorForSet<TypeOfKey>::operator=(const IteratorForSet<TypeOfKey>& newIt) {
	if (this == &newIt) {
		return *this;
	}
	obj = newIt.obj;
	obj = newIt.copySet;
	return *this;
}

template<typename TypeOfKey>
bool IteratorForSet<TypeOfKey>::operator==(const IteratorForSet<TypeOfKey>& newIter) const {
	return obj == newIter.obj;
}

template<typename TypeOfKey>
bool IteratorForSet<TypeOfKey>::operator!=(const IteratorForSet<TypeOfKey>& newIter) const {
	return obj != newIter.obj;
}

template<typename TypeOfKey>
IteratorForSet<TypeOfKey>::~IteratorForSet() {
	copySet = nullptr;
	obj = nullptr;
}
