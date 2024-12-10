#include <iostream>
#include <thread>

int shared_variable = 0;

void increment_variable(int num_increments) {
    for (int i = 0; i < num_increments; ++i) {
        ++shared_variable;
    }
}

int main() {
    const int num_threads = 4;
    const int increments_per_thread = 1000000;

    std::thread threads[num_threads];

    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(increment_variable, increments_per_thread);
    }

    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }

    std::cout << "Final value of shared_variable: " << shared_variable << std::endl;

    return 0;
}