
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "quicksort.h"

#define SHMSIZE 40
#define KEY 5656

void sort(int is_b) {
    sleep(0.2);  // wait
    key_t key = KEY;
    int shmid = shmget(key, SHMSIZE, 0666);
    int* ptr = (int*)shmat(shmid, NULL, 0);
    if (is_b) {
        printf("B: ");
        ptr += 5;
    } else {
        printf("A: ");
    }
    for (int i = 0; i < 5; i++) {
        printf("%d ", *(ptr + i));
    }
    printf("\n");

    quickSort(ptr, 0, 4);  // sort array of 5 elements

    (is_b) ? printf("B") : printf("A");
    printf(" (sorted): ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *(ptr + i));
    }
    printf("\n");
    shmdt(ptr);
    shmctl(shmid, IPC_RMID, NULL);
}

int main() {
    pid_t child_a, child_b;
    child_a = fork();
    if (child_a == 0) {
        // child a
        sort(0);
    } else {
        child_b = fork();
        if (child_b == 0) {
            // child b
            sort(1);
        } else {
            key_t key = KEY;
            int shmid = shmget(key, SHMSIZE, 0666 | IPC_CREAT);
            int* ptr = (int*)shmat(shmid, NULL, 0);

            int arr[10];
            // array of random elements
            for (int i = 0; i < 10; i++) {
                arr[i] = rand() / 10000000;
            }
            int* s = ptr;
            for (int i = 0; i < 10; i++) {
                *s = arr[i];
                s++;
            }
            printf("Given Array: ");
            for (int i = 0; i < 10; i++) {
                printf("%d ", *(ptr + i));
            }
            printf("\n");
            int status;
            waitpid(child_a, &status, 0);
            waitpid(child_b, &status, 0);
            int* a = ptr;
            int* b = ptr + 5;
            int *i = a, *j = b;
            int* i_end = i + 5;
            int* j_end = j + 5;

            int sorted[10];  // final sorted array
            int x = 0;

            // merging sorted arrays
            while (i != i_end && j != j_end) {
                if (*i < *j) {
                    sorted[x++] = *i;
                    i++;
                } else {
                    sorted[x++] = *j;
                    j++;
                }
            }
            while (i != i_end) {
                sorted[x++] = *i;
                i++;
            }
            while (j != j_end) {
                sorted[x++] = *j;
                j++;
            }
            printf("Sorted Array: ");
            for (int i = 0; i < 10; i++) {
                printf("%d ", sorted[i]);
            }
            printf("\n");
            shmdt(ptr);
            shmctl(shmid, IPC_RMID, NULL);
        }
    }
    return 0;
}
