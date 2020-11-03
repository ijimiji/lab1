CC=g++
CFLAGS=-std=c++17 -o
EXE= main
FILES= main.cpp app.cpp fraction.cpp

all: make run

test: test_build gcov lcov

test_build:
	$(CC) --coverage $(CFLAGS) $(EXE) $(FILES)

gcov:
	gcov $(FILES)

lcov:
	lcov --coverage --directory . --output-file main_coverage.info

clean:
	rm *.gcov
	rm *.gcno
	rm main

make: 
	$(CC) $(CFLAGS) $(EXE) $(FILES)
run:
	./main
