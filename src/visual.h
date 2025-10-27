#ifndef VISUAL_H
#define VISUAL_H

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Initialize SDL and create window/renderer
int init_sdl_window(SDL_Window** window, SDL_Renderer** renderer);

// Cleanup SDL resources
void clean_up_sdl_window(SDL_Window* window, SDL_Renderer* renderer);

// Clear the screen with background color
void clear_sdl_window(SDL_Renderer* renderer);

// Present the rendered frame
void refresh_present_window(SDL_Renderer* renderer);

// Draw array as vertical bars
// highlight1 and highlight2 are indices to highlight (-1 if none)
void draw_array_on_window(SDL_Renderer* renderer, int* array, int size, int highlight1, int highlight2);

#endif