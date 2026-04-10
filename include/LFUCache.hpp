#pragma once

#include "CachePolicy.hpp"
#include <unordered_map>
#include <list>
#include <stdexcept>

template <typename K, typename V>
class LFUCache : public CachePolicy<K, V> {
private:
    int capacity;
    int minFreq;
    int hits;
    int misses;

    struct Node {
        K key;
        V value;
        int freq;
    };

    std::unordered_map<K, typename std::list<Node>::iterator> keyMap;
    std::unordered_map<int, std::list<Node>> freqMap;

public:
    explicit LFUCache(int capacity);

    V get(const K& key) override;
    void put(const K& key, const V& value) override;
    void display() const override;
    int getHits() const override;
    int getMisses() const override;
};