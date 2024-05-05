#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

/*
THE PROJECT CODE IS IN LINES 171-183
This is Texas Hold'em. I won't cover basic game rules, so get familar somewhere else if you do not know how to play.
The menu is made up of various functions, however the game was easiest to process global data and make linearly. This means
that once a round is started, it remains in BeginGame() until you want to exit. This is mainly due to the shuffle system
since giving and taking integer arrays is quite tedius and above my knowledge. The shuffle system is super neat. It
uses a time seeded random number, indexes a full 52 deck of cards, pulls one at random, and inserts it into the next
space in a different array of 52. This allows me to simply pull the first 9 cards and have them be random, but also 
non-repetative. Once your hand is made, it puts a "picture" of it in the terminal, as well as the tables. The bot isn't
very good. In fact you could probably figure out its hand by what is does if you played enough or went through the code.
The winning decider function is the most comprehensive of the whole game and requires knowledge of the game to understand.
OUTDATED^^
The game and cards now runs through round functions 1-4, and through card structures that contain each card's english name
, integer number, suit number, and suit english name. This makes passing these values very easy.
Order of Gameplay functions needed.

    

*/

int guap = 10000;


struct oneCard { // just learned about structures and now am rewriting entire code

    int cardNum;
    int suit;
    char suitWord[12];
    char cardNumWord[10];

};


void WipeScreen() { // Since the game is in the terminal, clearing previous text makes the game easier to understand. This function simply throws a bunch of newlines.
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    return;
}

struct oneCard CardSetter(int cardNum) {
    struct oneCard card;
    int c;
    if (cardNum < 14) {
        card.suit = 1;
        strcpy(card.suitWord, "Clubs");
    }
    else if (cardNum < 27) {
        card.suit = 2;
        strcpy(card.suitWord, "Spades");
    }
    else if (cardNum < 40) {
        card.suit = 3;
        strcpy(card.suitWord, "Hearts");
    }
    else {
        card.suit = 4;
        strcpy(card.suitWord, "Diamonds");
    }
    c = cardNum % 13;


    switch (c) {
        case 0 :
            card.cardNum = 13;
            strcpy(card.cardNumWord, "King");
            break;
        case 1 :
            card.cardNum = 14;
            strcpy(card.cardNumWord, "Ace");
            break;
        case 2 :
            card.cardNum = 2;
            strcpy(card.cardNumWord, "2");
            break;
        case 3 :
            card.cardNum = 3;
            strcpy(card.cardNumWord, "3");
            break;
        case 4 :
            card.cardNum = 4;
            strcpy(card.cardNumWord, "4");
            break;
        case 5 :
            card.cardNum = 5;
            strcpy(card.cardNumWord, "5");
            break;
        case 6 :
            card.cardNum = 6;
            strcpy(card.cardNumWord, "6");
            break;
        case 7 :
            card.cardNum = 7;
            strcpy(card.cardNumWord, "7");
            break;
        case 8 :
            card.cardNum = 8;
            strcpy(card.cardNumWord, "8");
            break;
        case 9 :
            card.cardNum = 9;
            strcpy(card.cardNumWord, "9");
            break;
        case 10 :
            card.cardNum = 10;
            strcpy(card.cardNumWord, "10");
            break;
        case 11 :
            card.cardNum = 11;
            strcpy(card.cardNumWord, "Jack");
            break;
        case 12 :
            card.cardNum = 12;
            strcpy(card.cardNumWord, "Queen");
            break;




    }
    return card;

}

void CardPicture(struct oneCard card){
    printf("%s of %s", card.cardNumWord, card.suitWord);
    printf("\n");
    strcpy(card.cardNumWord, "");
    strcpy(card.suitWord, "");
    return;
}

void Restart() {
    int input;
    printf("Play Again?\n1 - Yes\n2 - No\n");
    scanf("%d", &input);
    if (input == 1) {
        BeginGame();
    }
    else {
        StartScreen();
    }
}

void BeginGame() {
    int deck[52];
    int fakeDeck[52];
    int i;
    int c;

    struct oneCard user1;
    struct oneCard user2;
    struct oneCard bot1;
    struct oneCard bot2;
    struct oneCard table1;
    struct oneCard table2;
    struct oneCard table3;
    struct oneCard table4;
    struct oneCard table5;

    int bet;
    int wl;


    WipeScreen();
    printf("Dealing...\n");
    sleep(2);
    for (i = 0; i < 52; ++i) { //creates full array of 1 - 52 for both deck and fakeDeck.
        deck[i] = i+1;
        fakeDeck[i] = i+1;
    }

    for (i = 0; i < 52; ++i) {
        c = rand() % 52; //some random int is pulled between 0-51
        while (fakeDeck[c]==0) { //the random int is used to index one card at random, if the card has already been used,
            c = rand() % 52;     // it will have already been set to zero in the fakeDeck array, and is skipped until a new card is pulled.
        }
        deck[i] = fakeDeck[c]; //set the first, second, third, etc... deck[key] to the randomly selected fakeDeck[]
        fakeDeck[c]=0; // set the used card to zero so no cards repeat.
    }

    user1 = CardSetter(deck[0]);
    bot1 = CardSetter(deck[1]);
    user2 = CardSetter(deck[2]);
    bot2 = CardSetter(deck[3]);
    
    bet = RoundOne(user1,user2,bot1,bot2);
    if (bet > 0) {
        guap -=bet;
    }
    if (bet < 0) {
        WipeScreen();
        printf("You folded!\n");
        Restart();
    }
    // Now that round 1 is over, rounds 2-4 work the exact same as eachother, so they can be repeated
    table1 = CardSetter(deck[5]);
    table2 = CardSetter(deck[7]);
    table3 = CardSetter(deck[9]);
    table4.cardNum = 0;
    table5.cardNum = 0;
    bet = RoundTwo(user1,user2,bot1,bot2,table1,table2,table3,table4,table5);
    if (bet > 0) {
        guap -=bet;
    }
    if (bet < 0) {
        WipeScreen();
        printf("You folded!\n");
        Restart();
    }

    table4 = CardSetter(deck[11]);
    bet = RoundTwo(user1,user2,bot1,bot2,table1,table2,table3,table4,table5);
    if (bet > 0) {
        guap -=bet;
    }
    if (bet < 0) {
        WipeScreen();
        printf("You folded!\n");
        Restart();
    }

    table5 = CardSetter(deck[13]);
    bet = RoundTwo(user1,user2,bot1,bot2,table1,table2,table3,table4,table5);
    if (bet > 0) {
        guap -=bet;
    }
    if (bet < 0) {
        WipeScreen();
        printf("You folded!\n");
        Restart();
    }
}



int RoundOne(struct oneCard user1, struct oneCard user2, struct oneCard bot1, struct oneCard bot2) {
    int option;
    int botBet;
    int bet = -1;
    int round;
    round = 1;
    WipeScreen();
    printf("The table:\n\n-----\n\n\n");
    printf("Your opponent:\n\n----------\n----------\n\n\n\n\n");
    printf("Your cards:\n\n");
    CardPicture(user1);
    CardPicture(user2);
    printf("\n\n\nWould you like to:\n1 - Anti in ($50)\n2 - Raise the Anti\n3 - Fold\n");
    scanf("%d", &option);
    if (option == 1) {
        return 50;
    }
    else if (option == 2) {
        while(1) {
            WipeScreen();
            printf("Your cards:\n");
            CardPicture(user1);
            CardPicture(user2);
            printf("\nHow much would much would you like to bet (Must be > $50) ? Money - %d\n", guap);
            scanf("%d", &bet);
            if (bet > 50 & (bet < guap)) {
                return bet;
            }
            
            else {
                WipeScreen();
                printf("Enter a cash value without a $, (ex. 5000). Make sure it's over $50 since that is the anti...\n\n");
            }
        }
    }
    else if (option == 3) {
        return -1;
    }

}

int RoundTwo(struct oneCard user1, struct oneCard user2, struct oneCard bot1, struct oneCard bot2, struct oneCard table1, struct oneCard table2,struct oneCard table3, struct oneCard table4,struct oneCard table5) {
    int user;
    int bet = -1;
    int round;
    WipeScreen();
    printf("The table:\n\n");
    CardPicture(table1);
    CardPicture(table2);
    CardPicture(table3);
    round = 2;
    if (table4.cardNum != 0) {
        CardPicture(table4);
        round = 3;
    }
    if (table5.cardNum != 0) {
        CardPicture(table5);
        round = 4;
    }
    printf("\n\nYour opponent:\n\n----------\n----------\n\n\n\n\n");
    printf("Your cards:\n\n");
    CardPicture(user1);
    CardPicture(user2);


    printf("\n\n\nWould you like to:\n1 - Raise\n2 - Check\n3 - Fold\n");
    scanf("%d", &user);
    if (user == 1) {
        while(1) {
            WipeScreen();
            printf("The table:\n\n");
            CardPicture(table1);
            CardPicture(table2);
            CardPicture(table3);
            if (table4.cardNum != 0) {
                CardPicture(table4);
            }
            if (table5.cardNum != 0) {
                CardPicture(table5);
            }
            printf("\n\n\nYour cards:\n\n");
            CardPicture(user1);
            CardPicture(user2);
            printf("\nHow much would much would you like to raise (Must be > $50) ? Money - %d\n", guap);
            scanf("%d", &bet);

            if (bet > guap) {
                continue;
            }
            else {
                return bet;
            }
        }
    }
    else if (user == 2) {
        return 0;
    }
    else if (user == 3) {
        return -1;
    }

}
/*
The checker will be super obscure, probably didn't have to be if I had created some card struct with a suit and number.
*/

/*
I want to make it where the table cards are burned and turned only when they are dealt so it is verifiable that the bot doesn't have 
that information. (Technically they are in deck[] indexed at 5, 7, 9, 11, and 13 if every other is burned) however these values are random and I
don't want to index these until the they are put on the table for my own satisfaction. I can't write one function with all the cards
to print after every round because of this. C only lets you call as many inputs as are present


*/


/*
1. Royal Flush
2. Straight Flush
3. Four of a Kind
4. Full House
5. Flush
6. Straight
7. Three of a Kind
8. Two Pair
9. One Pair
10. High card
*/




int AI(struct oneCard bot1, struct oneCard bot2, struct oneCard table1, struct oneCard table2,struct oneCard table3, struct oneCard table4,struct oneCard table5, int round, int bet) {
    /*int straight;
    int ofAKind;
    int flush;
    int fullHouse;
    int betOdds;
    int 
    
    if (bet < 0) {

    }
    
    
    
    if (round == 1) {

    }

    if (round == 2) {

    }

    if (round == 3) {

    }

    if (round == 4) {
        
    }
    */
   return rand() % 5000;
}   


int Credits() {
    return 0;
}

int ExitGame() { // this function double checks the user wants to exit since their money will be reset.
    int input;
    WipeScreen();
    printf("Are you sure you want to exit, your money will be reset to $10,000?\n0 - Yes\n1 - No\n\n");
    scanf("%d", &input);
    return input;
}

int StartScreen() { //this function is considered the main menu, integer input control the interface and are check by if and else ifs.
    int optionNum;
    int exitCode;

    while (1) { //while keeps the menu up when the game, credits, or exit prompts are exited.
        WipeScreen(); 
        printf("Welcome to Texas Hold'em! The game isn't actually functional yet, you can play through \nthe game and it will deal random cards without replacment.\nHowever, the opponent isn't functional and the game cannot tell who wins yet.\nTHE PROJECT CODE IS LOCATED IN LINES 171-182.\n\n1 - Start Game!\n2 - Credits\n3 - Exit\n\nEnter the number of what you would like to choose and press enter: ");
        scanf("%d", &optionNum);

        if (optionNum == 1) { //checks for input selection
            BeginGame();
        }
        else if (optionNum == 2) {
            Credits();
        }
        else if (optionNum == 3) {
            exitCode = ExitGame();
            if (exitCode == 0) {
                WipeScreen();
                printf("Bye bye!\n");
                exit(0);
            }
            else { //if anything but a 1 or a 2 is inputted, it considers it a no in case the user mistypes
                continue;
            }
        }
        else { //if anything but a 1,2, or 3 is inputted, we reiterate after the message below because of the while(1) {}
            printf("Please select one of the options!\nEnter the number of what you would like to choose and press enter: ");
            scanf("%d",&optionNum);
        }
    }
}

int main() {
    srand(time(NULL)); // Initializes rand() with seed generatated at time of launch
    StartScreen(); // Begins the program
    return 0;
}

