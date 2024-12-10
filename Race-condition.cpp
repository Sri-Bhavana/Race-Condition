#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

// Instrumented shared data with atomic operations
std::atomic<int> sharedCounter = 0;

void incrementCounter() {
    for (int i = 0; i < 100000; ++i) {
        sharedCounter.fetch_add(1, std::memory_order_relaxed);
    }
}

int main() {
    const int numThreads = 4;
    std::thread threads[numThreads];

    // Start multiple threads incrementing the shared counter
    for (int i = 0; i < numThreads; ++i) {
        threads[i] = std::thread(incrementCounter);
    }

    // Wait for all threads to complete
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }

    // Check for race conditions by verifying the final value of the shared counter
    int finalCounterValue = sharedCounter.load(std::memory_order_relaxed);
    std::cout << "Final value of sharedCounter: " << finalCounterValue << std::endl;

    if (finalCounterValue != numThreads * 100000) {
        std::cout << "Race condition detected!" << std::endl;
    }
    else {
        std::cout << "No race condition detected." << std::endl;
    }

    return 0;
}