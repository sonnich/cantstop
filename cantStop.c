
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//structs
struct diceThrow {
        int dice1;
        int dice2;
        int dice3;
        int dice4;
        int combo1p2;
        int combo1p3;
        int combo1p4;
        int combo2p3;
        int combo2p4;
        int combo3p4;
};

struct remainingDie{
        int die1;
        int die2;
        
        int combo;
};


//metode signaturer.
void printBoard(int board[11][14]);
int readHigh();
int charRead(FILE *fin);
int throwADie();
void boardData();
struct diceThrow rollDie(int dice[]);
void copyBoard(int source[11][14], int dest[11][14]);
int columnStatus(struct diceThrow dt);

//variable
int throwsInRound = 0, numberOfColPicked = 0, currentRound = 0, pickedCol1=-1, pickedCol2=-1, pickedCol3=-1;
int columnsPicked[3];
char input[1];
//ligesom chess er det et array af strings, der bestemmer, hvordan boardet vises i konsollen. Strings fordi 10, 11 og 12 ikke
//repræsenteres med en enkelt char.
char *abbre[16] = {"0", "1", "2", "3", "4", "5", "6","7","8","9", "10", "11", "12", " ","*", "x"};
int goalValues[11] ={4, 6, 8, 10, 12, 14, 12, 10, 8, 6, 4};
int scoreValues[11] ={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
struct remainingDie rd;


//værdier som boardet skal have i starten af et spil.
int initBoard[11][14]={{2, 0, 0, 2, 13, 13 , 13, 13, 13, 13, 13, 13, 13, 13},
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
        int gameBoard[11][14];
        copyBoard(initBoard, gameBoard);
        srand(time(NULL));
        readHigh();


        //hovedloop for et spil.
        while(input[0]!='q'){
               
                printBoard(gameBoard);
                printf("Tast r for at rulle.\n");
                scanf(" %c", input);
                currentRound++;
                //loop for en runde;
                while(input[0]!='p'){
                        
                        if(input[0]=='r'){

                                int roundBoard[11][14];
                                copyBoard(gameBoard, roundBoard);
                       
                                int dice[4] = {throwADie(), throwADie(), throwADie(), throwADie()};
                                struct diceThrow dt = rollDie(dice);
                                printf("Du rullede: %d, %d, %d og %d.\n", dt.dice1, dt.dice2, dt.dice3, dt.dice4);
                                columnStatus(dt);
                                scanf(" %c", input);
                                
                                printf("int tastet tolket %d", a);
                                if(c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'){
                                        int column = cm.
                                        if(columnsPicked[0])



                                }
                        
                        }
                }

        }

        return 0;

}

struct remainingDie resRemaining(struct diceThrow cm, int choice){

        struct remainingDie rd;

        switch(choice){
                case 1 :
                        rd.die1 = cm.dice3;
                        rd.die2 = cm.dice4;
                case 2 :
                        rd.die1 = cm.dice2;
                        rd.die2 = cm.dice4;
                case 3 : 
                        rd.die1 = cm.dice2;
                        rd.die2 = cm.dice3;
                case 4:
                        rd.die1 = cm.dice3;
                        rd.die2 = cm.dice4;
                case 5: 
                        rd.die1 = cm.dice1;
                        rd.die2 = cm.dice3;
                case 6: 
                        rd.die1 = cm.dice1;
                        rd.die2 = cm.dice2;
                default:
                        printf("Debug. Skipped switch with %d.\n", choice);
                         
        }
        rd.combo = rd.die1 + rd.die2;

        return rd;
}

int validInputchoice(char c){
        int status = 0;
        if(c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'){
                status = 1;
        }else{
                status = -1;
        }
        return status;
}

int columnStatus(struct diceThrow dt){
        int status =-1;
        if(numberOfColPicked<3){
                status = 0;
                printf("Du har stadig ulaaste kolonner og kan vaelge mellem: \n");
                printf("Tast 1 for terning 1 og 2 og vaelg kolonne %d\n", dt.combo1p2);
                printf("Tast 2 for terning 1 og 3 og vaelg kolonne %d\n", dt.combo1p3);
                printf("Tast 3 for terning 1 og 4 og vaelg kolonne %d\n", dt.combo1p4);
                printf("Tast 4 for terning 2 og 3 og vaelg kolonne %d\n", dt.combo2p3);
                printf("Tast 5 for terning 2 og 4 og vaelg kolonne %d\n", dt.combo2p4);
                printf("Tast 6 for terning 3 og 4 og vaelg kolonne %d\n", dt.combo3p4);
                printf("Tast p for at passe.\n");

        }else{
                status = 1;
                printf("Du har låst dig til:");
                
                for(int i = 0; i < numberOfColPicked; i++)
                {
                    printf(" %d", columnsPicked[i]);    
                }
                printf(".\n Tast 1 for terning 1 og 2 og vaelg kolonne %d\n", dt.combo1p2);
                printf("Tast 2 for terning 1 og 3 og vaelg kolonne %d\n", dt.combo1p3);
                printf("Tast 3 for terning 1 og 4 og vaelg kolonne %d\n", dt.combo1p4);
                printf("Tast 4 for terning 2 og 3 og vaelg kolonne %d\n", dt.combo2p3);
                printf("Tast 5 for terning 2 og 4 og vaelg kolonne %d\n", dt.combo2p4);
                printf("Tast 6 for terning 3 og 4 og vaelg kolonne %d\n", dt.combo3p4);
                printf("Tast p for at passe.\n");
                
        }
        return status;
                
        
}

      


struct diceThrow rollDie(int dice[]){
        struct diceThrow dt;
        dt.dice1 = dice[0];
        dt.dice2 = dice[1];
        dt.dice3 = dice[2];
        dt.dice4 = dice[3];
        dt.combo1p2 = dt.dice1 + dt.dice2;
        dt.combo1p3 = dt.dice1 + dt.dice3;
        dt.combo1p4 = dt.dice1 + dt.dice4;
        dt.combo2p3 = dt.dice2 + dt.dice3;
        dt.combo2p4 = dt.dice2 + dt.dice4;
        dt.combo3p4 = dt.dice3 + dt.dice4;

        //printf("Debug data rollDie. dice rolled: dice 1 = %d, dice 2 = %d, dice 3 = %d, dice 4 = %d\n", dt.dice1, dt.dice2, dt.dice3, dt.dice4);
        //printf("Debug data rollDIe. Combos: 1-2 = %d, 1-3 = %d, 1-4 = %d, 2-3 = %d, 2-4 = %d, 3-4 = %d\n", dt.combo1p2, dt.combo1p3,
        // dt.combo1p4, dt.combo2p3, dt.combo2p4, dt.combo3p4);
        return dt;
}

int throwADie(){
        int value = rand() % 6 + 1;
        return value;
}

int readHigh(){
        FILE *fptr;
        char filename[]="highscore.txt";
        int succes = 1;

        if((fptr = fopen(filename, "r"))==NULL){
                printf("Cannot open %s\n", filename);
                succes = 0;
        }else{
                printf("\nCurrent highscore: " );
                charRead(fptr);

                fclose(fptr);
        }
        return succes;
}

int charRead(FILE *fin){
         int c, num;
        num =0;

        while((c=fgetc(fin))!=EOF){
                putchar(c);
                num++;
        }
        printf("\n");
        return num;

}


void printBoard(int board[11][14])
{
         printf(" %s   %s   %s   %s   %s   %s   %s   %s   %s  %s  %s\n", abbre[board[0][0]], abbre[board[1][0]], abbre[board[2][0]], 
                abbre[board[3][0]], abbre[board[4][0]], abbre[board[5][0]], abbre[board[6][0]], abbre[board[7][0]], abbre[board[8][0]],
                abbre[board[9][0]], abbre[board[10][0]]);
   
    for (int i = 1; i < 14; i++)
    {

         
        printf(" %s   %s   %s   %s   %s   %s   %s   %s   %s   %s   %s\n", abbre[board[0][i]], abbre[board[1][i]], abbre[board[2][i]], 
                abbre[board[3][i]], abbre[board[4][i]], abbre[board[5][i]], abbre[board[6][i]], abbre[board[7][i]], abbre[board[8][i]],
                abbre[board[9][i]], abbre[board[10][i]]);
              
        
    }
   
}



void boardData(){
        printf("Current round: %d, throw: %d\n", currentRound, throwsInRound);
}

//metode til at kopiere værdierne i ét board over i et andet. 
void copyBoard(int source[11][14], int dest[11][14]){
        
        for(int x = 0; x < 11; x++)
        {
                for(int y = 0; y < 14; y++)
                {
                        dest[x][y]=source[x][y];
                }
        }

}
