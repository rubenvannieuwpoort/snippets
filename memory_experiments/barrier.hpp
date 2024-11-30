#pragma once

#include <atomic>
#include <cstdint>

inline void barrier_wait(std::atomic<uint32_t> *barrier) {
    uint32_t v = ++*barrier;
    if (v & 1) {
        for (v &= 2; (*barrier & 2) == v;);
    }
}
