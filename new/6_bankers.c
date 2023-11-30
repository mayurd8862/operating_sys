#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int n, m; // Number of processes and resources

void initialize() {
    // Initialize available, maximum, allocation, and need matrices
    // ...

    // Example Initialization
    n = 5; // Number of processes
    m = 3; // Number of resources

    int avail[] = {3, 3, 2};
    int max[][MAX_RESOURCES] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    int alloc[][MAX_RESOURCES] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};

    for (int i = 0; i < m; i++) {
        available[i] = avail[i];
        for (int j = 0; j < n; j++) {
            maximum[j][i] = max[j][i];
            allocation[j][i] = alloc[j][i];
            need[j][i] = maximum[j][i] - allocation[j][i];
        }
    }
}

int is_safe(int process, int work[], int finish[]) {
    // Check if it's safe to grant resources to the process
    for (int i = 0; i < m; i++) {
        if (need[process][i] > work[i] || finish[process])
            return 0;
    }
    return 1;
}

void bankers_algorithm() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES];

    // Initialize work and finish arrays
    for (int i = 0; i < m; i++)
        work[i] = available[i];

    for (int i = 0; i < n; i++)
        finish[i] = 0;

    int safe_sequence[MAX_PROCESSES];
    int count = 0;

    while (count < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {
            if (!finish[i] && is_safe(i, work, finish)) {
                // Grant resources to process i
                for (int j = 0; j < m; j++) {
                    work[j] += allocation[i][j];
                }

                safe_sequence[count++] = i;
                finish[i] = 1;
                found = 1;
            }
        }

        if (!found) {
            printf("System is not in a safe state!\n");
            return;
        }
    }

    printf("System is in a safe state. Safe sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", safe_sequence[i]);
    }
    printf("\n");
}

int main() {
    initialize();
    bankers_algorithm();

    return 0;
}

