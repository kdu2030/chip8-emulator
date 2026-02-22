#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "SDL.h"

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} sdl_t;

typedef struct {
   uint32_t window_width;
   uint32_t window_height;
   uint32_t fg_color; // Foreground color RGBA8888
   uint32_t bg_color; // Background color RGBA8888
} config_t;

bool init_sdl(sdl_t *sdl, const config_t config){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        SDL_Log("Could not initialize SDL Subsystems! %s\n", SDL_GetError());
        return false;
    }

    sdl->window = SDL_CreateWindow(
        "Chip8 Emulator", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        config.window_width, 
        config.window_height, 
        0
    );

    if(!sdl->window){
        SDL_Log("Could not create SDL Window %s", SDL_GetError());
        return false;
    }

    sdl->renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED);

    if(!sdl->renderer){
        SDL_Log("Could not create SDL Renderer %s", SDL_GetError());
        return false;
    }

    return true;
}

bool set_config_from_args(config_t *config, int argc, char *argv[]){
    *config = (config_t){
        .window_width = 64,
        .window_height = 32,
        .fg_color = 0xFFFF00FF, // Yellow
        .bg_color = 0x00000000 // Black
    };

    (void) argc;
    (void) argv;
    return true;
}

void final_cleanup(sdl_t sdl){
    SDL_DestroyRenderer(sdl.renderer);
    SDL_DestroyWindow(sdl.window);
    SDL_Quit();
}

int main(int argc, char *argv[]){
    sdl_t sdl = {0};
    config_t config = {0};

    if(!set_config_from_args(&config, argc, argv)){
        exit(EXIT_FAILURE);
    }

    if(!init_sdl(&sdl, config)){
        exit(EXIT_FAILURE);
    }

    const uint8_t foreground_r = config.fg_color >> 24;
    const uint8_t foreground_g = config.fg_color >> 16;
    const uint8_t foreground_b = config.fg_color >> 8;

    printf("R: %d \n", foreground_r);
    printf("G: %d \n", foreground_g);
    printf("B: %d \n", foreground_b);

    (void) foreground_r;
    (void) foreground_g;
    (void) foreground_b;
    
    SDL_RenderClear(sdl.renderer);

    // while(true){

    // }

    final_cleanup(sdl);

    exit(EXIT_SUCCESS);
}