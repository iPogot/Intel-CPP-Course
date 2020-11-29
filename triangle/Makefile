CC=g++
FLAGS= -lgtest -lgtest_main -pthread -lm

test: main_test.o point.o vector.o line.o plane.o triangle.o
	$(CC) main_test.o point.o vector.o line.o plane.o triangle.o -o test $(FLAGS)

main_test.o: main_test.cpp
	$(CC) $(FLAGS) -c main_test.cpp

point.o: point.cpp
	$(CC) $(FLAGS) -c point.cpp

vector.o: vector.cpp
	$(CC) $(FLAGS) -c vector.cpp

line.o: line.cpp
	$(CC) $(FLAGS) -c line.cpp

plane.o: plane.cpp
	$(CC) $(FLAGS) -c plane.cpp

triangle.o: triangle.cpp
	$(CC) $(FLAGS) -c triangle.cpp

clean:
	rm -rf *.o point test
