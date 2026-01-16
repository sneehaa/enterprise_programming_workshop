#include <stdio.h>
#include <pthread.h>


void* printMessage(void* arg) {
    printf("Hello from thread!\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, printMessage, NULL);
    pthread_join(tid, NULL);
    printf("Main thread finished.\n");
    return 0;
}