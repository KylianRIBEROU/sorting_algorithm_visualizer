#ifndef SORTING_H
#define SORTING_H

#include "stats.h"

// Callback function type for visualization
// Parameters: array, size, index1, index2
typedef void (*VisualCallback)(int*, int, int, int);

// Bubble Sort algorithm with visualization
void bubble_sort(int* array, int size, Statistics* stats, VisualCallback callback);

#endif