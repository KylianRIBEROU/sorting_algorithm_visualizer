#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>

#define MENU_WIDTH 400
#define MENU_HEIGHT 600

// Initialiser la fenêtre de menu (similaire à init_sdl_window)
int init_menu_window(SDL_Window** window, SDL_Renderer** renderer);

// Nettoyer les ressources du menu
void clean_up_menu_window(SDL_Window* window, SDL_Renderer* renderer);

// Effacer l'écran du menu
void clear_menu_window(SDL_Renderer* renderer);

// Afficher le rendu du menu
void refresh_menu_window(SDL_Renderer* renderer);

#endif