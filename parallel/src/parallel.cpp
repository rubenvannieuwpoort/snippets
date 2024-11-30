#include <thread>
#include <vector>
#include <atomic>
#include <cstdint>
#include <iostream>
#include <functional>

#include "hash.hpp"
#include "stopwatch.hpp"

const uint32_t n = 100000000;

uint32_t sum = 0;
void computeRange(uint32_t start, uint32_t end) {
	// TODO: implement
}

int main() {
	StopWatch s;
	s.Start();

	const int numThreads = 1;

	// initialize threads
	std::vector<std::thread> threads;
	for (int i = 0; i < numThreads; i++) {
		uint32_t lo = (n * i) / numThreads;
		uint32_t hi = (n * (i + 1)) / numThreads;
		threads.emplace_back(computeRange, lo, hi);
	}

	// wait for threads to finish
	for (auto& thread : threads) {
		thread.join();
	}

	s.Stop();
	std::cout << "0x" << std::hex << sum << " (" << s.Time() << "s)\n";
}
