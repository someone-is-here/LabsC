#pragma once
#include <cassert>
#include <iterator>
#include <initializer_list>
#include "Map2.h"

template<typename TypeOfKey, typename TypeOfValue>
class IteratorForMap2 : public std::iterator<std::bidirectional_iterator_tag, std::pair<const TypeOfKey, TypeOfValue>> {
private:
	Node<TypeOfKey, TypeOfValue>* obj;
	Map<TypeOfKey, TypeOfValue>* mapCopy;
public:
	IteratorForMap2() : obj(nullptr), mapCopy(nullptr) {}
	IteratorForMap2(Node<TypeOfKey, TypeOfValue>* newObj, Map<TypeOfKey, TypeOfValue>* mapCopy) : obj(newObj), mapCopy(mapCopy) {}
	IteratorForMap2(const IteratorForMap2<TypeOfKey, TypeOfValue>& newIter) : obj(newIter.obj), mapCopy(newIter.mapCopy) {}

	const Node<TypeOfKey, TypeOfValue>* operator->();
	const TypeOfKey& operator*();
	const TypeOfKey operator*() const;

	IteratorForMap2<TypeOfKey, TypeOfValue> operator++();
	IteratorForMap2<TypeOfKey, TypeOfValue> operator--();

	IteratorForMap2<TypeOfKey, TypeOfValue> operator++(int);
	IteratorForMap2<TypeOfKey, TypeOfValue> operator--(int);
	
	IteratorForMap2<TypeOfKey, TypeOfValue>& operator=(const IteratorForMap2<TypeOfKey, TypeOfValue>& newIt);
	bool operator==(const IteratorForMap2<TypeOfKey, TypeOfValue>& newIter) const;
	bool operator!=(const IteratorForMap2<TypeOfKey, TypeOfValue>& newIter) const;
	~IteratorForMap2();
};

template<typename TypeOfKey, typename TypeOfValue>
const Node<TypeOfKey, TypeOfValue>* IteratorForMap2<TypeOfKey, TypeOfValue>::operator->() {
	return obj;
}

template<typename TypeOfKey, typename TypeOfValue>
const TypeOfKey& IteratorForMap2<TypeOfKey, TypeOfValue>::operator*() {
	return obj->data.first;
}

template<typename TypeOfKey, typename TypeOfValue>
const TypeOfKey IteratorForMap2<TypeOfKey, TypeOfValue>::operator*() const {
	return obj->data.first;
}

template<typename TypeOfKey, typename TypeOfValue>
IteratorForMap2<TypeOfKey, TypeOfValue> IteratorForMap2<TypeOfKey, TypeOfValue>::operator++() {
	obj = mapCopy->FindNextNode(obj->data.first);
	return *this;
}

template<typename TypeOfKey, typename TypeOfValue>
IteratorForMap2<TypeOfKey, TypeOfValue> IteratorForMap2<TypeOfKey, TypeOfValue>::operator--() {
	obj = mapCopy->FindPreviousNode(obj->data.first);
	return *this;
}


template<typename TypeOfKey, typename TypeOfValue>
IteratorForMap2<TypeOfKey, TypeOfValue> IteratorForMap2<TypeOfKey, TypeOfValue>::operator++(int) {
	IteratorForMap2<TypeOfKey, TypeOfValue> temp(obj, mapCopy);
	++(*this);
	return temp;
}

template<typename TypeOfKey, typename TypeOfValue>
IteratorForMap2<TypeOfKey, TypeOfValue> IteratorForMap2<TypeOfKey, TypeOfValue>::operator--(int) {
	IteratorForMap2<TypeOfKey, TypeOfValue> temp(obj, mapCopy);
	--(*this);
	return temp;
}

template<typename TypeOfKey, typename TypeOfValue>
IteratorForMap2<TypeOfKey, TypeOfValue>& IteratorForMap2<TypeOfKey, TypeOfValue>::operator=(const IteratorForMap2<TypeOfKey, TypeOfValue>& newIt) {
	if (this == &newIt) {
		return *this;
	}
	obj = newIt.obj;
	mapCopy = newIt.mapCopy;
	return *this;
}

template<typename TypeOfKey, typename TypeOfValue>
bool IteratorForMap2<TypeOfKey, TypeOfValue>::operator==(const IteratorForMap2<TypeOfKey, TypeOfValue>& newIter) const {
	return obj == newIter.obj;
}

template<typename TypeOfKey, typename TypeOfValue>
bool IteratorForMap2<TypeOfKey, TypeOfValue>::operator!=(const IteratorForMap2<TypeOfKey, TypeOfValue>& newIter) const {
	return obj != newIter.obj;
}

template<typename TypeOfKey, typename TypeOfValue>
IteratorForMap2<TypeOfKey, TypeOfValue>::~IteratorForMap2() {
	mapCopy = nullptr;
	obj = nullptr;
}

