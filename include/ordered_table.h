#pragma once

#include <iostream>
#include <vector>

template<class TKey, class TValue>
class OrderedTable {
private:
	std::vector<std::pair<TKey, TValue>> data;

	int findIndex(const TKey& key) const {

		if (this->empty()) return -1;

		int left = 0;
		int right = data.size() - 1;
		int curr;

		while (left <= right) {
			curr = (left + right) / 2;
			if (data[curr].first < key) {
				left = curr+1;
			}
			else if (data[curr].first > key) {
				right = curr-1;
			}
			else {
				return curr;
			}
		}

		return -1;
	}

public:
	class Iterator {
	public:
		std::pair<TKey, TValue>* ptr;
		Iterator(std::pair<TKey, TValue>* pair) : ptr(pair) {}

		std::pair<TKey, TValue>& operator*() const {
			return *ptr;
		}

		std::pair<TKey, TValue>* operator->() const {
			return ptr;
		}

		TKey key()  { return ptr->first; }

		TValue& value()  { return ptr->second; }

		Iterator& operator++() {
			ptr++;
			return *this;
		}

		Iterator& operator--() {
			ptr--;
			return *this;
		}

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

		Iterator operator+(int k) {
			Iterator tmp = *this;
			for (int i = 0; i < k; ++i) {
				++tmp;
			}
			return tmp;
		}

		Iterator operator-(int k) {
			Iterator tmp = *this;
			for (int i = 0; i < k; ++i) {
				++tmp;
			}
			return tmp;
		}

		Iterator& operator+=(int k) {
			*this = *this + k;
			return *this;
		}

		Iterator& operator-=(int k) {
			*this = *this - k;
			return *this;
		}

		bool operator==(const Iterator& it) const {
			return ptr == it.ptr;
		}

		bool operator!=(const Iterator& it) const {
			return ptr != it.ptr;
		}
	};

	OrderedTable() = default;

	Iterator insert(const TKey& key, const TValue& value) {
		int index = findIndex(key);
		if (index!=-1) {
			return end();
		}
		std::pair<TKey, TValue> elem = std::make_pair(key, value);
		data.push_back(elem);
		int i = (index == -1) ? 0 : index;
		for (int j = data.size() - 1; j > i; j--) {
			if (data[j].first < data[j - 1].first)
				std::swap(data[j], data[j - 1]);
			else
				break;
		}
		return Iterator(&data.back());
	}

	Iterator erase(const TKey& key) {
		int index = findIndex(key);
		if (index == -1) return this->end();
		data.erase(data.begin() + index);
		return this->begin() + index;
		
	}

	Iterator find(const TKey& key) {
		int index = findIndex(key);
		if (index == -1) return this->end();
		return Iterator(&data[index]);
		
	}

	TValue& operator[](const TKey& key) {
		int index = findIndex(key);
		if (index == -1) throw std::runtime_error("The key is not in the table");
		return data[index].second;
	}

	const TValue& operator[](const TKey& key) const {
		int index = findIndex(key);
		if (index == -1) throw std::runtime_error("The key is not in the table");
		return data[index].second;
	}

	Iterator begin() {
		if (data.empty()) return Iterator(nullptr);
		return Iterator(data.data());
	}

	Iterator end() {
		if (data.empty()) return Iterator(nullptr);
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
