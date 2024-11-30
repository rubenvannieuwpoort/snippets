#include <atomic>
#include <thread>

#include "../barrier.hpp"

static constexpr int N = 10000000;

static std::atomic<int> x(0), y(0);
static std::atomic<uint32_t> barrier(0);

static void otherThread() {
    for (int i = 0; i < N; ++i) {
        barrier_wait(&barrier);

        std::atomic_store_explicit(&x, 1, std::memory_order_relaxed);
        std::atomic_store_explicit(&y, 1, std::memory_order_relaxed);

        barrier_wait(&barrier);
    }
}

int messagePassing() {
    int count = 0, r1, r2;
    std::thread t(otherThread);

    for (int i = 0; i < N; i++) {
        // initialize variables
        x = 0; y = 0;
        r1 = 0; r2 = 0;

        // synchronize
        barrier_wait(&barrier);

        // experiment
        r1 = std::atomic_load_explicit(&y, std::memory_order_relaxed);
        r2 = std::atomic_load_explicit(&x, std::memory_order_relaxed);

        barrier_wait(&barrier);

        // administration
        count += r1 == 1 && r2 == 0;
    }

    t.join();
    return count;
}
