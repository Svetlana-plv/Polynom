#pragma once


template<typename TKey, typename TValue>
class IMapContainer {
public:

    class Iterator {
    public:
        virtual ~Iterator() = default;

        virtual Iterator& operator++() = 0;
        virtual Iterator& operator--() = 0;
        virtual Iterator* operator++(int) = 0;
        virtual Iterator* operator--(int) = 0;
        virtual bool operator==(const Iterator& other) const = 0;
        virtual bool operator!=(const Iterator& other) const = 0;
        virtual std::pair<TKey, TValue>& operator*() const = 0;
        virtual std::pair<TKey, TValue>* operator->() const = 0;
    };

    virtual Iterator insert(const TKey& key, const TValue& value) = 0;
    virtual Iterator erase(const TKey& key) = 0;
    virtual Iterator find(const TKey& key) = 0;

    virtual TValue& operator[](const TKey& key) = 0;   
    virtual const TValue& operator[](const TKey& key) const = 0;

    virtual Iterator begin() = 0;
    virtual Iterator end() = 0;

    virtual int size() const = 0;
    virtual bool empty() const = 0;
    virtual void clear() = 0;
    virtual bool exist(const TKey& key) const = 0;


    virtual ~IMapContainer() = default;
};