cmake_minimum_required(VERSION 3.15)
project(CacheSimulator VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    scr/LRUCache.cpp
)

add_executable(cache_simulator
    cli/main.cpp
    ${SOURCES}
)

target_include_directories(cache_simulator PRIVATE include)