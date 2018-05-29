
#include <stdio.h>
char abbre[16] = {'0', '1', '2', '3', '4', '5', '6','7','8','9', 't', 'e', 'o',' ','*', 'x'};
void printBoard(int board[11][14]);


void printBoard(int board[11][14])
{
        //printf("i board");
   
    for (int i = 0; i < 14; i++)
    {
            
        printf(" %c  %c  %c  %c  %c  %c  %c  %c  %c  %c  %c\n", abbre[board[0][i]], abbre[board[1][i]], abbre[board[2][i]], 
                abbre[board[3][i]], abbre[board[4][i]], abbre[board[5][i]], abbre[board[6][i]], abbre[board[7][i]], abbre[board[8][i]],
                abbre[board[9][i]], abbre[board[10][i]]);
              
        
    }
   
}

int Board[11][14]={{2, 0, 0, 2, 13, 13 , 13, 13, 13, 13, 13, 13, 13, 13},
                   {3, 0, 0, 0, 0, 3, 13, 13, 13, 13, 13, 13, 13, 13},
                   {4, 0, 0, 0, 0, 0, 0, 4, 13, 13, 13, 13, 13, 13},
                   {5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 13, 13, 13, 13},
                   {6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 13, 13},
                   {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
                   {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 13, 13},
                   {9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 13, 13, 13, 13},
                   {10, 0, 0, 0, 0, 0, 0, 10, 13, 13, 13, 13, 13, 13},
                   {11, 0, 0, 0, 0, 11, 13, 13, 13, 13, 13, 13, 13, 13},
                   {12, 0, 0, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13}};


int main(){


        printBoard(Board);
        printf("efter board");



        return 0;
}
