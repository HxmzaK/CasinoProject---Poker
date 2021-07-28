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
		for(int i=2;i<11;i++){ // iterates for each normal card value
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
void DealtoPlayer(vector<Card*>& deck, PlayerOG& player){
	for(int i = 0; i<5; i++)
	{
	player.delt(deck.back());//gives community cards
	deck.pop_back(); // removes delt card from deck
	}
	player.Showhand();
}
void Shuffle(vector<Card*>& deck){	 
	srand(time(0)); // seeds random so there is a different shuffle every time prgm is run
	// auto rng = default_random_engine {};
	random_shuffle(deck.begin(), deck.end()); // randomly shuffels the deck
}
int findPairs(vector<Card*>& hand) 
{
    vector<Card*>::iterator it; 
    int counter[14] = {0};
    int pairCounter = 0;
    for (it = hand.begin(); it != hand.end(); it++)//runs through the hand and gets value of each element of hand
    {
      int value = (*it)->Getvalue();
      counter[value-1]++;
    }
    for(int i=0;i<14;i++)  
    if (counter[i] == 2)
    {
      pairCounter++;
    }
    return pairCounter;
}
int findThreeofaKind(vector<Card*>& hand) 
{
    vector<Card*>::iterator it; 
    int counter[14] = {0};
    int threePairCounter = 0;
    for (it = hand.begin(); it != hand.end(); it++)
    {
      int value = (*it)->Getvalue();
      counter[value-1]++;
    }
    for(int i=0;i<14;i++)
    if (counter[i] == 3)
    {
      threePairCounter++;
    }
    return threePairCounter;
}
int findFourofaKind(vector<Card*>& hand) 
{
    vector<Card*>::iterator it; 
    int counter[14] = {0};
    int fourPairCounter = 0;
    for (it = hand.begin(); it != hand.end(); it++)
    {
      int value = (*it)->Getvalue();
      counter[value-1]++;
    }
    for(int i=0;i<14;i++)
    if (counter[i] == 4)
    {
      fourPairCounter++;
    }
    return fourPairCounter;
}
int findHighCard(vector<Card*>& hand)
{
    vector<Card*>::iterator it; 
    int counter[14] = {0};
    int highCard = 0;
    for (it = hand.begin(); it != hand.end(); it++)
    {
      int value = (*it)->Getvalue();
      counter[value-1]++;
    }
    for(int i=0;i<14;i++){
      if (counter[i] != 0)
      {
        highCard = i+1;
      }
    }
    return highCard;
}
bool findaStraight(vector<Card*>& hand)
{
    vector<Card*>::iterator it; 
    int counter[14] = {0};
    int sequence = 0;
    int x = 0;
    for (it = hand.begin(); it != hand.end(); it++) //runs through the hand and gets value of each element of hand
    {
      int value = (*it)->Getvalue();
      counter[value-1]++;
    }
    for(int i=0;i<14;i++){
      if (counter[i] == 1)
      {
        x = i;
        sequence++;
        while(sequence != 5 && x < 13)
        {
          if(counter[x+1] == 1)
          {
              sequence++;
          }
          else
          {
              sequence = 0;
              break;
          }
        }
      }
    }
    if (sequence == 5)
    {
        return true;
    }
  return false;
}
bool findaFlush(vector<Card*>& hand)
{
    vector<Card*>::iterator it; 
    int counter[4] = {0};
    int sameSuit = 0;
    for (it = hand.begin(); it != hand.end(); it++)
    {
      char symbol = (*it)->Getsuit();
      switch (symbol)
      {
        case 'C':
        {
          counter[0]++;
          break;
        }
        case 'S':
        {
          counter[1]++;
          break;
        }
        case 'H':
        {
          counter[2]++;
          break;
        }
        case 'D':
        {
          counter[3]++;
          break;
        }
      }
    }
    for(int i=0;i<4;i++)
    {
      if (counter[i] == 5)
      {
        return true;
      }
    }
    return false;
}
char convertToSymbol(int facecard)
{
    switch (facecard)
    {
    case 11:
    return 'A';
    case 12:
    return 'J';
    case 13:
    return 'Q';
    case 14:
    return 'K';
    default:
    return ' ';
    }
}
int findWinner(PlayerOG& player)
{
    vector<Card*> hand = player.Gethand();
    if (findaFlush(hand) == true && findaStraight(hand) == true)
    {
        cout << "Found A Straight Flush!\n";
        return 9;
    }
    else if(findFourofaKind(hand) == 1){
        cout << "Found Four Of A Kind!\n";
        return 8;
    }
    
    else if (findPairs(hand) == 1 && findThreeofaKind(hand) == 1)
    {
        cout << "Full House!\n";
        return 7;
    }
    else if(findaFlush(hand) == true)
    {
        cout << "Found A Flush!\n";
        return 6;
    }
    else if(findaStraight(hand) == true)
    {
        cout << "Found A Straight!\n";
        return 5;
    }
    else if(findThreeofaKind(hand) == 1){
        cout << "Found Three Of A Kind!\n";
        return 4;
    }
    else if(findPairs(hand) == 2){
        cout << "Found Two Pair!\n";
        return 3;
    }
    else if (findPairs(hand) == 1) { 
        cout << "Found a Pair!\n";
        return 2;
    }
    else
    {
        if(findHighCard(hand) > 10)
        {
          cout <<"High Card is " << convertToSymbol(findHighCard(hand)) << endl;
        }
        else{
        cout << "High Card is " << findHighCard(hand) << endl;
        }
        return 1;
    }
}
int main()
{
    int pot = 0;                                   
  	string name1;
    string name2;
    string name3;
    string name4;
  	cout << "Player 1, Enter your name: ";
  	getline(cin, name1); 							// user input for their name
  	PlayerOG player1(name1);
  
  	cout << "Player 2, Enter your name: ";
  	getline(cin, name2); 
  	PlayerOG player2(name2);
  
  	cout << "Player 3, Enter your name: ";
  	getline(cin, name3); 
  	PlayerOG player3(name3);
  
  	cout << "Player 4, Enter your name: ";
  	getline(cin, name4); 
  	PlayerOG player4(name4);
  	
  	vector <Card*> deck;								// initiates vector that will become the deck
  	Makedeck(deck);										//adds all the cards to the deck
    Shuffle(deck);
    vector<Card*> hand;
    int handRanks[4];
  
  	cout<<endl;
  	cout << "\n\nWelcome to Poker!";
    cout << "\nYou will be delt 5 cards.\nYou can bet based on how good your hand is.\nOnce each player has placed a bet a winner is decided based on who had the best hand.\nGood Luck!";
  
    DealtoPlayer(deck,player1);
    handRanks[0] = findWinner(player1);
    pot += player1.Placebet();
    DealtoPlayer(deck,player2);
    handRanks[1] = findWinner(player2);
    pot += player2.Placebet();
    DealtoPlayer(deck,player3);
    handRanks[2] = findWinner(player3);
    pot += player3.Placebet();
    DealtoPlayer(deck,player4);
    handRanks[3] = findWinner(player4);
    pot += player4.Placebet();
    
    int max = 0;
    int location;
    for(int i=0;i<4;i++)
    {
        if(handRanks[i] > max)
        {
            location = i;
            max = handRanks[i];
        }
    }
    cout << "Pot is $"<< pot<< endl;
    switch (location)
    {
        case 0:
        {
          player1.Securebag(pot); 
          cout << "Winner is " << player1.Getname() << "! They have $"<< player1.Getaccount() << ".\n";
          break;
        }
        case 1:
        {
          player2.Securebag(pot);
          cout << "Winner is " << player2.Getname() << "! They have $"<< player2.Getaccount() << ".\n";
          break;
        }
        case 2:
        {
          player3.Securebag(pot);
          cout << "Winner is " << player3.Getname() << "! They have $"<< player3.Getaccount() << ".\n";
          break;
        }
        case 3:
        {
          player4.Securebag(pot);
          cout << "Winner is " << player4.Getname() << "! They have $"<< player4.Getaccount() << ".\n";
          break;
        }
    }
}