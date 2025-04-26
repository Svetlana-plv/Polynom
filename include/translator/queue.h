#include <deque>
#include <iostream>

#define CAPCITY_INCREASE_VALUE 2

template <class T>
class queue {
private:
	T* pMem;
	size_t front;
	size_t back;
	size_t sz; // current size
	size_t capacity; //max size

public:

	//�����������
	queue(size_t capacity) : front(0), back(0), sz(0), capacity(capacity) {
		if (capacity == 0) {
			throw std::out_of_range("size must be greater than zero");
		}
		pMem = new T[capacity];
	}
	
	//����������� �����������
	queue(const queue& q) {
		front = q.front;
		back = q.back;
		sz = q.sz;
		capacity = q.capacity;
		pMem = new T[capacity];

		for (size_t i = 0; i < sz; ++i) {
			pMem[i] = q.pMem[(front + i) % capacity];
		}
	}

	//����������
	~queue() {
		delete[] pMem;
	}

	//����������� �����������
	queue(queue&& q) noexcept {
		pMem = q.pMem;
		front = q.front;
		back = q.back;
		sz = q.sz;
		capacity = q.capacity;

		q.pMem = nullptr;
		q.front = 0;
		q.back = 0;
		q.sz = 0;
		q.capacity = 0;
	}

	//�������� ������������
	queue& operator=(const queue& q) {
		
		if (this == &q) {
			return *this;
		}
		
		//�� �������� ���������� ������
		delete[] pMem;

		front = q.front;
		back = q.back;
		sz = q.sz;
		capacity = q.capacity;
		pMem = new T[capacity];

		for (size_t i = 0; i < sz; ++i) {
			pMem[i] = q.pMem[(front + i) % capacity];
		}
	}

	//�������� �����������
	queue& operator=(queue&& q) noexcept {
		if (this == &q) {
			return *this;
		}

		delete[] pMem;

		pMem = q.pMem;
		front = q.front;
		back = q.back;
		sz = q.sz;
		capacity = q.capacity;

		q.pMem = nullptr;
		q.front = 0;
		q.back = 0;
		q.sz = 0;
		q.capacity = 0;

		return *this;
	}

	//push in top
	void push(const T& element) {
		if (sz == capacity) {
			repack();
		}

		pMem[back] = element;

		//����������� �������
		back = (back + 1) % capacity;
		
		++sz;
	}

	T pop() {
		if (empty()) {
			throw std::out_of_range("queue is empty");
		}

		T value = pMem[front];

		front = (front + 1) % capacity;
		
		--sz;
		
		return value;
	}

	T top() {
		if (empty()) {
			throw std::out_of_range("queue is empty");
		}

		T value = pMem[front];

		return value;
	}

	void clear() {
		sz = 0;
		front = 0;
		back = 0;
	}

	bool empty() const {
		return sz == 0;
	}

	size_t currentSize() const{
		return sz;
	}

	size_t maxSize() const{
		return capacity;
	}

private:
	void repack() {
		capacity *= CAPCITY_INCREASE_VALUE;
		T* ptmpMemory = new T[capacity];
		
		for (size_t i = 0; i < sz; ++i) {
			ptmpMemory[i] = std::move(pMem[(front + i) % (capacity / 2)]);
		}


		delete[] pMem;
		pMem = ptmpMemory;

		front = 0;
		back = sz;

	}
};
