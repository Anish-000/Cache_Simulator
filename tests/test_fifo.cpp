#include <gtest/gtest.h>
#include "FIFOCache.hpp"

TEST(FIFOCacheTest, BasicInsertAndGet) {
    FIFOCache<int, int> cache(3);
    cache.put(1, 100);
    cache.put(2, 200);
    cache.put(3, 300);
    EXPECT_EQ(cache.get(1), 100);
    EXPECT_EQ(cache.get(2), 200);
    EXPECT_EQ(cache.get(3), 300);
}

TEST(FIFOCacheTest, EvictionPolicy) {
    FIFOCache<int, int> cache(3);
    cache.put(1, 100);
    cache.put(2, 200);
    cache.put(3, 300);
    cache.put(4, 400);
    bool evicted = false;
    try { cache.get(1); } catch (const std::runtime_error&) { evicted = true; }
    EXPECT_TRUE(evicted);
    EXPECT_EQ(cache.get(2), 200);
    EXPECT_EQ(cache.get(3), 300);
    EXPECT_EQ(cache.get(4), 400);
}

TEST(FIFOCacheTest, CacheMiss) {
    FIFOCache<int, int> cache(3);
    bool exceptionThrown = false;
    try {
        cache.get(99);
    } catch (const std::runtime_error&) {
        exceptionThrown = true;
    }
    EXPECT_TRUE(exceptionThrown);
}

TEST(FIFOCacheTest, UpdateExistingKey) {
    FIFOCache<int, int> cache(3);
    cache.put(1, 100);
    cache.put(1, 999);
    EXPECT_EQ(cache.get(1), 999);
}

TEST(FIFOCacheTest, UpdateDoesNotChangeOrder) {
    FIFOCache<int, int> cache(2);
    cache.put(1, 100);
    cache.put(2, 200);
    cache.put(1, 999);
    cache.put(3, 300);
    bool evicted = false;
    try { cache.get(1); } catch (const std::runtime_error&) { evicted = true; }
    EXPECT_TRUE(evicted);
    EXPECT_EQ(cache.get(2), 200);
    EXPECT_EQ(cache.get(3), 300);
}

TEST(FIFOCacheTest, HitAndMissCount) {
    FIFOCache<int, int> cache(3);
    cache.put(1, 100);
    cache.get(1);
    try { cache.get(99); } catch (...) {}
    EXPECT_EQ(cache.getHits(), 1);
    EXPECT_EQ(cache.getMisses(), 1);
}

TEST(FIFOCacheTest, InvalidCapacity) {
    bool thrown1 = false;
    bool thrown2 = false;
    try { FIFOCache<int, int> c(0); } catch (const std::invalid_argument&) { thrown1 = true; }
    try { FIFOCache<int, int> c(-1); } catch (const std::invalid_argument&) { thrown2 = true; }
    EXPECT_TRUE(thrown1);
    EXPECT_TRUE(thrown2);
}

TEST(FIFOCacheTest, OldestAlwaysEvicted) {
    FIFOCache<int, int> cache(3);
    cache.put(1, 100);
    cache.put(2, 200);
    cache.put(3, 300);
    cache.get(1);
    cache.get(1);
    cache.get(1);
    cache.put(4, 400);
    bool evicted = false;
    try { cache.get(1); } catch (const std::runtime_error&) { evicted = true; }
    EXPECT_TRUE(evicted);
    EXPECT_EQ(cache.get(2), 200);
    EXPECT_EQ(cache.get(3), 300);
    EXPECT_EQ(cache.get(4), 400);
}