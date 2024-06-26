/*
    Benchmark instance monitoring
    the execution time of uniform_random.
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "benchmark.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_INT 100000000000000

void seed_random(long long seed) {
    std::srand(seed);
}

double uniform_random() {
    #ifdef __linux__
    return (double)drand48();
    #elif __APPLE__
    return (double)drand48();
    #elif _WIN32
    return (double)std::rand() / MAX_INT;
    #endif
}

class RandomWrapper : public TestUnit<void> {
    public:
        RandomWrapper() : TestUnit<void>(NULL) {}

        void init() {
            seed_random(std::time(nullptr));
        }

        void operator()() {
            uniform_random();
        }

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
    int N;
    
    if(argc != 2) return EXIT_FAILURE;
    N = atoi(argv[1]);
    
    RandomWrapper dut;
    Benchmark bench(N);

    bench(dut);
    
    return 0;
}