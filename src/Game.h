#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>
#include "Board.h"
#include "MinMax.h"
#include "Utils/Utils.h"


int turn = 1;
int winner = 0;
int waitTime = 0;


void gameStart(){
    createGrid();
    turn = 1;
    winner = 0;
    waitTime = 0;
}

void gameUpdate(){
    if(winner != 0){
        return;
    }
    //computer turn
    if(turn == -1){
        waitTime += deltaTime;
        if(waitTime >= 100){
            findBestMove();
            waitTime = 0;
            turn *= -1;
        }
    }

    winner = checkWinner();
}

void gameDraw(){

    if(winner == 1){
        showText(700/2 - 50 ,20,"Black Win!",1,1,1,font24);
    }
    else if(winner == -1){
        showText(700/2 - 50 ,20,"White Win!",111,1,1,font24);
    }
    drawGrid();


    if(winner != 0){
        return;
    }
    if(turn == 1){
        showText(700/2 - 50 ,20,"Player turn!",1,1,1,font24);
    }
    else if(turn == -1){
        showText(700/2 - 50 ,20,"Enemy Turn!",111,1,1,font24);
    }
}

void onMouseDown(float mouseX,float mouseY){
   Vec2i clickRC = toRowCol(mouseX,mouseY);
   if(winner != 0){
    gameStart();
    return;
   }
   if(grid[clickRC.y][clickRC.x] != 0){
    return;
   }
   if(turn == -1){
    return;
   }
   ArrayList_add(&nodes,newVec2P(clickRC.x,clickRC.y));
   printf("click: %d %d\n",clickRC.y,clickRC.x);
   grid[clickRC.y][clickRC.x] = turn;
   turn *= -1;
}


void onKeyDown(SDL_Keycode e){
    (void)e;
}

void onKeyUp(SDL_Keycode e){
    (void)e;
}

