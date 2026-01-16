// Add two arrays of size N=8 using OpenMP

#include <stdio.h>
#include <omp.h>

int main() {
    int N= 8;
    int a[8] = {1,2,3,4,5,6,7,8};
    int b[8] = {8,7,6,5,4,3,2,1};
    int c[8];

    #pragma omp parallel for
    for(int i = 0; i < N; i++){
        c[i] = a[i] + b[i];
    }
    for(int i = 0; i < N; i++)
        printf("%d " , c[i]);

    return 0;
}