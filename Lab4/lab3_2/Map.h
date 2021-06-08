#pragma once
#include "Node.h"
#include <list>
#include "Header1.h"

template<typename TypeOfKey, typename TypeOfValue>
class Map {
protected:
	Node<TypeOfKey, TypeOfValue>* root;
	size_t size;
	std::list<Node<TypeOfKey, TypeOfValue>*> listWithNodes;
public:
	Map();
	Map(const Map<TypeOfKey, TypeOfValue>& obj);
	Node<TypeOfKey, TypeOfValue>* Copy(Node<TypeOfKey, TypeOfValue>* node);
	size_t Size() const;
	bool Empty() const;
	void Clear();
	Iterator<TypeOfKey, TypeOfValue> begin();
	Iterator<TypeOfKey, TypeOfValue> end();
	void AddNewNode(Node<TypeOfKey, TypeOfValue>* node);
	void EraseNode(Node<TypeOfKey, TypeOfValue>* node);
	void HelpClear(Node<TypeOfKey, TypeOfValue>* node);
	void Insert(const TypeOfKey key, TypeOfValue value);
	Node<TypeOfKey, TypeOfValue>* Add(Node<TypeOfKey, TypeOfValue>* node, const TypeOfKey key, TypeOfValue value) const;
	TypeOfValue Find(const TypeOfKey key);
	Node<TypeOfKey, TypeOfValue>* Minimum(Node<TypeOfKey, TypeOfValue>* node) const;
	Node<TypeOfKey, TypeOfValue>* Maximum(Node<TypeOfKey, TypeOfValue>* node) const;
	Node<TypeOfKey, TypeOfValue>* HelpFind(Node<TypeOfKey, TypeOfValue>* node, const TypeOfKey key);
	void PrintBT(std::ostream& out, Node<TypeOfKey, TypeOfValue>* node) const;
	virtual TypeOfValue& operator[] (const TypeOfKey key);
	Node<TypeOfKey, TypeOfValue>* FindNextNode(const TypeOfKey key);
	Node<TypeOfKey, TypeOfValue>* GetRoot();
	Node<TypeOfKey, TypeOfValue>* FindPreviousNode(const TypeOfKey key);
	TypeOfKey FindNext(const TypeOfKey key);
	TypeOfKey FindPrevious(const TypeOfKey key);
	Node<TypeOfKey, TypeOfValue>* HelpErase(Node<TypeOfKey, TypeOfValue>* root, const TypeOfKey key);
	void Erase(const TypeOfKey key);
	void InOrderPrint(std::ostream& out, Node<TypeOfKey, TypeOfValue>* root) const;
	friend std::ostream& operator<<(std::ostream& out, const Map<TypeOfKey, TypeOfValue>& obj) {
		out << "Size: " << obj.size << '\n';
		if (obj.Empty()) {
			obj.InOrderPrint(out, obj.root);
		}
		else {
			out << "Empty\n";
		}
		return out;
	}
	Map<TypeOfKey, TypeOfValue>& operator=(const Map<TypeOfKey, TypeOfValue>& BinTreeObj);
	~Map();
	void showList() {
		for (Node<TypeOfKey, TypeOfValue>* node : listWithNodes) {
			std::cout << node->data.first << ' ';
		}
	}
};

template<typename TypeOfKey, typename TypeOfValue>
Map<TypeOfKey, TypeOfValue>::Map() {
	root = nullptr;
	size = 0;
}

template<typename TypeOfKey, typename TypeOfValue>
Node<TypeOfKey, TypeOfValue>* Map<TypeOfKey, TypeOfValue>::Copy(Node<TypeOfKey, TypeOfValue>* node) {
	if (node == nullptr) {
		return nullptr;
	}
	Node<TypeOfKey, TypeOfValue>* n1 = new Node<TypeOfKey, TypeOfValue>(node->data.first,node->data.second,Copy(node->left),Copy(node->right));
	return n1;
}
template<typename TypeOfKey, typename TypeOfValue>
Iterator<TypeOfKey, TypeOfValue> Map<TypeOfKey, TypeOfValue>::begin() {
	return Iterator<TypeOfKey, TypeOfValue>(Minimum(root), &listWithNodes);
}
template<typename TypeOfKey, typename TypeOfValue>
Iterator<TypeOfKey, TypeOfValue> Map<TypeOfKey, TypeOfValue>::end() {
	return Iterator<TypeOfKey, TypeOfValue>(Maximum(root), &listWithNodes);
}

template<typename TypeOfKey, typename TypeOfValue>
Map<TypeOfKey, TypeOfValue>::Map(const Map<TypeOfKey, TypeOfValue>& obj) {
	size = obj.size;
	root = Copy(obj.root);
	listWithNodes = obj.listWithNodes;
}

template<typename TypeOfKey, typename TypeOfValue>
Map<TypeOfKey, TypeOfValue>& Map<TypeOfKey, TypeOfValue>::operator=(const Map<TypeOfKey, TypeOfValue>& BinTreeObj) {
	if (this == &BinTreeObj) {
		return *this;
	}
	size = BinTreeObj.size;
	root = Copy(BinTreeObj.root);
	listWithNodes = this->listWithNodes;
	return *this;
}

template<typename TypeOfKey, typename TypeOfValue>
void Map<TypeOfKey, TypeOfValue>::PrintBT(std::ostream& out, Node<TypeOfKey, TypeOfValue>* node) const {
	if (node) {
		out << "Address " << node->left << " " << node->right << '\n';
		out << node->data.first << " - " << node->data.second << '\n';
		PrintBT(out, node->left);
		PrintBT(out, node->right);
	}
}

template<typename TypeOfKey, typename TypeOfValue>
Node<TypeOfKey, TypeOfValue>* Map<TypeOfKey, TypeOfValue>::GetRoot() {
	return root;
}

template<typename TypeOfKey, typename TypeOfValue>
void Map<TypeOfKey, TypeOfValue>::InOrderPrint(std::ostream& out, Node<TypeOfKey, TypeOfValue>* root) const {
	if (root) {
		InOrderPrint(out, root->left);
		out << root->data.first << " ";
		InOrderPrint(out, root->right);
	}
}
template<typename TypeOfKey, typename TypeOfValue>
void Map<TypeOfKey, TypeOfValue>::HelpClear(Node<TypeOfKey, TypeOfValue>* node) {
	if (node != nullptr) {
		HelpClear(node->left);
		HelpClear(node->right);
		delete node;
	}
}

template<typename TypeOfKey, typename TypeOfValue>
Node<TypeOfKey, TypeOfValue>* Map<TypeOfKey, TypeOfValue>::HelpFind(Node<TypeOfKey, TypeOfValue>* node, const TypeOfKey key) {
	if (node != nullptr) {
		if (node->data.first < key) {
			node = HelpFind(node->right, key);
		}
		else if (node->data.first > key) {
			node = HelpFind(node->left, key);
		}
	}
	return node;
}

template<typename TypeOfKey, typename TypeOfValue>
Node<TypeOfKey, TypeOfValue>* Map<TypeOfKey, TypeOfValue>::Maximum(Node<TypeOfKey, TypeOfValue>* node) const{
	if (node->right == nullptr) {
		return node;
	}
	return Maximum(node->right);
}

template<typename TypeOfKey, typename TypeOfValue>
Node<TypeOfKey, TypeOfValue>* Map<TypeOfKey, TypeOfValue>::Minimum(Node<TypeOfKey, TypeOfValue>* node) const{
	if (node->left == nullptr) {
		return node;
	}
	return Minimum(node->left);
}

template<typename TypeOfKey, typename TypeOfValue>
Node<TypeOfKey, TypeOfValue>* Map<TypeOfKey, TypeOfValue>::HelpErase(Node<TypeOfKey, TypeOfValue>* root, const TypeOfKey key) {
	if (root == nullptr) {
		return root;
	}
	if (root->data.first < key) {
		root->right = HelpErase(root->right, key);
	}
	else if (root->data.first > key) {
		root->left = HelpErase(root->left, key);
	}
	else if (root->right != nullptr && root->left != nullptr) {
		Node<TypeOfKey, TypeOfValue>* n1 = new Node<TypeOfKey, TypeOfValue>(Minimum(root->right)->data.first, Minimum(root->right)->data.second, root->left,root->right);
		delete root;
		root = nullptr;
		Node<TypeOfKey, TypeOfValue>* root = new Node<TypeOfKey, TypeOfValue>(n1->data.first, n1->data.second, n1->left, n1->right);
		delete n1;
		n1 = nullptr;
		root->right = HelpErase(root->right, root->data.first);
		return root;
	}
	else {
		if (root->left != nullptr) {
			root = root->left;
		}
		else if (root->right != nullptr) {
			root = root->right;
		}
		else {
			root = nullptr;
		}
	}
	return root;
}
template<typename TypeOfKey, typename TypeOfValue>
void Map<TypeOfKey, TypeOfValue>::EraseNode(Node<TypeOfKey, TypeOfValue>* node) {
	auto iterForErase = --listWithNodes.end();
	for (auto iter = listWithNodes.begin(); iter != listWithNodes.end(); iter++) {
		if ((*iter)->data.first == node->data.first) {
			if (iter == iterForErase) {
				listWithNodes.pop_back();
			}
			else {
				iterForErase = iter;
				listWithNodes.erase(iterForErase, ++iter);
			}
			break;
		}
	}
}
template<typename TypeOfKey, typename TypeOfValue>
void Map<TypeOfKey, TypeOfValue>::Erase(const TypeOfKey key) {
	EraseNode(HelpFind(this->root, key));
	HelpErase(root, key);
	size--;
}
template<typename TypeOfKey, typename TypeOfValue>
Node<TypeOfKey, TypeOfValue>* Map<TypeOfKey, TypeOfValue>::FindNextNode(const TypeOfKey key) {
	Node<TypeOfKey, TypeOfValue>* current = root, * node = nullptr;
	while (current != nullptr) {
		if (current->data.first > key) {
			node = current;
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	if(node == nullptr) {
		node = Maximum(root);
	}
	return node;
}

template<typename TypeOfKey, typename TypeOfValue>
TypeOfKey Map<TypeOfKey, TypeOfValue>::FindNext(const TypeOfKey key) {
	return FindNextNode(key)->data.first;
}
template<typename TypeOfKey, typename TypeOfValue>
Node<TypeOfKey, TypeOfValue>* Map<TypeOfKey, TypeOfValue>::FindPreviousNode(const TypeOfKey key) {
	Node<TypeOfKey, TypeOfValue>* current = root, * node = nullptr;
	while (current != nullptr) {
		if (current->data.first < key) {
			node = current;
			current = current->right;
		}
		else {
			current = current->left;
		}
	}
	if (node==nullptr) {
		node = Maximum(root);
	}
	return node;
}
template<typename TypeOfKey, typename TypeOfValue>
TypeOfKey Map<TypeOfKey, TypeOfValue>::FindPrevious(const TypeOfKey key) {
	return FindPreviousNode(key)->data.first;
}

template<typename TypeOfKey, typename TypeOfValue>
TypeOfValue Map<TypeOfKey, TypeOfValue>::Find(const TypeOfKey key) {
	Node<TypeOfKey, TypeOfValue>* res = HelpFind(root, key);
	if (res != nullptr) {
		return res->data.second;
	}
	TypeOfValue val = -1;
	return val;
}

template<typename TypeOfKey, typename TypeOfValue>
TypeOfValue& Map<TypeOfKey, TypeOfValue>::operator[] (const TypeOfKey key) {
	TypeOfValue val = Find(key);
	return val;
}

template<typename TypeOfKey, typename TypeOfValue>
Node<TypeOfKey, TypeOfValue>* Map<TypeOfKey, TypeOfValue>::Add(Node<TypeOfKey, TypeOfValue>* node, const TypeOfKey key, TypeOfValue value) const{
	if (node == nullptr) {
		node = new Node<TypeOfKey, TypeOfValue>(key, value, nullptr, nullptr);
	}
	else  if (key < node->data.first) {
		assert((node->data.first != key) && "Such a key already exists!");
		node->left = Add(node->left, key, value);
	}
	else {
		assert(node->data.first != key && "Such a key already exists!");
		node->right = Add(node->right, key, value);
	}
	return node;
}
template<typename TypeOfKey, typename TypeOfValue>
void Map<TypeOfKey, TypeOfValue>::AddNewNode(Node<TypeOfKey, TypeOfValue>* node) {
	auto iterForInsert = listWithNodes.begin();
	bool checked = false;
	for (auto iter = listWithNodes.begin(); iter != listWithNodes.end(); iter++) {
		if ((*iter)->data.first < node->data.first) {
			iterForInsert = iter;
			checked = true;
		}
	}
	if (iterForInsert != listWithNodes.end() ) {
		if (!checked) {
			listWithNodes.insert(iterForInsert, node);
		}
		else {
			listWithNodes.insert(++iterForInsert, node);
		}
	}
	else {
		listWithNodes.insert(iterForInsert, node);
	}
}
template<typename TypeOfKey, typename TypeOfValue>
void Map<TypeOfKey, TypeOfValue>::Insert(const TypeOfKey key, TypeOfValue value) {
	if (!root) {
		root = Add(root, key, value);
	}
	else {
		Add(root, key, value);
	}
	size++;
	AddNewNode(HelpFind(this->root, key));
}

template<typename TypeOfKey, typename TypeOfValue>
size_t Map<TypeOfKey, TypeOfValue>::Size() const {
	return size;
}

template<typename TypeOfKey, typename TypeOfValue>
bool Map<TypeOfKey, TypeOfValue>::Empty() const {
	return size;
}

template<typename TypeOfKey, typename TypeOfValue>
void Map<TypeOfKey, TypeOfValue>::Clear() {
	HelpClear(root);
	listWithNodes.clear();
}

template<typename TypeOfKey, typename TypeOfValue>
Map<TypeOfKey, TypeOfValue>::~Map() {
	HelpClear(root);
	listWithNodes.clear();
	root = nullptr;
	size = 0;
}
