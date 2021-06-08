#pragma once
#include <iostream>
#include <forward_list>
#include <functional>

template<typename KeyType, typename ValueType, typename Hasher = Hasher<KeyType>>
class HashTable {
private:
	int numberOfBucket;
	int numOfKeys;
	std::forward_list<std::pair<const KeyType, ValueType>>* bucket;
	Hasher hash;
public:
	HashTable(size_t m = 32);
	HashTable(const HashTable<KeyType, ValueType, Hasher>&);
	void Insert(const KeyType& key, const ValueType& value);
	void Show();
	void Clear();
	bool Empty();
	bool Contains(KeyType);
	void Erase(KeyType);
	HashTable<KeyType,ValueType,Hasher>& operator=(const HashTable<KeyType, ValueType, Hasher>&);
	ValueType& operator[](const KeyType&);
	ValueType operator[](const KeyType&)const;
	void ReHash();
	friend std::ostream& operator << (std::ostream& out,HashTable<KeyType, ValueType, Hasher>& obj) {
		if (!obj.Empty()) {
			out << "Empty table()\n";
		}
		else {
			for (int i = 0; i < obj.numberOfBucket; i++) {
				out << i << " ";
				for (auto x : obj.bucket[i]) {
					out << x.first << " --> " << x.second << " ";
				}
				out << '\n';
			}
		}
		return out;
	}
	~HashTable();
};

template<typename KeyType, typename ValueType, typename Hasher>
HashTable<KeyType, ValueType, Hasher>::HashTable(size_t m) : hash() {
	numberOfBucket = m;
	numOfKeys = 0;
	bucket = new std::forward_list<std::pair<const KeyType, ValueType>>[m];
}

template<typename KeyType, typename ValueType, typename Hasher>
HashTable<KeyType, ValueType, Hasher>::HashTable(const HashTable<KeyType, ValueType, Hasher>& obj) {
	numberOfBucket = obj.numberOfBucket;
	numOfKeys = obj.numOfKeys;
	bucket = obj.bucket;
	hash = obj.hash;
}

template<typename KeyType, typename ValueType, typename Hasher>
HashTable<KeyType, ValueType, Hasher>& HashTable<KeyType, ValueType, Hasher>::operator=(const HashTable<KeyType, ValueType, Hasher>& hashTable) {
	if (this == &hashTable) {
		return *this;
	}
	numOfKeys = hashTable.numOfKeys;
	numberOfBucket = hashTable.numberOfBucket;
	bucket = this->bucket;
	hash = this->hash;
	return *this;
}

template<typename KeyType, typename ValueType, typename Hasher>
void HashTable<KeyType, ValueType, Hasher>::Insert(const KeyType& key, const ValueType& value) {
	size_t pos = (size_t)(hash(key));
	bool check = false;
	for (auto x : bucket[pos % numberOfBucket]) {
		if (key == x.first) {
			check = true;
			x.second = value;
		}
	}
	if (!check) {
		pos = (size_t)(hash(key));
		bucket[pos % numberOfBucket].push_front(std::make_pair(key, value));
		numOfKeys++;
		if (((double)numOfKeys / (double)numberOfBucket) >= 0.5) {
			ReHash();
		}
	}
}

template<typename KeyType, typename ValueType, typename Hasher>
void HashTable<KeyType, ValueType, Hasher>::ReHash() {
	numberOfBucket *= 2;
	std::forward_list<std::pair<const KeyType, ValueType>>* newBucket = new std::forward_list<std::pair<const KeyType, ValueType>>[numberOfBucket];
	size_t pos;
	for (int i = 0; i < numberOfBucket/2; i++) {
		for (auto x : bucket[i]) {
			pos = (size_t)(hash(x.first));
			newBucket[pos % numberOfBucket].push_front(std::make_pair(x.first, x.second));
		}
		bucket[i].clear();
	}
	bucket = newBucket;
}

template<typename KeyType, typename ValueType, typename Hasher>
bool HashTable<KeyType, ValueType, Hasher>::Empty() {
	return numberOfBucket;
}

template<typename KeyType, typename ValueType, typename Hasher>
bool HashTable<KeyType, ValueType, Hasher>::Contains(const KeyType key) {
	size_t pos = (size_t)(hash(key));
	for (auto x : bucket[pos % numberOfBucket]) {
		if (key == x.first) {
			return true;
		}
	}
	return false;
}

template<typename KeyType, typename ValueType, typename Hasher>
void HashTable<KeyType, ValueType, Hasher>::Erase(const KeyType key) {
	size_t pos = (size_t)(hash(key));
	auto iter = bucket[pos % numberOfBucket].begin();
	auto iter2 = iter;
	for (; iter != bucket[pos % numberOfBucket].end();) {
		if ((*iter).first == key) {
			if (iter == bucket[pos % numberOfBucket].begin()) {
				bucket[pos % numberOfBucket].pop_front();
			}
			else {
				bucket[pos % numberOfBucket].erase_after(iter2);
			}
			return;
		}
		iter2 = iter;
		iter++;
	}
	numOfKeys--;
}

template<typename KeyType, typename ValueType, typename Hasher>
void HashTable<KeyType, ValueType, Hasher>::Clear() {
	for (int i = 0; i < numberOfBucket; i++) {
		bucket[i].clear();
	}
	numberOfBucket = 0;
	numOfKeys = 0;
	bucket = nullptr;
}
template<typename KeyType, typename ValueType, typename Hasher>
ValueType& HashTable<KeyType, ValueType, Hasher>::operator[](const KeyType& key) {
	size_t pos = (size_t)(hash(key));
	for (auto x : bucket[pos % numberOfBucket]) {
		if (key == x.first) {
			return x.second;
		}
	}
	ValueType val = ValueType();
	Insert(key, val);
	return val;
}

template<typename KeyType, typename ValueType, typename Hasher>
ValueType HashTable<KeyType, ValueType, Hasher>::operator[](const KeyType& key)const {
	size_t pos = (size_t)(hash(key));
	for (auto x : bucket[pos % numberOfBucket]) {
		if (key == x.first) {
			return x.second;
		}
	}
	Insert(key, ValueType());
	return ValueType();
}

template<typename KeyType, typename ValueType, typename Hasher>
void HashTable<KeyType, ValueType, Hasher>::Show() {
	if (!Empty()) {
		std::cout << "Empty table()\n";
	}
	else {
		for (int i = 0; i < numberOfBucket; i++) {
			std::cout << i << " ";
			for (auto x : bucket[i]) {
				std::cout << x.first << " --> " << x.second << " ";
			}
			std::cout << std::endl;
		}
	}
}

template<typename KeyType, typename ValueType, typename Hasher>
HashTable<KeyType, ValueType, Hasher>::~HashTable() {
	for (int i = 0; i < numberOfBucket; i++) {
		bucket[i].clear();
	}
	numberOfBucket = 0;
	numOfKeys = 0;
	bucket = nullptr;
}

template<typename KeyType>
class Hasher {
public:
	size_t operator()(KeyType key) {
		double A = 0.618033;
		return fmod(key * A, 1) * 2654435761;
	}
};