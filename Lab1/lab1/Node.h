#pragma once
template <typename T>
struct Node {
	Node<T>* next;
	Node<T>* prev;
	T data;
};