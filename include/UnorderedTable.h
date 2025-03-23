#pragma once

#include <vector>
#include <iostream>
#include <map>

using namespace std;

template<class Tkey, class Tvalue>
class UnorderedTable {
private:
	vector<pair<Tkey, Tvalue>> data;

	int findIndex(const TKey& key) const {
		for (int i = 0; i < data.size(); ++i) {
			if (data[i].first == key) {
				return i;
			}
		}
		return -1; //return -1 if index not found
	}

public:
	class Iterator {
	public:
		pair<Tkey, Tvalue>* p; //poinrer
		Iterator(pair<Tkey, Tvalue>* pair) : p(pair) {}

		Iterator& operator++() {
			p++;
			return *this;
		}
		
		Iterator& operator--() {
			p--;
			return *this;
		}

		//postfix
		Iterator operator++(int) {
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		Iterator operator--(int) {
			Iterator tmp = *this;
			--(*this);
			return tmp;
		}
		
		Iterator operator+(int move) {
			Iterator tmp = *this;
			if (move > 0) {
				for (int i = 0; i < move; ++i) {
					++tmp;
				}
			}
			else {
				for (int i = 0; i < -move; ++i) {
					--tmp;
				}
			}
			return tmp;
		}

		Iterator operator-(int move) {
			Iterator tmp = *this;
			if (move > 0) {
				for (int i = 0; i < move; ++i) {
					--tmp;
				}
			}
			else {
				for (int i = 0; i < -move; ++i) {
					++tmp;
				}
			}
			return tmp;
		}
		
		Iterator& operator+=(int move) {
			*this = *this + move;
			return *this;
		}

		Iterator& operator-=(int move) {
			*this = *this - move;
			return *this;
		}

		bool operator==(const Iterator& It) const {
			return p == It.p;
		}

		bool operator!=(const Iterator& It) const {
			return p != It.p;
		}

		pair<TKey, TValue>& operator*() const {
			return *p;
		}

		pair<TKey, TValue>* operator->() const {
			return p;
		}
	};

	UnorderedTable() {};

	Iterator insert(const TKey& key, const TValue& value) {
		int index = findIndex(key);
		if (index != -1) {
			data[index].second = value;  // reset value
			return Iterator(&data[index]);
		}
		data.push_back({ key, value });
		return Iterator(&data.back());
	}

	Iterator erase(const TKey& key) {
		int index = findIndex(key);
		if (index != -1) {
			data.erase(data.begin() + index);
			return end();
		}
		return end();
	}

	Iterator find(const TKey& key) {
		int index = findIndex(key);
		if (index != -1) {
			return Iterator(&data[index]);
		}
		return end();
	}

	TValue& operator[](const TKey& key) {
		int index = findIndex(key);
		if (index != -1) {
			return data[index].second;
		}
		throw std::runtime_error("The key is not in the table");
	}

	const TValue& operator[](const TKey& key) const {
		int index = findIndex(key);
		if (index != -1) {
			return data[index].second;
		}
		throw std::runtime_error("The key is not in the table");
	}

	Iterator begin() {
		if (data.empty()) {
			return Iterator(nullptr);
		}
		return Iterator(data.data());
	}

	Iterator end() {
		if (data.empty()) {
			return Iterator(nullptr);
		}
		return Iterator(data.data() + data.size());
	}

	int size() const {
		return data.size();
	}

	bool empty() const {
		return data.empty();
	}

	void clear() {
		data.clear();
	}

	bool exist(const TKey& key) {
		return findIndex(key) != -1;
	}
};