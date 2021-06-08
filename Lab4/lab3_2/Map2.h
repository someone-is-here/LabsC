#pragma once
#include "Node.h"
#include "Header.h"

template<typename TypeOfKey, typename TypeOfValue>
class Map2: public Map<TypeOfKey,TypeOfValue> {
public:
	IteratorForMap2<TypeOfKey, TypeOfValue> begin();
	IteratorForMap2<TypeOfKey, TypeOfValue> end();
};

template<typename TypeOfKey, typename TypeOfValue>
IteratorForMap2<TypeOfKey, TypeOfValue> Map2<TypeOfKey, TypeOfValue>::begin() {
	return IteratorForMap2<TypeOfKey, TypeOfValue>(this->Minimum(this->root), this);
}

template<typename TypeOfKey, typename TypeOfValue>
IteratorForMap2<TypeOfKey, TypeOfValue> Map2<TypeOfKey, TypeOfValue>::end() {
	return IteratorForMap2<TypeOfKey, TypeOfValue>(this->Maximum(this->root),this);
}
