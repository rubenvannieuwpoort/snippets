#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 512
#define GRID_WIDTH 256
#define GRID_HEIGHT 256


int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create SDL window and renderer
    SDL_Window *window = SDL_CreateWindow("Grayscale Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create a streaming SDL texture with RGB24 format, e.g. RGB with 1 byte per color channel
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING,
                                             GRID_WIDTH, GRID_HEIGHT);
    if (!texture) {
        printf("SDL_CreateTexture Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int t = 0;
    bool running = true;
    while (true) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                goto exit;
            }
        }

        // Update buffer that backs the texture
        int pitch;
        uint8_t *buffer;
        if (SDL_LockTexture(texture, NULL, (void **)&buffer, &pitch) != 0) {
            goto exit;
        }

        for (int y = 0; y < 256; y++) {
            int i = y * pitch;
            for (int x = 0; x < 256; x++) {
                uint8_t gray_value = (x + t) ^ y;
                buffer[i++] = gray_value;
                buffer[i++] = gray_value;
                buffer[i++] = gray_value;
            }
        }
        SDL_UnlockTexture(texture);

        t++;

        // Render the texture to the screen
        if (SDL_RenderCopy(renderer, texture, NULL, NULL) != 0) {
            goto exit;
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    exit:
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
