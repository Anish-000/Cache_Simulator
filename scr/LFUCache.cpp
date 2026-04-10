#include "LFUCache.hpp"
#include <iostream>

template <typename K, typename V>
LFUCache<K, V>::LFUCache(int cap) {
    if (cap <= 0) {
        throw std::invalid_argument("Cache capacity must be greater than 0");
    }
    capacity = cap;
    minFreq = 0;
    hits = 0;
    misses = 0;
}

template <typename K, typename V>
V LFUCache<K, V>::get(const K& key) {
    auto it = keyMap.find(key);

    if (it == keyMap.end()) {
        misses++;
        throw std::runtime_error("Cache miss - key not found");
    }

    hits++;
    auto nodeIt = it->second;
    Node node = *nodeIt;

    freqMap[node.freq].erase(nodeIt);
    if (freqMap[node.freq].empty()) {
        freqMap.erase(node.freq);
        if (minFreq == node.freq) {
            minFreq++;
        }
    }

    node.freq++;
    freqMap[node.freq].push_front(node);
    keyMap[key] = freqMap[node.freq].begin();

    return node.value;
}

template <typename K, typename V>
void LFUCache<K, V>::put(const K& key, const V& value) {
    if (capacity <= 0) return;

    auto it = keyMap.find(key);

    if (it != keyMap.end()) {
        it->second->value = value;
        get(key);
        return;
    }

    if ((int)keyMap.size() >= capacity) {
        auto& minFreqList = freqMap[minFreq];
        auto last = minFreqList.back();
        keyMap.erase(last.key);
        minFreqList.pop_back();
        if (minFreqList.empty()) {
            freqMap.erase(minFreq);
        }
    }

    Node newNode = {key, value, 1};
    freqMap[1].push_front(newNode);
    keyMap[key] = freqMap[1].begin();
    minFreq = 1;
}

template <typename K, typename V>
void LFUCache<K, V>::display() const {
    if (keyMap.empty()) {
        std::cout << "Cache is empty\n";
        return;
    }

    std::cout << "\n--- LFU Cache State ---\n";
    std::cout << "Capacity : " << capacity << "\n";
    std::cout << "Size     : " << keyMap.size() << "\n";
    std::cout << "Hits     : " << hits << "\n";
    std::cout << "Misses   : " << misses << "\n";
    std::cout << "Hit Rate : ";

    int total = hits + misses;
    if (total == 0) {
        std::cout << "N/A\n";
    } else {
        std::cout << (hits * 100 / total) << "%\n";
    }

    std::cout << "\n[Frequency → Keys]\n";
    for (const auto& pair : freqMap) {
        std::cout << "freq " << pair.first << " : ";
        for (const auto& node : pair.second) {
            std::cout << "[key: " << node.key
                      << " | val: " << node.value << "] ";
        }
        std::cout << "\n";
    }
    std::cout << "-----------------------\n";
}

template <typename K, typename V>
int LFUCache<K, V>::getHits() const {
    return hits;
}

template <typename K, typename V>
int LFUCache<K, V>::getMisses() const {
    return misses;
}

template class LFUCache<int, int>;
template class LFUCache<std::string, std::string>;
template class LFUCache<std::string, int>;