#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
int ready = 0;

void* producer(void* arg) {
    pthread_mutex_lock(&mutex);
    ready = 1;
    printf("Producer produced data\n");
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    pthread_mutex_lock(&mutex);
    while (!ready) {
        pthread_cond_wait(&cond, &mutex);
    }
    printf("Consumer consumed data\n");
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main() {
    pthread_t p, c;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&c, NULL, consumer, NULL);
    pthread_create(&p, NULL, producer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    return 0;
}
