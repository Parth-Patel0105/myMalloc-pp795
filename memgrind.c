#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include "mymalloc.h"

#define NUM_OBJECTS 120
#define NUM_ITERATIONS 50

long getMicrotime() {
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

void test1() {
    long totalTime = 0;
    for(int i = 0; i < NUM_ITERATIONS; i++) {
        long startTime = getMicrotime();
        for(int j = 0; j < NUM_OBJECTS; j++) {
            char *byte = (char*)mymalloc(1);
            myfree(byte);
        }
        long endTime = getMicrotime();
        totalTime += (endTime - startTime);
    }
    printf("Test 1 Average Time: %ld microseconds\n", totalTime / NUM_ITERATIONS);
}

void test2() {

char *pointers[NUM_OBJECTS]; // Array to hold pointers to allocated memory
    long totalTime = 0;

    for(int i = 0; i < NUM_ITERATIONS; i++) {
        long startTime = getMicrotime();

        // Allocate 120 1-byte objects and store their pointers
        for(int j = 0; j < NUM_OBJECTS; j++) {
            pointers[j] = (char*)mymalloc(1);
        }

        // Free the allocated memory
        for(int j = 0; j < NUM_OBJECTS; j++) {
            myfree(pointers[j]);
        }

        long endTime = getMicrotime();
        totalTime += (endTime - startTime);
    }

    printf("Test 2 Average Time: %ld microseconds\n", totalTime / NUM_ITERATIONS);
}
  
void test3() {
    char *pointers[NUM_OBJECTS] = {NULL}; // Array to hold pointers, initialized to NULL
    int allocCount = 0; // Count of successful allocations
    long totalTime = 0;

    for(int i = 0; i < NUM_ITERATIONS; i++) {
        long startTime = getMicrotime();
        int currentAllocs = 0; // Number of allocations in this iteration

        while(currentAllocs < NUM_OBJECTS) {
            int action = rand() % 2; // Randomly choose to allocate (0) or free (1)

            if(action == 0) { // Allocate
                char *ptr = (char*)mymalloc(1);
                if(ptr != NULL) {
                    // Find a NULL spot in the array to store this pointer
                    for(int j = 0; j < NUM_OBJECTS; j++) {
                        if(pointers[j] == NULL) {
                            pointers[j] = ptr;
                            currentAllocs++;
                            allocCount++;
                            break;
                        }
                    }
                }
            } else { // Free
                // Find a non-NULL pointer to free
                for(int j = 0; j < NUM_OBJECTS; j++) {
                    if(pointers[j] != NULL) {
                        myfree(pointers[j]);
                        pointers[j] = NULL; // Mark as freed
                        break; // Only free one at a time
                    }
                }
            }
        }

        // Free any remaining allocated objects
        for(int j = 0; j < NUM_OBJECTS; j++) {
            if(pointers[j] != NULL) {
                myfree(pointers[j]);
                pointers[j] = NULL;
            }
        }

        long endTime = getMicrotime();
        totalTime += (endTime - startTime);
    }

    printf("Test 3 Average Time: %ld microseconds\n", totalTime / NUM_ITERATIONS);
    printf("Total Allocations in Test 3: %d\n", allocCount);
}

//alternating allocations and freeing
void stresstest1(int iterations) {
    long startTime = getMicrotime()();
    for(int i = 0; i < iterations; i++) {
        char* ptr = (char*)mymalloc(1); // Allocate 1 byte
        if (ptr == NULL) {
            printf("Allocation failed\n");
            return;
        }
        myfree(ptr); // Immediately free it
    }
    long endTime = getMicrotime()();
    printf("Alternating Allocation and Free Time: %ld microseconds\n", endTime - startTime);
}

//random-sized allocation
void stresstest2(int count) {
    char* pointers[count];
    long startTime = getMicrotime()();
    for(int i = 0; i < count; i++) {
        size_t size = (rand() % 64) + 1; // Random size between 1 and 64 bytes
        pointers[i] = (char*)mymalloc(size);
        if (pointers[i] == NULL) {
            printf("Allocation failed\n");
            return;
        }
    }
    for(int i = 0; i < count; i++) {
        myfree(pointers[i]);
    }
    long endTime = getMicrotime()();
    printf("Random Size Allocations Time: %ld microseconds\n", endTime - startTime);
}

int main(int argc, char ** argv){

  printf("Each test is performed 100 times\n");

        printf("\nTEST1...\n");

        test1();

        printf("\nTEST2...\n");

        test2();

        printf("\nTEST3...\n");

        test3();

        printf("\nTEST4...\n");

        stresstest1(100);

        printf("\nTEST5...\n");

        stresstest2(64);

    return 0;

}
