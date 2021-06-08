#pragma once
#include"IteratorForList.h"

template <typename T>
class List {
private:
	Node<T>* head = NULL;
	Node<T>* tail = NULL;
	int count = 0;
public:
	List() {};
	List(const initializer_list<T>& list) {
		for (auto& val : list) {
			PushBack(val);
		}
	}
	List(const List<T>& list0) {
		head = tail = NULL;
		Node<T>* temp = list0.head->next;
		while (temp != list0.tail->next) {
			PushBack(temp->data);
			temp = temp->next;
		}
		delete temp;
		temp = NULL;
	}
	IteratorForList<T> begin() {
		return IteratorForList<T>(head->next);
	}
	IteratorForList<T> end() {
		Node<T>* temp = new Node<T>;
		tail->next = temp;
		temp->prev = tail;
		return IteratorForList<T>(temp);
	}
	bool Empty() {
		return count==0;
	}
	void PushFront(T data) {
		Node<T>* temp = new Node<T>;
		if (!(head && tail)) {
			head = new Node<T>;
			head->prev = NULL;
			head->next = temp;
			temp->prev = head;
			tail = temp;
			tail->data = data;			
		}
		else {
			head->next->prev = temp;
			temp->next = head->next;
			head = new Node<T>;
			head->prev = NULL;
			head->next = temp;
			temp->prev = head;
			temp->data = data;
		}
		count++;
	}
	void PushBack(T data) {
		Node<T>* temp = new Node<T>;
		if (count) {
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
			temp->data = data;
			temp->next = NULL;
		}
		else {
			head = new Node<T>;
			head->prev = NULL;
			head->next = temp;
			temp->prev = head;
			tail = temp;
			tail->data = data;
			tail->next = NULL;
		}
		temp = NULL;
		count++;
	}
	T PopBack() {
		Node<T>* temp = tail->prev;
		T data = tail->data;
		if (!Empty()) {
			delete tail;
			tail = temp;
			tail->next = NULL;
			temp = NULL;
			count--;
			return data;
		}
		else {
			assert(count==0);
			return -1;
		}
	}
	T PopFront() {
		Node<T>* temp = head->next;
		T data = head->next->data;
		if (!Empty()) {
			delete head;
			head = temp;
			head->prev = NULL;
			temp = NULL;
			count--;
			return data;
		}
		else {
			assert(count == 0);
			return -1;
		}
	}

	int Size() const{
		return count;
	}

	void ReverseShow() {
		Node<T>* temp = tail;
		int countCopy = count;
		while (countCopy != 0) {
			cout << temp->data << " ";
			temp = temp->prev;
			countCopy--;
		}
		temp = NULL;
		cout << endl;
	}

	void Show() {
		Node<T>* temp1 = head->next;
		int countCopy1 = count;

		while (countCopy1 != 0) {
			cout << temp1->data << " ";
			temp1 = temp1->next;
			countCopy1--;
		}
		temp1 = NULL;

		cout << endl;
	}
	friend ostream& operator<<(ostream& out, const List<T>& obj) {
		Node<T>* temp1 = obj.head->next;
		int countCopy1 = obj.count;
		while (countCopy1 != 0) {
			out << temp1->data << " ";
			temp1 = temp1->next;
			countCopy1--;
		}
		temp1 = NULL;

		out << endl;
		return out;
	}
	List<T>& operator=(const initializer_list<T>& list) {
		if (count) {
			Node<T>* temp = tail;
			while (tail != NULL) {
				temp = temp->prev;
				delete tail;
				tail = temp;
			}
			count = 0;
			delete temp;
			temp = NULL;
			head = tail = NULL;
		}

		for (auto& val : list) {
			PushBack(val);
		}
		return *this;
	}
	List<T>& operator=(const List<T>& list) {
		if (count) {
			Node<T>* temp = list.tail;
			while (list.tail != NULL) {
				temp = temp->prev;
				delete list.tail;
				list.tail = temp;
			}
			list.count = 0;
			delete temp;
			temp = NULL;
			list.head = list.tail = NULL;
		}

		for (auto& val : List) {
			PushBack(val);
		}
		return *this;
	}
	~List() {
		Node<T>* temp = tail;
		while (tail != NULL) {
			temp = temp->prev;
			delete tail;
			tail = temp;
		}
		count = 0;
		delete temp;
		temp = NULL;
		head = tail = NULL;
	}

};

