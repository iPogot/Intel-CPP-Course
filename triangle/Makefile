CC=g++
FLAGS= -lgtest -lgtest_main -pthread -lm

all: test 

test: main.o point.o 
	$(CC) main.o point.o -o test $(FLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

point.o: point.cpp
	$(CC) $(FLAGS) -c point.cpp

clean:
	rm -rf *.o point test
