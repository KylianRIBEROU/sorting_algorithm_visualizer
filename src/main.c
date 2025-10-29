#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "visual.h"
#include "menu.h"
#include "utils.h"
#include "sorting.h"
#include "stats.h"

#define ARRAY_SIZE 64
#define DELAY_MS 1

// Variables globales pour la visualisation
SDL_Renderer* g_renderer = NULL;
int* g_array = NULL;
int g_array_size = 0;

// Callback de visualisation
void visualize_step(int* array, int size, int highlight1, int highlight2) {
    clear_sdl_window(g_renderer);
    draw_array_on_window(g_renderer, array, size, highlight1, highlight2);
    refresh_present_window(g_renderer);
    SDL_Delay(DELAY_MS);
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit(0);
        }
    }
}

int main(int argc, char* argv[]) {
    // Fenêtres et renderers pour les deux fenêtres
    SDL_Window* visual_window = NULL;
    SDL_Renderer* visual_renderer = NULL;
    SDL_Window* menu_window = NULL;
    SDL_Renderer* menu_renderer = NULL;

    // Initialiser SDL (une seule fois)
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Créer la fenêtre de visualisation
    if (init_sdl_window(&visual_window, &visual_renderer) != 0) {
        fprintf(stderr, "Failed to initialize visual window\n");
        SDL_Quit();
        return 1;
    }

    // Créer la fenêtre de menu
    if (init_menu_window(&menu_window, &menu_renderer) != 0) {
        fprintf(stderr, "Failed to initialize menu window\n");
        clean_up_sdl_window(visual_window, visual_renderer);
        SDL_Quit();
        return 1;
    }

    printf("Both windows created successfully!\n");
    printf("Visual window: 800x600\n");
    printf("Menu window: 400x600\n");
    printf("\nPress ESC or close any window to quit.\n");
    printf("Press SPACE to regenerate array.\n");
    printf("Press ENTER to start Bubble Sort.\n");
    printf("Press S to start Selection Sort.\n");

    // Créer et générer le tableau
    int* array = (int*)malloc(ARRAY_SIZE * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        clean_up_menu_window(menu_window, menu_renderer);
        clean_up_sdl_window(visual_window, visual_renderer);
        return 1;
    }

    generate_random_array(array, ARRAY_SIZE);
    printf("Array generated with %d elements\n", ARRAY_SIZE);
    
    // Configurer les variables globales
    g_renderer = visual_renderer;
    g_array = array;
    g_array_size = ARRAY_SIZE;
    
    // Initialiser les statistiques
    Statistics stats;
    stats_init(&stats);
    
    int is_sorting = 0;

    // Boucle principale
    int running = 1;
    SDL_Event event;

    while (running) {
        // Gérer les événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                }
                else if (event.key.keysym.sym == SDLK_SPACE && !is_sorting) {
                    generate_random_array(array, ARRAY_SIZE);
                    stats_reset(&stats);
                    printf("Array regenerated\n");
                }
                else if (event.key.keysym.sym == SDLK_RETURN && !is_sorting) {
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
                else if (event.key.keysym.sym == SDLK_s && !is_sorting) {
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
            }
        }

        // Rafraîchir la fenêtre de visualisation
        clear_sdl_window(visual_renderer);
        draw_array_on_window(visual_renderer, array, ARRAY_SIZE, -1, -1);
        refresh_present_window(visual_renderer);

        // Rafraîchir la fenêtre de menu (pour l'instant juste le fond)
        clear_menu_window(menu_renderer);
        refresh_menu_window(menu_renderer);

        SDL_Delay(16); // ~60 FPS
    }

    // Nettoyage
    free(array);
    clean_up_menu_window(menu_window, menu_renderer);
    clean_up_sdl_window(visual_window, visual_renderer);
    SDL_Quit();
    printf("Program terminated successfully.\n");

    return 0;
}