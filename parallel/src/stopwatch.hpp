#include <chrono>
#include <iostream>


class StopWatch {
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

public:
	void Start() {
		this->startTime = std::chrono::high_resolution_clock::now();
	}

	void Stop() {
		this->endTime = std::chrono::high_resolution_clock::now();
	}

	double Time() {
		std::chrono::duration<double> d = endTime - startTime;
		return d.count();
	}
};
