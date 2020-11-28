CC=g++
FLAGS= -lgtest -lgtest_main -pthread -lm

all: ete gtest

ete: main

main: main.o
	$(CC) main.o -o main $(FLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp	


gtest: main_gtest

main_gtest: main_gtest.o det_test.o
	$(CC) main_gtest.o det_test.o -o main_gtest $(FLAGS)

main_gtest.o: main_gtest.cpp
	$(CC) $(FLAGS) -c main_gtest.cpp

det_test.o: det_test.cpp
	$(CC) $(FLAGS) -c det_test.cpp

clean:
	rm -rf *.o main_gtest main