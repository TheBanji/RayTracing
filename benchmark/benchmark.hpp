#pragma once

#include <iostream>
#include <cstdlib>
#include <sys/time.h>

template<typename T>
class TestUnit {
    public:
        TestUnit(T* args) : _args(args) {}
        
        virtual void operator()() const = 0;

    protected:
        T* _args;

};

class Benchmark {
    public:
        Benchmark(long iterations) : _iterations(iterations) {
            if(_iterations <= 0) {
                std::cout << "Iterations counter cannot be negative or null." << std::endl;
                std::exit(EXIT_FAILURE); // Should at least perform one iteration, exit otherwise.
            }
        }

        static long get_time() {
            struct timeval time;
            if(gettimeofday(&time, 0)) return (long)-1;
            return (long)(1000000 * time.tv_sec + time.tv_usec);
        }

        template<typename T>
        void operator()(const TestUnit<T>& dut) {
            long i;
            long start, total = 0;
            for(i = 0; i < _iterations; i++) {
                start = get_time();
                dut();
                total += (get_time()-start);
            }

            std::cout << "**** Benchmark results ****" << std::endl;
            std::cout << "Number of iterations:   " << _iterations << std::endl;
            std::cout << "Total execution time:   " << total << "µs." << std::endl;
            std::cout << "Average execution time: " << (double)total/_iterations << "µs." << std::endl;
        }

        void setIterations(long iterations) {
            _iterations = iterations;
        }

        long getIterations() {
            return _iterations;
        }
    
    private:
        long _iterations;
};