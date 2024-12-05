#include <stdint.h>
#include <string.h>


uint64_t run(uint64_t times, uint64_t size, void *_source, void *_target) {
	for (uint64_t i = 0; i < times; i++) {
		memcpy(_target, _source, size);
	}
	return 0;
}
