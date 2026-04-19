# Cache Simulator

A C++ implementation of a Cache Simulator supporting three eviction policies — LRU, LFU, and FIFO — with a full unit test suite and an interactive Python Flask web visualizer.

---

## Features

- Three cache eviction policies: LRU (Least Recently Used), LFU (Least Frequently Used), FIFO (First In First Out)
- Generic implementation using C++ templates — works with any key-value type
- Abstract base class with polymorphism — policies are interchangeable at runtime
- O(1) time complexity for get and put operations
- Hit/miss tracking with hit rate statistics
- 25 unit tests across all three policies using Google Test
- Interactive web visualizer built with Flask showing live cache state

---

## Tech Stack

| Layer | Technology |
|---|---|
| Core Logic | C++17 |
| OOP Design | Abstract classes, Inheritance, Polymorphism |
| Data Structures | Doubly Linked List, HashMap, Queue |
| Build System | CMake 3.15+ |
| Unit Testing | Google Test v1.14.0 |
| Visualizer Backend | Python, Flask |
| Visualizer Frontend | HTML, CSS, JavaScript |

---

## Project Structure

```
cache-simulator/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── include/
│   ├── CachePolicy.hpp       ← Abstract base class
│   ├── LRUCache.hpp
│   ├── LFUCache.hpp
│   └── FIFOCache.hpp
├── src/
│   ├── LRUCache.cpp
│   ├── LFUCache.cpp
│   └── FIFOCache.cpp
├── cli/
│   └── main.cpp              ← Interactive terminal interface
├── tests/
│   ├── test_lru.cpp
│   ├── test_lfu.cpp
│   └── test_fifo.cpp
└── visualizer/
    ├── app.py                ← Flask backend
    └── templates/
        └── index.html        ← Web UI
```
---

## How It Works

### LRU (Least Recently Used)
Evicts the key that has not been accessed for the longest time. Implemented using a doubly linked list and a hashmap for O(1) get and put operations.

### LFU (Least Frequently Used)
Evicts the key with the lowest access frequency. Uses two hashmaps — one for key-to-node mapping and one for frequency-to-key-list mapping — maintaining O(1) complexity.

### FIFO (First In First Out)
Evicts the key that was inserted first regardless of access pattern. Implemented using a queue and a hashmap for O(1) operations.

---

## Getting Started

### Prerequisites

- C++17 compatible compiler (MSVC, GCC, Clang)
- CMake 3.15+
- Python 3.x
- Flask (`pip install flask`)

---

### Build and Run (CLI)

```bash
git clone https://github.com/Anish-000/cache-simulator.git
cd cache-simulator
mkdir build
cd build
cmake ..
cmake --build .
.\Debug\cache_simulator.exe
```

---

### Run Unit Tests

```bash
cd build
.\Debug\test_lru.exe
.\Debug\test_lfu.exe
.\Debug\test_fifo.exe
```

---

### Run Web Visualizer

```bash
cd visualizer
pip install flask
python app.py
```

---

## Unit Test Coverage

| Policy | Tests | Status |
|---|---|---|
| LRU | 8 | Passed |
| LFU | 9 | Passed |
| FIFO | 8 | Passed |
| **Total** | **25** | **All Passed** |

---

## Key Concepts Demonstrated

- Object Oriented Programming — abstraction, inheritance, polymorphism, encapsulation
- Data Structures — doubly linked list, hashmap, queue, ordered map
- C++ Templates — generic cache working with any data type
- Smart Pointers — `std::unique_ptr` for safe memory management
- Unit Testing — Google Test framework with 25 test cases
- Build Systems — CMake with automatic Google Test integration via FetchContent
- REST API — Flask backend with JSON endpoints
- Frontend — vanilla HTML/CSS/JS with live UI updates

---

## Future Improvements

- [ ] Thread safety using mutexes (Phase 6)
- [ ] TTL (Time To Live) expiry for cache entries (Phase 8)
- [ ] Persistent storage to disk (Phase 8)
- [ ] Performance benchmarking and comparison between policies
- [ ] Docker containerization

---

## Author

**Anish Chattopadhyay**  
MCA Student — University of Kalyani  
[LinkedIn](https://linkedin.com/in/anish-chattopadhyay-6659192b9) | [GitHub](https://github.com/Anish-000)
