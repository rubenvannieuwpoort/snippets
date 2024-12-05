#include <stdint.h>
#include <immintrin.h>


void run(uint64_t times, uint64_t size, void *_source, void *_target) {
	__m256i *source = (__m256i *)_source;
	__m256i *target = (__m256i *)_target;

	for (uint64_t j = 0; j < times; j++) {
		for (uint64_t i = 0; i < size / 32; i++) {
			_mm256_store_si256(&target[i], _mm256_load_si256(&source[i]));
		}
		asm volatile ("nop");
	}
}
