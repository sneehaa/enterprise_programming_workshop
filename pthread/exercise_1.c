#include <stdio.h>
#include <pthread.h>

void* print_id(void* arg) {
    printf("Thread ID: %lu\n", pthread_self());
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[5];

    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, print_id, NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
