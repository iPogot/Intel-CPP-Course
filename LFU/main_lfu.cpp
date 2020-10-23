#include "LFU.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <chrono> 


int main() {
    int m, n;
    //std::cout << "first insert" << std::endl;
    std::cin >> m >> n;
    LFU::LFU_Cache<int, int> cache(m);
    size_t hits = 0;
    int key;

    auto start = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < n; ++i) {
        std::cin >> key; 
        assert(std::cin.good());
        
        if (cache.LookUp(key)) {
            hits += 1;
        } 
        cache.InsertData(key, i);
    }

    auto finish = std::chrono::high_resolution_clock::now();

    std::cout << hits;

    std::chrono::duration<double> elapsed = finish - start;

    std::cerr << "\nElapsed time = " << elapsed.count() << "seconds" << std::endl;

    return 0;

}
