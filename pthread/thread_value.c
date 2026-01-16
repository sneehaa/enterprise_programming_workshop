#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* sum(void* arg) {
    int* arr = (int*)arg;
    int* result = malloc(sizeof(int));
    *result = arr[0] + arr[1];
    pthread_exit(result);
}

int main() {
    pthread_t tid;
    int nums[2] = {10, 20};
    int* res;

    pthread_create(&tid, NULL, sum, nums);
    pthread_join(tid, (void**)&res);

    printf("Sum = %d\n", *res);
    free(res);

    return 0;
}
