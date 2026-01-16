#include <stdio.h>
#include <pthread.h>

void* square(void* arg) {
    int x = *(int*)arg;
    printf("Square of %d is %d\n", x, x*x);
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    int num = 5;
    pthread_create(&tid, NULL, square, &num);
    pthread_join(tid, NULL);
    return 0;

}