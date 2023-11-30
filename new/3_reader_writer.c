#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_ITERATIONS 20 // Define the maximum number of iterations

sem_t mutex, wrt;
int data = 0;
int reader_count = 0;
int iterations = 0;

void* reader(void* arg) {
    while (1) {
        sem_wait(&mutex);
        reader_count++;
        if (reader_count == 1) {
            sem_wait(&wrt);
        }
        sem_post(&mutex);

        // Reading data
        printf("Reader %ld read data: %d\n", (long)arg, data);

        sem_wait(&mutex);
        reader_count--;
        if (reader_count == 0) {
            sem_post(&wrt);
        }
        sem_post(&mutex);

        iterations++;
        if (iterations >= MAX_ITERATIONS) {
            break;
        }
        sleep(1); // Sleep to simulate reading
    }
    pthread_exit(NULL);
}

void* writer(void* arg) {
    while (1) {
        sem_wait(&wrt);
        data++; // Increment data to simulate writing
        printf("Writer %ld wrote data: %d\n", (long)arg, data);
        sem_post(&wrt);

        iterations++;
        if (iterations >= MAX_ITERATIONS) {
            break;
        }
        sleep(1); // Sleep to simulate writing
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t readers[2];
    pthread_t writers[2];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (long i = 0; i < 2; i++) {
        pthread_create(&readers[i], NULL, reader, (void*)i);
        pthread_create(&writers[i], NULL, writer, (void*)i);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}

