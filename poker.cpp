//Poker Game 
// Created by Hamza and Jason 
#include "deckofcards.h"
#include "player.h"
#include "baseclass.h"
#include <iostream>
#include <vector> 
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <sqlite3.h>
using namespace std;

void Makedeck(vector<Card*>& deck){ //passed by reference so it changes the original vector 
	char suit[4] = {'C','S','H','D'};//the 4 suits represented by caps
	char face[4] = {'J','Q','K','A'};// the 4 symbols to represent each face card
	for (int j=0;j<4;j++){ // itterates for each suit 
		for(int i=2;i<10;i++){ // iterates for each normal card value
			deck.push_back(new Card(i,suit[j])); // creates the number cards for the suit starts at 2
		}
		for (int i=0;i<4;i++){ // iterates for each facecard symbol
			deck.push_back(new FaceCard(face[i],suit[j])); // creates each face card for the suit
		}
	}
}
void Deletedeck(vector<Card*>& deck){
	vector<Card*>::iterator it; //iterator to iterate through deck vector
	 	for (it = deck.begin(); it != deck.end(); it++){
	 		delete *it; // deletes each pointer in deck
	 	}
	 	deck.clear(); // clears deck 
}
void DealtoPlayer(vector<Card*>& deck, PlayerOG& player, vector<Card*>& resultVector){
	for(int i = 0; i<5; i++)
	{
	player.delt(deck.back(), resultVector);//gives community cards
	deck.pop_back(); // removes delt card from deck
	}
	player.Showhand();
}
void Shuffle(vector<Card*>& deck){	 
	srand(time(0)); // seeds random so there is a different shuffle every time prgm is run
	// auto rng = default_random_engine {};
	random_shuffle(deck.begin(), deck.end()); // randomly shuffels the deck
}

void Bet(PlayerOG& player, int& pot)
{
    int account = player.Getaccount();  
    int amount = 0;
    while(amount == 0)
    {
	 	  cout << "How much would you like to bet min is $2 max is $500\n";
		  cin >> amount;
	 	  if (account < amount){ //makes sure player is betting money that they have 
 		  	cout << "You only have $" << account << " You can't bet more\n";
        amount = 0;          
 		  }
 		  else if(amount<2){  //makes sure player is betting above the minimum
 		  	cout << "The minimum bet is $2\n";
        amount = 0;          
 		  }
 	  	else if(amount>500){ //makes sure player is betting below the maximum
 	  		cout << "The maximum bet is $500\n";
        amount = 0;             
 		  }
 		  else{
 			  account -= amount; // takes the players bet out of their account 
        player.Setaccount(account);
        pot += amount;
        cout <<"The Pot Is $" << pot << "\n";
        player.Setbet(amount);
      }
 		}
}
bool findApair(vector<Card*>& hand) //https://www.guidearea.com/poker-console-game-ai-cpp/
{
    bool condition = false;
    int counter = 0;
    for(int i = 0; i < hand.size(); i++)
    {
      counter = counter + count(hand.begin(), hand.end(), hand[i]->Getvalue());
    }
    if (counter == 7)
    {
      condition = true;
    }
    return condition;
}
int main()
{
  									// initializes bet to 0 so so bet loop will start
    int pot = 0;                                   
  	string name1;
    string name2;
    string name3;
    string name4;
  	cout << "Player 1, Enter your name: ";
  	getline(cin, name1); 							// user input for their name
  	PlayerOG player1(name1);
  
//  	cout << "Player 2, Enter your name: ";
//  	getline(cin, name2); 
//  	PlayerOG player2(name2);
//  
//  	cout << "Player 3, Enter your name: ";
//  	getline(cin, name3); 
//  	PlayerOG player3(name3);
//  
//  	cout << "Player 4, Enter your name: ";
//  	getline(cin, name4); 
//  	PlayerOG player4(name4);
  	
  	vector <Card*> deck;								// initiates vector that will become the deck
  	Makedeck(deck);										//adds all the cards to the deck
    Shuffle(deck);
    vector<Card*> hand;
  
  	cout<<endl;
  	cout << "\n\nWelcome to Poker!";
    cout << "\nYou will be delt 5 cards.\nYou can bet based on how good your hand is.\nOnce each player has placed a bet a winner is decided based on who had the best hand.\nThe minimum bet is $2 and the maximum bet is $500.\nGood Luck!";
  
    DealtoPlayer(deck,player1, hand);
    if (findApair(hand) == true) { 
    cout << "Found a Pair\n";
    }
    else 
    {
     cout << "No Pair";
    }
//    Bet(player1, pot);
//    DealtoPlayer(deck,player2, hand);
//    Bet(player2, pot);
//    DealtoPlayer(deck,player3,hand);
//    Bet(player3, pot);
//    DealtoPlayer(deck,player4,hand);
//    Bet(player4, pot);
    
    
   
   
  
    //create function called GetHandRank in poker to take in player hand arguments and   community hand arguments
    //use getValue, getSuit, getCardType
}