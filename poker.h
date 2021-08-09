//Poker Game 
// Created by Hamza and Jason 
#include "poker_deckofcards.h"
#include "player_poker.h"
#include "baseclass.h"
#include <iostream>
#include <vector> 
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <sqlite3.h>

using namespace std;
class Poker: public Game
{
public:
  Poker(int id):Game(id){}
  void Makedeck(vector<Card_Poker*>& deck){ //passed by reference so it changes the original vector 
  char suit[4] = {'C','S','H','D'};//the 4 suits represented by caps
  char face[4] = {'J','Q','K','A'};// the 4 symbols to represent each face card
  for (int j=0;j<4;j++){ // itterates for each suit 
    for(int i=2;i<11;i++){ // iterates for each normal card value
      deck.push_back(new Card_Poker(i,suit[j])); // creates the number cards for the suit starts at 2
    }
    for (int i=0;i<4;i++){ // iterates for each facecard symbol
      deck.push_back(new FaceCard_Poker(face[i],suit[j])); // creates each face card for the suit
    }
  }
}
  void Deletedeck(vector<Card_Poker*>& deck){
    vector<Card_Poker*>::iterator it; //iterator to iterate through deck vector
      for (it = deck.begin(); it != deck.end(); it++){
        delete *it; // deletes each pointer in deck
      }
      deck.clear(); // clears deck 
  }
  void DealtoPlayer(vector<Card_Poker*>& deck, PlayerOG& player){
    for(int i = 0; i<5; i++)
    {
    player.delt(deck.back());//gives community cards
    deck.pop_back(); // removes delt card from deck
    }
    player.Showhand();
  }
  void Shuffle(vector<Card_Poker*>& deck){   
    srand(time(0)); // seeds random so there is a different shuffle every time prgm is run
    // auto rng = default_random_engine {};
    random_shuffle(deck.begin(), deck.end()); // randomly shuffels the deck
  }
  int findPairs(vector<Card_Poker*>& hand) 
  {
      vector<Card_Poker*>::iterator it; 
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
  int findThreeofaKind(vector<Card_Poker*>& hand) 
  {
      vector<Card_Poker*>::iterator it; 
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
  int findFourofaKind(vector<Card_Poker*>& hand) 
  {
      vector<Card_Poker*>::iterator it; 
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
  int findHighCard(vector<Card_Poker*>& hand)
  {
      vector<Card_Poker*>::iterator it; 
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
  bool findaStraight(vector<Card_Poker*>& hand)
  {
      vector<Card_Poker*>::iterator it; 
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
  bool findaFlush(vector<Card_Poker*>& hand)
  {
      vector<Card_Poker*>::iterator it; 
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
      vector<Card_Poker*> hand = player.Gethand();
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
};


int Pokergame(Player& player)
{ 
  srand(time(0));  
  Poker game(3);
  int pot = 0;                                   
  string name1;
  string name2 = "Player1";
  string name3 = "Player2";
  string name4 = "Player3";
  name1 = player.getName();
  int id = player.getID();
  PlayerOG player1(id, name1,"");  
  PlayerOG player2(0,name2,"");
  PlayerOG player3(0,name3,"");
  PlayerOG player4(0,name4,"");
    
  while(true){
    
  	srand(time(0)); // seeds the time so there is a different 
    
  	
  	vector <Card_Poker*> deck;								// initiates vector that will become the deck
  	game.Makedeck(deck);										//adds all the cards to the deck
    game.Shuffle(deck);
    vector<Card_Poker*> hand;
    int handRanks[4];
  
  	cout<<endl;
  	cout << "\n\nWelcome to Poker!";
    cout << "\nYou will be delt 5 cards.\nYou can bet based on how good your hand is.\nOnce each player has placed a bet a winner is decided based on who had the best hand.\nGood Luck!";
  
    game.DealtoPlayer(deck,player1);
    handRanks[0] = game.findWinner(player1);
    int amountplayer = player1.Placebet();
    pot += amountplayer; // computer bets random amount 1-500
    game.DealtoPlayer(deck,player2);
    handRanks[1] = game.findWinner(player2);
    pot += (rand()%500)+1; // computer bets random amount 1-500
    game.DealtoPlayer(deck,player3);
    handRanks[2] = game.findWinner(player3);
    pot += (rand()%500)+1; // computer bets random amount 1-500
    game.DealtoPlayer(deck,player4);
    handRanks[3] = game.findWinner(player4);
    pot += (rand()%500)+1; // computer bets random amount 1-500
    
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
          player1.Securebag(pot*0.95);//gives the player 95% of the pot 
          cout << "Winner is " << player1.Getname() << "! You have $"<< player1.Getaccount() << ".\n";
          player1.AddWinPlayer();
          game.AddAmountwon(pot*0.05);//gives the casino 5% of the total pot 
          break;
        }
        case 1:
        {
          player2.Securebag(pot);
          cout << "Winner is " << player2.Getname() << endl;
          player1.AddLossPlayer();
          game.AddAmountwon(pot*0.05);//gives the casino 5% of the total pot 
          break;
        }
        case 2:
        {
          player3.Securebag(pot);
          cout << "Winner is " << player3.Getname()<< endl;
          player1.AddLossPlayer();
          game.AddAmountwon(pot*0.05);//gives the casino 5% of the total pot 
          break;
        }
        case 3:
        {
          player4.Securebag(pot);
          cout << "Winner is " << player4.Getname()<< endl;
          player1.AddLossPlayer();
          game.AddAmountwon(pot*0.05);//gives the casino 5% of the total pot 
          break;
        }
    }

    player1.AddGameplayedPlayer(); //adds to a palyers total
    game.AddGameplayed(); // add a game played for poker
    int playagain;
    cout << "press 0 to stop playing or press any other key to keep playing.\n";
    cin >> playagain;
    if (playagain==0){
      //update the database
      player1.UpdateBalance(player1.Getaccount());//updates palyers balance in the db after they cash out
      player1.UpdateWins();//updates palyers wins in the db after they cash out
      player1.UpdateLosses();//updates palyers losses in the db after they cash out
      player1.UpdateGamesplayed();//updates palyers Gamesplayed in the db after they cash out

      
      game.UpdateGamesplayed();//Updates games played in the db after the player cashes out
      game.UpdateAmountwon();//Updates amount won played in the db after the player cashes out
      return 0; // ends the function
    }

    game.Deletedeck(deck); // delete deck before next game starts

  }//ends while loop
}