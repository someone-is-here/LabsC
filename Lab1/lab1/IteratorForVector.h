#pragma once
#include <iostream>
#include <cassert>
#include <iterator>
#include <initializer_list>

using namespace std;

template<typename T>

class IteratorForVector : public std::iterator<std::bidirectional_iterator_tag, T> {
private:
	T* obj;
public:
	IteratorForVector() : obj(nullptr) {};
	explicit IteratorForVector(T* value) : obj(value) {};
	IteratorForVector(const IteratorForVector<T>& newIter) : obj(newIter.obj) {};

	T* operator->() {
		return obj;
	}

	IteratorForVector<T>& operator++() {
		obj++;
		return *this;
	}

	IteratorForVector<T>& operator--() {
		obj--;
		return *this;
	}
	IteratorForVector<T> operator++(int) {
		IteratorForVector<T> temp(obj);
		++(*this);
		return temp;
	}
	IteratorForVector<T> operator--(int) {
		IteratorForVector<T> temp(obj);
		--(*this);
		return temp;
	}
	friend IteratorForVector<T> operator+(int num, const IteratorForVector<T>& iter) {
		return IteratorForVector<T>(iter.obj + num);
	}
	friend IteratorForVector<T> operator+(const IteratorForVector<T>& iter,int num) {
		return IteratorForVector<T>(iter.obj + num);
	}
	friend IteratorForVector<T> operator-(int num, const IteratorForVector<T>& iter) {
		return IteratorForVector<T>(iter.obj - num);
	}
	friend IteratorForVector<T> operator-(const IteratorForVector<T>& iter, int num) {
		return IteratorForVector<T>(iter.obj - num);
	}
	int operator-(IteratorForVector<T>& iter) {
		return obj - iter.obj;
	}
	IteratorForVector<T>& operator-=(int num) {
		obj -= num;
		return *this;
	}
	IteratorForVector<T>& operator+=(int num) {
		obj += num;
		return *this;
	}
	T& operator*() {
		return *obj;
	}
	T operator*() const {
		return *obj;
	}
	IteratorForVector<T> operator[](int index) {
		return IteratorForVector<T>(obj + index);
	}
	bool operator<(IteratorForVector<T> obj1) {
		return obj < obj1.obj;
	}
	bool operator>(IteratorForVector<T> obj1) {
		return obj > obj1.obj;
	}
	bool operator<=(IteratorForVector<T> obj1) {
		return obj <= obj1.obj;
	}
	bool operator>=(IteratorForVector<T> obj1) {
		return obj >= obj1.obj;
	}
	bool operator==(const IteratorForVector<T>& newIter) const {
		return obj == newIter.obj;
	}
	bool operator!=(const IteratorForVector<T>& newIter) const {
		return obj != newIter.obj;
	}
	IteratorForVector<T>& operator=(const IteratorForVector<T>& newIt) {
		if (this == &newIt) {
			return *this;
		}
		obj = newIt.obj;
		return *this;
	}
	~IteratorForVector() {
		obj = NULL;
	}
};
