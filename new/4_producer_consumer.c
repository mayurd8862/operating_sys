#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];

// Variables for tracking the index to insert and remove items from the buffer
int in = 0; // Index for inserting items
int out = 0; // Index for removing items

// Semaphore declarations synchronization mechanism used in concurrent programming to control access to shared resources
sem_t empty; // Semaphore to track empty slots in the buffer
sem_t full;  // Semaphore to track filled slots in the buffer

// Producer function
void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = rand() % 100; // Generate a random item

        sem_wait(&empty); // Wait if the buffer is full
        buffer[in] = item; // Add the item to the buffer
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE; // Move the insert index
        sem_post(&full); // Signal that a slot is filled
    }
    pthread_exit(NULL);
}

// Consumer function
void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        sem_wait(&full); // Wait if the buffer is empty
        item = buffer[out]; // Remove an item from the buffer
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE; // Move the remove index
        sem_post(&empty); // Signal that a slot is empty
    }
    pthread_exit(NULL);
}

int main() {
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // All slots are initially empty
    sem_init(&full, 0, 0); // No slots are initially full

    // Create producer and consumer threads
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

