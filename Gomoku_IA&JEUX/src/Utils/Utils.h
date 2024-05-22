
#pragma once
#include <math.h>
#include <SDL2/SDL_ttf.h>

#define PI 3.14159265359

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700
#define TILE_SIZE 32
#define ROWS 18
#define COLS 18

SDL_Renderer *renderer;


uint32_t deltaTime = 0;
Uint32 minimum_fps_delta_time = (1000 / 6); //
Uint32 last_game_step ; // initial value
uint32_t last_tick_time = 0;

void tickClock(){
    Uint32 now = SDL_GetTicks();
    // Check so we don't render for no reason, avoid having a 0 delta time
    if (last_game_step < now) {

        Uint32 delta_time = now - last_game_step;

        if (delta_time > minimum_fps_delta_time) {
            delta_time = minimum_fps_delta_time; // slow down if the computer is too slow
        }
        deltaTime = delta_time;
        last_game_step = now;
    }
}

typedef struct Vec2i{
   int x;
   int y;
} Vec2i;

typedef struct Vec2f{
   float x;
   float y;
} Vec2f;

typedef struct Color{
   int r;
   int g;
   int b;
} Color;

Color newColor(int r,int g,int b){
    Color c;
    c.r = r;
    c.g = g;
    c.b = b;

    return c;
}

Vec2i newVec2(int x,int y){
    Vec2i v;
    v.x = x;
    v.y = y;

    return v;
}

Vec2i* newVec2P(int x,int y){
    Vec2i* v = (struct Vec2i*)malloc( sizeof(struct Vec2i));
    v->x = x;
    v->y = y;
    return v;
}

Vec2f newVec2f(float x,float y){
    Vec2f v;
    v.x = x;
    v.y = y;

    return v;
}

Vec2f* newVec2fP(float x,int y){
    Vec2f* v = (struct Vec2f*)malloc( sizeof(struct Vec2f));
    v->x = x;
    v->y = y;
    return v;
}

float point_distance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x2 - x1, 2) +
		pow(y2 - y1, 2) * 1.0);
}

float Vec2f_length(Vec2f v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

Vec2f Vec2f_normalize(Vec2f v) {
    float length = Vec2f_length(v);
    if (length == 0) {
        return v;  // Avoid division by zero
    }
    v.x /= length;
    v.y /= length;
    return v;
}

int rectCollide(SDL_Rect a, SDL_Rect b) {

    if (a.x < b.x + b.w &&
        a.x + a.w > b.x &&
        a.y < b.y + b.h &&
        a.h + a.y > b.y) {
        return 1;
    }
    return 0;
}

int pointInRect(int x, int y, SDL_Rect rect) {
    if (x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h) {
        return 1; // Point is inside the rectangle
    }
    return 0; // Point is outside the rectangle
}

// text
TTF_Font* font16; 
TTF_Font* font24;
TTF_Font* font32;
TTF_Font* font48;
TTF_Font* font60;
SDL_Surface* surface = NULL;
SDL_Texture* texture = NULL;
void showText(int x, int y, const char* text, int r,int g,int b,TTF_Font* font ) {

    SDL_Color fg ;
    fg.r = r;fg.g = g;fg.b = b;

    surface = TTF_RenderText_Solid(font, text, fg);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect srcRest;
    SDL_Rect desRect;
    TTF_SizeText(font, text, &srcRest.w, &srcRest.h);

    srcRest.x = 0;
    srcRest.y = 0;

    desRect.x = x;
    desRect.y = y;

    desRect.w = srcRest.w;
    desRect.h = srcRest.h;
    SDL_RenderCopy(renderer, texture, &srcRest, &desRect);

    SDL_DestroyTexture(texture);
}