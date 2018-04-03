/**********************************************************
*AUTHOR    	     : Andrew Moss
*Assignment #1       : Blackjack
*CLASS     	     : CS 003A
*SECTION   	     : MW: 1:00p - 2:25p
*                    : TR: 1:00p - 3:05p
*Due Date  	     : 2/27/18
**********************************************************/
#include <iostream>
#include <cstdlib>
#include <string>
/**********************************************************
*
* Blackjack
* ________________________________________________________
* Program Description: This program is a single-player version of the casino
*   card game Blackjack, also known as 21.
*
* ________________________________________________________
* OUTPUT:
*   amount: Calculated double based on pay rate and hours worked
*
*
**********************************************************/
using namespace std;

//Function prototype
/********************************************************************
*  draw_card
*      Uses rand() to draw a card then returns the numerical
*	   value and card name
*********************************************************************/
int draw_card(string &card,               //IN - card name
              int drawer_points);         //IN - drawer's total points

/********************************************************************
*  getSuit
*      This function takes integer value and converts to corresponding card
*
*********************************************************************/
string getSuit(int suitValue);            //IN - numeric value representing
                                          //the suit

/********************************************************************
*  getRank
*      This function takes integer value and converts to corresponding card
*
*********************************************************************/
string getRank(int suitRank);            //IN - numeric value representing
                                         //the card rank

/********************************************************************
*  moneyTracker
*      This function tracks the amount of money for player
*
*********************************************************************/
void moneyTracker(int &amount,           //IN -
                  int bet,               //IN -
                  int &playerTotal,      //IN -
                  int &dealerTotal);     //IN -

/********************************************************************
*  endGame
*      This function ends the game based on one of two outcomes
*
*********************************************************************/
void endGame(int &amount);               //IN -

/********************************************************************
*  initTurn
*      This function ends the game based on one of two outcomes
*
*********************************************************************/
void initTurn(string &card,              //IN -
              int &currTotalTracker);    //IN -

/********************************************************************
*  endTurn
*      This function ends the turn on one of two outcomes
*
*********************************************************************/
void endTurn(int &currTotalTracker,      //IN -
             int &amount,                //IN -
             int bet);                   //IN -


int main()
{

    int money = 100;                  //CALC OUT: integer variable tracking
                                      //player's money
    int currTotalPlayer = 0;          //CALC OUT: integer variable that keeps
                                      //track of the current total for the player
    int currTotalDealer = 0;          //CALC OUT: integer variable that keeps
                                      //track of the current total for the dealer
    string drawnCard;                 //CALC OUT: string variable representing the
                                      //card drawn
    int bet = 0;                      //INPUT: integer variable representing
                                      //the bet
    char hit;                         //INPUT: char variable for if player
                                      //wants to hit or stay
    char play;                        //INPUT: char variable for if player
                                      //wants to contineu playing

    //see random number generator
    srand(333);


    do
    {
        //Player's turn

        //OUTPUT: Displays player's money and asks player to enter bet
        cout << "You have $" << money << ". Enter bet: " << endl;

        //INPUT: Player enters a bet
        cin >> bet;

        cout << "Your cards are: " << endl;

        //initTurn - function initiates the turn and draws 2 cards
        initTurn(drawnCard, currTotalPlayer);

        //OUTPUT: Display total value of player's hand
        cout << "Your total is " << currTotalPlayer << ". ";

        //The player can continue to draw cards while their total is less than 21.
        while(currTotalPlayer < 21)
        {

            //INPUT: Asks if player wants to draw another card
            cout << "Do you want another card (y/n)? " << endl;
            cin >> hit;

            if(hit == 'y')
            {
                //draw_card - function draws a play card at random
                currTotalPlayer = draw_card(drawnCard, currTotalPlayer);

                //OUTPUT: Drawn card and the total value of player's hand
                cout << "You draw a: " << endl << "  " << drawnCard << endl
                     << "Your total is " << currTotalPlayer << ". ";

                //endTurn - function evaluates if player's turn should continue
                endTurn(currTotalPlayer, money, bet);

            }

            else if(hit == 'n')
            {
                //endTurn - function evaluates if player's turn should continue
                endTurn(currTotalPlayer, money, bet);
                break;
            }
        }

        //Dealer turn

        if(currTotalPlayer <= 21)
        {
            //OUTPUT: Dealer's cards
            cout << endl << endl << "The dealer's cards are: " << endl;

            //initTurn - function initiates the turn and draws 2 cards
            initTurn(drawnCard, currTotalDealer);

            //OUTPUT: Total value of dealer's hand
            cout << "The dealer's total is " << currTotalDealer << "." << endl;

            //PROCESSING: The player can continue to draw cards while their
            //total is less than 21
            while(currTotalPlayer <= 21 && currTotalDealer < 21)
            {

                //PROCESSING: The dealer continues to draw cards if their total
                //is less than or equal to 16
                if(currTotalDealer < 17)
                {
                    //draw_card - function draws a play card at random
                    currTotalDealer = draw_card(drawnCard, currTotalDealer);

                    //OUTPUT: Drawn card and the total value of dealer's hand
                    cout << "The dealer draws a card." << endl << "  " << drawnCard << endl
                         << "The dealer's total is " << currTotalDealer << ".";

                         //endTurn - function evaluates if player's turn should
                         //continue
                         endTurn(currTotalDealer, money, bet);
                }

                //PROCESSING: End turn if dealer draws total card value of 17
                //or more
                else if(currTotalDealer >= 17)
                {
                    //endTurn - function evaluates if player's turn should
                    //continue
                    endTurn(currTotalDealer, money, bet);
                    break;
                }
            }
        }

        //moneyTracker - function tracks the amount of money for player and
        //declares outcome of game
        moneyTracker(money, bet, currTotalPlayer, currTotalDealer);


        cout << "Play again? (y/n): " << endl;
        cin >> play;

        //reinitialize card values to 0
        currTotalPlayer = 0;
        currTotalDealer = 0;

    }while(play == 'y');

    return 0;
}

//Function definitions
/************************************************************
*  draw_card
* ___________________________________________________________
*  Simulates the drawing of a card. Passes by reference the
*    kind of card (value and suite in string value) as well
*    as returns the card's equivalent numerical value (to be
*    added to totals in main())
*  Also reads current drawer's points to determind value of
*    aces
* ___________________________________________________________
*  PRE-CONDITIONS:
*    &card : passes card info
*    drawer_points : reads current drawer's points to
*      determin value of ace
*
*  POST-CONDITIONS:
*    passes card info by reference, returns card numerical
*      value
*************************************************************/
int draw_card (string &card,           //card info
               int drawer_points)      //current drawer's points
{
    int cardRank = (rand() % 13) + 1;  //CALC OUT: Integer variable representing
                                       //random card value
    int cardSuit = (rand() % 4);       //CALC OUT: Integer variable representing
                                       //random card suit value

    //getRank - function converts card rank value to name of card type/rank
    //getSuit - function converts card suit value to name of card suit
    card = getRank(cardRank) + " of " + getSuit(cardSuit);

    //PROCESSING: Evaluates card type and adds the appropriate card value
    if(card == "Ace of Clubs" || card == "Ace of Diamonds" ||
            card == "Ace of Hearts" || card == "Ace of Spades")
    {
        if(drawer_points > 10)
        {
            drawer_points += 1;
        }
        else if(drawer_points <= 10)
        {
            drawer_points += 11;
        }
    }
    else if(card == "Two of Clubs" || card == "Two of Diamonds" ||
            card == "Two of Hearts" || card == "Two of Spades")
    {
        drawer_points += 2;
    }
    else if(card == "Three of Clubs" || card == "Three of Diamonds" ||
            card == "Three of Hearts" || card == "Three of Spades")
    {
        drawer_points += 3;
    }
    else if(card == "Four of Clubs" || card == "Four of Diamonds" ||
            card == "Four of Hearts" || card == "Four of Spades")
    {
        drawer_points += 4;
    }
    else if(card == "Five of Clubs" || card == "Five of Diamonds" ||
            card == "Five of Hearts" || card == "Five of Spades")
    {
        drawer_points += 5;
    }
    else if(card == "Six of Clubs" || card == "Six of Diamonds" ||
            card == "Six of Hearts" || card == "Six of Spades")
    {
        drawer_points += 6;
    }
    else if(card == "Seven of Clubs" || card == "Seven of Diamonds" ||
            card == "Seven of Hearts" || card == "Seven of Spades")
    {
        drawer_points += 7;
    }
    else if(card == "Eight of Clubs" || card == "Eight of Diamonds" ||
            card == "Eight of Hearts" || card == "Eight of Spades")
    {
        drawer_points += 8;
    }
    else if(card == "Nine of Clubs" || card == "Nine of Diamonds" ||
            card == "Nine of Hearts" || card == "Nine of Spades")
    {
        drawer_points += 9;
    }
    else if(card == "Ten of Clubs" || card == "Ten of Diamonds" ||
            card == "Ten of Hearts" || card == "Ten of Spades" ||
            card == "Jack of Clubs" || card == "Jack of Diamonds" ||
            card == "Jack of Hearts" || card == "Jack of Spades" ||
            card == "Queen of Clubs" || card == "Queen of Diamonds" ||
            card == "Queen of Hearts" || card == "Queen of Spades" ||
            card == "King of Clubs" || card == "King of Diamonds" ||
            card == "King of Hearts" || card == "King of Spades")
    {
        drawer_points += 10;
    }

    return drawer_points;

}

/************************************************************
*  initTurn
* ___________________________________________________________
*  Simulates the drawing of a card. Passes by reference the
*    kind of card (value and suite in string value) as well
*    as returns the card's equivalent numerical value (to be
*    added to totals in main())
*  Also reads current drawer's points to determind value of
*    aces
* ___________________________________________________________
* PRE-CONDITIONS:
*   &card : passes card info
*   drawer_points : reads current drawer's points to
*     determin value of ace
*
* POST-CONDITIONS:
*   passes card info by reference, returns card numerical
*     value
*************************************************************/
void initTurn(string &card,           //card info
              int &currTotalTracker)  //total value of player's hand
{
    int cardNum = 0;                  //CALC OUT: Counter for while loop
    bool noCardsDrawn = true;         //CALC OUT: Boolean to evaluate while loop

    //PROCESSING: Draws two cards
    while(noCardsDrawn)
    {

        while(cardNum !=2)
        {

            //draw_card - function draws a play card at random
            currTotalTracker = draw_card(card, currTotalTracker);

            //OUTPUT: Card drawn
            cout << "  " << card << endl;
            cardNum++;
        }

        noCardsDrawn = false;
    }

}

/************************************************************
* getSuit
* _________________________________________________________
*   Converts integer value to corresponding card suit
* _________________________________________________________
* PRE-CONDITIONS
*   suitValue : integer variable representing the
*     corresponding suit for card.
*
* POST-CONDITIONS
*   Passes the integer value representing the suit of card.
*     Returns the card suit.
*
*************************************************************/
string getSuit(int suitValue)       //numeric value representing card suit
{

    string suit;                    //OUTPUT: string value representing suit

    //PROCESSING: Converting suit integer value to corresponding card suit
    if(suitValue == 0)
    {
        suit = "Spades";
    }
    else if(suitValue == 1)
    {
        suit = "Clubs";
    }
    else if(suitValue == 2)
    {
        suit = "Diamonds";
    }
    else if(suitValue == 3)
    {
        suit = "Hearts";
    }

    return suit;

}

/************************************************************
* getRank
* _________________________________________________________
*   Converts integer value to corresponding rank or card type
* _________________________________________________________
* PRE-CONDITIONS
*   rankValue : integer variable representing the
*     corresponding type of card.
*
* POST-CONDITIONS
*   Passes the integer value representing the rank of card.
*     Returns the rank or card type.
*
*************************************************************/
string getRank(int rankValue)      //numeric value representing card rank
{

    string rank;                   //CALC OUT: String value representing rank

    //PROCESSING: Converting rank integer value to corresponding card rank
    if(rankValue == 1)
    {
        rank = "Ace";
    }
    else if(rankValue == 2)
    {
        rank = "Two";
    }
    else if(rankValue == 3)
    {
        rank = "Three";
    }
    else if(rankValue == 4)
    {
        rank = "Four";
    }
    else if(rankValue == 5)
    {
        rank = "Five";
    }
    else if(rankValue == 6)
    {
        rank = "Six";
    }
    else if(rankValue == 7)
    {
        rank = "Seven";
    }
    else if(rankValue == 8)
    {
        rank = "Eight";
    }
    else if(rankValue == 9)
    {
        rank = "Nine";
    }
    else if(rankValue == 10)
    {
        rank = "Ten";
    }
    else if(rankValue == 11)
    {
        rank = "Jack";
    }
    else if(rankValue == 12)
    {
        rank = "Queen";
    }
    else if(rankValue == 13)
    {
        rank = "King";
    }

    return rank;

}

/************************************************************
* moneyTracker
* _________________________________________________________
*   Tracks amount of money player has based on amount won or
*     lost. Passes by reference the total amount of money
*     that the player has, the total value of player's hand
*     and total value of dealer's hand. Passes by value the
*     amount of player's bet.
* _________________________________________________________
* PRE-CONDITIONS
*   amount : integer variable representing the total amount
*     of money the player has.
*   bet : integer variable representing the bet amount
*   playerTotal : integer variable representing total value
*     of player's hand.
*   dealerTotal : integer variable representing total value
*     of dealer's hand.
*
* POST-CONDITIONS
*   Passes total value of player's hand, total value of
*     dealer's hand, amount of money by reference and bet by
*     value. Does not return value.
*
*************************************************************/
void moneyTracker(int &amount,             //total amount player's money
                  int bet,                 //player's bet
                  int &playerTotal,        //total value of player's hand
                  int &dealerTotal)        //total value of dealer's hand
{
    //Player comes closer to 21 than the dealer or the dealer busts but the
    //player did not bust -> player wins the bet amount.
    if((playerTotal <= 21 && playerTotal > dealerTotal) ||
            (playerTotal <= 21 && dealerTotal > 21))
    {
        amount += bet;
        cout << endl << "You win $" << bet << "." << endl << endl;
    }

    //The dealer comes closer to 21 than the player or the player's total
    //exceeds 21 -> player loses. Note if both the player and the dealer bust,
    //then the dealer wins. This is called the "house advantage".
    else if((playerTotal < dealerTotal)
            || (playerTotal > 21 && dealerTotal > 21))
    {
        amount -= bet;
        cout << "Too bad.  You lose $" << bet << "." << endl << endl;

    }

    //Both player and dealer have the same total and neither player busts
    //-> tie, no money is exchanged.
    else if((playerTotal == 21 && dealerTotal == 21) || (playerTotal == dealerTotal))
    {
        cout << "A draw! You get back your $" << bet << endl;
    }

}

/************************************************************
* endGame
* _________________________________________________________
*   Evaluates the outcome of the game when it ends
* _________________________________________________________
* PRE-CONDITIONS
*   amount : integer variable representing the total amount
*     of money the player has.
*
* POST-CONDITIONS
*   Passes player's amount of money by reference. Does not
*     return value.
*
*************************************************************/
void endGame(int &amount)
{
    //when the player is down to $0 or their amount exceeds $1,000.
    if(amount <= 0)
    {
        cout << "You have $" << amount << ". GAME OVER." << endl;

    }

    else if(amount > 1000)
    {
        cout << "You have $" << amount << ". YOU WIN." << endl;

    }

    else if(amount > 0 && amount <= 1000)
    {
        return;

    }

    exit(0);
}

/************************************************************
* endTurn
* _________________________________________________________
*   Evaluates whether player's turn should continue or end.
*     Passes by reference the total value of player's hand
*     and the amount of money player has. Passes by value
*     the amount of player's bet.
* _________________________________________________________
* PRE-CONDITIONS
*   currTotalTracker : integer variable representing the
*     total value of player's hand.
*   amount : integer variable representing the total amount
*     of money the player has.
*   bet : integer variable representing the bet amount
*
* POST-CONDITIONS
*   Passes total value of player's hand, amount of money by
*     reference and bet by value. Does not return value.
*
*************************************************************/
void endTurn(int &currTotalTracker,      //total value of player's hand
             int &amount,                //total amount of player's money
             int bet)                    //player's bet
{
    //when the player is down to $0 or their amount exceeds $1,000.
    if(currTotalTracker > 21)
    {
        cout << "You busted!" << endl << endl;
        amount -= bet;
        endGame(amount);
    }

    else if(currTotalTracker == 21)
    {
        cout << "BlackJack!!" << endl << endl;
    }

}
