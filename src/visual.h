#ifndef VISUAL_H
#define VISUAL_H

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Initialize SDL and create window/renderer
int visual_init(SDL_Window** window, SDL_Renderer** renderer);

// Cleanup SDL resources
void visual_cleanup(SDL_Window* window, SDL_Renderer* renderer);

// Clear the screen with background color
void visual_clear(SDL_Renderer* renderer);

// Present the rendered frame
void visual_present(SDL_Renderer* renderer);

// Draw array as vertical bars
// highlight1 and highlight2 are indices to highlight (-1 if none)
void visual_draw_array(SDL_Renderer* renderer, int* array, int size, int highlight1, int highlight2);

#endif