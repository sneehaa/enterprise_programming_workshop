#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int N;
long sum = 0;
pthread_mutex_t lock;

void* calculate_sum(void* arg) {
    pthread_mutex_lock(&lock);
    for (int i = 1; i <= N; i++) {
        sum += i;
    }
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;

    printf("Enter N: ");
    scanf("%d", &N);

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, calculate_sum, NULL);
    pthread_create(&t2, NULL, calculate_sum, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Sum = %ld\n", sum);

    pthread_mutex_destroy(&lock);
    return 0;
}
