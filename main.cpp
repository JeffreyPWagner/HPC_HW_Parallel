#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
// pi.cc
//
// program to calculate pi

#include <iostream>
#include <cstdlib>
#include "omp.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

int main (int argc, char *argv[])
{
    if (argc != 2) {
        cerr << "usage: pi num_steps" << endl;
        exit(-1);
    }

    cout << "Max threads: " << omp_get_max_threads() << "\n";
    // num_steps is number of rectangles to use
    long int num_steps = atol (argv[1]);
    // step is width of each rectangle
    double step = 1.0/(double) num_steps;

    // x is midpoint of each rectangle
    // sum accumulates rectangle heights (i.e. values of f(x))
    double x, sum = 0.0;

    auto start = std::chrono::system_clock::now();

    //#pragma omp parallel for reduction(+: sum) private(x)
    for (long int i=1; i <= num_steps; i++){
        x = (i - 0.5) * step;
        sum = sum + 4.0 / (1.0 + x*x);
    }

    std::chrono::duration<double> duration = (std::chrono::system_clock::now() - start);

    // pi is area under curve (sum of rectangle areas)
    cout << "Pi is about " << sum * step << endl;
    cout << "This run took: " << duration.count() << " seconds";

    return 0;
}
