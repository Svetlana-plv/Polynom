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
    size_t item_count; // current size of tree

public:

    // Iterator
    class Iterator {
    private:
        Node* current;

    public:

        Iterator(Node* node) : current(node) {}

        const std::pair<const Key&, const Value&> operator*() const {
            if (!current) throw std::out_of_range("Elemint is nullptr");
            return { current->key, current->value };
        }

        //const std::pair<const Key, Value>* operator->() const {
        //    if (!current) throw std::out_of_range("Elemint is nullptr");
        //    return reinterpret_cast<std::pair<const Key, Value>*>(&current->key);
        //}
        
        Iterator& operator++() {
            if (current) {
                current = RBTree<Key, Value>::successor(current);
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator& operator--() {
            if (current) {
                current = RBTree<Key, Value>::predecessor(current);
            }
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };


    RBTree() : root(nullptr), item_count(0) {}
    ~RBTree() { clear(); }

    const Iterator RBTree<Key, Value>::find(const Key& key) const {
        Node* node = find(key, root);
        if (node) return RBTree<Key, Value>::Iterator(node);
        return RBTree<Key, Value>::Iterator(nullptr);
    }
    Iterator insert(const Key& key, const Value& value);
    void erase(const Key& key);

    size_t size() const { return item_count; }
    bool empty() const { return item_count == 0; }
    void clear();
    Iterator begin() const {
        if (!root) return end();
        return Iterator(RBTree<Key, Value>::minimum(root));
    }
    Iterator end() const { return Iterator(nullptr); }
    Node* get_root() const { return root; };

    static Node* minimum(Node* node);
    static Node* maximum(Node* node);
    static Node* predecessor(Node* node); // previous elsment
    static Node* successor(Node* node); // next element

private:
    void rotateLeft(Node* x);
    void rotateRight(Node* y);
    void balanceInsert(Node* z);
    void balanceDelete(Node* z);
    void transplant(Node* u, Node* v);
    Node* find(const Key& key, Node* current) const;

    void clear(Node* node);
};

// Insert
template <typename Key, typename Value>
typename RBTree<Key, Value>::Iterator RBTree<Key, Value>::insert(const Key& key, const Value& value) {
    Node* node = new Node(key, value);
    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (node->key < x->key) {
            x = x->left;
        }
        else if (node->key > x->key) {
            x = x->right;
        }
        else {
            // Ключ уже существует - обновляем значение
            x->value = value;
            delete node;
            return Iterator(x);
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
    }
    else if (node->key < y->key) {
        y->left = node;
    }
    else {
        y->right = node;
    }

    item_count++;
    if (node->parent == nullptr) {
        node->color = Color::BLACK;
        return Iterator(node);
    }

    //if (node->parent->parent == nullptr) {
    //    return Iterator(node);
    //}

    balanceInsert(node);
    return Iterator(node);
}

template <typename Key, typename Value>
void RBTree<Key, Value>::balanceInsert(Node* z) {
    Node* u;
    while (z->parent != nullptr && z->parent->color == Color::RED) {
        if (z->parent == z->parent->parent->right) {
            u = z->parent->parent->left;
            if (u != nullptr && u->color == Color::RED) {
                u->color = Color::BLACK;
                z->parent->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(z);
                }
                z->parent->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                rotateLeft(z->parent->parent);
            }
        }
        else {
            u = z->parent->parent->right;
            if (u != nullptr && u->color == Color::RED) {
                u->color = Color::BLACK;
                z->parent->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(z);
                }
                z->parent->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                rotateRight(z->parent->parent);
            }
        }
        if (z == root) {
            break;
        }
    }
    root->color = Color::BLACK;
}

// Private find
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

// Rotates
template <typename Key, typename Value>
void RBTree<Key, Value>::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

template <typename Key, typename Value>
void RBTree<Key, Value>::rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != nullptr) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullptr) {
        root = x;
    }
    else if (y == y->parent->right) {
        y->parent->right = x;
    }
    else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

//Min
template <typename Key, typename Value>
typename RBTree<Key, Value>::Node* RBTree<Key, Value>::minimum(Node* node){
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

//Max
template <typename Key, typename Value>
typename RBTree<Key, Value>::Node* RBTree<Key, Value>::maximum(Node* node){
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

// Previous element
template <typename Key, typename Value>
typename RBTree<Key, Value>::Node* RBTree<Key, Value>::predecessor(Node* node){
    if (node->left)
        return RBTree<Key, Value>::maximum(node->left);

    Node* parent_curr = node->parent;
    while (parent_curr && node == parent_curr->left) {
        node = parent_curr;
        parent_curr = parent_curr->parent;
    }
    if (!parent_curr) return nullptr;
    return parent_curr;
}

// Next element
template <typename Key, typename Value>
typename RBTree<Key, Value>::Node* RBTree<Key, Value>::successor(Node* node){
    if (node->right)
        return RBTree<Key, Value>::minimum(node->right);

    Node* parent_curr = node->parent;
    while (parent_curr && node == parent_curr->right) {
        node = parent_curr;
        parent_curr = parent_curr->parent;
    }
    if (!parent_curr) return nullptr;
    return parent_curr;
}

//Public clear
template <typename Key, typename Value>
void RBTree<Key, Value>::clear() {
    clear(root);
    root = nullptr;
    item_count = 0;
}

//Private clear
template <typename Key, typename Value>
void RBTree<Key, Value>::clear(Node* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

// Delete and supportive functions
template <typename Key, typename Value>
void RBTree<Key, Value>::erase(const Key& key) {

    Node* z = find(key, this->root);
    if (!z) return; // Node not found

    Node* x;
    Node* y = z;
    Color original_color = y->color;

    if (z->left == nullptr) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == nullptr) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = RBTree<Key, Value>::successor(z);
        original_color = y->color;
        x = y->right;

        if (y->parent == z) {
            if (x) x->parent = y;
        }
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;
    item_count--;

    if (original_color == Color::BLACK) {
        balanceDelete(x);
    }
}


template <typename Key, typename Value>
void RBTree<Key, Value>::transplant(Node* u, Node* v) {
    if (u->parent == nullptr) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }

    if (v != nullptr) {
        v->parent = u->parent;
    }
}


template <typename Key, typename Value>
void RBTree<Key, Value>::balanceDelete(Node* x) {
    if (!x) return;

    while (x != root && x->color == Color::BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;

            if (w->color == Color::RED) {
                w->color = Color::BLACK;
                x->parent->color = Color::RED;
                rotateLeft(x->parent);
                w = x->parent->right;
            }

            if ((!w->left || w->left->color == Color::BLACK) &&
                (!w->right || w->right->color == Color::BLACK)) {
                w->color = Color::RED;
                x = x->parent;
            }
            else {
                if (!w->right || w->right->color == Color::BLACK) {
                    if (w->left) w->left->color = Color::BLACK;
                    w->color = Color::RED;
                    rotateRight(w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = Color::BLACK;
                if (w->right) w->right->color = Color::BLACK;
                rotateLeft(x->parent);
                x = root;
            }
        }
        else {
            Node* w = x->parent->left;

            if (w->color == Color::RED) {
                w->color = Color::BLACK;
                x->parent->color = Color::RED;
                rotateRight(x->parent);
                w = x->parent->left;
            }

            if ((!w->right || w->right->color == Color::BLACK) &&
                (!w->left || w->left->color == Color::BLACK)) {
                w->color = Color::RED;
                x = x->parent;
            }
            else {
                if (!w->left || w->left->color == Color::BLACK) {
                    if (w->right) w->right->color = Color::BLACK;
                    w->color = Color::RED;
                    rotateLeft(w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = Color::BLACK;
                if (w->left) w->left->color = Color::BLACK;
                rotateRight(x->parent);
                x = root;
            }
        }
    }

    x->color = Color::BLACK;
}


