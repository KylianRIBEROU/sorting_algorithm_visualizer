#include "sorting.h"
#include "utils.h"
#include <stddef.h>

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