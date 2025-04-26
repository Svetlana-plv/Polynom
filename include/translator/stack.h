#include <deque>

template <class T, class cont = std::deque<T>>
class stack {
private:
	cont data;

	void check_empty() const {
		if (empty()) {
			throw std::out_of_range("stack is empty");
		}
	}

public:

	stack() : data() {}

	stack(const stack& stk) {
		data = stk.data;
	}

	stack(stack&& stk) noexcept {
		data = std::move(stk.data);
	}

	stack& operator=(const stack& stk) {
		if (this != &stk) {
			data = stk.data; 
		}
		return *this;
	}

	stack& operator=(stack&& stk) noexcept {
		if (this != &stk) {
			data = std::move(stk.data); 
		}
		stk.data.clear();
		return *this;
	}

	void push(const T& elem) {
		data.push_back(elem);
	}

	void pop() {
		check_empty();
		data.pop_back();  
	}

	T top() const {
		check_empty();
		return data.back();
	}

	void clear() {
		data.clear();
	}

	bool empty() const {
		return data.empty();
	}

	size_t size() const {
		return data.size();
	}
};