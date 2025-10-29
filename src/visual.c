#include "visual.h"
#include <stdio.h>
#include <SDL2/SDL_ttf.h>


static SDL_Rect g_button_rects[BTN_COUNT];
static const char* g_button_labels[BTN_COUNT] = {
    "Bubble", "Selection", "Quick", "Merge", "Insertion", "Shuffle", "Speed +", "Speed -"
};

static TTF_Font* g_font = NULL;

int init_ttf_and_load_font(const char* font_path, int font_size) {
    if (TTF_Init() != 0) {
        fprintf(stderr, "TTF_Init failed: %s\n", TTF_GetError());
        return -1;
    }
    g_font = TTF_OpenFont(font_path, font_size);
    if (g_font == NULL) {
        fprintf(stderr, "Failed to load font '%s': %s\n", font_path, TTF_GetError());
        TTF_Quit();
        return -1;
    }
    return 0;
}

void close_ttf_font(void) {
    if (g_font != NULL) {
        TTF_CloseFont(g_font);
        g_font = NULL;
    }
    TTF_Quit();
}

void draw_text_centered(SDL_Renderer* renderer, const char* text, SDL_Rect rect, SDL_Color color) {
    if (g_font == NULL || text == NULL) return;

    SDL_Surface* surf = TTF_RenderUTF8_Blended(g_font, text, color);
    if (surf == NULL) {
        fprintf(stderr, "TTF_RenderUTF8_Blended failed: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    if (tex == NULL) {
        fprintf(stderr, "SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
        SDL_FreeSurface(surf);
        return;
    }

    int tw = surf->w;
    int th = surf->h;
    SDL_FreeSurface(surf);

    SDL_Rect dst = {
        rect.x + (rect.w - tw) / 2,
        rect.y + (rect.h - th) / 2,
        tw,
        th
    };
    SDL_RenderCopy(renderer, tex, NULL, &dst);
    SDL_DestroyTexture(tex);
}


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


// Initialise la position et taille des boutons (appeler après la création du renderer)
void init_ui_buttons(void) {
    int margin = 10;
    int spacing = 8;
    int btn_width = (WINDOW_WIDTH - 2 * margin - (BTN_COUNT - 1) * spacing) / BTN_COUNT;
    int btn_height = UI_HEIGHT - 2 * margin;
    for (int i = 0; i < BTN_COUNT; ++i) {
        g_button_rects[i].x = margin + i * (btn_width + spacing);
        g_button_rects[i].y = margin;
        g_button_rects[i].w = btn_width;
        g_button_rects[i].h = btn_height;
    }
}

// Dessine la barre d'UI (boutons). Pas de texte sans SDL_ttf, on utilise couleurs et contours.
void draw_ui(SDL_Renderer* renderer) {
    int mx, my;
    SDL_GetMouseState(&mx, &my);

    for (int i = 0; i < BTN_COUNT; ++i) {
        SDL_Rect r = g_button_rects[i];

        // couleur de fond des boutons (varie selon l'id)
        switch (i) {
            case BTN_BUBBLE:    SDL_SetRenderDrawColor(renderer, 70, 130, 180, 255); break; // steelblue
            case BTN_SELECTION: SDL_SetRenderDrawColor(renderer, 46, 139, 87, 255);  break; // sea green
            case BTN_QUICK:     SDL_SetRenderDrawColor(renderer, 205, 92, 92, 255);  break; // indianred
            case BTN_MERGE:     SDL_SetRenderDrawColor(renderer, 218, 165, 32, 255); break; // goldenrod
            case BTN_INSERTION: SDL_SetRenderDrawColor(renderer, 138, 43, 226, 255); break; // blueviolet
            case BTN_SHUFFLE:   SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); break; // gray
            case BTN_UP_SPEED:  SDL_SetRenderDrawColor(renderer, 155, 100, 100, 255); break; // gray
            case BTN_DOWN_SPEED:SDL_SetRenderDrawColor(renderer, 100, 156, 100, 255); break; // gray
            default:            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); break;
        }

        // hover effect
        if (mx >= r.x && mx <= r.x + r.w && my >= r.y && my <= r.y + r.h) {
            // lighten color for hover
            SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
            SDL_RenderFillRect(renderer, &r);
        } else {
            SDL_RenderFillRect(renderer, &r);
        }

        // Draw border
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderDrawRect(renderer, &r);

        // Draw label text (si police chargée)
        if (g_font != NULL) {
            SDL_Color text_color = { 255, 255, 255, 255 }; // blanc
            draw_text_centered(renderer, g_button_labels[i], r, text_color);
        }
    }
}

// Retourne l'id du bouton cliqué ou -1 si aucun
int button_id_from_mouse(int x, int y) {
    for (int i = 0; i < BTN_COUNT; ++i) {
        SDL_Rect r = g_button_rects[i];
        if (x >= r.x && x <= r.x + r.w && y >= r.y && y <= r.y + r.h) {
            return i;
        }
    }
    return -1;
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
        // Leave some margin at top and bottom + space for UI
        int max_bar_height = WINDOW_HEIGHT - 50 - UI_HEIGHT;
        if (max_bar_height < 10) max_bar_height = WINDOW_HEIGHT - 50;
        int bar_height = (array[i] * max_bar_height) / max_value;
        
        // Calculate bar position (shift down by UI_HEIGHT)
        int x = i * bar_width;
        int y = WINDOW_HEIGHT - bar_height - 20;
        y = y; // bars will appear below UI because max_bar_height reserved
  
        // highlight selected bar ( element of the list being sorted ) in yellow
        if (i == highlight1 || i == highlight2) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 100, 255);
        } else {
            // Create gradient color based on value
            float ratio = (float)array[i] / (float)max_value;
            
            int r, g, b;
            if (ratio < 0.5f) {
                float local_ratio = ratio * 2.0f;
                r = (int)(local_ratio * 100);
                g = (int)(100 + local_ratio * 155);
                b = (int)(255 - local_ratio * 155);
            } else {
                float local_ratio = (ratio - 0.5f) * 2.0f;
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