#include "LRUCache.hpp"
#include <iostream>
#include <stdexcept>

template <typename K, typename V>
LRUCache<K, V>::LRUCache(int cap) {
    if (cap <= 0) {
        throw std::invalid_argument("Cache capacity must be greater than 0");
    }
    capacity = cap;
    hits = 0;
    misses = 0;
}

template <typename K, typename V>
V LRUCache<K, V>::get(const K& key) {
    auto it = cacheMap.find(key);
    
    if (it == cacheMap.end()) {
        misses++;
        throw std::runtime_error("Cache miss - key not found");
    }
    
    hits++;
    cacheList.splice(cacheList.begin(), cacheList, it->second);
    return it->second->second;
}

template <typename K, typename V>
void LRUCache<K, V>::put(const K& key, const V& value) {
    auto it = cacheMap.find(key);
    
    if (it != cacheMap.end()) {
        it->second->second = value;
        cacheList.splice(cacheList.begin(), cacheList, it->second);
        return;
    }
    
    if ((int)cacheList.size() >= capacity) {
        auto last = cacheList.back();
        cacheMap.erase(last.first);
        cacheList.pop_back();
    }
    
    cacheList.push_front({key, value});
    cacheMap[key] = cacheList.begin();
}

template <typename K, typename V>
void LRUCache<K, V>::display() const {
    if (cacheList.empty()) {
        std::cout << "Cache is empty\n";
        return;
    }
    
    std::cout << "\n--- LRU Cache State ---\n";
    std::cout << "Capacity : " << capacity << "\n";
    std::cout << "Size     : " << cacheList.size() << "\n";
    std::cout << "Hits     : " << hits << "\n";
    std::cout << "Misses   : " << misses << "\n";
    std::cout << "Hit Rate : ";
    
    int total = hits + misses;
    if (total == 0) {
        std::cout << "N/A\n";
    } else {
        std::cout << (hits * 100 / total) << "%\n";
    }
    
    std::cout << "\n[MRU] → [LRU]\n";
    int position = 1;
    for (const auto& pair : cacheList) {
        std::cout << position << ". key: " << pair.first
                  << " | value: " << pair.second << "\n";
        position++;
    }
    std::cout << "-----------------------\n";
}

template <typename K, typename V>
int LRUCache<K, V>::getHits() const {
    return hits;
}

template <typename K, typename V>
int LRUCache<K, V>::getMisses() const {
    return misses;
}

template class LRUCache<int, int>;
template class LRUCache<std::string, std::string>;
template class LRUCache<std::string, int>;