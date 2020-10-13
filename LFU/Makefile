CC=g++
CFLAGS= -lgtest -lgtest_main -pthread

#all: test

test: main.o LFU_test.o
	$(CC) main.o LFU_test.o -o test $(CFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

LFU_test.o: LFU_test.cpp
	$(CC) $(CFLAGS) -c LFU_test.cpp

clean:
	rm -rf *.o test