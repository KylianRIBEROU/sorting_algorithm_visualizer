#ifndef UTILS_H
#define UTILS_H

// Generate a random array with values going from 1 to the defined size of the array
void generate_random_array(int* array, int size);

// Swap two integers
void swap_int_values(int* a, int* b);

// Swap two values in an array
void swap_array_values(int array[], int i, int j);

// Print array to console (for debugging)
void print_array(int* array, int size);

#endif