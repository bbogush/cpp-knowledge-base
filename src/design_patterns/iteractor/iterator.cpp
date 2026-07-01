/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <memory>
#include <vector>

template<typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool has_next() const = 0;
    virtual T next() = 0;
};

template<typename T>
class Aggregate {
public:
    virtual ~Aggregate() = default;
    virtual std::unique_ptr<Iterator<T>> create_iterator() const = 0;
};

template<typename T>
class Collection : public Aggregate<T> {
public:
    void add(const T &item)
    {
        items.push_back(item);
    }

    size_t size() const
    {
        return items.size();
    }

    const T &get(size_t index) const
    {
        return items[index];
    }

    std::unique_ptr<Iterator<T>> create_iterator() const override;

private:
    std::vector<T> items;
};

template<typename T>
class CollectionIterator : public Iterator<T> {
public:
    explicit CollectionIterator(const Collection<T> &collection) : collection(collection), index(0)
    {
    }

    bool has_next() const override
    {
        return index < collection.size();
    }

    T next() override
    {
        return collection.get(index++);
    }

private:
    const Collection<T> &collection;
    size_t index;
};

template<typename T>
std::unique_ptr<Iterator<T>> Collection<T>::create_iterator() const
{
    return std::make_unique<CollectionIterator<T>>(*this);
}

int main()
{
    Collection<int> collection;
    collection.add(10);
    collection.add(20);
    collection.add(30);

    auto it = collection.create_iterator();

    while (it->has_next()) {
        std::cout << it->next() << std::endl;
    }

    return 0;
}
