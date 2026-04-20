/*Authors: Devin Barrow, Briseis Ramirez, Antoinette Hults*/

#ifndef POKER_H
#define POKER_H

typedef struct Card {
    int value;
    char stringValue[10];
    char suitSymbol[5];
    char suit[30];
} Card;

typedef enum handValue {
    HIGH_CARD = 0,
    ONE_PAIR = 1,
    TWO_PAIR = 2,
    THREE_OF_KIND = 3,
    STRAIGHT = 4,
    FLUSH = 5,
    FULL_HOUSE = 6,
    FOUR_OF_KIND = 7,
    STRAIGHT_FLUSH = 8    
} handValue;

typedef struct hand {
    Card c1;
    Card c2;
    Card t1;
    Card t2;
    Card t3;
    Card t4;
    Card t5;
} hand;

typedef struct handRank {
    handValue rank;
    int hRank;
    int tiebreak[5];
} handRank;

#endif
