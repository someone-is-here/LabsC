#pragma once
#include "Map2.h"
#include "IteratorForSet2.h"

template<typename TypeOfKey>
class Set2 : public Map2<TypeOfKey, char> {
public:
	void Insert(TypeOfKey key);
	IteratorForSet2<TypeOfKey> begin();
	IteratorForSet2<TypeOfKey> end();
};

template<typename TypeOfKey>
void Set2<TypeOfKey>::Insert(TypeOfKey key) {
	Map2<TypeOfKey, char>::Insert(key, ' ');
}

template<typename TypeOfKey>
IteratorForSet2<TypeOfKey> Set2<TypeOfKey>::begin() {
	return IteratorForSet2<TypeOfKey>(this->Minimum(this->root), &(this->listWithNodes));
}

template<typename TypeOfKey>
IteratorForSet2<TypeOfKey> Set2<TypeOfKey>::end() {
	return IteratorForSet2<TypeOfKey>(this->Minimum(this->root), &(this->listWithNodes));
}
