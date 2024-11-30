#include <thread>
#include <cstdint>
#include <iostream>
#include <functional>

#include "hash.hpp"
#include "stopwatch.hpp"


const uint32_t n = 100000000;

uint32_t sum = 0;
void computeRange(uint32_t start, uint32_t end) {
	for (uint32_t i = start; i < end; i++) {
		sum += hash(i);
	}
}

int main() {
	StopWatch s;
	s.Start();

	computeRange(0, n);

	s.Stop();
	std::cout << "0x" << std::hex << sum << " (" << s.Time() << "s)\n";
}
