#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "visual.h"
#include "utils.h"
#include "sorting.h"
#include "stats.h"

#define ARRAY_SIZE 200
#define DELAY_MS 1  // Delay between each step (adjust for speed)

// Global variables for visualization
SDL_Renderer* g_renderer = NULL;
int* g_array = NULL;
int g_array_size = 0;

// Visualization callback function
void visualize_step(int* array, int size, int highlight1, int highlight2) {
    // Clear screen
    visual_clear(g_renderer);
    
    // Draw array with highlighted elements
    visual_draw_array(g_renderer, array, size, highlight1, highlight2);
    
    // Present the frame
    visual_present(g_renderer);
    
    // Small delay to make animation visible
    SDL_Delay(DELAY_MS);
    
    // Handle events to keep window responsive
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            // User closed window during sorting
            exit(0);
        }
    }
}

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    // Initialize SDL and create window
    if (visual_init(&window, &renderer) != 0) {
        fprintf(stderr, "Failed to initialize visual system\n");
        return 1;
    }

    printf("Window created successfully!\n");
    printf("Press ESC or close the window to quit.\n");
    printf("Press SPACE to regenerate array.\n");
    printf("Press ENTER to start Bubble Sort.\n");

    // Create and generate array
    int* array = (int*)malloc(ARRAY_SIZE * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        visual_cleanup(window, renderer);
        return 1;
    }

    generate_random_array(array, ARRAY_SIZE, 100);
    printf("Array generated with %d elements\n", ARRAY_SIZE);
    
    // Set global variables for visualization callback
    g_renderer = renderer;
    g_array = array;
    g_array_size = ARRAY_SIZE;
    
    // Initialize statistics
    Statistics stats;
    stats_init(&stats);
    
    int is_sorting = 0; // Flag to prevent sorting during sorting

    // Main event loop
    int running = 1;
    SDL_Event event;

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                }
                else if (event.key.keysym.sym == SDLK_SPACE && !is_sorting) {
                    // Regenerate array when SPACE is pressed
                    generate_random_array(array, ARRAY_SIZE, 100);
                    stats_reset(&stats);
                    printf("Array regenerated\n");
                }
                else if (event.key.keysym.sym == SDLK_RETURN && !is_sorting) {
                    // Start Bubble Sort when ENTER is pressed
                    printf("Starting Bubble Sort...\n");
                    is_sorting = 1;
                    stats_reset(&stats);
                    
                    bubble_sort(array, ARRAY_SIZE, &stats, visualize_step);
                    
                    printf("Bubble Sort completed!\n");
                    printf("Comparisons: %lu\n", stats.comparisons);
                    printf("Memory reads: %lu\n", stats.memory_reads);
                    printf("Memory writes: %lu\n", stats.memory_writes);
                    printf("Execution time: %.2f ms\n", stats.execution_time_ms);
                    
                    is_sorting = 0;
                }
            }
        }

        // Clear screen
        visual_clear(renderer);

        // Draw array bars (no highlighting for now)
        visual_draw_array(renderer, array, ARRAY_SIZE, -1, -1);

        // Present the frame
        visual_present(renderer);

        // Small delay to avoid consuming too much CPU
        SDL_Delay(16); // ~60 FPS
    }

    // Cleanup
    free(array);
    visual_cleanup(window, renderer);
    printf("Program terminated successfully.\n");

    return 0;
}