
#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
    int number = *(int *)arg;
    printf("Thread %d is running. Thread ID: %lu\n", number, (unsigned long)pthread_self());
    return NULL;
}

int main() {
    pthread_t threads[3];
    int numbers[3] = {1, 2, 3};
    
    for (int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, &numbers[i]) != 0) {
            fprintf(stderr, "Thread creation failed\n");
            return 1;
        }
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
