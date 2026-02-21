#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "SDL.h"

bool init_sdl(void){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        SDL_Log("Could not initialize SDL Subsystems! %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void final_cleanup(void){
    SDL_Quit();
}

int main(int argc, char *argv[]){
    (void) argc;
    (void) argv;

    if(!init_sdl()){
        exit(EXIT_FAILURE);
    }

    final_cleanup();

    exit(EXIT_SUCCESS);
}