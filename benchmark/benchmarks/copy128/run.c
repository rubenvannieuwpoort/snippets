#include <stdint.h>
#include <immintrin.h>


void run(uint64_t times, uint64_t size, void *_source, void *_target) {
	__m128i *source = (__m128i *)_source;
	__m128i *target = (__m128i *)_target;

	for (uint64_t j = 0; j < times; j++) {
		for (uint64_t i = 0; i < size / 16; i++) {
			_mm_store_si128(&target[i], _mm_load_si128(&source[i]));
		}
		asm volatile ("nop");
	}
}