#pragma once
#include "IteratorForVector.h"

template <typename T>
class Vector {
private:
	T* arr = NULL;
	size_t vectSize = 0;
	int memorySize = 0;
public:
	Vector() {};
	Vector(int newSize){
		memorySize = newSize * 2;
		vectSize = newSize;
		arr = new T[memorySize];
		for (int i = 0; i < vectSize; i++) {
			arr[i] = 0;
		}
	}
	IteratorForVector<T> begin() {
		return IteratorForVector<T>(arr);
	}
	IteratorForVector<T> end() {
		return IteratorForVector<T>(&arr[vectSize]);
	}
	Vector(const initializer_list<T>& list): Vector(list.size()) {
		int i = 0;
		for (auto& val : list){
			arr[i] = val;
			i++;
		}
	}
	Vector<T>& operator=(initializer_list<T>& list){
		if (list.size() != static_cast<size_t>(vectSize)){
			delete[] arr;
			vectSize = list.size();
			memorySize = list.size();
			arr = new T[vectSize];
		}
		int i = 0;
		for (auto& val : list) {
			arr[i] = val;
			i++;
		}
		return *this;
	}
	Vector(const Vector<T>& obj) {
		vectSize = obj.vectSize;
		memorySize = obj.memorySize;
		arr = new T[memorySize];
		for (int i = 0; i < vectSize; i++) {
			arr[i] = obj.arr[i];
		}
	}
	void Resize(int newSize) {
		MoreMemory(newSize);
		vectSize = newSize;
	}
	int Size(){
		return vectSize;
	}
	bool Empty() {
		return !vectSize;
	}
	void MoreMemory(size_t newSize = 0) {
		if (!newSize) {
			memorySize++;
			T* newArr = new T[vectSize];
			for (int i = 0; i < vectSize; i++) {
				newArr[i] = arr[i];
			}
			delete[] arr;
			memorySize *= 2;
			arr = new T[memorySize];
			for (int i = 0; i < vectSize; i++) {
				arr[i] = newArr[i];
			}
			delete[] newArr;
			newArr = NULL;
		} else {
			T* newArr = new T[newSize];
			if (vectSize > newSize) {
				vectSize = newSize;
			}
			for (int i = 0; i < vectSize; i++) {
				newArr[i] = arr[i];
			}
			delete[] arr;
			memorySize = newSize;
			arr = new T[memorySize];
			for (int i = 0; i < vectSize; i++) {
				arr[i] = newArr[i];
			}
			for (int i = vectSize; i < newSize; i++) {
				arr[i] = 0;
			}
			delete[] newArr;
			newArr = NULL;
		}
	}

	void PushBack(T value) {
		if (vectSize + 1 >= memorySize - 1) {
			MoreMemory();
		}
		vectSize++;
		arr[vectSize - 1] = value;
	}
	
	void PopBack() {
		DeletePos(vectSize - 1);
	}

	void InsertPos(int index, T el) {
		if (vectSize + 1 >= memorySize - 1) {
			MoreMemory();
		}
		vectSize++;
		for (int i = vectSize - 1; i != index; i--) {
			arr[i] = arr[i - 1];
		}
		arr[index] = el;
	}

	void DeletePos(int index) {
		vectSize--;
		for (int i = index; i < vectSize + 1; i++) {
			arr[i] = arr[i + 1];
		}
	}

	void Clear() {
		delete[] arr;
		arr = NULL;
		vectSize = 0;
		memorySize = 0;
	}
	
	int FindIndexOfValue(T el) {
		int index = -1;
		for (int i = 0; i < vectSize; i++) {
			if (arr[i] == el) {
				index = i;
				break;
			}
		}
		return index;
	}

	Vector<T>& operator=(const Vector<T>& obj) {
		vectSize = obj.vectSize;
		memorySize = obj.memorySize;
		arr = new T[memorySize];
		for (int i = 0; i < vectSize; i++) {
			arr[i] = obj.arr[i];
		}
		return *this;
	}
	T& operator[](int index) {
		assert(index >= 0 && index < vectSize);
		return arr[index];
	}
	T& at(int index) {
		assert(index >= 0 && index < vectSize);
		return arr[index];
	}
	friend ostream& operator<<(ostream& out, const Vector<T>& obj) {
		for (int i = 0; i < obj.vectSize; i++) {
			out << obj.arr[i] << " ";
		}
		out << endl;
		return out;
	}
	~Vector() {
		delete[] arr;
		arr = NULL;
		vectSize = 0;
		memorySize = 0;
	}
};


