# pragma once

# include "CachePolicy.hpp"
# include <unordered_map>
# include <list>
# include <stdexcept>

template <typename K, typename V>
class LRUCache : public CachePolicy <K, V> {

    private:
        int capacity;
        int hits;
        int misses;

        std::list<std::pair<K, V>> cacheList;
        std::unordered_map<K, typename std::list<std::pair<K, V>>::iterator> cacheMap;

    public:
        explicit LRUCache(int capacity);

        V get(const K& key) override;
        void put(const K& key, const V& value) override;
        void display() const override;
        int getHits() const override;
        int getMisses() const override;
};