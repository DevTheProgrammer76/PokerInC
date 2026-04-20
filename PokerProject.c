/* 
 * File: PokerProject.c
 * Authors: Devin Barrow, Antoinette Hults, Briseis Ramirez
 * Purpose: Create a playable poker with working visuals
 * Date: 17th April, 2026
 * 
 * Sources of help:
 * Microsoft Co-Pilot (Used for error checking), Ideas for hand checking and comparison, function in function setup.
 * Sawyer Curless (idea drafting)
 * Dr. O (Idea drafting)
 * Payton Macias (Idea Drafting)
 */


/* including needed modules and h files*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "pokerStruct.h"


/* Function prototypes*/

void printPlayerCard(hand player);
void printTableCard(hand player, int round);
void valueToString(Card *c);
void getCardValue(hand* p, hand* a);
void getCardSuit(Card *c);
void straight(int* rankCount);
void flush(int* suitCount);
void checkValue(Card *hand, int* rankCount, int* suitCount);
void clearBuffer();
void bettingNumbers(int round, handRank pRank, handRank aiRank);
int suitToIndex(const char *suit);
int whoWon(handRank pRank, handRank aRank);
void playGame();
handRank rankHand(Card* hand);



/*
 * Function: main
 * Purpose: The game will be runned
 * Args: None
 * Returns: EXIT_SUCCESS;
 */

int main () {

    srand(time(NULL));    

    int option = 0;

    printf("What would you like to do? (1: Rules, 2: Play Game, 3: Quit): ");
    scanf("%d", &option);

    while (option != 3) {

        printf("\n");

        switch (option) {
    
        case 1:
            printf("Welcome to Poker! This follows texas hold em rules.\n");
            printf("If you dont like your hand, you can fold and skip to the next game! However you will lose all the money you bet for the current game.\n");
            printf("There are 8 total hands to win this game as follows (highest to lowest): \n");
            printf("Straight Flush: (5 cards in a row of the same suit)\nFour of A Kind: (Four cards of the same number such as four 4's\n");
            printf("Flush: (5 cards of the same suit)\nStraight: (5 cards in a row)\nThree of A Kind: (Three cards of the same value)\n");
            printf("Two Pair: (Two pairs of the same numbered cards such as two 2s and two 4s)\nOne Pair: (One pair of cards such as two 2s)\nHigh Card: (Highest valued card A-> HIGHEST 2-> LOWEST)\n\n");
            break;
        case 2:
            playGame();
            break;
        case 3:
            return EXIT_SUCCESS;
            break;
        default: 
            break;
    
        }    

    printf("What would you like to do? (1: Rules, 2: Play Game, 3: Quit): ");
    scanf("%d", &option);
    
    }

    return EXIT_SUCCESS;
    
}

/*
 * Function: printCard
 * Purpose: Call conversion function then print cards
 * Args: Card num1 (1st card variable), Card num2 (2nd card variable)
 * Returns: None
 */

void printPlayerCard(hand player) {

    char *s1;
    char *s2;
    char *sym1;
    char *sym2;
    int row = 0;
    int i = 0;

    valueToString(&player.c1);
    valueToString(&player.c2);

    s1 = player.c1.stringValue;
    s2 = player.c2.stringValue;
    sym1 = player.c1.suitSymbol;
    sym2 = player.c2.suitSymbol;
    
    char* pSym[2] = {sym1, sym2};
    char* pHand[2] = {s1, s2};

    
    /*Uses for loops to print a player card visual*/ 

    for (i = 0; i < 2; i++) {
         printf(" --------     ");
    }
   
    printf("\n");

    
    for (i = 0; i < 2; i++) {
        if(strcmp(pHand[i], "10") == 0) {
            printf("|%s%s     |    ", pHand[i], pSym[i]);
        }
        else {
            printf("|%s%s      |    ", pHand[i], pSym[i]);
        }
    }

    printf("\n");


    for (row = 0; row < 3; row++) {
        for(i = 0; i < 2; i++) {
             printf("|        |    ");
        }
        printf("\n");
    }

    
    for (i = 0; i < 2; i++) {
        if(strcmp(pHand[i], "10") == 0) {
            printf("|     %s%s|    ", pSym[i], pHand[i]);
        }
        else {
            printf("|      %s%s|    ", pSym[i], pHand[i]);
        }
    }
    
    printf("\n");
    
    
    for (i = 0; i < 2; i++) {
         printf(" --------     ");
    }
   
    printf("\n");

}

/*
 * Function: printTableCard
 * Purpose: This will print the cards on the table (these are the cards that both hands use)
 * Args: hand player and round
 * Returns: None
 */

void printTableCard(hand player, int round) {

    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    
    char *sym1;
    char *sym2;
    char *sym3;
    char *sym4;
    char *sym5;

    int count = 0;
    int i = 0;
    int row = 0;

    /*Converts the cards integer value to a string for dynamic visual printing*/

    valueToString(&player.t1);
    valueToString(&player.t2);
    valueToString(&player.t3);
    valueToString(&player.t4);
    valueToString(&player.t5);
  

    t1 = player.t1.stringValue;
    t2 = player.t2.stringValue;
    t3 = player.t3.stringValue;
    t4 = player.t4.stringValue;
    t5 = player.t5.stringValue;

    sym1 = player.t1.suitSymbol;
    sym2 = player.t2.suitSymbol;
    sym3 = player.t3.suitSymbol;
    sym4 = player.t4.suitSymbol;
    sym5 = player.t5.suitSymbol;

    char* tSym[5] = {sym1, sym2, sym3, sym4, sym5};
    char* tHand[5] = {t1, t2, t3, t4, t5};


    /*Tells the code how many cards to print depending on the round*/    

    if (round == 1) {
        count = 3;
    }
    else if (round == 2) {
        count = 4;
    }   
    else {
        count = 5;
    }
    
    

    for (i = 0; i < count; i++) {
         printf(" --------     ");
    }
   
    printf("\n");

    
    for (i = 0; i < count; i++) {
        if(strcmp(tHand[i], "10") == 0) {
            printf("|%s%s     |    ", tHand[i], tSym[i]);
        }
        else {
            printf("|%s%s      |    ", tHand[i], tSym[i]);
        }
    }

    printf("\n");


    for (row = 0; row < 3; row++) {
        for(i = 0; i < count; i++) {
             printf("|        |    ");
        }
        printf("\n");
    }

    
    for (i = 0; i < count; i++) {
        if(strcmp(tHand[i], "10") == 0) {
            printf("|     %s%s|    ", tSym[i], tHand[i]);
        }
        else {
            printf("|      %s%s|    ", tSym[i], tHand[i]);
        }
    }
    
    printf("\n");
    
    
    for (i = 0; i < count; i++) {
         printf(" --------     ");
    }
   
    printf("\n");
            

}

/*
 * Function: valueToString
 * Purpose: It will assign an int value to a string value and make it fall under the card category to make printing cards easy and dynamic
 * Args: Card *c
 * Returns: None
 */ 

void valueToString(Card *c) {

    if (c->value >= 2 && c->value <= 10) {
        sprintf(c->stringValue, "%d", c->value);
    }
    else {
        switch (c->value) {
            case 11: 
                sprintf(c -> stringValue, "J");
                break;
            case 12: 
                sprintf(c -> stringValue, "Q");
                break;
            case 13: 
                sprintf(c -> stringValue, "K");
                break;
            case 14: 
                sprintf(c -> stringValue, "A");
                break;
        }
    }


}

/*
 * Function: getCardSuit
 * Purpose: This function uses a random number generator to generate a number, then depending on that value assigns the card a suit
 * Args: Card *c
 * Returns: None
 */

void getCardSuit(Card* c) {
    int suit = 0;
    int min = 1;
    int max = 3;
    int range = 0;
    
    range = max - min + 1;

    suit = rand() % range + min;
    
    switch(suit) {
        case 0: 
            strcpy(c->suitSymbol, "♠");
            strcpy(c->suit, "Spades");
            break;
        case 1:
            strcpy(c->suitSymbol, "♥");
            strcpy(c->suit, "Hearts"); 
             break;
        case 2:
            strcpy(c->suitSymbol, "♦");
            strcpy(c->suit, "Diamonds");
            break;
        case 3:
            strcpy(c->suitSymbol, "♣");
            strcpy(c->suit, "Clubs");
            break; 
    }
    
}

/*
 * Function: getCardValue
 * Purpose: This gets a hand and assigns each card in the hand (helps with comparing later)
 * Args: hand* p and hand* a
 * Returns: None
 */


void getCardValue(hand* p, hand* a) {
        
    int min = 2;
    int max = 14;
    int range = 0;
    
    range = max - min + 1;

    /*Assigns values to the player, ai, and table cards*/           

    p->c1.value = rand() % range + min;
    p->c2.value = rand() % range + min;
    
    a->c1.value = rand() % range + min;
    a->c2.value = rand() % range + min;
    
    p->t1.value = rand() % range + min;
    p->t2.value = rand() % range + min;
    p->t3.value = rand() % range + min;
    p->t4.value = rand() % range + min;
    p->t5.value = rand() % range + min;

    /*Assigns a suit to the player, ai, and table cards*/

    getCardSuit(&p->c1);
    getCardSuit(&p->c2);

    getCardSuit(&a->c1);
    getCardSuit(&a->c2);

    getCardSuit(&p->t1);
    getCardSuit(&p->t2);
    getCardSuit(&p->t3);
    getCardSuit(&p->t4);
    getCardSuit(&p->t5);


    /*Copies the table card from the player to the ai to correctly compare hands*/

    a->t1 = p->t1;
    a->t2 = p->t2;
    a->t3 = p->t3;
    a->t4 = p->t4;
    a->t5 = p->t5;
   
}


/*
* Function: clearBuffer
* Purpose: Checks for bad input from the user
* Args: badInput, while loop
* Returns: None
*/

void clearBuffer() {
    char badInput = 'a';
    while (scanf("%c", &badInput) == 1 && badInput != '\n') {
    }
}

/*
 * Function: suitToIndex
 * Purpose: It will check and place the cards into a suit
 * Args: const char *suit
 * Returns: -1 if they don't follow under the other suit loops
 */


int suitToIndex(const char *suit) {
    if (strcmp(suit, "Spades") == 0) {
        return 0; 
    }
    if (strcmp(suit, "Hearts") == 0) {
        return 1;
    }
    if (strcmp(suit, "Diamonds") == 0) { 
        return 2;
    } 
    if (strcmp(suit, "Clubs") == 0) {
        return 3;
    }
    return -1; 
}

/*
 * Function: checkValue
 * Purpose: This will check the values of all the cards in play using arrays to help with assigning ranks later
 * Args: Card *allCards, int* rankCount, and int* suitCount
 * Returns: None
 */

void checkValue(Card *hand, int* rankCount, int* suitCount) {
    
    int i = 0;
    
    /*Takes a hand and arrays and checks an index value matching the card to be used for hand rankings*/    

    for(i = 0; i < 7; i++) {
        rankCount[i] = 0;
    }

    for (i = 0; i < 4; i++) {
        suitCount[i] = 0;
    }

    for (i = 0; i < 7; i++) {
        rankCount[ hand[i].value ]++;
        suitCount[ suitToIndex(hand[i].suit) ]++;
    }

}
/*
 * Function: straightF
 * Purpose: This function checks for straight flush, then straight, then flush (this takes care of ranking 3 hand values) 
 * Args: Card* allCards, int* rankCount, and int* suitCoun
 * Returns: Results
 */

handRank straightF(Card* hand, int* rankCount, int* suitCount) {

    int i = 0;
    int a = 0;
    int b = 0;
    int r = 0;
    int temp = 0;
    int flushSuit = 0;
    int straightHigh = 0;
    int count = 0;
    int flushCards[7];
    int suitedRanks[15];
    memset(flushCards, 0, sizeof(flushCards));
    memset(suitedRanks, 0, sizeof(suitedRanks)); 
    handRank result;

    /*Checks for possibilities matching straights and flushes, then if both are met, it assigns the straight flush value to the hand*/

    for (i = 0; i < 4; i++) {
        if (suitCount[i] >= 5) {
            flushSuit = i;
        }
    }

    for (i = 0; i < 7; i++) { 
        if (suitToIndex(hand[i].suit) == flushSuit) {
            flushCards[count] = hand[i].value;
            count++;
        }
    }

    for (i = 0; i < count; i++) {
        suitedRanks[ flushCards[i] ]++;
    }

    /*Sorts high valued cards to the front in cases of tiebreakers and straight detections(Help from Co-Pilot)*/
    for (a = 0; a < count - 1; a++) {
        for (b = a + 1; b < count; b++) {
            if (flushCards[b] > flushCards[a]) {
                temp = flushCards[a];
                flushCards[a] = flushCards[b];
                flushCards[b] = temp;
            }
        }
    }

    /*Assigns the cards into the tiebreak array for breaking ties later if needed*/

    for (i = 0; i < 5; i++) {
        result.tiebreak[i] = flushCards[i];
    }

    
    for (r = 14; r >= 6; r--) {
        if (suitedRanks[r] > 0 && suitedRanks[r-1] > 0 && suitedRanks[r-2] > 0 && suitedRanks[r-3] > 0 && suitedRanks[r-4] > 0) {
                 straightHigh = r;
        }
    }
            
    if (straightHigh > 0 && flushSuit > 0) {
        result.rank = STRAIGHT_FLUSH;
    }
    else if (straightHigh > 0) {
        result.rank = STRAIGHT;
    }
    else if (flushSuit > 0) {
        result.rank = FLUSH;
    }

        
    return result;
}

/*
 * Function: rankHand
 * Purpose: Main hand ranking function, check out nested arrays for suit and card value to determine the player and AI's hand
 * Args: Card* allCards
 * Returns: Results
 */


handRank rankHand(Card* hand) {

    int i = 0;
    int max = 0;
    int fH2 = 0;
    int fH3 = 0;
    int tripV = 0;
    int tP1 = 0;
    int tP = 0;
    int oP = 0;
    int rankCount[15];
    int suitCount[4];
    /*Sets the memory of the arrys to 0 for ensuring fresh cards are assigned*/
    memset(rankCount, 0, sizeof(rankCount));
    memset(suitCount, 0, sizeof(suitCount));
    handRank result;
   
    /*Checks for a value compared to your card, if you have a card matching the index value it will add one to the index value*/

    for (i = 0; i < 7; i++) {
        rankCount[ hand[i].value ]++;
        suitCount[ suitToIndex(hand[i].suit) ]++;
    }


    result = straightF(hand, rankCount, suitCount);
    

    /* The following MASSIVE if tree tests conditions for each hand rank then sets the correct value accordingly*/

    if (result.rank == STRAIGHT_FLUSH) {
        return result;
    }
    
    
    for (i = 0; i < 7; i++) {
        if (rankCount[i] >= 4) {
            result.rank = FOUR_OF_KIND;
            result.tiebreak[0] = i;
            return result;
        }
    }

    for (i = 0; i < 7; i++) {
        if (rankCount[i] >= 3) {
            fH3++;
            tripV = i;
        }
        else if (rankCount[i] >= 2) {
            fH2++;
        }
    }

    if (fH3 >= 1 && fH2 >= 1) {
        result.rank = FULL_HOUSE;
        result.tiebreak[0] = tripV;
        return result;
    }

    if(result.rank == FLUSH) {
        return result;
    }

    if (result.rank == STRAIGHT) {
        return result;
    }

    for (i = 0; i < 7; i++) {
        if (rankCount[i] >= 3) {
            result.rank = THREE_OF_KIND;
            result.tiebreak[0] = i;
            return result;
        }
    }

    for (i = 0; i < 15; i++) {
        if (rankCount[i] >= 2) {
            tP++;
            result.tiebreak[0] = i;
        }
    }  
    

    if(tP1 > 0) {
        result.rank = TWO_PAIR;
        return result;
    }

    for (i = 0; i < 7; i++) {
        if (rankCount[i] >= 2) {
            oP++;
            result.tiebreak[0] = i;
        }
    }  

    if (oP > 1) {
        result.rank = ONE_PAIR;
        return result;
    }

    for (i = 0; i < 7; i++) {
        if (rankCount[i] > max) {
            max = rankCount[i];
            result.rank = HIGH_CARD;
            result.tiebreak[0] = max;
        }
    }  
    
    return result;
}


/*
* Function: bettingNumbers
* Purpose: Asks the user to enter an amount they want to bet and uses loops to determine winning values and assigning
* Args: round, handRank pRank, handRank aiRank
* Returns: None
*/


void bettingNumbers(int round, handRank pRank, handRank aiRank) {
   
    static int userMoney = 250;
    static int aiMoney = 250;
    static int totalBetU = 0;
    static int totalBetA = 0;
    static int pot = 0;
    static int fold = 0;
    static int foldFlag = 0;

    int min = 0;
    int max = 0;
    int result = 0;
    int aiMin = 1;
    int aiMax = 4;
    int willBet = 0;
    int minBet = 0;
    int range = 0;
    int range2 = 0;
    int userBet = 0;
    int aiBet = 0;
    
    range = aiMax - aiMin + 1;
    willBet = rand() % range + min;

    /*Implemented folding system*/

    if (round == 1) {
        foldFlag = 0;
        fold = 0;
    }

    if (foldFlag == 1) {
        return;
    }

    printf("Would you like to fold? (1 = yes, 0 = no): ");
    scanf("%d", &fold);
    clearBuffer();

    if (fold == 1) {
        foldFlag = 1;
        pot += totalBetU + totalBetA;
        aiMoney += pot;

        totalBetU = 0;
        totalBetA = 0;
        pot = 0;
        
       

        printf("You folded, the AI wins the pot\n\n");
        return;
    }



    
    /*Uses random number generations to determine if the "ai" will bet, if it does, uses another random range to determie "ai" bet ammount*/

    if (willBet > 2) {
        if(round == 1){
            min = 10;
            max = 30;
            printf("Minimum Bet: $10\n");
            range2 = max - min + 1;
            aiBet = rand() % range2 + min; 
        }
        else if (round == 2) {
            min = 10; 
            max = 100;
            range2 = aiMax - aiMin + 1;
            aiBet = rand() % range2 + min;
            
        }
        else {
            min = 10;
            max = aiMoney;
            range2 = aiMax - aiMin + 1;
            aiBet = rand() % range2 + min; 
        }
    }

    totalBetA += aiBet;
    aiMoney -= aiBet;

    if (round ==1) {
        minBet = 10;
    }
    else {
        minBet = totalBetA - totalBetU;
        if (minBet < 0) {
            minBet = 0;
            }
    }
             

    printf("Minimum Bet: $%d\n", minBet);
    printf("Maximum Bet: $%d\n", userMoney);
    printf("Computer bet: %d\n", aiBet);
    printf("User bet: ");

    while (scanf("%d", &userBet) == 0 || userBet > userMoney || userBet < minBet) {
        clearBuffer();
        printf("Invalid bet! Enter a valid bet.\n");
        printf("User bet: ");
    }

    totalBetU += userBet;
    userMoney -= userBet;

    printf("\n\n");

    FILE* fp = NULL;

    

    /*allocates money from bets into the pot, then allocates the money to the winner and resets the pot to 0*/


    if (round == 3) {
        pot += totalBetU + totalBetA;
        result = whoWon(pRank, aiRank);

        if (result == 1) {
            userMoney += pot;
        }
        else if (result == -1) {
            aiMoney += pot;
        }
        else { 
            userMoney += pot/2;
            aiMoney += pot/2;
        }

        totalBetU = 0;
        totalBetA = 0;
        pot = 0;
    }
        

    


    fp = fopen("moneyLogs.txt", "w");

    fprintf(fp, "Computer winnings: %d\n", aiMoney);
    fprintf(fp, "User winnings: %d\n", userMoney);
    
    fclose(fp);

    aiBet = 0;
}

/*
 * Function: playGame
 * Purpose: It will ask the user if they want to play and calls all the helper functions necessary for the game to run
 * Args: None
 * Returns: None
 */ 

void playGame() {
    
    char play = 'y';

    while (play == 'y') {
        int i = 0;
        int result = 0;
        hand player;
        hand ai;
    
        getCardValue(&player, &ai);

        Card playerCards[7] = {player.c1, player.c2, player.t1, player.t2, player.t3, player.t4, player.t5};
        Card aiCards[7] = {ai.c1, ai.c2, ai.t1, ai.t2, ai.t3, ai.t4, ai.t5};  

      
        handRank pRank = rankHand(playerCards);
        handRank aiRank = rankHand(aiCards);

          

        for(i = 1; i < 4; i++) {

            printf("-----TABLE CARDS-----\n");
            printTableCard(player, i);        

            printf("\n");
            printf("\n");

            printf("-----PLAYER CARDS-----\n");
            printPlayerCard(player);

            printf("\n");
            printf("\n");    

            bettingNumbers(i, pRank, aiRank);

        }


         result = whoWon(pRank, aiRank);

        if (result == 1) {
             printf("YOU WIN!\n");
        }
        else if (result == -1) {
             printf("YOU LOSE!\n");
        }
        else { 
            printf("TIE\n");
        } 

        printf("THE AI's Cards were %d%s and %d%s\n", ai.c1.value, ai.c1.suitSymbol, ai.c2.value, ai.c2.suitSymbol);

        printf("Would you like to play again? (y/n)\n");
        scanf(" %c", &play);
    
    
    }
}

/*
 * Function: whoWon
 * Purpose: Check which hand wins depending on which value was assigned from previous functions
 * Args: handRank p, handRank a
 * Returns: None
 */ 

int whoWon(handRank p, handRank a) {
    
    int i = 0;
    
    if (p.rank > a.rank) {
        return 1;
    }
    if (p.rank < a.rank) {
        return -1;
    }

    for (i = 0; i < 5; i++) {
        if (p.tiebreak[i] > a.tiebreak[i]) {
            return 1;
        }
        if (p.tiebreak[i] < a.tiebreak[i]) {
            return -1;
        }
    }

    return 0;
}

