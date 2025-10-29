#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "visual.h"
#include "utils.h"
#include "sorting.h"
#include "stats.h"

#define ARRAY_SIZE 64
#define DELAY_MS 1  // Delay between each step (adjust for speed)

// Global variables for visualization
SDL_Renderer* g_renderer = NULL;
int* g_array = NULL;
int g_array_size = 0;

// Visualization callback function
void visualize_step(int* array, int size, int highlight1, int highlight2, Statistics* stats) {
    // Clear screen
    clear_sdl_window(g_renderer);

    // Draw UI (buttons)
    draw_ui(g_renderer);
    
    // Draw array with highlighted elements
    draw_array_on_window(g_renderer, array, size, highlight1, highlight2, stats);
    
    // Present the frame
    refresh_present_window(g_renderer);
    
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
    if (init_sdl_window(&window, &renderer) != 0) {
        fprintf(stderr, "Failed to initialize visual system\n");
        return 1;
    }

    // Initialize TTF and load font (mettre le fichier de font dans assets/fonts/)
    if (init_ttf_and_load_font("assets/fonts/arial_bold.ttf", 16) != 0) {
        fprintf(stderr, "Error: font loading failed.\n");
        return EXIT_FAILURE;
    }
    // Initialize UI buttons
    init_ui_buttons();
    // Create and generate array

    int* array = (int*)malloc(ARRAY_SIZE * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        clean_up_sdl_window(window, renderer);
        return 1;
    }

    generate_random_array(array, ARRAY_SIZE);
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
                    generate_random_array(array, ARRAY_SIZE);
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
                //TODO optimiser
                else if (event.key.keysym.sym == SDLK_s && !is_sorting) {
                    // start selection short
                    printf("Starting Selection Sort...\n");
                    is_sorting = 1;
                    stats_reset(&stats);
                    selection_sort(array, ARRAY_SIZE, &stats, visualize_step);

                    printf("Selection Sort completed!\n");
                    printf("Comparisons: %lu\n", stats.comparisons);
                    printf("Memory reads: %lu\n", stats.memory_reads);
                    printf("Memory writes: %lu\n", stats.memory_writes);
                    printf("Execution time: %.2f ms\n", stats.execution_time_ms);

                    is_sorting = 0;
                }
                else if (event.key.keysym.sym == SDLK_i && !is_sorting) {
                    // start selection short
                    printf("Starting Insertion Sort...\n");
                    is_sorting = 1;
                    stats_reset(&stats);
                    insertion_sort(array, ARRAY_SIZE, &stats, visualize_step);

                    printf("Insertion Sort completed!\n");
                    printf("Comparisons: %lu\n", stats.comparisons);
                    printf("Memory reads: %lu\n", stats.memory_reads);
                    printf("Memory writes: %lu\n", stats.memory_writes);
                    printf("Execution time: %.2f ms\n", stats.execution_time_ms);

                    is_sorting = 0;
                }
                else if (event.key.keysym.sym == SDLK_m && !is_sorting) {
                    // start selection short
                    printf("Starting Merge Sort...\n");
                    is_sorting = 1;
                    stats_reset(&stats);
                    merge_sort(array, ARRAY_SIZE, &stats, visualize_step);

                    printf("Merge Sort completed!\n");
                    printf("Comparisons: %lu\n", stats.comparisons);
                    printf("Memory reads: %lu\n", stats.memory_reads);
                    printf("Memory writes: %lu\n", stats.memory_writes);
                    printf("Execution time: %.2f ms\n", stats.execution_time_ms);

                    is_sorting = 0;
                }
                else if (event.key.keysym.sym == SDLK_q && !is_sorting) {
                    // start selection short
                    printf("Starting QuickSort...\n");
                    is_sorting = 1;
                    stats_reset(&stats);
                    quick_sort(array, ARRAY_SIZE, &stats, visualize_step);

                    printf("Quick Sort completed!\n");
                    printf("Comparisons: %lu\n", stats.comparisons);
                    printf("Memory reads: %lu\n", stats.memory_reads);
                    printf("Memory writes: %lu\n", stats.memory_writes);
                    printf("Execution time: %.2f ms\n", stats.execution_time_ms);

                    is_sorting = 0;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT && !is_sorting) {
                    int bx = event.button.x;
                    int by = event.button.y;
                    int bid = button_id_from_mouse(bx, by);
                    if (bid >= 0) {
                        // map button ids to actions (ne pas oublier le verrou is_sorting)
                        if (bid == BTN_BUBBLE) {
                            printf("Starting Bubble Sort (button)...\n");
                            is_sorting = 1;
                            stats_reset(&stats);
                            bubble_sort(array, ARRAY_SIZE, &stats, visualize_step);
                            is_sorting = 0;
                        } else if (bid == BTN_SELECTION) {
                            printf("Starting Selection Sort (button)...\n");
                            is_sorting = 1;
                            stats_reset(&stats);
                            selection_sort(array, ARRAY_SIZE, &stats, visualize_step);
                            is_sorting = 0;
                        } else if (bid == BTN_QUICK) {
                            printf("Starting Quick Sort (button)...\n");
                            is_sorting = 1;
                            stats_reset(&stats);
                            quick_sort(array, ARRAY_SIZE, &stats, visualize_step);
                            is_sorting = 0;
                        } else if (bid == BTN_MERGE) {
                            printf("Starting Merge Sort (button)...\n");
                            is_sorting = 1;
                            stats_reset(&stats);
                            merge_sort(array, ARRAY_SIZE, &stats, visualize_step);
                            is_sorting = 0;
                        } else if (bid == BTN_INSERTION) {
                            printf("Starting Insertion Sort (button)...\n");
                            is_sorting = 1;
                            stats_reset(&stats);
                            insertion_sort(array, ARRAY_SIZE, &stats, visualize_step);
                            is_sorting = 0;
                        } else if (bid == BTN_SHUFFLE) {
                            printf("Shuffling array (button)...\n");
                            generate_random_array(array, ARRAY_SIZE);
                            stats_reset(&stats);
                        }
                    }
                }
            }
        }

        // Clear screen
        clear_sdl_window(renderer);

        // Draw UI (boutons)
        draw_ui(renderer);
        // Draw array bars (no highlighting for now)
        draw_array_on_window(renderer, array, ARRAY_SIZE, -1, -1,  &stats);

        // Present the frame
        refresh_present_window(renderer);

        // Small delay to avoid consuming too much CPU
        SDL_Delay(16); // ~60 FPS
    }

    // Cleanup
    free(array);
    close_ttf_font();
    clean_up_sdl_window(window, renderer);
    printf("Program terminated successfully.\n");

    return 0;
}