#include <stdio.h>
#include <pthread.h>
#define N 4

void* task(void* arg) {
    int id = *(int*)arg;
    printf("Thread %d is running\n", id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[N];
    int ids[N];
    for(int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, task, &ids[i]);
    }
    for(int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}