.PHONY: all clean run
all: test
test: main.o min_circle.o
	g++ main.o min_circle.o -o test
main.o: main.cpp
	g++ -c main.cpp
min_circle.o: min_circle.cpp
	g++ -c min_circle.cpp
clean:
	rm -rf *.o test
run: all
	./test
