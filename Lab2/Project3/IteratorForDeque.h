#pragma once
#include <iostream>
#include <iterator>

using namespace std;

template<typename T>
class IteratorForDeque : public std::iterator<std::bidirectional_iterator_tag, T> {
private:
	T* obj;
	T** container;
	size_t capacity;
	size_t capacityOfContainer;
	size_t containerNum;
	size_t k;
public:
	IteratorForDeque() : obj(nullptr), capacityOfContainer(0), containerNum(0),container(NULL), capacity(0), k(0) {};
	IteratorForDeque(T* value, size_t capacityOfContainer, size_t containerNum, T** container, size_t capacity, size_t k);
	IteratorForDeque(const IteratorForDeque<T>& newIter);

	T* operator->();
	T& operator*();
	T operator*() const;

	IteratorForDeque<T>& operator++();
	IteratorForDeque<T>& operator--();
	IteratorForDeque<T> operator++(int);
	IteratorForDeque<T> operator--(int);

	friend IteratorForDeque<T> operator+(int num, const IteratorForDeque<T>& iter) {
		IteratorForDeque<T> temp(iter.obj, iter.capacityOfContainer, iter.containerNum, iter.container, iter.capacity, iter.k);
		do {
			++temp;
		} while (--num != 0);
		return temp;
	}

	friend IteratorForDeque<T> operator+(const IteratorForDeque<T>& iter, int num) {
		IteratorForDeque<T> temp(iter.obj, iter.capacityOfContainer, iter.containerNum, iter.container, iter.capacity, iter.k);
		do {
			++temp;
		} while (--num != 0);
		return temp;
	}

	friend IteratorForDeque<T> operator-(int num, const IteratorForDeque<T>& iter) {
		IteratorForDeque<T> temp(iter.obj, iter.capacityOfContainer, iter.containerNum, iter.container, iter.capacity, iter.k);
		do {
			--temp;
		} while (--num != 0);
		return temp;
	}

	friend IteratorForDeque<T> operator-(const IteratorForDeque<T>& iter, int num) {
		IteratorForDeque<T> temp(iter.obj, iter.capacityOfContainer, iter.containerNum, iter.container, iter.capacity, iter.k);
		do {
			--temp;
		} while (--num != 0);
		return temp;
	}

	IteratorForDeque<T>& operator-=(int num);
	IteratorForDeque<T>& operator+=(int num);

	bool operator==(const IteratorForDeque<T>& newIter) const;
	bool operator!=(const IteratorForDeque<T>& newIter) const;

	bool operator<(IteratorForDeque<T> iter);
	bool operator>(IteratorForDeque<T> iter);
	bool operator<=(IteratorForDeque<T> iter);
	bool operator>=(IteratorForDeque<T> iter);

	int operator-(IteratorForDeque<T>& iter);
	IteratorForDeque<T> operator[](int index);
	IteratorForDeque<T>& operator=(const IteratorForDeque<T>& newIter);

	~IteratorForDeque();
};

template<typename T>
IteratorForDeque<T>::IteratorForDeque(T* value, size_t capacityOfContainer, size_t containerNum, T** container, size_t capacity, size_t k) {
	this->obj = value;
	this->capacityOfContainer = capacityOfContainer;
	this->containerNum = containerNum;
	this->container = container;
	this->capacity = capacity;
	this->k = k;
}

template<typename T>
IteratorForDeque<T>::IteratorForDeque(const IteratorForDeque<T>& newIter) {
	obj = newIter.obj;
	capacityOfContainer = newIter.capacityOfContainer;
	containerNum = newIter.containerNum;
	container = newIter.container;
	capacity = newIter.capacity;
	k = newIter.k;
}

template<typename T>
T* IteratorForDeque<T>::operator->() {
	return obj;
}

template<typename T>
T& IteratorForDeque<T>::operator*() {
	return *obj;
}

template<typename T>
T IteratorForDeque<T>::operator*() const {
	return *obj;
}

template<typename T>
IteratorForDeque<T>& IteratorForDeque<T>::operator++() {
	if (--capacityOfContainer == 0) {
		if (containerNum == capacity - 1) {
			containerNum = 0;
			obj = container[containerNum];
		}
		else {
			obj = container[++containerNum];
		}
		capacityOfContainer = k;
	}
	else {
		obj++;
	}
	return *this;
}

template<typename T>
IteratorForDeque<T>& IteratorForDeque<T>::operator--() {
	if (capacityOfContainer == k) {
		if (containerNum == 0) {
			containerNum = capacity - 1;
			obj = container[containerNum] + (k - 1);
		}
		else {
			obj = container[--containerNum] + (k - 1);
		}
		capacityOfContainer = 1;
	}
	else {
		capacityOfContainer++;
		obj--;
	}
	return *this;
}

template<typename T>
IteratorForDeque<T> IteratorForDeque<T>::operator++(int) {
	IteratorForDeque<T> temp(obj, capacityOfContainer, containerNum, container, capacity, k);
	++(*this);
	return temp;
}

template<typename T>
IteratorForDeque<T> IteratorForDeque<T>::operator--(int) {
	IteratorForDeque<T> temp(obj, capacityOfContainer, containerNum, container, capacity, k);
	--(*this);
	return temp;
}


template<typename T>
IteratorForDeque<T>& IteratorForDeque<T>::operator-=(int num) {
	do {
		--obj;
	} while (--num != 0);
	return *this;
}

template<typename T>
IteratorForDeque<T>& IteratorForDeque<T>::operator+=(int num) {
	do {
		++obj;
	} while (--num != 0);
	return *this;
}

template<typename T>
bool IteratorForDeque<T>::operator<(IteratorForDeque<T> iter) {
	if (containerNum < iter.containerNum) {
		return true;
	}
	else if (containerNum == iter.containerNum && capacityOfContainer > iter.capacityOfContainer) {
		return true;
	}
	return false;
}

template<typename T>
bool IteratorForDeque<T>::operator>(IteratorForDeque<T> iter) {
	if (containerNum > iter.containerNum) {
		return true;
	}
	else if (containerNum == iter.containerNum && capacityOfContainer < iter.capacityOfContainer) {
		return true;
	}
	return false;
}

template<typename T>
bool IteratorForDeque<T>::operator<=(IteratorForDeque<T> iter) {
	if (containerNum < iter.containerNum) {
		return true;
	}
	else if (containerNum == iter.containerNum && capacityOfContainer >= iter.capacityOfContainer) {
		return true;
	}
	return false;
}

template<typename T>
bool IteratorForDeque<T>::operator>=(IteratorForDeque<T> iter) {
	if (containerNum > iter.containerNum) {
		return true;
	}
	else if (containerNum == iter.containerNum && capacityOfContainer <= iter.capacityOfContainer) {
		return true;
	}
	return false;
}

template<typename T>
int IteratorForDeque<T>::operator-(IteratorForDeque<T>& iter) {
	int res = -1;
	IteratorForDeque<T> temp(iter.obj, iter.capacityOfContainer, iter.containerNum, iter.container, iter.capacity, iter.k);
	while (temp.obj != obj) {
		++temp;
		res++;
	}
	return res + 1;
}

template<typename T>
IteratorForDeque<T> IteratorForDeque<T>::operator[](int index) {
	IteratorForDeque<T> temp(obj, capacityOfContainer, containerNum, container, capacity, k);
	do {
		++temp;
	} while (--index > 0);
	return IteratorForDeque<T>(temp.obj, temp.capacityOfContainer, temp.containerNum, temp.container, temp.capacity, temp.k);
}

template<typename T>
IteratorForDeque<T>& IteratorForDeque<T>::operator=(const IteratorForDeque<T>& newIter) {
	if (this == &newIter) {
		return *this;
	}
	obj = newIter.obj;
	capacityOfContainer = newIter.capacityOfContainer;
	containerNum = newIter.containerNum;
	container = newIter.container;
	capacity = newIter.capacity;
	k = newIter.k;
	return *this;
}

template<typename T>
bool IteratorForDeque<T>::operator==(const IteratorForDeque<T>& newIter) const {
	return obj == newIter.obj;
}

template<typename T>
bool IteratorForDeque<T>::operator!=(const IteratorForDeque<T>& newIter) const {
	return obj != newIter.obj;
}

template<typename T>
IteratorForDeque<T>::~IteratorForDeque() {
	container = NULL;
	capacity = 0;
	capacityOfContainer = 0;
	containerNum = 0;
	k = 0;
	obj = NULL;
}
