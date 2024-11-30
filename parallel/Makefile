.PHONY: all

all: serial parallel

serial: src/serial.cpp src/stopwatch.hpp
	g++ src/serial.cpp -O3 -o serial -std=c++11


parallel: src/parallel.cpp src/stopwatch.hpp
	g++ src/parallel.cpp -O3 -o parallel -std=c++11

.PHONY: clean

clean:
	rm -rf serial parallel
