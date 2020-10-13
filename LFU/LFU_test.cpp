#include "LFU.hpp"
#include <gtest/gtest.h>

const size_t cache_size = 25;

TEST(LFU_cache, initialization) {
    
    LFU::LFU_Cache<int> cache(cache_size);

    ASSERT_EQ(cache.GetSmallestFrequency(), 1);
    ASSERT_EQ(cache.GetCacheSize(), cache_size);
    ASSERT_EQ(cache.GetItemsNumInCache(), 0);

}

TEST(LFU_cache, full_cache_test) {
    
    LFU::LFU_Cache<int> cache(cache_size);

    for(int i = 1; i <= cache_size; i++) {
        ASSERT_FALSE(cache.LookUp(i));
        ASSERT_EQ(cache.GetSmallestFrequency(), 1);
        ASSERT_EQ(cache.GetItemsNumInCache(), i);
    }

}

TEST(LFU_cache, cache_overflow_test) {
    
    LFU::LFU_Cache<int> cache(cache_size);

    for(int i = 1; i <= 100; i++) {
        ASSERT_FALSE(cache.LookUp(i));
        ASSERT_EQ(cache.GetSmallestFrequency(), 1);
        if(i <= cache_size) {
            ASSERT_EQ(cache.GetItemsNumInCache(), i);
        } else {
            ASSERT_EQ(cache.GetItemsNumInCache(), 25);
        }
    }

}

TEST(LFU_cache, check_frequency_increase) {
    
    LFU::LFU_Cache<int> cache(cache_size);

    for(int k = 1; k <= 10; k++) {
        for(int i = 1; i <= cache_size; i++) {
            if(k == 1) {
                ASSERT_EQ(cache.GetSmallestFrequency(), k);
                ASSERT_FALSE(cache.LookUp(i));
                ASSERT_EQ(cache.GetItemsNumInCache(), i);
            } else {

                ASSERT_TRUE(cache.LookUp(i));
                ASSERT_EQ(cache.GetItemsNumInCache(), 25);
                if(i == cache_size) {
                    ASSERT_EQ(cache.GetSmallestFrequency(), k);
                } 
                else {
                     ASSERT_EQ(cache.GetSmallestFrequency(), k - 1);
                }
                
            }
        
        }
    }
}

TEST(LFU_cache, complete_test) {
    LFU::LFU_Cache<int> cache(cache_size);
    size_t cnt = cache_size / 3;
    int elem = 1;
    size_t i_lim = 0;

    for(int k = 1; k <= cnt; k++) {
        if(k != cnt) {
            i_lim = k * 3;
        } else {
            i_lim = cache_size;  
        }

        for(int repeat = 1; repeat <= k; repeat++) {
            for(int elem = (k - 1) * 3 + 1; elem <= i_lim; elem++) { 
                if(repeat == 1) {
                    ASSERT_FALSE(cache.LookUp(elem));
                    ASSERT_EQ(cache.GetItemsNumInCache(), elem);
                } else {
                    ASSERT_TRUE(cache.LookUp(elem));
                    ASSERT_EQ(cache.GetItemsNumInCache(), i_lim);
                }
                ASSERT_EQ(cache.GetSmallestFrequency(), 1);
            }
        }
    }

    ASSERT_EQ(cache.GetSmallestFrequency(), 1);
    ASSERT_EQ(cache.GetItemsNumInCache(), cache_size);

    size_t min_freq = 1;
    for(int k = 1; k <= cnt; k++) {

        if(k != cnt) {
            i_lim = k * 3;
        } else {
            i_lim = cache_size;  
        }

        
        for(int repeat = k; repeat <= cnt; repeat++) {
            for(int elem = (k - 1) * 3 + 1; elem <= i_lim; elem++) {
                ASSERT_TRUE(cache.LookUp(elem));
                ASSERT_EQ(cache.GetItemsNumInCache(), cache_size);
            }
            if(repeat == k) {
                min_freq++;
            }
            ASSERT_EQ(cache.GetSmallestFrequency(), min_freq);
        }
    }

    ASSERT_EQ(cache.GetSmallestFrequency(), cnt + 1);

    for(int elem = cache_size + 1; elem <= 2 * cache_size; elem++) {
        ASSERT_FALSE(cache.LookUp(elem));
        ASSERT_EQ(cache.GetItemsNumInCache(), cache_size);
    }
}