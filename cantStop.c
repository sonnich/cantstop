
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//structs
//struct til at holde på 4 terningværdier og deres combinationer.
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
//struct til at holde på de terninger og den combination, som er tilbage.
struct remainingDie{
        int die1;
        int die2;
        
        int combo;
};


//metode declarations.
void printBoard(int board[11][13]);
int readHigh();
void charRead(FILE *fin);
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
void resolveThrow(struct diceThrow dt);
void updateGameboard();
int checkWin();
void gameWon();
int validPick(int i);

//variable
int throwsInRound = 0, numberOfColPicked = 0, currentRound = 0, pickedCol1=-1, pickedCol2=-1, pickedCol3=-1;
int columnsFinished = 0, roundDone =0, throwDone=0, gameCol1 =-1, gameCol2 = -1, gameCol3 = -1, numColGame=0;
int totalThrows = 0, highscoreRunder=20, highscoreKast=10, gameDone =0;
int *columnsPicked[3]= {&pickedCol1, &pickedCol2, &pickedCol3};
char input[1];

//ligesom chessopgaven er det et array af strings, der bestemmer, hvordan boardet vises i konsollen. Strings fordi 10, 11 og 12 ikke
//repræsenteres med en enkelt char.
char *abbre[16] = {"0", "1", "2", "3", "4", "5", "6","7","8","9", "10", "11", "12", " ","*", "x"};
//score i kolonne man skal opnå for at fylde den op.
int goalValues[11] ={2, 4, 6, 8, 10, 12, 10, 8, 6, 4, 2};
//int goalValues[11] ={1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
//array til at holde på spillerens score i de enkelte kolonner;
int scoreValues[11] ={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//array til at holde på den score spilleren har fået i en runde, men som stadig kan tabes.
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

// 2d array til at holde på boardet som det gemmes mellem runder.
int gameBoard[11][13];
//2d array som skal holde boardet som det ser ud i runden.
int roundBoard[11][13];


int main(){
        
        //sætter gameboardet som det ser ud fra start. Seeder
        copyBoard(initBoard, gameBoard);
        srand(time(NULL));
        readHigh();


        //hovedloop for et spil.
        while(input[0]!='q'){

                currentRound++;
                printBoard(gameBoard);                
                printf("Tast r for at rulle.\n");
                scanf(" %c", input);

                        if(input[0]=='r'){
                                //"Bool til at checke om runden er overstået."
                                roundDone=0;
                                //Kopierer de faste værdier over i de respektive holdere til rundens værdier. 
                                copyBoard(gameBoard, roundBoard);
                                copyScoreValues(scoreValues, roundScores);
                                numberOfColPicked = numColGame;
                                pickedCol1 = gameCol1;
                                pickedCol2 = gameCol2;
                                pickedCol3 = gameCol3;


                                

                                while(roundDone==0){
                      
                                        int dice[4] = {throwADie(), throwADie(), throwADie(), throwADie()};
                                        struct diceThrow dt = rollDie(dice);
                                        resolveThrow(dt);
                                }
                                
                        
                        }
                

        }

        return 0;

}

//Håndterer hvilke valg man har alt efter, hvad man har rullet. 
void resolveThrow(struct diceThrow dt){
       
        if(possibleChoice(dt)==1){
                //"Bool til at styre hvor længe man er i det samme kast"
                throwDone=0;

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
                                if(c=='q'){
                                        break;
                                }
                                int col = validateChoice(dt, c);
                                if(col!=-1){
                                        roundScores[col-2]++;
                                        updateRoundBoard(col, roundScores[col-2]);
                                        updateColumnsPicked(col);
                                        printBoard(roundBoard);
                                        if(checkWin()==1){
                                                gameWon();

                                        }else{
                                                                
                                                resolveRemaining(dt, c);
                                                printf("Vil du kaste igen (r) eller passe og afslutte runden(p)\n");
                                                if(input[0]=='q'){
                                                        break;
                                                }
                                                scanf(" %c", input);
                                                if(input[0]=='q'){
                                                        break;
                                                }
                                                if(input[0]=='r'){
                                                throwDone=1;
                                                }else if(input[0]=='p'){
                                                        updateGameboard();
                                                        copyScoreValues(roundScores, scoreValues);
                                                        roundDone=1;
                                                        throwDone=1;  
                                                }
 
                                        }
                                }

                        }else if(c == 'p'){
                                updateGameboard();
                                copyScoreValues(roundScores, scoreValues);
                                roundDone=1;
                                throwDone=1;

                        }
                                       
                }
        }else{
                printf("Du rullede: %d, %d, %d og %d.\n", dt.dice1, dt.dice2, dt.dice3, dt.dice4);
                printf("Ingen mulige kombinationer! BUST!!\n");
                roundDone=1;
                throwDone=1;
        }

}

//opdaterer scoren til det board der holder de sikrede point.
void updateGameboard(){
        
        for(int x = 0; x < 11; x++)
        {
                for(int y = 0; y < 13; y++)
                {
                        if(roundBoard[x][y]==14){
                                gameBoard[x][y]=15;
                        }
                }
        }
        
        numColGame = numberOfColPicked;
        gameCol1 = pickedCol1;
        gameCol2 = pickedCol2;
        gameCol3 = pickedCol3;

}

void gameWon(){
        printf("Tillykke, du kom i maal paa %d runder, og med %d kast!\n", currentRound, totalThrows);
        roundDone=1;
        throwDone=1;
        gameDone=1;
        input[0]='q';
        

        if(currentRound<highscoreRunder||(currentRound==highscoreRunder&&totalThrows<highscoreKast)){
                printf("Du har faaet highscoren!!! Indtast dine initaler\n");
                char initialer[3];
                scanf(" %c", initialer);
                
                char toPrint[4];
                memcpy(toPrint, initialer, 3);
                toPrint[3]='\0';
          
                FILE *f = fopen("highscore.txt", "w");
                if (f == NULL){
                        printf("Error opening file!\n");
                        exit(1);
                }

                //fputs(toPrint, f);
                //fwrite(initialer, sizeof(char), 3, f);
                
                fprintf(f,"%s ROUNDS %d THROWS %d", initialer, currentRound, totalThrows);
                fclose(f);
        
        }
        

}

//metode til at 
void resolveRemaining(struct diceThrow dt, char c){
        //laver en remainingdie ud fra det valg der blev truffet og det terningkast der blev kastet. 
        struct remainingDie rd = resRemaining(dt, c);
        int found = 0;
        int i = 0;
        
        //søger efter, hvorvidt kolonnen er valgt.
        while(found==0&&i<3){
                if(*columnsPicked[i]==rd.combo){
                        found=1;
                     
                }
                i++;
        }
        //Checker om der er frie kolonner og at den ikke er valgt. 
        if(numberOfColPicked<3&&found==0){
                int remainDecision=0;
                while(remainDecision==0){
                        printf("Du kan vaelge %d, som din %d. kolonne. Tast v for at vaelge eller p for at passe.\n", rd.combo, numberOfColPicked+1);
                        scanf(" %c", input);
                        if(input[0]=='q'){
                                roundDone=1;
                                throwDone=1;
                                break;
                        }else if(input[0]=='v'){
                                int col = rd.combo;
                                roundScores[col-2]++;
                                updateRoundBoard(col, roundScores[col-2]);
                                updateColumnsPicked(col);
                                printBoard(roundBoard);
                                if(checkWin()==1){
                                        gameWon();
                                }
                                remainDecision=1;
                        }else if(input[0]=='p'){
                                remainDecision=1;
                        }
                }

        //ser efter, hvis kolonnen allerede er valgt om den har ledige felter.
        }else if(found&&scoreValues[rd.combo-2]<goalValues[rd.combo-2]){
                int remainDecision=0;
                while(remainDecision==0){
                        printf("Du kan vaelge %d ud fra de restende terninger. Tast v for at vaelge eller p for at passe.\n", rd.combo);
                        scanf(" %c", input);
                        if(input[0]=='q'){
                                break;
                        }else if(input[0]=='v'){
                                int col = rd.combo;
                                roundScores[col-2]++;
                                updateRoundBoard(col, roundScores[col-2]);
                                printBoard(roundBoard);
                                remainDecision=1;
                                if(checkWin()==1){
                                        gameWon();
                                }
                        }else if(input[0]=='p'){
                                remainDecision=1;
                        }
                }
        }

        
}


//metode til at opdatere hvilke kolonner, der er "låst"
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

//opdaterer det board, der viser de midlertidige point i en runde.
void updateRoundBoard(int column, int value){
   
        roundBoard[column-2][value-1]=14;
       
}

//funktion til at kopiere værdierne mellem de arrays der holder henholdvist på de "sikre" point mellem runderne,
// og de flygtige point man har scoret i en runde. 
void copyScoreValues(int source[13], int dest[13]){
        
        for(int i = 0; i < 13; i++)
        {
                dest[i]=source[i];
        }
}

//funktion til at lave en struct der holder på de terninger der er tilovers, når ét par terninger er valgt.
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
                        rd.die1 = dt.dice1;
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


int columnStatus(struct diceThrow dt){
        int status =-1;
        if(numberOfColPicked<3){
                status = 1;
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

//metode der checker om et spil er vundet. 
int checkWin(){
        int won =0;

        int counter =0;
        for(int i = 0; i < 11; i++)
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

//metode der checker om der ud fra terningslaget er nogen mulige valg.
int possibleChoice(struct diceThrow dt){
        int status =-1;
        int values[6]= {dt.combo1p2, dt.combo1p3, dt.combo1p4, dt.combo2p3, dt.combo2p4, dt.combo3p4};
        
        
        if(numberOfColPicked==3){
                
                
                for(int i = 0; i < 6; i++)
                {
                        if((values[i]==pickedCol1&&roundScores[pickedCol1-2]<goalValues[pickedCol1-2])||
                        (values[i]==pickedCol2&&roundScores[pickedCol2-2]<goalValues[pickedCol2-2])||
                        (values[i]==pickedCol3&&roundScores[pickedCol3-2]<goalValues[pickedCol3-2])){
                                status = 1;
                        }
                }
   
        }else{
                status = 1;
        }
        return status;
        
  
       
}



//metode til at checke hvorvidt det valg der er blevet indtastet, er legalt.
int validateChoice(struct diceThrow dt, char c){
        
        int valid =-1;

        switch(c){
                case '1':
                        valid = validPick(dt.combo1p2);
                        break;
                 

                case '2':
                        valid = validPick(dt.combo1p3);
                        break;

                case '3' : 
                        valid = validPick(dt.combo1p4);
                        break;

                case '4' :
                        valid = validPick(dt.combo2p3);
                        break;

                case '5' :
                        valid = validPick(dt.combo2p4);
                        break;

                case '6' :
                        valid = validPick(dt.combo3p4);
                        break;
                default:
                        printf("skipped validatChoice switch with %c\n", c);
                        break;
        }
        return valid;
        
}

//hjælpemetode til validateChoice som checker om, den værdi man har valgt, enten er fyldt, eller uden for de mulige kolonner.
int validPick(int i){
        int valid =-1;
        if(numberOfColPicked==3){
                if(checkColumns(i)==1&&roundScores[i-2]<goalValues[i-2]){
                        valid=i;
                }else{
                        valid = -1;
                }
                
        }else{
                if(roundScores[i-2]<goalValues[i-2]){
                        valid = i;
                }

        }
        return valid;
}

//hjælpemetode til validPick som checker om den værdi man har valgt er en af spillerens valgte kolloner. 
int checkColumns(int value){
        int status = -1;
        if(value ==pickedCol1||value==pickedCol2||value==pickedCol3){
                status = 1;
        }else{
                printf("Du har valgt 3 kolonner. Vaelg en vaerdi, der passer til en af dem\n");
        }
        return status;
}

      

//laver en struct dicethrow, ud fra et array af fire random værdier. 
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

        return dt;
}

//skaber en random værdi 
int throwADie(){
        int value = rand() % 6 + 1;
        return value;
}
//metode til at læse highscore fra fil. Har ikke kunnet finde en måde, at læse de specifikke tal, 
//og derfor virker highscore delen ikke helt. 
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

void charRead(FILE *fin){
         int c;
        

        while((c=fgetc(fin))!=EOF){
                putchar(c);
                
        }
        printf("\n");
      

}


void printBoard(int board[11][13])
{
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
