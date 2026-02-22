#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "SDL.h"

typedef struct {
    SDL_Window *window;
} sdl_t;

typedef struct {
   int window_width;
   int window_height;
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

    return true;
}

bool set_config_from_args(config_t *config, int argc, char *argv[]){
    *config = (config_t){
        .window_width = 64,
        .window_height = 32
    };

    (void) argc;
    (void) argv;
    return true;
}

void final_cleanup(sdl_t sdl){
    SDL_DestroyWindow(sdl.window);
    SDL_Quit();
}

int main(int argc, char *argv[]){
    (void) argc;
    (void) argv;

    sdl_t sdl = {0};
    config_t config = {0};

    if(!set_config_from_args(&config, argc, argv)){
        exit(EXIT_FAILURE);
    }

    if(!init_sdl(&sdl, config)){
        exit(EXIT_FAILURE);
    }

    final_cleanup(sdl);

    exit(EXIT_SUCCESS);
}