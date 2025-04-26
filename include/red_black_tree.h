#pragma once
#include <iostream>
#include <stack>

enum class Color { 
    RED, 
    BLACK 
};

template <typename Key, typename Value>
class RBTree {
private:
    struct Node {
        Key key;
        Value value;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        Node(const Key& k, const Value& v, Color c = Color::RED,
            Node* p = nullptr, Node* l = nullptr, Node* r = nullptr)
            : key(k), value(v), color(c), parent(p), left(l), right(r) {}
    };

    Node* root;
    size_t size_;

public:

    RBTree() : root(nullptr), size_(0) {}
    ~RBTree() { clear(); }

    const Value* find(const Key& key) const;
    void clear();
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

private:

};

template <typename Key, typename Value>
void RBTree<Key, Value>::clear(Node* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename Key, typename Value>
void RBTree<Key, Value>::clear() {
    clear(root);
    root = nullptr;
    size_ = 0;
}
