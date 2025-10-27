#include "visual.h"
#include <stdio.h>

int init_sdl_window(SDL_Window** window, SDL_Renderer** renderer) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return -1;
    }

    // Create window
    *window = SDL_CreateWindow(
        "Sorting Algorithm Visualizer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (*window == NULL) {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Create renderer
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

    if (*renderer == NULL) {
        fprintf(stderr, "Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return -1;
    }

    return 0;
}

void clean_up_sdl_window(SDL_Window* window, SDL_Renderer* renderer) {
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != NULL) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void clear_sdl_window(SDL_Renderer* renderer) {
    // Set background color to dark gray
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);
}

void refresh_present_window(SDL_Renderer* renderer) {
    SDL_RenderPresent(renderer);
}

void draw_array_on_window(SDL_Renderer* renderer, int* array, int size, int highlight1, int highlight2) {
    // Calculate bar width based on window width and array size
    int bar_width = WINDOW_WIDTH / size;
    int spacing = 1; // Small gap between bars
    
    // Find max value for color scaling
    int max_value = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] > max_value) {
            max_value = array[i];
        }
    }
    
    for (int i = 0; i < size; i++) {
        // Calculate bar height (proportional to value)
        // Leave some margin at top and bottom
        int max_bar_height = WINDOW_HEIGHT - 50;
        int bar_height = (array[i] * max_bar_height) / max_value;
        
        // Calculate bar position
        int x = i * bar_width;
        int y = WINDOW_HEIGHT - bar_height - 20; // 20px margin at bottom
        
        // Choose color based on highlighting or value
        if (i == highlight1 || i == highlight2) {
            // Highlighted bars (bright yellow)
            SDL_SetRenderDrawColor(renderer, 255, 255, 100, 255);
        } else {
            // Create gradient color based on value
            // Low values -> Blue/Cyan, High values -> Red/Orange
            float ratio = (float)array[i] / (float)max_value;
            
            int r, g, b;
            if (ratio < 0.5f) {
                // Blue to Cyan to Green (low to medium values)
                float local_ratio = ratio * 2.0f; // 0.0 to 1.0
                r = (int)(local_ratio * 100);
                g = (int)(100 + local_ratio * 155);
                b = (int)(255 - local_ratio * 155);
            } else {
                // Green to Yellow to Red (medium to high values)
                float local_ratio = (ratio - 0.5f) * 2.0f; // 0.0 to 1.0
                r = (int)(100 + local_ratio * 155);
                g = (int)(255 - local_ratio * 155);
                b = (int)(100 * (1.0f - local_ratio));
            }
            
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        }
        
        // Draw the bar
        SDL_Rect bar = {
            x + spacing,
            y,
            bar_width - 2 * spacing,
            bar_height
        };
        SDL_RenderFillRect(renderer, &bar);
    }
}