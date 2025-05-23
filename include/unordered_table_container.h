#pragma once

#include "polynom_container.h"
#include "unordered_table.h"
#include "polynom.h"

class unorderedTablecontainer : public polynomContainer {
private:
    UnorderedTable<std::string, Polynom> data;
public:

    class unorderedTableIteratorAdapter : public polynomContainer::Iterator {
    private:
        UnorderedTable<std::string, Polynom>::Iterator it;
    public:
        unorderedTableIteratorAdapter(UnorderedTable<std::string, Polynom>::Iterator iter)
            : it(std::move(iter)) {
        }

        std::pair<std::string, Polynom>& operator*() override {
            return *it;
        }

        std::pair<std::string, Polynom>* operator->() override {
            return it.operator->();
        }

        Iterator& operator++() override {
            ++it;
            return *this;
        }

        Iterator& operator--() override {
            --it;
            return *this;
        }

        Iterator* operator++(int) override {
            Iterator* copy = new unorderedTableIteratorAdapter(it);
            ++it;
            return copy;
        }

        Iterator* operator--(int) override {
            Iterator* copy = new unorderedTableIteratorAdapter(it);
            --it;
            return copy;
        }

        bool operator==(const Iterator& other) const override {
            auto* otherPtr = dynamic_cast<const unorderedTableIteratorAdapter*>(&other);
            return otherPtr && this->it == otherPtr->it;
        }

        bool operator!=(const Iterator& other) const override {
            return !(*this == other);
        }

        std::string key() override {
            return it.key();
        }

        Polynom& value() override {
            return it.value();
        }
    };

    std::unique_ptr<Iterator> find(const std::string& v) override {
        auto it = data.find(v);
        if (it == data.end()) return nullptr;
        return std::make_unique<unorderedTableIteratorAdapter>(it);
    }

    std::unique_ptr<Iterator> insert(const std::string& v, const Polynom& m) override {
        auto it = data.insert(v, m);
        return std::make_unique<unorderedTableIteratorAdapter>(it);
    }

    std::unique_ptr<Iterator> erase(const std::string& v) override {
        auto it = data.find(v);
        if (it == data.end()) return nullptr;
        data.erase(v);
        return std::make_unique<unorderedTableIteratorAdapter>(it);
    }


    std::unique_ptr<Iterator> begin() override {
        return std::make_unique<unorderedTableIteratorAdapter>(data.begin());
    }

    std::unique_ptr<Iterator> end() override {
        return std::make_unique<unorderedTableIteratorAdapter>(data.end());
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
