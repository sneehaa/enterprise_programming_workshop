#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX 100000

typedef struct {
    int start;
    int end;
    int thread_no;
} thread_data;

void* print_numbers(void* arg) {
    thread_data* data = (thread_data*)arg;

    printf("Thread %d printing from %d to %d\n",
           data->thread_no, data->start, data->end);

    for (int i = data->start; i <= data->end; i++) {
        printf("%d ", i);
    }

    printf("\n");
    pthread_exit(NULL);
}

int main() {
    int n;
    printf("Enter number of threads: ");
    scanf("%d", &n);

    pthread_t threads[n];
    thread_data data[n];

    int chunk = MAX / n;
    int current = 1;

    for (int i = 0; i < n; i++) {
        data[i].start = current;
        data[i].end = (i == n - 1) ? MAX : current + chunk - 1;
        data[i].thread_no = i + 1;

        pthread_create(&threads[i], NULL, print_numbers, &data[i]);
        current = data[i].end + 1;
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
