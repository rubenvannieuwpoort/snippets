main: main.cpp experiments/load_buffering.cpp experiments/message_passing.cpp experiments/store_buffering.cpp
	g++ main.cpp experiments/message_passing.cpp experiments/store_buffering.cpp experiments/load_buffering.cpp -O3 -o main

.PHONY: clean

clean:
	rm -rf main
