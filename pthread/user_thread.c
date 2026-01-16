#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* thread_function(void* arg) {
    int thread_num = *(int*)arg;
    printf("Hello from thread %d | Thread ID: %lu\n", thread_num, pthread_self());
    pthread_exit(NULL);
}

int main() {
    int n;
    printf("Enter number of threads: ");
    scanf("%d", &n);

    pthread_t threads[n];
    int thread_ids[n];

    for (int i = 0; i < n; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
