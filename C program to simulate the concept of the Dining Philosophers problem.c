#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Number of philosophers
sem_t chopstick[N];  // Semaphores for chopsticks

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        // Pick up left chopstick
        sem_wait(&chopstick[left]);
        printf("Philosopher %d picked up left chopstick\n", id);

        // Pick up right chopstick
        sem_wait(&chopstick[right]);
        printf("Philosopher %d picked up right chopstick and is eating\n", id);
        sleep(1);

        // Release chopsticks
        printf("Philosopher %d finished eating and released chopsticks\n", id);
        sem_post(&chopstick[right]);
        sem_post(&chopstick[left]);
    }
    return NULL;
}

int main() {
    pthread_t p[N];
    int id[N];

    // Initialize semaphores
    for (int i = 0; i < N; i++) {
        sem_init(&chopstick[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&p[i], NULL, philosopher, &id[i]);
    }

    // Join threads
    for (int i = 0; i < N; i++) {
        pthread_join(p[i], NULL);
    }

    // Destroy semaphores
    for (int i = 0; i < N; i++) {
        sem_destroy(&chopstick[i]);
    }

    return 0;
}

