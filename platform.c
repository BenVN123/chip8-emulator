#include <SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "platform.h"
#include "components.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

void build_platform(
    char *title,
    int window_width,
    int window_height,
    int texture_width,
    int texture_height
) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("sdl could not initialize: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow(title,
        0,
        0,
        window_width,
        window_height,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        printf("window could not be created: %s\n", SDL_GetError());
        destroy_platform();
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("renderer could not be created: %s\n", SDL_GetError());
        destroy_platform();
        exit(EXIT_FAILURE);
    }

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        texture_width,
        texture_height
    );
    if (!texture) {
        printf("texture could not be created: %s\n", SDL_GetError());
        destroy_platform();
        exit(EXIT_FAILURE);
    }   
}

void destroy_platform(void) {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    window = NULL;
    renderer = NULL;
    texture = NULL;
}

void update(void const *buffer, int pitch) {
    SDL_UpdateTexture(texture, NULL, buffer, pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

bool process_input(uint8_t *keys) {
    bool quit = false;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_x:
                        keys[0] = 1;
                        break;
                    case SDLK_1:
                        keys[1] = 1;
                        break;
                    case SDLK_2:
                        keys[2] = 1;
                        break;
                    case SDLK_3:
                        keys[3] = 1;
                        break;
                    case SDLK_q:
                        keys[4] = 1;
                        break;
                    case SDLK_w:
                        keys[5] = 1;
                        break;
                    case SDLK_e:
                        keys[6] = 1;
                        break;
                    case SDLK_a:
                        keys[7] = 1;
                        break;
                    case SDLK_s:
                        keys[8] = 1;
                        break;
                    case SDLK_d:
                        keys[9] = 1;
                        break;
                    case SDLK_z:
                        keys[0xA] = 1;
                        break;
                    case SDLK_c:
                        keys[0xB] = 1;
                        break;
                    case SDLK_4:
                        keys[0xC] = 1;
                        break;
                    case SDLK_r:
                        keys[0xD] = 1;
                        break;
                    case SDLK_f:
                        keys[0xE] = 1;
                        break;
                    case SDLK_v:
                        keys[0xF] = 1;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_x:
                        keys[0] = 0;
                        break;
                    case SDLK_1:
                        keys[1] = 0;
                        break;
                    case SDLK_2:
                        keys[2] = 0;
                        break;
                    case SDLK_3:
                        keys[3] = 0;
                        break;
                    case SDLK_q:
                        keys[4] = 0;
                        break;
                    case SDLK_w:
                        keys[5] = 0;
                        break;
                    case SDLK_e:
                        keys[6] = 0;
                        break;
                    case SDLK_a:
                        keys[7] = 0;
                        break;
                    case SDLK_s:
                        keys[8] = 0;
                        break;
                    case SDLK_d:
                        keys[9] = 0;
                        break;
                    case SDLK_z:
                        keys[0xA] = 0;
                        break;
                    case SDLK_c:
                        keys[0xB] = 0;
                        break;
                    case SDLK_4:
                        keys[0xC] = 0;
                        break;
                    case SDLK_r:
                        keys[0xD] = 0;
                        break;
                    case SDLK_f:
                        keys[0xE] = 0;
                        break;
                    case SDLK_v:
                        keys[0xF] = 0;
                        break;
                }
                break;
        }
    }

    return quit;
}

