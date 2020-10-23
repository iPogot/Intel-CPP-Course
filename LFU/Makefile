CC=g++
FLAGS= -lgtest -lgtest_main -pthread

all: lfu_gtest lfu_cache

lfu_gtest: main_gtest.o LFU_test.o
	$(CC) main_gtest.o LFU_test.o -o lfu_gtest $(FLAGS)

main_gtest.o: main_gtest.cpp
	$(CC) $(FLAGS) -c main_gtest.cpp

LFU_test.o: LFU_test.cpp
	$(CC) $(FLAGS) -c LFU_test.cpp


lfu_cache: 
	$(CC) main_lfu.cpp -o lfu_cache $(FLAGS)
clean:
	rm -rf *.o lfu_gtest lfu_cache