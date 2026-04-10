cmake_minimum_required(VERSION 3.15)
project(CacheSimulator VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    scr/LRUCache.cpp
    scr/LFUCache.cpp
    scr/FIFOCache.cpp
)

add_executable(cache_simulator
    cli/main.cpp
    ${SOURCES}
)

target_include_directories(cache_simulator PRIVATE include)

# Google Test setup
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_lru tests/test_lru.cpp ${SOURCES})
target_include_directories(test_lru PRIVATE include)
target_link_libraries(test_lru GTest::gtest_main)

add_executable(test_lfu tests/test_lfu.cpp ${SOURCES})
target_include_directories(test_lfu PRIVATE include)
target_link_libraries(test_lfu GTest::gtest_main)

add_executable(test_fifo tests/test_fifo.cpp ${SOURCES})
target_include_directories(test_fifo PRIVATE include)
target_link_libraries(test_fifo GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_lru)
gtest_discover_tests(test_lfu)
gtest_discover_tests(test_fifo)