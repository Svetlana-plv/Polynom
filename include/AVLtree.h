#include <iostream>
#include <stack>
#include <stdexcept>

using namespace std;

template<typename Tkey, typename Tvalue>
class AVLTree {
private:

	// =========================== Node =====================================
	struct Node
	{
		Node* lChild;
		Node* rChild;
		pair<Tkey, Tvalue> data;
		int height;

		Node(Tkey key, Tvalue value) {
			data = { key, value };
			lChild = nullptr;
			rChild = nullptr;
			height = 1;
		}
	};

	int sz;
	Node* root;

	int getHeight(Node* node) {
		return node ? node->height : 0;
	}

	int getDiff(Node* node) {
		return getHeight(node->rChild) - getHeight(node->lChild);
	}

	void updateHeight(Node* node) {
		node->height = max(getHeight(node->lChild), getHeight(node->rChild)) + 1;
	}

	Node* rotateLeft(Node* node) {
		Node* r = node->rChild;
		Node* rl = r->lChild;
		r->lChild = node;
		node->rChild = rl;
		updateHeight(rl);
		updateHeight(r);
		return r;
	}

	Node* rotateRight(Node* node) {
		Node* l = node->lChild;
		Node* lr = l->rChild;
		l->rChild = node;
		node->lChild = lr;
		updateHeight(lr);
		updateHeight(l);
		return l;
	}

	Node* balancerNodes(Node* node) {
		updateHeight(node);

		if (getDiff(node) >= 2) { //right tree heighter
			if (getDiff(node->rChild) <= -1) {
				node->rChild = rotateRight(node->rChild);
			}
			return rotateLeft(node);
		}

		else if (getDiff(node) <= -2) {
			if (getDiff(node->rChild) >= 1) {
				node->lChild = rotateLeft(node->lChild);
			}
			return rotateRight(node);
		}

		return node;
	}

	Node* find(Node* node, const Tkey& key) { //не видит реализацию структуры
		if (!node) return nullptr;
		if (key < node->data.first) return find(node->lChild, key);
		else if (key > node->data.first) return find(node->rChild, key);
		else return node;
	}

	Node* insert(Node* node, Tkey key, Tvalue value) {
		if (!node) {
			sz++;
			return new Node(key, value);
		}
		if (key == node->data.first) throw std::runtime_error("The element with this key already exists");
		
		else if (key < node->data.first) node->lChild = insert(node->lChild, key, value);
		else node->rChild = insert(node->rChild, key, value);

		return balancerNodes(node);
	}

	Node* erase(Node* node, Tkey key) {
		if (!node) return nullptr;

		//search
		if (key < node->data.first) node->lChild = erase(node->lChild, key);
		else if (key > node->data.first) node->rChild = erase(node->rChild, key);
		
		//delete
		else {
			sz--;
			if (!node->lChild || !node->rChild) {
				Node* temp = node->lChild ? node->lChild : node->rChild;
				delete node;
				return temp;
			}
			else {
				Node* max = node->lChild;
				while (max->rChild) {
					max = max->rChild;
				}
				node->data = max->data;
				node->lChild = erase(node->lChild, max->data.first);
			}
		}
		return balancerNodes(node);
	}

	void clear(Node* node) {
		if (!node) return;
		clear(node->lChild);
		clear(node->rChild);
		delete node;
	}



public:

	// =========================== Iterator ==================================
	class Iterator {
	private:
		stack<Node*> sNodes;

		void leftSheet(Node* node) {
			while (node) {
				sNodes.push(node);
				node = node->lChild;
			}
		}

	public:

		Iterator(Node* root) {
			leftSheet(root);
		}

		Iterator& operator++() {
			Node* node = sNodes.top()->rChild;
			sNodes.pop();
			leftSheet(node);
			return *this;
		}

		pair<Tkey, Tvalue> operator*() const {
			return sNodes.top()->data;
		}

		bool operator==(const Iterator& it) const {
			if (sNodes.empty() && it.sNodes.empty()) return true;
			if (sNodes.empty() || it.sNodes.empty()) return false;
			else return sNodes.top() == it.sNodes.top();
		}

		bool operator!=(const Iterator& it) const {
			return !(*this == it);
		}
	};

	// =========================== Methods AVLTree ===========================
	AVLTree() : root(nullptr), sz(0) {};
	
	Iterator find(const Tkey& key) {
		return Iterator(find(root, key));
	}

	Iterator insert(Tkey key, Tvalue value) {
		root = insert(root, key, value);
		return Iterator(find(root, key));
	}

	void erase(Tkey key) {
		root = erase(root, key);
	}

	bool empty() const {
		return sz == 0;
	}

	int size() const {
		return sz;
	}

	void clear() {
		clear(root);
		root = nullptr;
		sz = 0;
	}

	bool exist(const Tkey& key) {
		return find(root, key) != nullptr;
	}

	Iterator begin() const {
		return Iterator(root);
	}

	Iterator end() const {
		return Iterator(nullptr);
	}
};