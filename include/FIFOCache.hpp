#pragma once

#include "CachePolicy.hpp"
#include <unordered_map>
#include <queue>
#include <stdexcept>

template <typename K, typename V>
class FIFOCache : public CachePolicy<K, V> {
private:
    int capacity;
    int hits;
    int misses;

    std::queue<K> fifoQueue;
    std::unordered_map<K, V> cacheMap;

public:
    explicit FIFOCache(int capacity);

    V get(const K& key) override;
    void put(const K& key, const V& value) override;
    void display() const override;
    int getHits() const override;
    int getMisses() const override;
};