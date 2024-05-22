#pragma once
#include "Utils/Utils.h"
#include "Utils/MImage.h"
#include "Utils/ArrayList.h"
#define MAX_WIN 5 // Number of aligned pieces

Vec2f gridPos;
    //generate map_matrix from file
int** grid;
MImage* tile1;
MImage* blackImg;
MImage* whiteImg;
ArrayList nodes;

void createGrid(){
    ArrayList_init(&nodes);
    tile1 = createMImage("../assets/tile1.png",0,0);
    blackImg = createMImage("../assets/black.png",0,0);
    whiteImg = createMImage("../assets/white.png",0,0);
    gridPos = newVec2f(60,60);

    grid = (int**)malloc(ROWS * sizeof(int*));
    for (int i = 0; i < ROWS; i++) {
        grid[i] = (int*)malloc(COLS * sizeof(int));
    }
    for(int row = 0; row < ROWS;row++){
        for(int col = 0; col < COLS;col++){
            grid[row][col] = 0;
        }
    }

}

void drawGrid(){
    for(int row = 0; row < ROWS; row++){
        for(int col = 0 ; col < COLS;col++){
            tile1->dest.x = gridPos.x + col * TILE_SIZE;
            tile1->dest.y = gridPos.y + row * TILE_SIZE;
            drawMImage(tile1);
            if(grid[row][col] == 1){
                blackImg->dest.x = gridPos.x + col * TILE_SIZE;
                blackImg->dest.y = gridPos.y + row * TILE_SIZE;
                drawMImage(blackImg);
            }
            else if(grid[row][col] == -1){
                whiteImg->dest.x = gridPos.x + col * TILE_SIZE;
                whiteImg->dest.y = gridPos.y + row * TILE_SIZE;
                drawMImage(whiteImg);
            }
            // char str[20]; 
            // sprintf(str, "%d,%d", row,col);
            // showText(gridPos.x + col * TILE_SIZE ,gridPos.y + row * TILE_SIZE,str,111,1,1,font16);
        }
    }
}

Vec2i toRowCol(float x,float y){
    int col = (x - gridPos.x) / TILE_SIZE;
    int row = (y - gridPos.y) / TILE_SIZE;
    return newVec2(col,row);
}

int checkDirection(int row, int col, int dRow, int dCol) {
    int player = grid[row][col];
    if (player == 0) return 0;
    int win_count = MAX_WIN;

    for (int i = 1; i < win_count; i++) {
        int newRow = row + i * dRow;
        int newCol = col + i * dCol;
        if (newRow < 0 || newRow >= ROWS || newCol < 0 || newCol >= COLS || grid[newRow][newCol] != player) {
            return 0;
        }
    }
    return player;
}

int checkWinner() {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (grid[row][col] != 0) {
                if (checkDirection(row, col, 0, 1) || // Check row
                    checkDirection(row, col, 1, 0) || // Check column
                    checkDirection(row, col, 1, 1) || // Check diagonal (top-left to bottom-right)
                    checkDirection(row, col, 1, -1)) { // Check diagonal (top-right to bottom-left)
                    return grid[row][col];
                }
            }
        }
    }
    return 0; // No winner
}
