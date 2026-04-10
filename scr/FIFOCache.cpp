#include "FIFOCache.hpp"
#include <iostream>

template <typename K, typename V>
FIFOCache<K, V>::FIFOCache(int cap) {
    if (cap <= 0) {
        throw std::invalid_argument("Cache capacity must be greater than 0");
        }
    capacity = cap;
    hits = 0;
    misses = 0;
}

template <typename K, typename V>
V FIFOCache<K, V>::get(const K& key) {
    auto it = cacheMap.find(key);

    if (it == cacheMap.end()) {
        misses++;
        throw std::runtime_error("Cache miss - key not found");
    }

    hits++;
    return it->second;
}

template <typename K, typename V>
void FIFOCache<K, V>::put(const K& key, const V& value) {
    auto it = cacheMap.find(key);

    if (it != cacheMap.end()) {
        it->second = value;
        return;
    }

    if ((int)cacheMap.size() >= capacity) {
        K oldest = fifoQueue.front();
        fifoQueue.pop();
        cacheMap.erase(oldest);
    }

    cacheMap[key] = value;
    fifoQueue.push(key);
}

template <typename K, typename V>
void FIFOCache<K, V>::display() const {
    if (cacheMap.empty()) {
        std::cout << "Cache is empty\n";
        return;
    }

    std::cout << "\n--- FIFO Cache State ---\n";
    std::cout << "Capacity : " << capacity << "\n";
    std::cout << "Size     : " << cacheMap.size() << "\n";
    std::cout << "Hits     : " << hits << "\n";
    std::cout << "Misses   : " << misses << "\n";
    std::cout << "Hit Rate : ";

    int total = hits + misses;
    if (total == 0) {
        std::cout << "N/A\n";
    } else {
        std::cout << (hits * 100 / total) << "%\n";
    }

    std::cout << "\n[Insertion Order: oldest → newest]\n";
    std::queue<K> temp = fifoQueue;
    int position = 1;
    while (!temp.empty()) {
        K key = temp.front();
        temp.pop();
        std::cout << position << ". key: " << key
                  << " | value: " << cacheMap.at(key) << "\n";
        position++;
    }
    std::cout << "------------------------\n";
}

template <typename K, typename V>
int FIFOCache<K, V>::getHits() const {
    return hits;
}

template <typename K, typename V>
int FIFOCache<K, V>::getMisses() const {
    return misses;
}

template class FIFOCache<int, int>;
template class FIFOCache<std::string, std::string>;
template class FIFOCache<std::string, int>;