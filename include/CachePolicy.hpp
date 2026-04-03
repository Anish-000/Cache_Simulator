# pragma once

# include <iostream>
# include <string>

template <typename K, typename V>
class CachePolicy{

    public:
        virtual V get(const K& key) = 0;
        virtual void put(const K& key, const V& value) = 0;
        virtual void display() const = 0;
        virtual getHits() const = 0;
        virtual getMisses() const = 0;

        virtual ~CachePolicy() = default;
};