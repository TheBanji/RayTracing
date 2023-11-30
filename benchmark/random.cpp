////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "benchmark.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

        void operator()() const {
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

    seed_random(std::time(nullptr));
    bench(dut);
    
    return 0;
}