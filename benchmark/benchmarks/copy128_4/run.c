#include <stdint.h>
#include <immintrin.h>


void run(uint64_t times, uint64_t size, void *_source, void *_target) {
	__m128i *source = (__m128i *)_source;
	__m128i *target = (__m128i *)_target;

	for (uint64_t j = 0; j < times; j++) {
		for (uint64_t i = 0; i < size / 16; i += 4) {
			_mm_store_si128(&target[i], _mm_load_si128(&source[i]));
			_mm_store_si128(&target[i + 1], _mm_load_si128(&source[i + 1]));
			_mm_store_si128(&target[i + 2], _mm_load_si128(&source[i + 2]));
			_mm_store_si128(&target[i + 3], _mm_load_si128(&source[i + 3]));
		}
		asm volatile ("nop");
	}
}
