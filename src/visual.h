#ifndef VISUAL_H
#define VISUAL_H

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define UI_HEIGHT 60

typedef enum {
    BTN_BUBBLE = 0,
    BTN_SELECTION,
    BTN_QUICK,
    BTN_MERGE,
    BTN_INSERTION,
    BTN_SHUFFLE,
    BTN_COUNT
} ButtonId;

// Initialiser la configuration des boutons (appel une fois après la création du renderer)
void init_ui_buttons(void);

// Dessiner la barre d'UI (boutons)
void draw_ui(SDL_Renderer* renderer);

// Retourne l'id du bouton cliqué ou -1 si aucun
int button_id_from_mouse(int x, int y);

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

// Initialise SDL_ttf et charge une police depuis font_path (retourne 0 si OK)
int init_ttf_and_load_font(const char* font_path, int font_size);

// Ferme la police et TTF
void close_ttf_font(void);

// Dessine du texte centré dans un rectangle (utilisé pour les labels de boutons)
void draw_text_centered(SDL_Renderer* renderer, const char* text, SDL_Rect rect, SDL_Color color);

#endif