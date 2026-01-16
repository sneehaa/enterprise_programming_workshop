// Estimate π using the Monte Carlo method with OpenMP

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main() {
    int N = 1000000;
    int count = 0;

    #pragma omp parallel
    {
        unsigned int seed = omp_get_thread_num();
        int local = 0;

        #pragma omp for
        for(int i = 0; i < N; i++){
            double x = rand_r(&seed) / (double)RAND_MAX;
            double y = rand_r(&seed) / (double)RAND_MAX;
            if(x*x + y*y <= 1.0)
            local++;
        }
        #pragma omp atomic
        count += local;
    }

    double pi = 4.0 * count / N;
    printf ("Estimated Pi = %f\n", pi);

    return 0;
}