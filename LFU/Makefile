CC=g++
CFLAGS= -lgtest -lgtest_main -pthread

#all: test

# lfu_gtest: main_gtest.o LFU_test.o
# 	$(CC) main_gtest.o LFU_test.o -o lfu_gtest $(CFLAGS)

# main_gtest.o: main_gtest.cpp
# 	$(CC) $(CFLAGS) -c main_gtest.cpp

# LFU_test.o: LFU_test.cpp
# 	$(CC) $(CFLAGS) -c LFU_test.cpp

# clean:
# 	rm -rf *.o test

lfu_cache: 
	$(CC) main_lfu.cpp -o lfu_cache $(CFLAGS)
clean:
	rm -rf *.o lfu_cache