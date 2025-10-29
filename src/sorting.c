#include "sorting.h"
#include "utils.h"

#include <string.h>

// array listing all the sorting algorithms proposed by the application
SortingAlgorithm sorting_algorithms[] = {
    {1, "Bubble Sort", bubble_sort},
    {2, "Selection Sort", selection_sort},
     {3, "Insertion Sort", insertion_sort},
     {4, "Quick Sort", quick_sort},
     {5, "Merge Sort", merge_sort},
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
                stats_update_timer(stats);
                callback(array, size, j, j + 1, stats);
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
                    stats_update_timer(stats);
                    callback(array, size, j, j + 1, stats);
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
                stats_update_timer(stats);
                callback(array, size, j, min_index, stats);
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
                stats_update_timer(stats);
                callback(array, size, i, min_index, stats);
            }
        }
    }

    stats_stop_timer(stats);
}

void insertion_sort(int* array, int size, Statistics* stats, VisualCallback callback) {
    stats_start_timer(stats);

    for (int i = 1; i < size; i++) {
        int key = array[i];
        stats_increment_read(stats);

        int j = i - 1;

        while (j >= 0) {
            stats_increment_comparison(stats);
            stats_increment_read(stats);
            stats_increment_read(stats);

            if (callback != NULL) {
                stats_update_timer(stats);
                callback(array, size, j, j + 1, stats);
            }

            if (array[j] > key) {
                array[j + 1] = array[j];
                stats_increment_write(stats);

                if (callback != NULL) {
                    stats_update_timer(stats);
                    callback(array, size, j, j + 1, stats);
                }

                j--;
            } else {
                break;
            }
        }

        array[j + 1] = key;
        stats_increment_write(stats);
    }

    stats_stop_timer(stats);
}
static void quick_sort_recursive(
    int* array,
    int low,
    int high,
    int* full_array,
    int full_size,
    Statistics* stats,
    VisualCallback callback
) {
    if (low >= high) return;

    int pivot = array[high];
    stats_increment_read(stats);

    int i = low - 1;

    for (int j = low; j < high; j++) {
        stats_increment_comparison(stats);
        stats_increment_read(stats);
        stats_increment_read(stats);

        if (callback != NULL) {
            stats_update_timer(stats);
            callback(full_array, full_size, j, high, stats);
        }

        if (array[j] < pivot) {
            i++;
            swap_int_values(&array[i], &array[j]);
            stats_increment_write(stats);
            stats_increment_write(stats);

            if (callback != NULL) {
                stats_update_timer(stats);
                callback(full_array, full_size, i, j, stats);
            }
        }
    }

    swap_int_values(&array[i + 1], &array[high]);
    stats_increment_write(stats);
    stats_increment_write(stats);

    if (callback != NULL) {
        stats_update_timer(stats);
        callback(full_array, full_size, i + 1, high, stats);
    }

    int p = i + 1;

    quick_sort_recursive(array, low, p - 1, full_array, full_size, stats, callback);
    quick_sort_recursive(array, p + 1, high, full_array, full_size, stats, callback);
}

void quick_sort(int* array, int size, Statistics* stats, VisualCallback callback) {
    stats_start_timer(stats);
    quick_sort_recursive(array, 0, size - 1, array, size, stats, callback);
    stats_stop_timer(stats);
}



static void merge(int* array, int left, int mid, int right, int* full_array,
    int full_size, Statistics* stats, VisualCallback callback) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = array[left + i];
        stats_increment_read(stats);
    }
    for (int j = 0; j < n2; j++) {
        R[j] = array[mid + 1 + j];
        stats_increment_read(stats);
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        stats_increment_comparison(stats);
        stats_increment_read(stats);
        stats_increment_read(stats);

        if (callback != NULL) {
            stats_update_timer(stats);
            callback(full_array, full_size, left + i, mid + 1 + j, stats);
        }
        if (L[i] <= R[j]) {
            array[k] = L[i];
            stats_increment_write(stats);
            i++;
        } else {
            array[k] = R[j];
            stats_increment_write(stats);
            j++;
        }
        //
        // if (callback != NULL) {
        //     callback(array, right + 1, k, k);
        // }

        k++;
    }
    while (i < n1) {
        array[k] = L[i];
        stats_increment_write(stats);
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        stats_increment_write(stats);
        j++;
        k++;
    }
}
static void merge_sort_recursive(
    int* array,
    int left,
    int right,
    int* full_array,
    int full_size,
    Statistics* stats,
    VisualCallback callback
) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    merge_sort_recursive(array, left, mid, full_array, full_size, stats, callback);
    merge_sort_recursive(array, mid + 1, right, full_array, full_size, stats, callback);
    merge(array, left, mid, right, full_array, full_size, stats, callback);
}


void merge_sort(int* array, int size, Statistics* stats, VisualCallback callback) {
    stats_start_timer(stats);
    merge_sort_recursive(array, 0, size - 1, array, size, stats, callback);
    stats_stop_timer(stats);
}

