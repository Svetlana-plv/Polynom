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
    size_t item_count;

public:

    class Iterator {
    private:
        Node* current;
        std::stack<Node*> stack;

    public:
        Iterator(const Node* node): current(node){}
    };


    RBTree() : root(nullptr), item_count(0) {}
    ~RBTree() { clear(); }

    const RBTree<Key, Value>::Iterator RBTree<Key, Value>::find(const Key& key) const {
        Node* node = find(key, root);
        if (node) return RBTree<Key, Value>::Iterator(node);
        return RBTree<Key, Value>::Iterator(nullptr);
    }
    size_t size() const { return item_count; }
    bool empty() const { return item_count == 0; }
    void clear();

private:
    Node* find(const Key& key, Node* current) const;
    Node* minimum(Node* node) const;
    Node* maximum(Node* node) const;
    Node* predecessor(Node* node) const;
    Node* successor(Node* node) const;
    void clear(Node* node);
};

template <typename Key, typename Value>
typename RBTree<Key, Value>::Node* RBTree<Key, Value>::find(const Key& key, Node* current) const {
    while (current != nullptr) {
        if (key == current->key) {
            return current;
        }
        else if (key < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return nullptr;
}

template <typename Key, typename Value>
typename RBTree<Key, Value>::Node* RBTree<Key, Value>::minimum(Node* node) const {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template <typename Key, typename Value>
typename RBTree<Key, Value>::Node* RBTree<Key, Value>::maximum(Node* node) const {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

template <typename Key, typename Value>
typename RBTree<Key, Value>::Node* RBTree<Key, Value>::predecessor(Node* node) const {
    if (node->left)
        return maximum(node->left);
    Node* parent_curr = node->parent;
    while (!parent_curr && node = parent_curr->left) {
        x = parent_curr;
        parent_curr = parent_curr->parent;
    }
    return parent_curr;
}

template <typename Key, typename Value>
typename RBTree<Key, Value>::Node* RBTree<Key, Value>::successor(Node* node) const {
    if (node->right)
        return minimum(node->right);
    Node* parent_curr = node->parent;
    while (!parent_curr && node = parent_curr->right) {
        x = parent_curr;
        parent_curr = parent_curr->parent;
    }
    return parent_curr;
}

template <typename Key, typename Value>
void RBTree<Key, Value>::clear() {
    clear(root);
    root = nullptr;
    item_count = 0;
}

template <typename Key, typename Value>
void RBTree<Key, Value>::clear(Node* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}