#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void swap_array_values(int array[], int i, int j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void swap_int_values(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle_array(int array[], int size) {
    for (int i = size - 2; i >= 0; i--) {
        int r = rand() % size;
        swap_array_values(array,r, i);
    }
}

void generate_random_array(int* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = i + 1;
    }
    shuffle_array(array, size);
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