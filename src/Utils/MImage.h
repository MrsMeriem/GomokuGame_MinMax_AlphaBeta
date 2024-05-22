#pragma once
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "Utils.h"


typedef struct MImage{
    SDL_Texture* texture;
    SDL_Rect    src;
    SDL_Rect    dest;
    SDL_Point center;
    float angle;
} MImage;

MImage* createMImage(const char* path, int x, int y) {
    MImage* mImage = (struct MImage*)malloc(sizeof(struct MImage));

    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL) {
        // Handle error (e.g., image not found)
        free(mImage);
        return NULL;
    }

    mImage->texture = SDL_CreateTextureFromSurface(renderer, surface);
    mImage->src.x = 0;
    mImage->src.y = 0;
    mImage->src.w = surface->w; // Width of the loaded image
    mImage->src.h = surface->h; // Height of the loaded image

    mImage->dest.x = x;
    mImage->dest.y = y;
    mImage->dest.w = surface->w; // Width of the destination rectangle
    mImage->dest.h = surface->h; // Height of the destination rectangle

    SDL_FreeSurface(surface); // Free the surface after getting width and height
    return mImage;
}

void drawMImage(MImage* mImage){
    SDL_RenderCopy(renderer, mImage->texture, NULL, &mImage->dest);
}
void drawMImageEx(MImage* mImage,float angle,Color color){
    SDL_SetTextureColorMod(mImage->texture,color.r,color.g,color.b);
    SDL_RenderCopyEx(renderer,
                    mImage->texture,
                    NULL,
                    &mImage->dest,
                    angle,
                    NULL,
                   SDL_FLIP_NONE);
}
