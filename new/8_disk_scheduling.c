// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <limits.h>  // Include this header for INT_MAX

// // Function to find the index of the next request to serve
// int findNextRequest(int head, int* requests, int n, bool* visited) {
//     int minDist = INT_MAX;
//     int index = -1;

//     for (int i = 0; i < n; i++) {
//         if (!visited[i]) {
//             int distance = abs(head - requests[i]);
//             if (distance < minDist) {
//                 minDist = distance;
//                 index = i;
//             }
//         }
//     }

//     return index;
// }

// // FCFS Disk Scheduling Algorithm
// void fcfs(int* requests, int n, int head) {
//     printf("FCFS Disk Scheduling:\n");
//     int totalSeekTime = 0;

//     for (int i = 0; i < n; i++) {
//         totalSeekTime += abs(head - requests[i]);
//         head = requests[i];
//         printf("Move to %d\n", head);
//     }

//     printf("Total Seek Time: %d\n", totalSeekTime);
// }

// // SCAN Disk Scheduling Algorithm
// void scan(int* requests, int n, int head, int size) {
//     printf("SCAN Disk Scheduling:\n");
//     int totalSeekTime = 0;
//     int direction = 1; // 1 for right, -1 for left

//     while (true) {
//         int nextIndex = findNextRequest(head, requests, n, NULL);

//         if (nextIndex == -1) {
//             // No more requests in the current direction
//             direction = -direction; // Change direction
//             continue;
//         }

//         totalSeekTime += abs(head - requests[nextIndex]);
//         head = requests[nextIndex];
//         printf("Move to %d\n", head);

//         requests[nextIndex] = -1; // Mark the request as served
//     }

//     printf("Total Seek Time: %d\n", totalSeekTime);
// }

// // C-SCAN Disk Scheduling Algorithm
// void cscan(int* requests, int n, int head, int size) {
//     printf("C-SCAN Disk Scheduling:\n");
//     int totalSeekTime = 0;

//     // Move to the rightmost end
//     totalSeekTime += abs(head - size);
//     head = size;

//     // Move back to the leftmost end
//     totalSeekTime += size;
//     head = 0;

//     for (int i = 0; i < n; i++) {
//         if (requests[i] == -1) {
//             // Skip already served requests
//             continue;
//         }

//         totalSeekTime += abs(head - requests[i]);
//         head = requests[i];
//         printf("Move to %d\n", head);
//     }

//     printf("Total Seek Time: %d\n", totalSeekTime);
// }

// // SSTF Disk Scheduling Algorithm
// void sstf(int* requests, int n, int head) {
//     printf("SSTF Disk Scheduling:\n");
//     int totalSeekTime = 0;
//     bool* visited = (bool*)malloc(n * sizeof(bool));

//     for (int i = 0; i < n; i++) {
//         visited[i] = false;
//     }

//     for (int i = 0; i < n; i++) {
//         int nextIndex = findNextRequest(head, requests, n, visited);

//         totalSeekTime += abs(head - requests[nextIndex]);
//         head = requests[nextIndex];
//         visited[nextIndex] = true;
//         printf("Move to %d\n", head);
//     }

//     free(visited);
//     printf("Total Seek Time: %d\n", totalSeekTime);
// }

// int main() {
//     int n, head, size;

//     printf("Enter the number of requests: ");
//     scanf("%d", &n);

//     int* requests = (int*)malloc(n * sizeof(int));

//     printf("Enter the disk requests:\n");
//     for (int i = 0; i < n; i++) {
//         scanf("%d", &requests[i]);
//     }

//     printf("Enter the initial position of the disk head: ");
//     scanf("%d", &head);

//     printf("Enter the size of the disk: ");
//     scanf("%d", &size);

//     // Execute FCFS Disk Scheduling
//     fcfs(requests, n, head);

//     // Execute SCAN Disk Scheduling
//     scan(requests, n, head, size);

//     // Execute C-SCAN Disk Scheduling
//     cscan(requests, n, head, size);

//     // Execute SSTF Disk Scheduling
//     sstf(requests, n, head);

   
// }



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>  // Include this header for INT_MAX

// Function to find the index of the next request to serve
int findNextRequest(int head, int* requests, int n, bool* visited) {
    int minDist = INT_MAX;
    int index = -1;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int distance = abs(head - requests[i]);
            if (distance < minDist) {
                minDist = distance;
                index = i;
            }
        }
    }

    return index;
}

// FCFS Disk Scheduling Algorithm
void fcfs(int* requests, int n, int head) {
    printf("FCFS Disk Scheduling:\n");
    int totalSeekTime = 0;

    for (int i = 0; i < n; i++) {
        totalSeekTime += abs(head - requests[i]);
        head = requests[i];
        printf("Move to %d\n", head);
    }

    printf("Total Seek Time: %d\n", totalSeekTime);
}

// SCAN Disk Scheduling Algorithm
// void scan(int* requests, int n, int head, int size) {
//     printf("SCAN Disk Scheduling:\n");
//     int totalSeekTime = 0;
//     int direction = 1; // 1 for right, -1 for left

//     while (true) {
//         int nextIndex = findNextRequest(head, requests, n, NULL);

//         if (nextIndex == -1) {
//             // No more requests in the current direction
//             direction = -direction; // Change direction
//             continue;
//         }

//         totalSeekTime += abs(head - requests[nextIndex]);
//         head = requests[nextIndex];
//         printf("Move to %d\n", head);

//         requests[nextIndex] = -1; // Mark the request as served
//     }

//     printf("Total Seek Time: %d\n", totalSeekTime);
// }

// SCAN Disk Scheduling Algorithm
void scan(int* requests, int n, int head, int size) {
    printf("SCAN Disk Scheduling:\n");
    int totalSeekTime = 0;
    int direction = 1; // 1 for right, -1 for left

    while (true) {
        int nextIndex = findNextRequest(head, requests, n, NULL);

        if (nextIndex == -1) {
            // Change direction if no more requests in the current direction
            direction = -direction;

            // Check in the opposite direction
            nextIndex = findNextRequest(head, requests, n, NULL);
            if (nextIndex == -1) {
                // No more requests in both directions, break the loop
                break;
            }
        }

        totalSeekTime += abs(head - requests[nextIndex]);
        head = requests[nextIndex];
        printf("Move to %d\n", head);

        requests[nextIndex] = -1; // Mark the request as served
    }

    printf("Total Seek Time: %d\n", totalSeekTime);
}




// C-SCAN Disk Scheduling Algorithm
void cscan(int* requests, int n, int head, int size) {
    printf("C-SCAN Disk Scheduling:\n");
    int totalSeekTime = 0;

    // Move to the rightmost end
    totalSeekTime += abs(head - size);
    head = size;

    // Move back to the leftmost end
    totalSeekTime += size;
    head = 0;

    for (int i = 0; i < n; i++) {
        if (requests[i] == -1) {
            // Skip already served requests
            continue;
        }

        totalSeekTime += abs(head - requests[i]);
        head = requests[i];
        printf("Move to %d\n", head);
    }

    printf("Total Seek Time: %d\n", totalSeekTime);
}

// SSTF Disk Scheduling Algorithm
void sstf(int* requests, int n, int head) {
    printf("SSTF Disk Scheduling:\n");
    int totalSeekTime = 0;
    bool* visited = (bool*)malloc(n * sizeof(bool));

    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    for (int i = 0; i < n; i++) {
        int nextIndex = findNextRequest(head, requests, n, visited);

        totalSeekTime += abs(head - requests[nextIndex]);
        head = requests[nextIndex];
        visited[nextIndex] = true;
        printf("Move to %d\n", head);
    }

    free(visited);
    printf("Total Seek Time: %d\n", totalSeekTime);
}

int main() {
    int n, head, size;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int* requests = (int*)malloc(n * sizeof(int));

    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    printf("Enter the size of the disk: ");
    scanf("%d", &size);

    // Execute FCFS Disk Scheduling
    fcfs(requests, n, head);

    // Execute SCAN Disk Scheduling
    scan(requests, n, head, size);

    // Execute C-SCAN Disk Scheduling
    cscan(requests, n, head, size);

    // Execute SSTF Disk Scheduling
    sstf(requests, n, head);

    free(requests);
   
    return 0;
}
