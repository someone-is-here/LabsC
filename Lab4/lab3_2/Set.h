#pragma once
#include "Map2.h"
#include "IteratorForSet.h"

template<typename TypeOfKey>
class Set : public Map2<TypeOfKey, char> {
public:
	void Insert(TypeOfKey key);
	IteratorForSet<TypeOfKey> begin();
	IteratorForSet<TypeOfKey> end();
};
template<typename TypeOfKey>
void Set<TypeOfKey>::Insert(TypeOfKey key){
	Map<TypeOfKey, char>::Insert(key, ' ');
}
template<typename TypeOfKey>
IteratorForSet<TypeOfKey> Set<TypeOfKey>::begin() {
	return IteratorForSet<TypeOfKey>(this->Minimum(this->root), this);
}

template<typename TypeOfKey>
IteratorForSet<TypeOfKey> Set<TypeOfKey>::end() {
	return IteratorForSet<TypeOfKey>(this->Minimum(this->root), this);
}