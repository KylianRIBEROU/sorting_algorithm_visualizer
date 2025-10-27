#include "sorting.h"
#include "utils.h"

#include <string.h>

// array listing all the sorting algorithms proposed by the application
SortingAlgorithm sorting_algorithms[] = {
    {1, "Bubble Sort", bubble_sort},
    {2, "Selection Sort", selection_sort},
    // {3, "Insertion Sort", insertion_sort},
    // {4, "Quick Sort", quick_sort},
    // {5, "Merge Sort", merge_sort},
};

// sizeof(array) gives the total length in bytes of the array, so we must divise by an element to
// get the actual size
const int SORTING_ALGO_COUNT = sizeof(sorting_algorithms) / sizeof(sorting_algorithms[0]);


SortingAlgorithm* get_sorting_algorithm_by_id(const int id) {
    if (id < 1 || id > SORTING_ALGO_COUNT) {
        return NULL;
    }
    for (int i = 0; i < SORTING_ALGO_COUNT; i++) {
        if (sorting_algorithms[i].id == id) {
            return &sorting_algorithms[i];
        }
    }
    return NULL;
}

SortingAlgorithm* find_sorting_algorithm_by_name(const char* name) {
    for (int i = 0; i < SORTING_ALGO_COUNT; i++) {
        if (strcmp(sorting_algorithms[i].name, name) == 0)
            return &sorting_algorithms[i];
    }
    return NULL;
}

void bubble_sort(int* array, int size, Statistics* stats, VisualCallback callback) {
    stats_start_timer(stats);
    
    for (int i = 0; i < size - 1; i++) {
        int swapped = 0;
        
        for (int j = 0; j < size - i - 1; j++) {
            // Increment comparison counter
            stats_increment_comparison(stats);
            
            // Read both values for comparison
            stats_increment_read(stats);
            stats_increment_read(stats);
            
            // Call visualization callback to show comparison
            if (callback != NULL) {
                callback(array, size, j, j + 1);
            }
            
            // Compare adjacent elements
            if (array[j] > array[j + 1]) {
                // Swap if they are in wrong order
                swap_int_values(&array[j], &array[j + 1]);
                
                // Count writes (2 writes for a swap)
                stats_increment_write(stats);
                stats_increment_write(stats);
                
                swapped = 1;
                
                // Show the swap visually
                if (callback != NULL) {
                    callback(array, size, j, j + 1);
                }
            }
        }
        
        // If no swaps were made, array is sorted
        if (swapped == 0) {
            break;
        }
    }
    
    stats_stop_timer(stats);
}


void selection_sort(int* array, int size, Statistics* stats, VisualCallback callback) {
    stats_start_timer(stats);

    for (int i = 0; i < size - 1; i++) {
        int min_index = i;

        // find smallest element in the non-sorted array
        for (int j = i + 1; j < size; j++) {
            stats_increment_comparison(stats);  // comparison array[j] < array[min_index]
            stats_increment_read(stats);
            stats_increment_read(stats);

            if (callback != NULL) {
                callback(array, size, j, min_index);
            }

            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }

        // if new min element is found, swap it with the other one
        if (min_index != i) {
            swap_int_values(&array[i], &array[min_index]);
            stats_increment_write(stats);
            stats_increment_write(stats);

            if (callback != NULL) {
                callback(array, size, i, min_index);
            }
        }
    }

    stats_stop_timer(stats);
}
