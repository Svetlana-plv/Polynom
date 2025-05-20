#pragma once

#include "polynom_container.h"
#include "ordered_table.h"
#include "polynom.h"


class orderedTablecontainer : public polynomContainer {
private:
    OrderedTable<std::string, Polynom> data;
public:

    class orderedTableIteratorAdapter : public polynomContainer::Iterator {
    private:
        OrderedTable<std::string, Polynom>::Iterator it;
    public:
        orderedTableIteratorAdapter(OrderedTable<std::string, Polynom>::Iterator& iter)
            : it(iter) {}

        std::pair<std::string, Polynom>& operator*() override {
            return *it;
        }

        std::pair<std::string, Polynom>* operator->() override {
            return it.ptr;
        }

        std::pair<std::string, Polynom>& operator++() override {
            return *(++it);
        }

        std::pair<std::string, Polynom>& operator--() override {
            return *(--it);
        }

        std::pair<std::string, Polynom>& operator++(int) override {
            OrderedTable<std::string, Polynom>::Iterator temp = it;
            it++;
            return *temp;
        }

        std::pair<std::string, Polynom>& operator--(int) override {
            OrderedTable<std::string, Polynom>::Iterator temp = it;
            it--;
            return *temp;
        }

        bool operator==(const polynomContainer::Iterator& other) const override {
            const auto* o = dynamic_cast<const orderedTableIteratorAdapter*>(&other);
            return o && this->it == o->it;
        }

        bool operator!=(const polynomContainer::Iterator& other) const override {
            return !(*this == other);
        }

        std::string key() override {
            return it.key();
        }

        Polynom& value() override {
            return it.value();
        }
    };

    polynomContainer::Iterator* find(const std::string& v) override {
        auto it = data.find(v);
        if (it == data.end()) return nullptr;
        return new orderedTableIteratorAdapter(it);
    }

    polynomContainer::Iterator* insert(const std::string& v, const Polynom& m) override {
        auto it = data.insert(v, m); 
        return new orderedTableIteratorAdapter(it);
    }

    polynomContainer::Iterator* erase(const std::string& v) override {
        auto it = data.find(v);
        if (it == data.end()) return nullptr;

        data.erase(v);
        return new orderedTableIteratorAdapter(it);
    }

    polynomContainer::Iterator* begin() override {
        OrderedTable<std::string, Polynom>::Iterator it = data.begin();
        return new orderedTableIteratorAdapter(it);
    }

    polynomContainer::Iterator* end() override {
        OrderedTable<std::string, Polynom>::Iterator it = data.end();
        return new orderedTableIteratorAdapter(it);
    }

    int size() const override {
        return data.size();
    }

    bool empty() const override {
        return data.empty();
    }

    void clear() override {
        data.clear();
    }
};
