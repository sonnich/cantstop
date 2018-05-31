
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
void printBoard(int board[11][13]);
int readHigh();
int charRead(FILE *fin);
int throwADie();
void gameData();
struct diceThrow rollDie(int dice[]);
void copyBoard(int source[11][13], int dest[11][13]);
int columnStatus(struct diceThrow dt);
int checkColumns(int value);
int possibleChoice(struct diceThrow dt);
int validateChoice(struct diceThrow dt, char c);
void updateRoundBoard(int column, int value);
void copyScoreValues(int source[13], int dest[13]);
void updateColumnsPicked(int c);
void resolveRemaining(struct diceThrow dt, char c);
struct remainingDie resRemaining(struct diceThrow dt, char choice);

//variable
int throwsInRound = 0, numberOfColPicked = 0, currentRound = 0, pickedCol1=-1, pickedCol2=-1, pickedCol3=-1, columnsFinished = 0, roundDone =0, throwDone=0;
int totalThrows = 0;
int *columnsPicked[3]= {&pickedCol1, &pickedCol2, &pickedCol3};
char input[1];

//ligesom chessopgaven er det et array af strings, der bestemmer, hvordan boardet vises i konsollen. Strings fordi 10, 11 og 12 ikke
//repræsenteres med en enkelt char.
char *abbre[16] = {"0", "1", "2", "3", "4", "5", "6","7","8","9", "10", "11", "12", " ","*", "x"};
int goalValues[11] ={3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3};
int scoreValues[11] ={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int roundScores[11];
struct remainingDie rd;


//værdier som boardet skal have i starten af et spil.
int initBoard[11][13]={{ 0, 0, 2, 13, 13 , 13, 13, 13, 13, 13, 13, 13, 13},
                   { 0, 0, 0, 0, 3, 13, 13, 13, 13, 13, 13, 13, 13},
                   { 0, 0, 0, 0, 0, 0, 4, 13, 13, 13, 13, 13, 13},
                   { 0, 0, 0, 0, 0, 0, 0, 0, 5, 13, 13, 13, 13},
                   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 13, 13},
                   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
                   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 13, 13},
                   { 0, 0, 0, 0, 0, 0, 0, 0, 9, 13, 13, 13, 13},
                   { 0, 0, 0, 0, 0, 0, 10, 13, 13, 13, 13, 13, 13},
                   { 0, 0, 0, 0, 11, 13, 13, 13, 13, 13, 13, 13, 13},
                   { 0, 0, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13}};

int roundBoard[11][13];
int gameBoard[11][13];


int main(){
        
        copyBoard(initBoard, gameBoard);
        srand(time(NULL));
        readHigh();


        //hovedloop for et spil.
        while(input[0]!='q'){
               
                printBoard(gameBoard);
                printf("Tast r for at rulle.\n");
                scanf(" %c", input);
                currentRound++;
 
 
                        if(input[0]=='r'){
 
                                
                                copyBoard(gameBoard, roundBoard);
                                copyScoreValues(scoreValues, roundScores);
                       
                                int dice[4] = {throwADie(), throwADie(), throwADie(), throwADie()};
                                struct diceThrow dt = rollDie(dice);
                              
                                if(possibleChoice(dt)==1){


                                        while(throwDone!=1){
                                                if(input[0]=='q'){
                                                        break;
                                                }
                                                printBoard(roundBoard);

                                                printf("Du rullede: %d, %d, %d og %d.\n", dt.dice1, dt.dice2, dt.dice3, dt.dice4);
                                                columnStatus(dt);
                                                scanf(" %c", input);
                                                char c = input[0];
                                

                                                if(c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'){
                                                        int col = validateChoice(dt, c);
                                                        if(col!=-1){
                                                                roundScores[col-2]++;
                                                                updateRoundBoard(col, roundScores[col-2]);
                                                                updateColumnsPicked(col);
                                                                printBoard(roundBoard);
                                                                
                                                                resolveRemaining(dt, c);

                                                        }

                                                }else if(c == 'p'){

                                                }
                                       
                                        }
                                }else{
                                        //busted
                                }
                        
                        }
                

        }

        return 0;

}

void resolveRemaining(struct diceThrow dt, char c){
        struct remainingDie rd = resRemaining(dt, c);
        int found = 0;
        int i = 0;
        
        while(found==0&&i<3){
                if(*columnsPicked[i]==rd.combo){
                        found=1;
                        
                }
                i++;
        }
      
        if(numberOfColPicked<3&&found==0){
                int remainDecision=0;
                while(remainDecision==0){
                        printf("Du kan vaelge %d, som din %d. kolonne. Tast v for at vaelge eller p for at passe.\n", rd.combo, numberOfColPicked+1);
                        scanf(" %c", input);
                        if(input[0]=='q'){
                                break;
                        }else if(input[0]=='v'){
                                int col = rd.combo;
                                roundScores[col-2]++;
                                updateRoundBoard(col, roundScores[col-2]);
                                updateColumnsPicked(col);
                                printBoard(roundBoard);
                                remainDecision=1;
                        }else if(input[0]=='p'){
                                remainDecision=1;
                        }
                }
                
        }else if(found){
                int remainDecision=0;
                while(remainDecision==0){
                        printf("Du kan vaelge %d ud fra de restende terninger. Tast v for at vælge eller p for at passe.\n", rd.combo);
                        scanf(" %c", input);
                        if(input[0]=='q'){
                                break;
                        }else if(input[0]=='v'){
                                int col = rd.combo;
                                roundScores[col-2]++;
                                updateRoundBoard(col, roundScores[col-2]);
                                printBoard(roundBoard);
                                remainDecision=1;
                        }else if(input[0]=='p'){
                                remainDecision=1;
                        }
                }
        }

        
}

void updateColumnsPicked(int c){
        int found = 0;
        int i = 0;
        while(found==0&&i<3){
                if(*columnsPicked[i]==c){
                        found=1;
                }
                i++;
        }

        if(numberOfColPicked==0&&found==0){
                pickedCol1=c;
                numberOfColPicked=1;
        }else if(numberOfColPicked==1&&found==0){
                pickedCol2=c;
                numberOfColPicked=2;
        }else if(numberOfColPicked==2&&found==0){
                pickedCol3=c;
                numberOfColPicked=3;
        }
}

void updateRoundBoard(int column, int value){
   
        roundBoard[column-2][value-1]=14;
       
}

void copyScoreValues(int source[13], int dest[13]){
        
        for(int i = 0; i < 13; i++)
        {
                dest[i]=source[i];
        }
}

struct remainingDie resRemaining(struct diceThrow dt, char choice){

        struct remainingDie rd;

        switch(choice){
                case '1' :
                        rd.die1 = dt.dice3;
                        rd.die2 = dt.dice4;
                        break;
                case '2' :
                        rd.die1 = dt.dice2;
                        rd.die2 = dt.dice4;
                        break;
                case '3' : 
                        rd.die1 = dt.dice2;
                        rd.die2 = dt.dice3;
                        break;
                case '4':
                        rd.die1 = dt.dice3;
                        rd.die2 = dt.dice4;
                        break;
                case '5': 
                        rd.die1 = dt.dice1;
                        rd.die2 = dt.dice3;
                        break;
                case '6': 
                        rd.die1 = dt.dice1;
                        rd.die2 = dt.dice2;
                        break;
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
                printf("Du har laast dig til:");
                
                for(int i = 0; i < numberOfColPicked; i++)
                {
                    printf(" %d", *columnsPicked[i]);    
                }
                printf(".\nTast 1 for terning 1 og 2 og vaelg kolonne %d\n", dt.combo1p2);
                printf("Tast 2 for terning 1 og 3 og vaelg kolonne %d\n", dt.combo1p3);
                printf("Tast 3 for terning 1 og 4 og vaelg kolonne %d\n", dt.combo1p4);
                printf("Tast 4 for terning 2 og 3 og vaelg kolonne %d\n", dt.combo2p3);
                printf("Tast 5 for terning 2 og 4 og vaelg kolonne %d\n", dt.combo2p4);
                printf("Tast 6 for terning 3 og 4 og vaelg kolonne %d\n", dt.combo3p4);
                printf("Tast p for at passe.\n");
                
        }
        return status;
                
        
}

int CheckWin(){
        int won =0;

        int counter =0;
        for(int i = 0; i < 13; i++)
        {
               if(roundScores[i]==goalValues[i]){
                       counter++;
               }
        }
        columnsFinished=counter;
        if(columnsFinished ==3){
                won=1;
        }
        return won;
        
}

int possibleChoice(struct diceThrow dt){
        int status =-1;
        
        
        if(numberOfColPicked==3){
                int values[6]= {dt.combo1p2, dt.combo1p3, dt.combo1p4, dt.combo2p3, dt.combo2p4, dt.combo3p4};
                
                for(int i = 0; i < 6; i++)
                {
                        if(values[i]==pickedCol1||values[i]==pickedCol2||values[i]==pickedCol3){
                                status = 1;
                        }
                }
   
        }else{
                status = 1;
        }
        return status;
        
  
       
}

int validateChoice(struct diceThrow dt, char c){
        
        int valid =-1;

        switch(c){
                case '1': if(numberOfColPicked==3){
                                if(checkColumns(dt.combo1p2)==1){
                                    valid=dt.combo1p2;
                                }else{
                                     valid = -1;
                                }
                            
                            }else{
                               valid=dt.combo1p2; 
                            }
                          break;
                 

                case '2': if(numberOfColPicked==3){
                                if(checkColumns(dt.combo1p2)==1){
                                    valid=dt.combo1p3;
                                }else{
                                     valid = -1;
                                }
                            
                            }else{
                               valid=dt.combo1p2; 
                            }
                          break;

                case '3' :if(numberOfColPicked==3){
                                if(checkColumns(dt.combo1p4)==1){
                                    valid=dt.combo1p4;
                                }else{
                                     valid = -1;
                                }
                            
                            }else{
                               valid=dt.combo1p4; 
                            }
                          break;

                case '4' :if(numberOfColPicked==3){
                                if(checkColumns(dt.combo2p3)==1){
                                    valid=dt.combo2p3;
                                }else{
                                     valid = -1;
                                }
                            
                            }else{
                               valid=dt.combo2p3; 
                            }
                          break;

                case '5' :if(numberOfColPicked==3){
                                if(checkColumns(dt.combo2p4)==1){
                                    valid=dt.combo2p4;
                                }else{
                                     valid = -1;
                                }
                            
                            }else{
                               valid=dt.combo2p4; 
                            }
                          break;
                case '6' :if(numberOfColPicked==3){
                                if(checkColumns(dt.combo3p4)==1){
                                    valid=dt.combo3p4;
                                }else{
                                     valid = -1;
                                }
                            
                            }else{
                               valid=dt.combo3p4; 
                            }
                          break;
                default:
                        printf("skipped validatChoice switch with %c\n", c);
                        break;
        }
        return valid;
        
}

int checkColumns(int value){
        int status = -1;
        if(value ==pickedCol1||value==pickedCol2||value==pickedCol3){
                status = 1;
        }else{
                printf("Du har valgt 3 kolonner. Vaelg en vaerdi, der passer til en af dem\n");
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
        totalThrows++;

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


void printBoard(int board[11][13])
{
        //  printf(" %s   %s   %s   %s   %s   %s   %s   %s   %s  %s  %s\n", abbre[board[0][0]], abbre[board[1][0]], abbre[board[2][0]], 
        //         abbre[board[3][0]], abbre[board[4][0]], abbre[board[5][0]], abbre[board[6][0]], abbre[board[7][0]], abbre[board[8][0]],
        //         abbre[board[9][0]], abbre[board[10][0]]);
        gameData();

        printf(" 2   3   4   5   6   7   8   9   10  11  12\n");
   
    for (int i = 0; i < 13; i++)
    {

         
        printf(" %s   %s   %s   %s   %s   %s   %s   %s   %s   %s   %s\n", abbre[board[0][i]], abbre[board[1][i]], abbre[board[2][i]], 
                abbre[board[3][i]], abbre[board[4][i]], abbre[board[5][i]], abbre[board[6][i]], abbre[board[7][i]], abbre[board[8][i]],
                abbre[board[9][i]], abbre[board[10][i]]);
              
        
    }
   
}



void gameData(){
        printf("Current round: %d, throw: %d\n", currentRound, totalThrows);
}

//metode til at kopiere værdierne i ét board over i et andet. 
void copyBoard(int source[11][13], int dest[11][13]){
        
        for(int x = 0; x < 11; x++)
        {
                for(int y = 0; y < 13; y++)
                {
                        dest[x][y]=source[x][y];
                }
        }

}
