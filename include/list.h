#pragma once
#include <iostream>


const int MAX_LIST_SIZE = 100000;

template<typename T>
class List {

private:

	struct Node {
		Node* next;
		T value;

		Node(T value_, Node* next_ = nullptr) : value(value_), next(next_) {}
	};

	size_t size = 0;
	Node* first = nullptr;

public:

	class Iterator {

	private:

		Node* ptr = nullptr;

	public:

		Iterator(Node* p): ptr(p) {}

		Node& operator*() const { return *ptr; }
		Node* operator->() const { return ptr; }

		T value() {
			return ptr->value;
		}

		void set_value(const T& data) {
			ptr->value = data;
		}

		Iterator operator+(int k) {
			Iterator tmp = *this;
			for(int i=0; i<k; i++)
				tmp++;
			return tmp;
		}

		Iterator& operator++() {
			ptr = ptr->next;
			return *this;
		}

		Iterator operator++(int) {
			Iterator tmp = *this;
			ptr = ptr->next;
			return tmp;
		}

		bool operator==(const Iterator& iterator) const { return this->ptr == iterator.ptr; }
		bool operator!=(const Iterator& iterator) const { return this->ptr != iterator.ptr; }
	};

	List(size_t n = 0) {
		if (n > MAX_LIST_SIZE) throw std::out_of_range("Incorrect size of list!");
		size = n;
		while (n--) {
			Node* tmp = new Node(T(), first);
			first = tmp;
		}
	}

	~List() {
		clear();
	}

	List(const List& other) : size(other.size) {
		if (other.first != nullptr) {
			Node* curr1 = other.first;
			Node* curr2 = new Node(curr1->value, nullptr);
			this->first = curr2;
			while (curr1) {
				Node* next1 = curr1->next;
				if (!next1) {
					break;
				}
				curr2->next = new Node(next1->value, nullptr);
				curr2 = curr2->next;
				curr1 = curr1->next;
			}
		}
	}

	List& operator=(const List& other) {
		if (this == &other) return *this;
		clear();
		size = other.size;
		if (other.first != nullptr) {
			Node* curr1 = other.first;
			Node* curr2 = new Node(curr1->value, nullptr);
			this->first = curr2;
			while (curr1) {
				Node* next1 = curr1->next;
				if (!next1) {
					break;
				}
				curr2->next = new Node(next1->value, nullptr);
				curr2 = curr2->next;
				curr1 = curr1->next;
			}
		}
		return *this;
	}

	List(List&& other) {
		this->first = other.first;
		other.first = nullptr;
		other.size=0;
	}

	List& operator=(List&& other) {
		this->size = other.size;
		this->first = other.first;
		other.size = 0;
		other.first = nullptr;
		return *this;
	}

	Iterator begin() const { return Iterator(this->first); }
	Iterator end() const { return Iterator(nullptr); }
	bool empty() const { return size == 0; }

	void clear() {
		this->size = 0;
		Node* curr;
		while (this->first != nullptr) {
			curr = this->first->next;
			delete this->first;
			this->first = curr;
		}
	}

	size_t get_size()const {
		return size;
	}

	void print() {

		for (Iterator it = this->begin(); it != this->end(); ++it) {
			std::cout << it.value() << " ";
		}
		std::cout << std::endl;
	}

	T& operator[](size_t index) {
		Iterator it = this->begin();
		while (index--) {
			++it;
		}
		return it->value;
	}

	const T& operator[](size_t index) const {
		Iterator it = this->begin();
		while (index--) {
			++it;
		}
		return it.value();
	}

	Iterator insert_after(T data, Iterator prev) {
		if (prev == nullptr) throw std::invalid_argument("Incorrect Node pointer");
		Node* tmp = new Node(data, nullptr);
		tmp->next = prev->next;
		prev->next = tmp;
		++size;
		return Iterator(tmp);
	}

	Iterator insert_front(T data) {
		++size;
		first = new Node(data, first);
		return Iterator(first);
	}

	Iterator erase_after(Iterator prev) {
		Node* tmp = prev->next;
		if (tmp) {
			size--;
			prev->next = prev->next->next;
			delete tmp;
		}
		return Iterator(prev->next);
	}

	Iterator erase_front() {
		if (first) {
			Node* tmp = first->next;
			delete first;
			first = tmp;
			size--;
		}
		return Iterator(first);
	}

	void set_value(const T& data, Iterator it) {
		it.set_value(data);
	}



	void task_10() {

		if (!first) std::cout<<"List is empty!" << std::endl;

		Node* prev = nullptr;
		Node* curr = first;
		Node* next;


		while (curr) {
			next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		first = prev;

		(*this).print();
	}
};