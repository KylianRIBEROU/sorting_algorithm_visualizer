#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void generate_random_array(int* array, int size, int max_value) {
    // Seed random number generator
    srand(time(NULL));
    
    for (int i = 0; i < size; i++) {
        array[i] = (rand() % max_value) + 1; // Values between 1 and max_value
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_array(int* array, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", array[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}