#pragma once
#include "deckofcards.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class PlayerOG{
protected:
	 vector<Card*> hand;
	 vector<Card*> hand2;
	 string name;
   int account;
   int lastbet;
public:
	//constuctor that initializes the player
	 PlayerOG(string name){
	 	this->name = name;
	 	this->account = 500; //initilizes player to have $500 in account 
    lastbet = 0;              
	 }
	 //Get functions
	 string Getname(){
	 	return(name);
	 }
	 int Getaccount(){
	 	return(account);
	 }
   void Setaccount(int number){
   this->account = number; 
   }
   void Setbet(int bet){
   this->lastbet = bet;
   }

	 int Gethandsize(){
		return(hand.size());
	 }
   vector<Card*> Gethand(){
   return hand;
   }
	 void Printaccount(){
	 	// prints the amount of money that the player has
	 	 cout << name << " has $" << account << " in the account\n";
	 }
	 //adds a card object pointer to the hand vector
	 void delt(Card* card){
	 	hand.push_back (card);
	 }
	 //function neatly prints the cards in hand as text that resembles a playing card
	 virtual void Showhand(bool split = false){
	 		 vector<Card*> hand;
	 		vector<Card*>::iterator it; 								//iterator to iterate through hand vector
	 		 cout <<  endl;

	 		if(split){
	 			hand = this->hand2;
	 		}
	 		else{
	 			hand = this->hand;
	 		}
   	  cout << name << " Bet: "<< lastbet <<  endl; 
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		 cout << "==========     "; 						// prints the top of each card
	 	 	}
	 	 	 cout<< endl;
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		 cout << "|";
	 	 		(*it)->printValue(); 									//prints each card in the player's hand
	 	 		if((*it)->Getvalue() == 10){ 							//if statement keeps card edges in line
	 	 			 cout << "      |     ";
	 	 		}else{
	 	 			 cout << "       |     ";
	 	 		}
	 	 	}
	 	 	 cout<< endl;
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		 cout << "|        |     ";							//prints the sides of the card for the row
	 	 	}
	 	 	 cout<< endl;
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		//switch statement prints the name of the suit with the corresponding char
	 	 		switch((*it)->Getsuit()){
	 	 			case 'C':
	 	 				 cout << "|  Club  |     ";
	 	 				break;
	 	 			case 'S':
	 	 				 cout << "| Spades |     ";
	 	 				break;
	 	 			case 'H':
	 	 				 cout << "| Hearts |     ";
	 	 				break;
	 	 			case 'D':
	 	 				 cout << "|Diamonds|     ";
	 	 				break;
	 	 			default:
	 	 				break;
	 	 		}
	 	 	}
	 	 	 cout<< endl;
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		 cout << "|        |     ";							//prints the sides of the card for the row
	 	 	}
	 	 	 cout<< endl;
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		if((*it)->Getvalue() == 10){							//if statement keeps card edges in line
	 	 			 cout << "|      ";
	 	 		}else{
	 	 			 cout << "|       ";
	 	 		}
	 	 		(*it)->printValue(); 									//prints the value of each card in the player's hand
	 	 		 cout << "|     ";									//prints card side and spaces for the next card
	 	 	}
	 	 	 cout <<  endl;
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		 cout << "==========     ";							//prints the bottom row for each card
	 	 	}
	 	 	 cout<< endl;
	 	 }

	 void clearhand(){
	 	vector<Card*>::iterator it; //iterator to iterate through hand vector
	 	for (it = hand.begin(); it != hand.end(); it++){
	 		delete *it; //delete the card pointer for each card in hand
	 	}
	 	hand.clear(); // makes entire hand empty
	 }

	 int Placebet(){
 	
	 	// removes money from players account and returns what they bet 
	 	int amount; // initializes amount variable
     while(true)
     {
	 	   cout << "How much would you like to bet min is $2 max is $500\n";
		   cin >> amount;
	 	  if (account < amount){ //makes sure player is betting money that they have 
        cout << "You only have $" << account << " You can't bet more\n";
 		  }
 		  else if(amount<2){  //makes sure player is betting above the minimum
        cout << "The minimum bet is $2\n";
 		  }
 		  else if(amount>500){ //makes sure player is betting below the maximum
        cout << "The maximum bet is $500\n";
 		  }
 		  else{
 			  account -= amount; // takes the players bet out of their account 
 		  	return amount; // returns nonzero number to break the bet input loop
      }
 		}
	 }

	 void Securebag(int amount){
 	
	 	account += amount;  //adds winning to account 
	 }

	~PlayerOG(){};
	
};
class DealerOG : public PlayerOG{
private:

public:
	// dealer consturctor calls player constructor 
	DealerOG( string name):PlayerOG(name){
	}
	~DealerOG(){
	}

	virtual void Showhand(bool split = false){
	 		 vector<Card*> hand;
	 		vector<Card*>::iterator it; 								//iterator to iterate through hand vector
	 		 cout <<  endl;

	 		if(split){
	 			hand = this->hand2;
	 		}
	 		else{
	 			hand = this->hand;
	 		}
   	  cout << name <<  endl; 
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		 cout << "==========     "; 						// prints the top of each card
	 	 	}
	 	 	 cout<< endl;
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		 cout << "|";
	 	 		(*it)->printValue(); 									//prints each card in the player's hand
	 	 		if((*it)->Getvalue() == 10){ 							//if statement keeps card edges in line
	 	 			 cout << "      |     ";
	 	 		}else{
	 	 			 cout << "       |     ";
	 	 		}
	 	 	}
	 	 	 cout<< endl;
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		 cout << "|        |     ";							//prints the sides of the card for the row
	 	 	}
	 	 	 cout<< endl;
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		//switch statement prints the name of the suit with the corresponding char
	 	 		switch((*it)->Getsuit()){
	 	 			case 'C':
	 	 				 cout << "|  Club  |     ";
	 	 				break;
	 	 			case 'S':
	 	 				 cout << "| Spades |     ";
	 	 				break;
	 	 			case 'H':
	 	 				 cout << "| Hearts |     ";
	 	 				break;
	 	 			case 'D':
	 	 				 cout << "|Diamonds|     ";
	 	 				break;
	 	 			default:
	 	 				break;
	 	 		}
	 	 	}
	 	 	 cout<< endl;
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		 cout << "|        |     ";							//prints the sides of the card for the row
	 	 	}
	 	 	 cout<< endl;
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		if((*it)->Getvalue() == 10){							//if statement keeps card edges in line
	 	 			 cout << "|      ";
	 	 		}else{
	 	 			 cout << "|       ";
	 	 		}
	 	 		(*it)->printValue(); 									//prints the value of each card in the player's hand
	 	 		 cout << "|     ";									//prints card side and spaces for the next card
	 	 	}
	 	 	 cout <<  endl;
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		 cout << "==========     ";							//prints the bottom row for each card
	 	 	}
	 	 	 cout<< endl;
	 	 }
};
