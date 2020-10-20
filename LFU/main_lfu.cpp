#include "LFU.hpp"
#include <cassert>


int main() {
    int m, n;

    std::cin >> m >> n;
    LFU::LFU_Cache<int, int> cache(m);
    size_t hits = 0;
    int key;
    for(int i = 0; i < n; ++i) {
        std::cin >> key; 
        assert(std::cin.good());
        
        if (cache.LookUp(key)) {
            hits += 1;
        } 
        cache.InsertData(key, i);
    }

    std::cout << hits;

    return 0;

}
