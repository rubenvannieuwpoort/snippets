#include <cstdint>


uint32_t hash(uint32_t value) {
	static std::atomic<uint32_t> v;
	v = value;
	for (int i = 0; i < 50; i++) {
		v ^= (value >> 17);
		v = v * 0xED5AD4BB;
		v ^= (value >> 11);
		v = v * 0xAC4C1B51;
		v ^= (value >> 15);
		v = v * 0x31848BAB;
		v ^= (value >> 14);
	}
	return v;
}
