#pragma once
#include <iostream>
#include <assert.h>
#include "IteratorForDeque.h"

template<typename T>
class Deque{
private:
	size_t capacity;
	size_t size;
	int k;
	T** container = NULL;
	T* beginDec;
	T* endDec;
	size_t containerWithBeginNum;
	size_t containerWithEndNum;
	size_t containerBeginCapacity;
	size_t containerEndCapacity;
public:
	Deque();
	Deque(size_t);
	Deque(const Deque<T>& obj);
	IteratorForDeque<T> begin();
	IteratorForDeque<T> end();
	bool Empty();
	size_t Size() const;
	int GetK()const;
	void Resize();
	void Clear();
	void Show();
	void PushBack(T value);
	T PopBack();
	void PushFront(T value);
	T PopFront();
	T& operator[](int index) const;
	Deque<T>& operator=(const Deque<T>& newDec);
	friend ostream& operator<<(ostream& out, const Deque<T>& obj) {
		for (int i = 0; i < obj.size; i++) {
			out << obj[i] << " ";
		}
		out << endl;
		return out;
	}
	~Deque();
};

template<typename T>
Deque<T>::Deque() {
	size = 1;
	k = 10;
	capacity = size * 3;
	container = new T * [capacity];
	for (int i = 0; i < capacity; i++) {
		*(container + i) = new T[k];
	}
	size = 0;
	containerBeginCapacity = k;
	containerEndCapacity = k;
	containerWithBeginNum = 0;
	beginDec = container[containerWithBeginNum];
	containerWithEndNum = 0;
	endDec = container[containerWithEndNum];
}

template<typename T>
Deque<T>::Deque(size_t size) {
	this->size = size;
	k = 10;
	capacity = size * 3;
	container = new T * [capacity];
	for (int i = 0; i < capacity; i++) {
		*(container + i) = new T[k];
	}
	size = 0;
	containerBeginCapacity = k;
	containerEndCapacity = k;
	containerWithBeginNum = 0;
	beginDec = container[containerWithBeginNum];
	containerWithEndNum = 0;
	endDec = container[containerWithEndNum];
}

template<typename T>
Deque<T>::Deque(const Deque<T>& obj) {
	size = obj.size;
	capacity = obj.capacity;
	k = obj.k;
	container = obj.container;
	for (int i = 0; i < capacity; i++) {
		container[i] = obj.container[i];
	}
	containerBeginCapacity = obj.containerBeginCapacity;
	containerEndCapacity = obj.containerEndCapacity;
	containerWithBeginNum = obj.containerWithBeginNum;
	containerWithEndNum = obj.containerWithEndNum;
	beginDec = obj.beginDec;
	endDec = obj.endDec;
}

template<typename T>
IteratorForDeque<T> Deque<T>::begin() {
	return IteratorForDeque<T>(beginDec,containerBeginCapacity,containerWithBeginNum,container,capacity,k);
}

template<typename T>
IteratorForDeque<T> Deque<T>::end() {
	return IteratorForDeque<T>(endDec,containerEndCapacity,containerWithEndNum,container,capacity,k);
}

template<typename T>
bool Deque<T>::Empty() {
	return (size == 0) ? true : false;
}

template<typename T>
size_t Deque<T>::Size() const {
	return size;
}

template<typename T>
int Deque<T>::GetK()const {
	return k;
}

template<typename T>
void Deque<T>::Resize() {
	capacity *= 3;
	T** newContainer = new T * [capacity];
	for (int i = 0; i < capacity; i++) {
		newContainer[i] = container[i];
	}
	delete[] container;
	container = new T * [capacity];
	for (int i = 0; i < containerWithEndNum; i++) {
		container[i] = newContainer[i];
	}
	for (int i = capacity - (capacity / 3 - containerWithBeginNum); i < capacity; i++) {
		container[i] = newContainer[i];
	}
	for (int i = containerWithEndNum; i < capacity - (capacity / 3 - containerWithBeginNum); i++) {
		*(container + i) = new T[k];
	}
	delete[] newContainer;
	newContainer = NULL;
	beginDec = container[capacity - (capacity / 3 - containerWithBeginNum)];
	containerWithBeginNum = capacity - (capacity / 3 - containerWithBeginNum);
	endDec = container[containerWithEndNum];
}

template<typename T>
void Deque<T>::Clear() {
	for (int i = 0; i < capacity; i++) {
		for (int j = 0; j < k; j++) {
			container[i][j] = 0;
		}
	}
	size = 0;
	containerBeginCapacity = k;
	containerEndCapacity = k;
	containerWithBeginNum = 0;
	beginDec = container[containerWithBeginNum];
	endDec = container[containerWithEndNum];
	containerWithEndNum = 0;
}

template<typename T>
void Deque<T>::PushBack(T value) {
	size++;
	*endDec = value;
	if (--containerEndCapacity == 0) {
		if (containerWithEndNum + 1 == containerWithBeginNum) {
			Resize();
		}
		endDec = container[++containerWithEndNum];
		containerEndCapacity = k;
	}
	else {
		endDec++;
	}
}

template<typename T>
T Deque<T>::PopBack() {
	T value = -1;
	if (!size) {
		assert(size == 0);
	}
	else {
		if (containerEndCapacity == k) {
			if (containerWithEndNum == 0) {
				endDec = container[capacity - 1] + (k - 1);
				containerWithEndNum = capacity - 1;
			}
			else {
				endDec = container[--containerWithEndNum] + (k - 1);
			}
			value = *(endDec);
			*(endDec) = 0;
			size--;
			containerEndCapacity = 1;
		}
		else {
			endDec--;
			value = *(endDec);
			*(endDec) = 0;
			size--;
			containerEndCapacity++;
		}
	}
	return value;
}

template<typename T>
void Deque<T>::PushFront(T value) {
	if (beginDec == container[containerWithBeginNum] && containerWithBeginNum == 0) {
		containerWithBeginNum = capacity;
		beginDec = container[containerWithBeginNum] + (k - 1);
	}
	if (--containerBeginCapacity == 0) {
		size++;
		beginDec--;
		*beginDec = value;
		containerBeginCapacity = k;
	}
	else if (containerBeginCapacity == k - 1) {
		if (containerWithBeginNum - 1 == containerWithEndNum) {
			Resize();
		}
		beginDec = container[--containerWithBeginNum] + (k - 1);
		size++;
		*beginDec = value;
	}
	else {
		beginDec--;
		size++;
		*beginDec = value;
	}
}

template<typename T>
T Deque<T>::PopFront() {
	T value = NULL;
	if (!size) {
		assert(size == 0);
	}
	else {
		if (containerBeginCapacity == k) {
			value = *beginDec;
			*beginDec = 0;
			beginDec++;
			size--;
			containerBeginCapacity = 1;
		}
		else {
			value = *beginDec;
			*beginDec = 0;
			if (containerBeginCapacity + 1 == k) {
				if (containerWithBeginNum + 1 == capacity) {
					containerWithBeginNum = 0;
					beginDec = container[containerWithBeginNum];
				}
				else {
					beginDec = container[++containerWithBeginNum];
				}
			}
			else {
				beginDec++;
			}
			size--;
			containerBeginCapacity++;
		}
	}
	return value;
}

template<typename T>
T& Deque<T>::operator[](int index) const {
	if (index > size - 1) {
		assert(index > size - 1);
	}
	else {
		if (index % k - (k - containerBeginCapacity) < 0) {
			return container[(index / k + containerWithBeginNum) % capacity][index % k - (k - containerBeginCapacity) + k];
		}
		else if (index % k - (k - containerBeginCapacity) < 0) {
			return container[(index / k + containerWithBeginNum) % capacity][index % k - (k - containerBeginCapacity) + k];
		}
	}
	return container[(index / k + containerWithBeginNum) % capacity][index % k - (k - containerBeginCapacity)];
}

template<typename T>
void Deque<T>::Show() {
	cout << "Capacity: " << capacity << endl;
	cout << "Size: " << size << endl;
	cout << "k: " << k << endl;
	cout << "beginNum: " << containerWithBeginNum << endl;
	cout << "endNum: " << containerWithEndNum << endl;
	cout << "begin capacity: " << containerBeginCapacity << endl;
	cout << "end capacity: " << containerEndCapacity << endl;

	int counter = 0;
	for (int i = 0; i < capacity; i++) {
		cout << "Container: ";
		for (int j = 0; j < k; j++) {
			cout << container[i][j] << " ";
		}
		cout << endl;
	}
}

template<typename T>
Deque<T>& Deque<T>::operator=(const Deque<T>& newDec) {
	if (this == &newDec) {
		return *this;
	}
	size = newDec.size;
	capacity = newDec.capacity;
	k = newDec.k;
	container = newDec.container;
	for (int i = 0; i < capacity; i++) {
		container[i] = newDec.container[i];
	}
	containerBeginCapacity = newDec.containerBeginCapacity;
	containerEndCapacity = newDec.containerEndCapacity;
	containerWithBeginNum = newDec.containerWithBeginNum;
	containerWithEndNum = newDec.containerWithEndNum;
	beginDec = newDec.beginDec;
	endDec = newDec.endDec;
	return *this;
}

template<typename T>
Deque<T>::~Deque() {
	for (int i = 0; i < capacity; i++) {
		delete[] container[i];
	}
	delete[] container;
	container = NULL;
	beginDec = NULL;
	containerWithBeginNum = NULL;
	containerWithEndNum = NULL;
	containerBeginCapacity = 0;
	containerEndCapacity = 0;
	endDec = NULL;
	capacity = 0;
	size = 0;
	k = 0;
}
