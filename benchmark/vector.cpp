/*
    Benchmark instance monitoring
    the execution time of some Vector
    (vector.hpp) class' functions.
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <ctime>
#include "benchmark.hpp"
#include "vector.hpp"

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

typedef struct {
    Vector u;
    Vector v;
    Vector w;
} Tuple;

class VectorWrapper : public TestUnit<Tuple> {
    public:
        VectorWrapper(Tuple* tuple) : TestUnit<Tuple>(tuple) {}

        void init() {
            _args->u = Vector(uniform_random(), uniform_random(), uniform_random());
            _args->v = Vector(uniform_random(), uniform_random(), uniform_random());
        }

        void operator()() {
            //for(int i = 0; i < 1; i++) {
                _args->w = _args->u ^ _args->v;
            //}
        }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
    int N;

    if(argc != 2) std::exit(EXIT_FAILURE);
    N = atoi(argv[1]);

    seed_random(std::time(nullptr));

    Tuple tuple;
    VectorWrapper dut(&tuple);
    Benchmark bench(N);

    bench(dut);

    return 0;
}