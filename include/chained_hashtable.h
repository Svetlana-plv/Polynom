#pragma once

#include <iostream>
#include <vector>
#include <list>


template<typename Key, typename Value>
class HashTable {
public:
    // Avaliable hash functions
    enum HashFunction {
        STD,       // std::hash
        DJB2,      // Hash function djb2
        SIMPLE     // Simple hash function
    };

private:
    using Chain = std::list<std::pair<Key, Value>>;
    std::vector<Chain> table;
    size_t item_count = 0;
    HashFunction current_hash_func;

    // Hash functions
    size_t hash_std(const Key& key) const {
        return std::hash<Key>{}(key);
    }

    size_t hash_djb2(const std::string& key) const {
        size_t hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash;
    }

    size_t hash_simple(const std::string& key) const {
        size_t sum = 0;
        if (key.empty()) return 0;
        for (size_t i = 0; i < key.size(); i++)
            sum += key[i];
        return sum;
    }

    size_t compute_hash(const Key& key) const {
        switch (current_hash_func) {
        case STD: return hash_std(key);
        case DJB2: return hash_djb2(key);
        case SIMPLE: return hash_simple(key);
        default: return hash_std(key);
        }
    }

    size_t get_index(const Key& key) const {
        return compute_hash(key) % table.size();
    }

    typename Chain::iterator find_in_chain(size_t index, const Key& key) {
        Chain& chain = table[index];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == key) {
                return it;
            }
        }
        return chain.end();
    }

    void check_rehash() {
        if (static_cast<float>(item_count) / table.size() > 0.8f) {
            rehash(table.size() * 2 + 1);
        }
    }

public:
    class Iterator {
        typename std::vector<Chain>::iterator table_it;
        typename std::vector<Chain>::iterator table_end;
        typename Chain::iterator chain_it;

        void move_to_next() {
            while (table_it != table_end && chain_it == table_it->end()) {
                ++table_it;
                if (table_it != table_end) {
                    chain_it = table_it->begin();
                }
            }
        }

    public:
        Iterator(typename std::vector<Chain>::iterator begin, typename std::vector<Chain>::iterator end,
            typename Chain::iterator elem = typename Chain::iterator()) : table_it(begin), table_end(end), chain_it(elem) 
        {
            if (table_it != table_end && chain_it == table_it->end()) {
                move_to_next();
            }
        }

        std::pair<Key, Value>& operator*() { return *chain_it; }
        std::pair<Key, Value>* operator->() { return &(*chain_it); }

        Iterator& operator++() {
            ++chain_it;
            move_to_next();
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator& operator+(int k) {
            for (size_t i = 0; i < k; i++) {
                if (table_it == table_end) break;
                ++(*this);
            }
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return table_it == other.table_it && (table_it == table_end || chain_it == other.chain_it);
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };


    HashTable(size_t initial_size = 10, HashFunction hash_func = STD)
        : table(initial_size), current_hash_func(hash_func) {}


    void set_hash_function(HashFunction hash_func) {
        if (current_hash_func != hash_func) {
            current_hash_func = hash_func;
            rehash(table.size());
        }
    }

    Iterator find(const Key& key) {
        size_t index = get_index(key);
        typename Chain::iterator it = find_in_chain(index, key);
        if (it == table[index].end()) return (*this).end();
        return Iterator(table.begin()+index, table.end(), it);
    }

    void insert(const Key& key, const Value& value) {
        size_t index = get_index(key);
        typename Chain::iterator it = find_in_chain(index, key);

        if (it != table[index].end()) {
            it->second = value;  // Updating an existing one
        }
        else {
            table[index].emplace_back(key, value);
            item_count++;
            check_rehash();
        }
    }

    Value& at(const Key& key) {
        size_t index = get_index(key);
        typename Chain::iterator it = find_in_chain(index, key);

        if (it == table[index].end()) {
            throw std::out_of_range("Key not found");
        }
        return it->second;
    }

    bool erase(const Key& key) {
        size_t index = get_index(key);
        typename Chain::iterator it = find_in_chain(index, key);

        if (it != table[index].end()) {
            table[index].erase(it);
            item_count--;
            return true;
        }
        return false;
    }

    Value& operator[](const Key& key) {
        size_t index = get_index(key);
        auto it = find_in_chain(index, key);

        return it->second;
    }

    void rehash(size_t new_size) {
        std::vector<Chain> new_table(new_size);
        for (auto& chain : table) {
            for (auto& item : chain) {
                size_t new_index = compute_hash(item.first) % new_size;
                new_table[new_index].push_back(std::move(item));
            }
        }
        table = std::move(new_table);
    }

    Iterator begin() {
        return Iterator(table.begin(), table.end(), table.front().begin());
    }

    Iterator end() {
        return Iterator(table.end(), table.end());
    }

    size_t size() const { return item_count; }
    size_t table_size() const { return table.size(); }
};
