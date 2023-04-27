/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: Harry Lee
 *
 * Created on April 19, 2023, 6:24 PM
 * Purpose: BlackJack Game.
 */


//System Libraries Here
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <list>
#include <deque>
#include <bits/stdc++.h>

using namespace std;

//User Libraries Here
struct avl {
   int d;
   struct avl *l;
   struct avl *r;
}*r;

class avl_tree {
   public:
      int height(avl *);
      int difference(avl *);
      avl *rr_rotat(avl *);
      avl *ll_rotat(avl *);
      avl *lr_rotat(avl*);
      avl *rl_rotat(avl *);
      avl * balance(avl *);
      avl * insert(avl*, int);
      void show(avl*, int);
      void inorder(avl *);
      void preorder(avl *);
      void postorder(avl*);
      avl_tree() {
         r = NULL;
      }
};

int avl_tree::height(avl *t) {
   int h = 0;
   if (t != NULL) {
      int l_height = height(t->l);
      int r_height = height(t->r);
      int max_height = max(l_height, r_height);
      h = max_height + 1;
   }
   return h;
}

int avl_tree::difference(avl *t) {
   int l_height = height(t->l);
   int r_height = height(t->r);
   int b_factor = l_height - r_height;
   return b_factor;
}

avl *avl_tree::rr_rotat(avl *parent) {
   avl *t;
   t = parent->r;
   parent->r = t->l;
   t->l = parent;
   cout << "Right-Right Rotation";
   return t;
}

avl *avl_tree::ll_rotat(avl *parent) {
   avl *t;
   t = parent->l;
   parent->l = t->r;
   t->r = parent;
   cout << "Left-Left Rotation";
   return t;
}

avl *avl_tree::lr_rotat(avl *parent) {
   avl *t;
   t = parent->l;
   parent->l = rr_rotat(t);
   cout << "Left-Right Rotation";
   return ll_rotat(parent);
}

avl *avl_tree::rl_rotat(avl *parent) {
   avl *t;
   t = parent->r;
   parent->r = ll_rotat(t);
   cout << "Right-Left Rotation";
   return rr_rotat(parent);
}

avl *avl_tree::balance(avl *t) {
   int bal_factor = difference(t);
   if (bal_factor > 1) {
      if (difference(t->l) > 0)
         t = ll_rotat(t);
      else
         t = lr_rotat(t);
   } else if (bal_factor < -1) {
      if (difference(t->r) > 0)
         t = rl_rotat(t);
      else
         t = rr_rotat(t);
   }
   return t;
}

avl *avl_tree::insert(avl *r, int v) {
   if (r == NULL) {
      r = new avl;
      r->d = v;
      r->l = NULL;
      r->r = NULL;
      return r;
   } else if (v< r->d) {
      r->l = insert(r->l, v);
      r = balance(r);
   } else if (v >= r->d) {
      r->r = insert(r->r, v);
      r = balance(r);
   } return r;
}

void avl_tree::show(avl *p, int l) {
   int i;
   if (p != NULL) {
      show(p->r, l+ 1);
      cout<<" ";
      if (p == r)
         cout << "Root -> ";
      for (i = 0; i < l&& p != r; i++)
         cout << " ";
         cout << p->d;
         show(p->l, l + 1);
   }
}

void avl_tree::inorder(avl *t) {
   if (t == NULL)
      return;
      inorder(t->l);
      cout << t->d << " ";
      inorder(t->r);
}

void avl_tree::preorder(avl *t) {
   if (t == NULL)
      return;
      cout << t->d << " ";
      preorder(t->l);
      preorder(t->r);
}

void avl_tree::postorder(avl *t) {
   if (t == NULL)
      return;
      postorder(t ->l);
      postorder(t ->r);
      cout << t->d << " ";
}


//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
void rules();
bool cardDrawn(deque<int> q, int x);
int value(int);
int addlist(list<int>);
void printCards(list<int>, string[]);

//For Trees
int countList(list<int>);
void makeArr(int [], list<int>);
int addRec(int [], int);


//Program Execution Begins Here
int main(int argc, char** argv) {
    //Set Random Number seed
    srand(static_cast<unsigned int>(time(0)));
    
    // Declare all Variables Here
    int totalPV, totalDV, draw, dListSz, pListSz;
    char choice;
    bool game = false;
    
    //Declare Tree
    avl_tree avl;
    
    //Initialize Name and Hash
    char name[3];  //Name data
    char hash[3];  //Hash
    int  intHash;  //Hash in int
    
    //Decalre values for card array
    const int size = 52;
    string card[size] = {"Ace of Spades", "Two of Spades", "Three of Spades", "Four of Spades", "Five of Spades", "Six of Spades", 
                         "Seven of Spades", "Eight of Spades", "Nine of Spades", "Ten of Spades", "Jack of Spades", "Queen of Spades", 
                         "King of Spades", "Ace of Clovers", "Two of Clovers", "Three of Clovers", "Four of Clovers", "Five of Clovers",
                         "Six of Clovers", "Seven of Clovers", "Eight of Clovers", "Nine of Clovers", "Ten of Clovers", "Jack of Clovers",
                         "Queen of Clovers", "King of Clovers", "Ace of Hearts", "Two of Hearts", "Three of Hearts", "Four of Hearts", 
                         "Five of Hearts", "Six of Hearts", "Seven of Hearts", "Eight of Hearts", "Nine of Hearts", "Ten of Hearts",
                         "Jack of Hearts", "Queen of Hearts", "King of Hearts", "Ace of Diamonds", "Two of Diamonds", "Three of Diamonds", 
                         "Four of Diamonds", "Five of Diamonds", "Six of Diamonds", "Seven of Diamonds", "Eight of Diamonds", "Nine of Diamonds",
                         "Ten of Diamonds", "Jack of Diamonds", "Queen of Diamonds", "King of Diamonds",};
    
    
    //List of drawn cards total, player and dealer
    deque<int> drawn;         //Use deque to find if card has been drawn, if not add to list of cards
    list<int> playerCards;
    list<int> playerValue;
    list<int> dealerCards;
    list<int> dealerValue;
    
    
    //Ask player what their name is
    cout << "Hello! What is the player's Initials?" << endl;
    cout << "Input Three Initials from A-Z..." << endl;
    cout << "Input: ";
    cin >> name[0] >> name[1] >> name[2];
    
    //Hash name
    for(int i = 0; i < 3; i++) {
        if(name[i] == 'A' || name[i] == 'B' || name[i] == 'C') {
            hash[i] = '2';
        }
        else if(name[i] == 'D' || name[i] == 'E' || name[i] == 'F') {
            hash[i] = '3';
        }
        else if(name[i] == 'G' || name[i] == 'H' || name[i] == 'I') {
            hash[i] = '4';
        }
        else if(name[i] == 'J' || name[i] == 'K' || name[i] == 'L') {
            hash[i] = '5';
        }
        else if(name[i] == 'M' || name[i] == 'N' || name[i] == 'O') {
            hash[i] = '6';
        }
        else if(name[i] == 'P' || name[i] == 'Q' || name[i] == 'R' || name[i] == 'S') {
            hash[i] = '7';
        }
        else if(name[i] == 'T' || name[i] == 'U' || name[i] == 'V') {
            hash[i] = '8';
        }
        else if(name[i] == 'W' || name[i] == 'X' || name[i] == 'Y' || name[i] == 'Z') {
            hash[i] = '9';
        }
        else {
            hash[i] = '1';
        }
    }
    
    //Change char hash to an int value
    intHash = 0;
    intHash += (hash[2] - '0');
    intHash += (hash[1] - '0') * 10;
    intHash += (hash[0] - '0') * 100;
    
    //Output player's ID
    cout << endl << "Hello " << name[0] << name[1] << name[2] << "! Your player ID is " << intHash << "!" << endl;
    cout << "Enjoy the Program!" << endl << endl;
    
    //Ask if they want to play black jack
    cout << "Hello Again! Would you like to play Black Jack?" << endl;
    cout << "Input (y/n): ";
    cin >> choice;
    //Validate input
    while(choice != 'y' && choice != 'n') {
        cout << choice << " is invalid! Try again: ";
        cin >> choice;
    }
    
    //Output depending on results
    if(choice == 'y') {
        //Change boolean
        game = true;
        
        //Ask if they want to know the rules
        cout << endl << "Nice! Would you like to know the rules of the game?" << endl;
        cout << "Input (y/n): ";
        cin >> choice;
        
        //Validate input
        while(choice != 'y' && choice != 'n') {
            cout << choice << " is invalid! Try again: ";
            cin >> choice;
        }
        
        //Output rules
        if(choice == 'y') {
            rules();
            cout <<  endl;
        }
        
        //Ask if they are ready to play
        cout << endl << "Are you ready to play?" << endl;
        cout << "Input (y/n): ";
        cin >> choice;
        
        //Validate input
        while(choice != 'y' && choice != 'n') {
            cout << choice << " is invalid! Try again: ";
            cin >> choice;
        }
        
        //Loop to keep asking player to play
        while(choice != 'y') {
            cout << endl << "Thats a shame!" << endl;
            cout << "Are you ready now?" << endl;
            cout << "Input (y/n): ";
            cin >> choice;
        }
        
        //Loop to say game is starting
        if(choice == 'y') {
            cout << endl << "Nice we can start!" << endl;
        }
        
        //play game
        while(game) {
            //For loop to draw cards for player
            for(int i = 0; i < 2; i++) {
                // draw initial Player Cards
                draw = rand() % 52;
                //Check if card has already been drawn
                if(cardDrawn(drawn, draw)) {
                    while(cardDrawn(drawn, draw)) {
                        draw = rand() % 52;
                    }
                }
                //If card draw is not in list of cards pulled out push value into list so wont get drawn again
                if(!cardDrawn(drawn, draw)) {
                    //Push to drawn deque
                    drawn.push_back(draw);
                    r = avl.insert(r, draw);
                    //Push to player's drawn cards list
                    playerCards.push_back(draw);
                    //Push back value of card drawn into player's value
                    playerValue.push_back(value(draw));
                }
            }
            
            //For loop to draw cards for dealer
            for(int i = 0; i < 2; i++) {
                // draw initial Player Cards
                draw = rand() % 52;
                //Check if card has already been drawn
                if(cardDrawn(drawn, draw)) {
                    while(cardDrawn(drawn, draw)) {
                        draw = rand() % 52;
                    }
                }
                //If card draw is not in list of cards pulled out push value into list so wont get drawn again
                if(!cardDrawn(drawn, draw)) {
                    //Push to drawn deque
                    drawn.push_back(draw);
                    r = avl.insert(r, draw);
                    //Push to player's drawn cards list
                    dealerCards.push_back(draw);
                    //Push back value of card drawn into player's value
                    dealerValue.push_back(value(draw));
                }
            } 
            
            //Sort functions cause why not?
            playerValue.sort();
            dealerValue.sort();
            
            //Add up total values for player and dealer's cards
            totalPV = addlist(playerValue);
            totalDV = addlist(dealerValue);
            
            //Output some results for player to work with
            cout << "You drew the cards: " << endl;
            //Print cards list
            printCards(playerCards, card);
            //Print total of cards drawn
            cout << "Your cards add up to: " << totalPV << endl << endl;
            
            //Output dealer's card
            cout << "Dealer drew the cards: " << endl;
            //Only show first value since other card is face down
            cout << '\t' << card[dealerCards.front()] << endl;
            cout << '\t' << "Unknown" << endl;
            //Print value of first card
            cout << "Dealer's cards add up to: " << dealerValue.front() <<  endl << endl;
            
            //ask player if they would like to draw another card
            cout << "Would you like to draw again?" << endl
                 << "Input (y/n): ";
            cin >> choice;
            //Validate input
            while(choice != 'y' && choice != 'n') {
                cout << choice << " is invalid! Try again: ";
                cin >> choice;
            }
            
            //Change boolean depending on answer
            while(choice == 'y') {
                // draw initial Player Cards
                draw = rand() % 52;
                //Check if card has already been drawn
                if(cardDrawn(drawn, draw)) {
                    while(cardDrawn(drawn, draw)) {
                        draw = rand() % 52;
                    }
                }
                //If card draw is not in list of cards pulled out push value into list so wont get drawn again
                if(!cardDrawn(drawn, draw)) {
                    //Push to drawn deque
                    drawn.push_back(draw);
                    r = avl.insert(r, draw);
                    //Push to player's drawn cards list
                    playerCards.push_back(draw);
                    //Push back value of card drawn into player's value
                    playerValue.push_back(value(draw));
                }
                
                //Output drawed card
                cout << endl <<  "You drew the card: " << card[draw] << endl;
                cout << "Card has value of " << value(draw) << endl;
                
                //Add to the total
                totalPV += value(draw);
                
                //output total
                cout << endl << "Your total value is now: " << totalPV << endl << endl;
                
                //Ask again if they would like to
                cout << "Would you like to draw again?" << endl
                     << "Input (y/n): ";
                cin >> choice;
                //Validate input
                while(choice != 'y' && choice != 'n') {
                    cout << choice << " is invalid! Try again: ";
                    cin >> choice;
                }
            }
            
            // Conditions if dealer reveals second card or player loses
            if(totalPV > 21) {
                //Output that player has lost
                cout << endl << "You have lost, since your cards have went over 21!" << endl
                     << "Better luck next time!" << endl;
            }
            else if(totalPV < 21) {
                //reveal player's second card
                cout << endl << "The Dealer reveals their second card..." << endl
                     << "The Dealer has the cards: " << endl;
                //Print cards list
                printCards(dealerCards, card);
                //Print total of cards drawn
                cout << "Your cards add up to: " << totalDV << endl << endl;
                
                //Think of an AI for dealer
                //Teach to count cards, or keep it simple?
                
                //Simple AI for dealer to draw card if need be
                //Might update to utilize STL algorithm to count cards and think if have time
                if(totalDV <= 15 && totalDV < totalPV) {
                    //Output dealer's choice
                    cout << "Dealer decides to draw a card!" << endl;
                    // draw initial Player Cards
                    draw = rand() % 52;
                    //Check if card has already been drawn
                    if(cardDrawn(drawn, draw)) {
                        while(cardDrawn(drawn, draw)) {
                            draw = rand() % 52;
                        }
                    }
                    //If card draw is not in list of cards pulled out push value into list so wont get drawn again
                    if(!cardDrawn(drawn, draw)) {
                        //Push to drawn deque
                        drawn.push_back(draw);
                        r = avl.insert(r, draw);
                        //Push to player's drawn cards list
                        dealerCards.push_back(draw);
                        //Push back value of card drawn into player's value
                        dealerValue.push_back(value(draw));
                    }

                    //Output drawed card
                    cout << endl <<  "Dealer drew the card: " << card[draw] << endl;
                    cout << "Card has value of " << value(draw) << endl;

                    //Sort function cause why not?
                    dealerValue.sort();
                    
                    //Add to the total
                    totalDV = addlist(dealerValue);

                    //output total
                    cout << endl << "Dealers total value is now: " << totalDV << endl << endl;
                }
            }
            
            //Sort function cause why not?
            dealerValue.sort();

            //List size to add recursion for total player value cause why not
            dListSz = countList(dealerValue);

            //Declare and Intialize array for total dealer's cards
            int dlCards[dListSz];
            makeArr(dlCards, dealerValue);

            //Add to the total of dealers using recursions
            totalDV = addRec(dlCards, dListSz);
        
            // Output the final results
            cout << endl << "The final results are... " << endl;
            
            //Player data
            //Output some results for player to work with
            cout << "You drew the cards: " << endl;
            
            //Print cards list
            printCards(playerCards, card);
            
            //Print total of cards drawn
            cout << "Your cards add up to: " << totalPV << endl << endl;
            
            //Dealer data
            //Output some results for player to work with
            cout << "Dealer drew the cards: " << endl;
            
            //Print cards list
            printCards(dealerCards, card);
            
            //Print total of cards drawn
            cout << "Dealers cards add up to: " << totalDV << endl << endl;
            
            //Output final verdict
            if(totalPV > totalDV && totalPV <= 21) {
                cout << "The Player has won against the Dealer!" << endl;
            }
            else if(totalDV > totalPV && totalDV <= 21) {
                cout << "The Player's cards are less than the Dealer, so you have lost." << endl;
            }
            else if((totalDV == totalPV) && (totalDV <= 21) && (totalPV <= 21)){
                cout << "The Player's and Dealer's cards equal the same amount, so it is a tie." << endl;
            }
            else if(totalPV > 21) {
                cout << "The Player's cards are above 21, You Lose :(" << endl;
            }
            else if(totalDV > 21) {
                cout << "The Dealer's cards are above 21, You Win!" << endl;
            }
            
            //Clear Player and dealer's hands
            playerCards.clear();
            playerValue.clear();
            dealerCards.clear();
            dealerValue.clear();
            
            //Ask if they want to play again
            cout << endl << "Would you like to play again?" << endl
                 << "Input (y/n): ";
            cin >> choice;
            
            //Validate input
            while(choice != 'y' && choice != 'n') {
                cout << choice << " is invalid! Try again: ";
                cin >> choice;
            }
            //Change boolean depending on answer
            if(choice == 'y') {
                game = true;
                //Ask player if they would like to play on a fresh deck
                cout << endl << "Would you like to reset the deck?" << endl
                     << "Input (y/n): ";
                cin >> choice;
                //Validate input
                while(choice != 'y' && choice != 'n') {
                    cout << choice << " is invalid! Try again: ";
                    cin >> choice;
                }
                
                //If statement for reseting or not
                if(choice == 'y') {
                    //Clear data inside
                    drawn.clear();
                }
            }
            else {
                game = false;
            }
        }
    }
    else {
        cout << endl << "Well That's a shame!" << endl;
    }
    
    //Ask if they ant to see the tree diagram of the cards drawn
    cout << endl << "Would you like to see a tree of every card draw?" << endl
         << "Input (y/n): ";
    cin >> choice;
    
    //Validate input
    while(choice != 'y' && choice != 'n') {
        cout << choice << " is invalid! Try again: ";
        cin >> choice;
    }
    
    //Output balanced AVL tree for cards drawn
    if(choice == 'y') {
        cout << endl;
        if (r == NULL) {
           cout << "Tree is Empty" << endl;
        }
        cout << "Balanced AVL Tree:" << endl;
        avl.show(r, 1);
        cout << endl;
    }
    
    cout << endl << "Thank you for your time!" << endl;
    
    
    //Exit
    return 0;
}


void rules() {
    cout << endl << "The rules are as follows..." << endl;
    cout << "1. The dealer draws 2 cards. One face up and one face down." << endl
         << "2. The player is then given 2 cards, where only the player knows their value." << endl
         << "3. Each card has a set value, number cards are the same value as their corresponding numbers," << endl
         << "   while face cards have a value of 10 and ace cards have a value of 11." << endl
         << "4. Given the players cards and the dealers cards, the player has a choice to draw more cards." << endl
         << "5. The player's goal is to draw cards and get as close to the value of 21, while not going" << endl
         << "   over that set value." << endl
         << "6. Win condition is determined if the player goes over 21 or the player's value is lower than the dealers." << endl;
}


bool cardDrawn(deque<int> q, int x) {
    //Initialize iterator
    deque<int>::iterator itr;
    //Initialize the find functions to find value wanted
    itr = find(q.begin(), q.end(), x);
    //If statement for find
    //find() returns end if not found
    //if itr returns end of deque then it was not found
    if(itr != q.end()) {
        return true;
    }
    else {
        return false;
    }
}


int value(int n) {
    //declare x and set equal to n + 1
    int x = n + 1;
    //Find mod of x to find what type of card it is
    x = x % 13;
    //If statements to return value of card
    //If mod is 10, it is a king face card so value of 10
    if(x == 0) {
        x = 10;
    }
    //If mod greater than 10 then it is a face card
    else if(x > 10) {
        x = 10;
    }
    //If mod of 1 then it is an ace card, so value of 11
    else if(x == 1) {
        x = 11;
    }
    //return value of card
    return x;
}

int addlist(list<int> g) {
    //Initialize total
    int total = 0;
    //Initialize iterator
    list<int>::iterator it;
    //Loop to add with iterator
    for (it = g.begin(); it != g.end(); ++it) {
        total += *it;
    }
    //Return value
    return total;
}

void printCards(list<int> g, string a[]) {
    //Initialize iterator
    list<int>::iterator it;
    //Output each card
    for (it = g.begin(); it != g.end(); ++it) {
        //Output value of array
        cout << '\t' << a[*it];
        cout << '\n';
    }
}

int countList(list<int> g) {
    //Initialize total
    int total = 0;
    //Initialize iterator
    list<int>::iterator it;
    //Loop to add with iterator
    for (it = g.begin(); it != g.end(); ++it) {
        total++;
    }
    //Return value
    return total;
}

void makeArr(int x[], list<int> g) {
    //Initialize count
    int count = 0;
    //Initialize iterator
    list<int>::iterator it;
    //Loop to Set array equal to list values
    for (it = g.begin(); it != g.end(); ++it) {
        x[count] = *it;
        count++;
    }
}

int addRec(int x[], int size) {
    if (size <= 0)
        return size;
    return x[size - 1] + addRec(x, size - 1);
}