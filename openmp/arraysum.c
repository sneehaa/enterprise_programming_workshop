// Sum all elements of an array using OpenMP reduction

#include <stdio.h>
#include <omp.h>

int main() {
    int a[8] = {1,2,3,4,5,6,7,8};
    int sum = 0;
    
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < 8; i++){
        sum += a[i];
    }

    printf("Sum = %d\n", sum);
    return 0;

}