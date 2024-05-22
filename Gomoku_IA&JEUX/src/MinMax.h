#include "Board.h"
#define MAX_DEPTH 3
#include <time.h>

int evaluate() {
    int winner = checkWinner();
    if (winner == 1) return 10; // High score for Black win
    if (winner == -1) return -10; // Low score for White win
    return 0; // No win situation
}

int isInMoveList(ArrayList* moveList,int row,int col){
    for(int i = 0 ; i < moveList->total;i++){
        Vec2i* rowCol = (Vec2i*) moveList->items[i];
        if(rowCol->x == col && rowCol->y == row){
            return 1;
        }
    }
    return 0;
}

void getmoveList(ArrayList* moveList){
    ArrayList_init(moveList);
    // for(int i = 0 ; i < nodes.total;i++){
    //     Vec2i* rowCol = (Vec2i*) nodes.items[i];
    //     int row = rowCol->y;
    //     int col = rowCol->x;
    //     printf("exit: %d %d\n",row,col);
    // }

    // for(int i = 0 ; i < nodes.total;i++){
    //     Vec2i* rowCol = (Vec2i*) nodes.items[i];
    //     int row = rowCol->y;
    //     int col = rowCol->x;

       
    // }
    for(int row = 0; row < ROWS;row++){
        for(int col = 0; col < COLS;col++){
            if(grid[row][col] != 0){
                int dirX[8] = { 0,1,-1,1,-1,1,-1,0 };
                int dirY[8] = { -1,-1,-1,1,1,0,0,1 };

                for(int i = 0; i < 8;i++){
                    int nextRow = row + dirY[i];
                    int nextCol = col + dirX[i];
                    if(nextCol < 0 || nextCol > COLS-1 || nextRow < 0 || nextRow > ROWS-1 ){
                        continue;
                    }
                    if(isInMoveList(moveList,nextRow,nextCol) == 1){
                        continue;
                    }
                    ArrayList_add(moveList,newVec2P(nextCol,nextRow));
                }
            }
            
        }
    }
}

// void printD(int depth,int row,int col,int score){
//     for(int i= 0 ; i < depth;i++){
//         printf("- ");
//     }
//     printf(" %d %d: %d\n",row,col,score);
// }

int minimax(int depth, int isMaximizing, int alpha, int beta) {
    int score = evaluate();
    if (score == 10 || score == -10 || depth == MAX_DEPTH) return score;

    ArrayList moveList;
    getmoveList(&moveList);

    if (isMaximizing) {
        int best = -1000;
        for(int i = 0 ; i < moveList.total;i++){
            Vec2i* rowCol = (Vec2i*) moveList.items[i];
            int row = rowCol->y;
            int col = rowCol->x;
            if(grid[row][col] == 0){
                grid[row][col] = 1;
                best = fmax(best, minimax(depth + 1, 0, alpha, beta));
                alpha = fmax(alpha, best);
                grid[row][col] = 0;
                if (beta <= alpha) break; // Beta cut-off
            }
        }
        return best;
    } else {
        int best = 1000;
        for(int i = 0 ; i < moveList.total;i++){
            Vec2i* rowCol = (Vec2i*) moveList.items[i];
            int row = rowCol->y;
            int col = rowCol->x;
            if(grid[row][col] == 0){
                grid[row][col] = -1;
                best = fmin(best, minimax(depth + 1, 1, alpha, beta));
                beta = fmin(beta, best);
                grid[row][col] = 0;
                if (beta <= alpha) break; // Alpha cut-off
            }
        }
        return best;
    }
}

void findBestMove() {
    int bestVal = -1000;
    int bestMoveRow = -1;
    int bestMoveCol = -1;
    ArrayList moveList;
    getmoveList(&moveList);
    int alpha = -1000; // Initialize alpha for maximizer
    int beta = 1000;   // Initialize beta for minimizer
    // Mesure du temps de début
    clock_t start, end;
    double cpu_time_used;
     start = clock();

    for(int i = 0 ; i < moveList.total;i++){
        Vec2i* rowCol = (Vec2i*) moveList.items[i];
        int row = rowCol->y;
        int col = rowCol->x;
        if(grid[row][col] == 0){
            grid[row][col] = 1;
            int moveVal = minimax(0, 0, alpha, beta); // Call minimax with appropriate parameters
            grid[row][col] = 0;
            if (moveVal > bestVal ) {
                bestMoveRow = row;
                bestMoveCol = col;
                bestVal = moveVal;
            }
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("place-------------!\n");
    printf("%d %d\n",bestMoveRow,bestMoveCol);
    printf("-------best: %d\n",bestVal);
    printf("Temps de calcul: %f secondes\n", cpu_time_used);

    if (bestMoveRow != -1 && bestMoveCol != -1) {
        grid[bestMoveRow][bestMoveCol] = -1;
        ArrayList_add(&nodes,newVec2P(bestMoveCol,bestMoveRow));
    }
}