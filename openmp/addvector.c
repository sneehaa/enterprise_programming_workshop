// Add two arrays of size N=16 using OpenMP and multiple threads
#include <stdio.h>
#include <omp.h>

int main() {
    int N= 16;
    int a[16], b[16], c[16];

    for(int i = 0; i < N; i++){
       a[i] = i;
       b[i] = i * 2;
    }
    #pragma omp parallel for
    for(int i = 0; i < N; i++){
        c[i] = a[i] + b[i];
    }

    for(int i = 0; i < N; i++)
        printf("%d " , c[i]);

    return 0;
}