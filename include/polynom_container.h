#pragma once
#include "polynom.h"

class polynomContainer {
public:

    class Iterator {
    public:
        virtual std::pair<std::string, Polynom>& operator*() = 0;
        virtual std::pair<std::string, Polynom>* operator->() = 0;
        virtual Iterator& operator++() = 0;
        virtual Iterator& operator--() = 0;
        virtual Iterator* operator++(int) = 0;
        virtual Iterator* operator--(int) = 0;
        virtual bool operator!=(const Iterator& other) const = 0;
        virtual bool operator==(const Iterator& other) const = 0;
        virtual std::string key() = 0;
        virtual Polynom& value() = 0;
    };

    virtual ~polynomContainer() = default;

    virtual std::unique_ptr<Iterator> insert(const std::string& v, const Polynom& m) = 0;
    virtual std::unique_ptr<Iterator> erase(const std::string& v) = 0;
    virtual std::unique_ptr<Iterator> find(const std::string& v) = 0;

    virtual std::unique_ptr<Iterator> begin() = 0;
    virtual std::unique_ptr<Iterator> end() = 0;

    virtual int size() const = 0;
    virtual bool empty() const = 0;
    virtual void clear() = 0;
};
