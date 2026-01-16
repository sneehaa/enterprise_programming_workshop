#include <stdio.h>
#include <pthread.h>

#define SIZE 5

int buffer[SIZE];
int count = 0;

pthread_mutex_t mutex;
pthread_cond_t not_full;
pthread_cond_t not_empty;

void* producer(void* arg) {
    pthread_mutex_lock(&mutex);

    while (count == SIZE) {
        pthread_cond_wait(&not_full, &mutex);
    }

    buffer[count++] = 1;
    printf("Produced item\n");

    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    pthread_mutex_lock(&mutex);

    while (count == 0) {
        pthread_cond_wait(&not_empty, &mutex);
    }

    count--;
    printf("Consumed item\n");

    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main() {
    pthread_t p, c;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    return 0;
}
