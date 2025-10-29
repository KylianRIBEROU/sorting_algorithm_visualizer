#include "menu.h"
#include <stdio.h>

int init_menu_window(SDL_Window** window, SDL_Renderer** renderer) {
    // Créer la fenêtre de menu
    *window = SDL_CreateWindow(
        "Menu - Sorting Visualizer",
        SDL_WINDOWPOS_UNDEFINED,  // Position à gauche de l'écran
        SDL_WINDOWPOS_CENTERED,
        MENU_WIDTH,
        MENU_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (*window == NULL) {
        fprintf(stderr, "Menu window creation failed: %s\n", SDL_GetError());
        return -1;
    }

    // Créer le renderer pour le menu
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

    if (*renderer == NULL) {
        fprintf(stderr, "Menu renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        return -1;
    }

    return 0;
}

void clean_up_menu_window(SDL_Window* window, SDL_Renderer* renderer) {
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != NULL) {
        SDL_DestroyWindow(window);
    }
}

void clear_menu_window(SDL_Renderer* renderer) {
    // Fond gris foncé pour le menu
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);
}

void refresh_menu_window(SDL_Renderer* renderer) {
    SDL_RenderPresent(renderer);
}