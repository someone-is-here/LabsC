#pragma once
#include <iostream>
#include <iterator>
#include <initializer_list>
#include "Node.h"
#include <assert.h>

using namespace std;

template<typename T>

class IteratorForList : public iterator<bidirectional_iterator_tag, T> {
private:
	Node<T>* obj;
public:
	IteratorForList() : obj(nullptr) {};
	explicit IteratorForList(Node<T>* value) : obj(value) {};
	IteratorForList(const IteratorForList<T>& newIter) : obj(newIter.obj) {};

	Node<T>* operator->() {
		return obj;
	}

	IteratorForList<T>& operator++() {
		obj = obj->next;
		return *this;
	}
	IteratorForList<T>& operator--() {
		obj = obj->prev;		
		return *this;
	}
	IteratorForList<T> operator++(int) {
		IteratorForList<T> temp(obj);
		++(*this);
		return temp;
	}
	IteratorForList<T> operator--(int) {
		IteratorForList<T> temp(obj);
		--(*this);
		return temp;
	}
	IteratorForList<T> operator[](int index) {
		IteratorForList<T> temp(obj);
		temp = temp + index;
		return IteratorForList<T>(temp);
	}
	friend IteratorForList<T> operator+(int num, const IteratorForList<T>& iter) {
		return IteratorForList<T>(iter + num);
	}
	friend IteratorForList<T> operator-(int num, const IteratorForList<T>& iter) {
		return IteratorForList<T>(iter - num);
	}
	friend IteratorForList<T> operator-(const IteratorForList<T>& iter, int num) {
		IteratorForList<T> temp(iter.obj);
		while (num > 0) {
			if (temp.obj->prev != NULL) {
				temp.obj = temp.obj->prev;
			}
			else {
				assert(temp.obj->prev == NULL);
			}
			num--;
		}
		return IteratorForList<T>(temp.obj);
		
	}
	friend IteratorForList<T> operator+(const IteratorForList<T>& iter, int num) {
		IteratorForList<T> temp(iter.obj);
		while (num > 0) {
			if (temp.obj->next != NULL) {
				temp.obj = temp.obj->next;
			}
			else {
				assert(temp.obj->next == NULL);
			}
			num--;
		}
		return IteratorForList<T>(temp.obj);
	}
	friend int operator-(IteratorForList<T>& iter, IteratorForList<T>& iter1) {
		IteratorForList<T> temp1(iter.obj);
		IteratorForList<T> temp(iter1.obj);
		int counter = 0;
		while (temp.obj->next != nullptr) {
			if (temp.obj == temp1.obj) {
				break;
			}
			else {
				counter++;
				if (temp.obj->next != NULL) {
					temp.obj = temp.obj->next;
				}
			}
		}

		if (temp.obj != temp1.obj) {
			temp.obj = iter.obj;
			counter = 0;
			while (temp.obj != nullptr) {
				if (temp.obj == temp1.obj) {
					break;
				}
				else {
					counter++;
					if (temp.obj->prev != NULL) {
						temp.obj = temp.obj->prev;
					}

				}
			}
			counter = (-counter);
		}
		return counter;
	}

	T& operator*() {
		return obj->data;
	}

	T operator*() const {
		return obj->data;
	}
	bool operator==(const IteratorForList<T>& newIter) const {
		return obj == newIter.obj;
	}
	bool operator!=(const IteratorForList<T>& newIter) const {
		return obj != newIter.obj;
	}
	bool operator<(IteratorForList<T> obj1) {
		IteratorForList<T> temp(obj);
		if ((temp-obj1) < 0) {
			return true;
		}
		return false;
	}
	bool operator>(IteratorForList<T> obj1) {
		IteratorForList<T> temp(obj);
		if ((temp - obj1) > 0) {
			return true;
		}
		return false;
	}
	bool operator<=(IteratorForList<T> obj1) {
		IteratorForList<T> temp(obj);
		if ((temp - obj1) <= 0) {
			return true;
		}
		return false;
	}
	bool operator>=(IteratorForList<T> obj1) {
		IteratorForList<T> temp(obj);
		if ((temp - obj1) >= 0) {
			return true;
		}
		return false;
	}
	IteratorForList<T>& operator=(const IteratorForList<T>& newIt){
		if (this == &newIt) {
			return *this;
		}
		obj = newIt.obj;
		return *this;
	}
	~IteratorForList() {
		obj = NULL;
	}
};
