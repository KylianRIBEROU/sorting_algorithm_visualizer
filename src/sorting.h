#ifndef SORTING_H
#define SORTING_H

#include "stats.h"

// Callback function type for visualization
// Parameters: array, size, index1, index2
typedef void (*VisualCallback)(int*, int, int, int);

typedef struct {
    const int id;
    const char* name;
    void (*function)(int*, int, Statistics*, VisualCallback);
} SortingAlgorithm;

SortingAlgorithm* get_sorting_algorithm_by_id(int id);
SortingAlgorithm* find_sorting_algorithm_by_name(const char* name);

// Bubble Sort algorithm with visualization
void bubble_sort(int* array, int size, Statistics* stats, VisualCallback callback);

void selection_sort(int* array, int size, Statistics* stats, VisualCallback callback);

#endif