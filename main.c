#include <SDL2/SDL.h>
#include <stdio.h>
#include "src/Game.h"
#include <time.h>
#include <SDL_image.h>




int init(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    IMG_Init(IMG_INIT_PNG);
    if (TTF_Init() < 0)
	{
		SDL_Log("%s", TTF_GetError());
		return -1;
	}
    font16 = TTF_OpenFont("../assets/font.ttf", 16);
    font24 = TTF_OpenFont("../assets/font.ttf", 24);
    font32 = TTF_OpenFont("../assets/font.ttf", 32);
    font48 = TTF_OpenFont("../assets/font.ttf", 48);
    font60 = TTF_OpenFont("../assets/font.ttf", 60);
    //another lib init here

    return 0;
}

int main(int argc, char** argv){
    (void)argc;(void)argv;
    if(init() == 1){ //init
        return 1;
    }    
    srand(time(NULL));
    SDL_Window *window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(!window){
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    last_game_step = SDL_GetTicks();
    gameStart();

    int running = 1;
    while(running == 1){
        tickClock();

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    onMouseDown(event.button.x, event.button.y);
                    break;
                case SDL_KEYDOWN:
                    onKeyDown(event.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    onKeyUp(event.key.keysym.sym);
                    break;
                default:
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 205, 232, 229, 0);
        SDL_RenderClear(renderer);
        gameUpdate();
        gameDraw();
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}

