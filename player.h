#pragma once
#include "deckofcards.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;





class Player{
protected:
	//AJ
	std::vector<Card*> hand;
	std::vector<Card*> hand2;
	std::string name;
	int account;
	int lastbet;
public:
	//constuctor that initializes the player
	 Player(string name){
	 	//AJ
	 	this->name = name;
	 	this->account = 500; //initilizes palyer to have $500 in account 
	 }
	 //Get functions
	 string Getname(){
	 	//AJ
	 	return(name);
	 }
	 int Getaccount(){
	 	//AJ
	 	return(account);
	 }

	 int Gethandsize(){
		return(hand.size());
	 }

	 bool CheckSplit(){
	 	if(account < lastbet){ // checks if you have enough money to split
	 		return false;
	 	}
		if (Gethandsize()==2){
			if((*hand.begin())->Getcardtype()==1){
					return((*hand.begin())->Getsymbol() == (*(hand.begin()+1))->Getsymbol());
				}
			if((*hand.begin())->Getvalue() == (*(hand.begin()+1))->Getvalue())
				return(true);			
		}
		return false;
	 }

	 void Split(){
	 	hand2.push_back(hand.pop_back());
	 	account-=lastbet;	
	 }

	 void Printaccount(){
	 	//AJ
	 	// prints the amount of money that the player has
	 	std::cout << name << " has $" << account << " in the account\n";
	 }
	 //adds a card object pointer to the hand vector
	 void delt(Card* card){
	 	//AJ
	 	hand.push_back(card);
	 }

	 //Nick
	 //function neatly prints the cards in hand as text that resembles a playing card
	 virtual void Showhand(bool split = false){
	 		std::vector<Card*> hand;
	 		vector<Card*>::iterator it; 								//iterator to iterate through hand vector
	 		std::cout << std::endl;

	 		if(split){
	 			hand = this->hand2;
	 		}
	 		else{
	 			hand = this->hand;
	 		}
	 	 	
	 	 	cout << name << " has: "<< sumofhand() <<std::endl;
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		std::cout << "==========     "; 						// prints the top of each card
	 	 	}
	 	 	std::cout<<std::endl;
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		std::cout << "|";
	 	 		(*it)->printValue(); 									//prints each card in the player's hand
	 	 		if((*it)->Getvalue() == 10){ 							//if statement keeps card edges in line
	 	 			std::cout << "      |     ";
	 	 		}else{
	 	 			std::cout << "       |     ";
	 	 		}
	 	 	}
	 	 	std::cout<<std::endl;
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		std::cout << "|        |     ";							//prints the sides of the card for the row
	 	 	}
	 	 	std::cout<<std::endl;
	 	 	//Nick
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		//switch statement prints the name of the suit with the corresponding char
	 	 		switch((*it)->Getsuit()){
	 	 			case 'C':
	 	 				std::cout << "|  Club  |     ";
	 	 				break;
	 	 			case 'S':
	 	 				std::cout << "| Spades |     ";
	 	 				break;
	 	 			case 'H':
	 	 				std::cout << "| Hearts |     ";
	 	 				break;
	 	 			case 'D':
	 	 				std::cout << "|Diamonds|     ";
	 	 				break;
	 	 			default:
	 	 				break;
	 	 		}
	 	 	}
	 	 	//Nick
	 	 	std::cout<<std::endl;
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		std::cout << "|        |     ";							//prints the sides of the card for the row
	 	 	}
	 	 	std::cout<<std::endl;
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		if((*it)->Getvalue() == 10){							//if statement keeps card edges in line
	 	 			std::cout << "|      ";
	 	 		}else{
	 	 			std::cout << "|       ";
	 	 		}
	 	 		(*it)->printValue(); 									//prints the value of each card in the player's hand
	 	 		std::cout << "|     ";									//prints card side and spaces for the next card
	 	 	}
	 	 	std::cout << std::endl;
	 	 	for (it = hand.begin(); it != hand.end(); it++){
	 	 		std::cout << "==========     ";							//prints the bottom row for each card
	 	 	}
	 	 	std::cout<<std::endl;
	 	 }

	 void clearhand(){
	 	//AJ
	 	vector<Card*>::iterator it; //iterator to iterate through hand vector
	 	for (it = hand.begin(); it != hand.end(); it++){
	 		delete *it; //delete the card pointer for each card in hand
	 	}
	 	hand.clear(); // makes entire hand empty
	 }

	 //Nick
	 int sumofhand(){
		int sum = 0; 													//initializes sum as 0
	 	vector<Card*>::iterator it; 									//iterator to iterate through hand vector
	 	for (it = hand.begin(); it != hand.end(); it++){
	 		sum += (*it)->Getvalue(); 									//ads the value of each card to the sum
	 	}
	 	if(sum > 21){ 													//sets the value of ace to 1 if needed otherwise its an 11
	 		//Nick
	 		for (it = hand.begin(); it != hand.end(); it++){  
	 			if((*it)->Getsymbol() == 'A'){
	 				(*it)->Setvalue(1); 								// changes the value of the Ace
	 				sum = 0; 											// resets the sum to 0
	 				for (it = hand.begin(); it != hand.end(); it++){
	 					sum += (*it)->Getvalue(); 						// recalculates the sum with new value of Ace
	 				}
	 				break; 
	 			}
	 		}

	 	}
	 	return(sum);
	 }

	 int Placebet(){
	 	//AJ
	 	// removes money from players account and returns what they bet 
	 	int amount; // initializes amount variable
	 	std::cout << "How much would you like to bet min is $2 max is $500\n";
		std::cin >> amount;
	 	if (account < amount){ //makes sure player is betting money that they have 
 			std::cout << "You only have $" << account << " You can't bet more\n";
 			return 0; // returns 0 so the bet loop will ask for palyers bet again
 		}
 		else if(amount<2){  //makes sure player is betting above the minimum
 			std::cout << "The minimum bet is $2\n";
 			return 0; // returns 0 so the bet loop will ask for palyers bet again
 		}
 		else if(amount>500){ //makes sure player is betting below the maximum
 			std::cout << "The maximum bet is $500\n";
 			return 0; // returns 0 so the bet loop will ask for palyers bet again
 		}
 		else{
 			account -= amount; // takes the players bet out of their account 
 			lastbet = amount; // saves the last bet so program can take out same amount if split
 			return amount; // returns nonzero number to break the bet input loop
 		}
	 }

	 void Securebag(int amount){
	 	//AJ
	 	account += amount;  //adds winning to account 
	 }

	~Player(){};
	
};



class Dealer : public Player{
private:

public:
	// dealer consturctor calls player constructor 
	Dealer(std::string name):Player(name){
	}
	~Dealer(){
	}

	//Nick
	void Showhand(){												//hides one of the cards for dealer
			vector<Card*>::iterator it; 							//iterator to iterate through hand vector
		 	for (it = hand.begin(); it != hand.end()-1; it++){ 		//iterates through dealrs hand except the last card
		 		std::cout << "==========     ";						// prints the top of each card
		 	}
		 	std::cout << "==========     "; 						// prints the top of hidden card
		 	std::cout<<std::endl;
		 	for (it = hand.begin(); it != hand.end()-1; it++){ 		//iterates through dealrs hand except the last card
		 		//std::cout << "=========     ";
		 		std::cout << "|";
		 		(*it)->printValue(); 								//prints each card in the player's hand
		 		if((*it)->Getvalue() == 10){ 						//if statement keeps card edges in line
		 			std::cout << "      |     ";
		 		}else{
		 			std::cout << "       |     ";
		 		}
		 	}
		 	std::cout << "|        |     ";
		 	std::cout<<std::endl;
		 	for (it = hand.begin(); it != hand.end()-1; it++){ 		//iterates through dealrs hand except the last card
		 		std::cout << "|        |     "; 					//prints the sides of the card for the row
		 	}
		 	std::cout << "|        |     "; 						//prints the sides of the hidden card for the row
		 	std::cout<<std::endl;
		 	for (it = hand.begin(); it != hand.end()-1; it++){ 		//iterates through dealrs hand except the last card


		 		//Nick
		 		//switch statement prints the name of the suit with the corresponding char
		 		switch((*it)->Getsuit()){
		 			case 'C':
		 				std::cout << "|  Club  |     ";
		 				break;
		 			case 'S':
		 				std::cout << "| Spades |     ";
		 				break;
		 			case 'H':
		 				std::cout << "| Hearts |     ";
		 				break;
		 			case 'D':
		 				std::cout << "|Diamonds|     ";
		 				break;
		 			default:
		 				break;
		 		}
		 	}
		 	std::cout << "| Hidden |     ";
		 	std::cout<<std::endl;
		 	for (it = hand.begin(); it != hand.end()-1; it++){ 					//iterates through dealrs hand except the last card
		 		std::cout << "|        |     "; 								//prints the sides of the card for the row
		 	}
		 	std::cout << "|        |     "; 									//prints the sides of the hidden card for the row
		 	std::cout<<std::endl;
		 	for (it = hand.begin(); it != hand.end()-1; it++){ 					//iterates through dealrs hand except the last card
		 		if((*it)->Getvalue() == 10){
		 			std::cout << "|      ";
		 		}else{
		 			std::cout << "|       ";
		 		}
		 		(*it)->printValue(); 											//prints each card in the Dealer's han
		 		std::cout << "|     ";
		 	}
		 	std::cout << "|        |     ";
		 	std::cout << std::endl;
		 	for (it = hand.begin(); it != hand.end()-1; it++){ 					//iterates through dealrs hand except the last card
		 		std::cout << "==========     "; 								// Prints the bottom of each card
		 	}
		 	std::cout << "==========     "; 									// Prints the bottom of hidden card
		 	std::cout<<std::endl;
		 }
	//Nick
	void showAll(){
			vector<Card*>::iterator it;
		 	std::cout<<std::endl;
			std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
			std::cout << std::endl;
			cout << name << " has: "<< sumofhand() <<std::endl;
		 	for (it = hand.begin(); it != hand.end(); it++){
		 		std::cout << "==========     ";
		 	}
		 	std::cout<<std::endl;
		 	for (it = hand.begin(); it != hand.end(); it++){
		 		//std::cout << "=========     ";
		 		std::cout << "|";
		 		(*it)->printValue(); 									//prints each card in the Dealer's han
		 		if((*it)->Getvalue() == 10){ 							//if statement keeps card edges in line
		 			std::cout << "      |     ";
		 		}else{
		 			std::cout << "       |     ";
		 		}
		 	}
		 	std::cout<<std::endl;
		 	for (it = hand.begin(); it != hand.end(); it++){
		 		std::cout << "|        |     "; 						//prints the sides of the card for the row
		 	}
		 	std::cout<<std::endl;
		 	for (it = hand.begin(); it != hand.end(); it++){
		 		//Nick
		 		//switch statement prints the name of the suit with the corresponding char
		 		switch((*it)->Getsuit()){
		 			case 'C':
		 				std::cout << "|  Club  |     ";
		 				break;
		 			case 'S':
		 				std::cout << "| Spades |     ";
		 				break;
		 			case 'H':
		 				std::cout << "| Hearts |     ";
		 				break;
		 			case 'D':
		 				std::cout << "|Diamonds|     ";
		 				break;
		 			default:
		 				break;
		 		}
		 	}
		 	std::cout<<std::endl;
		 	//Nick
		 	for (it = hand.begin(); it != hand.end(); it++){
		 		std::cout << "|        |     "; 					//prints the sides of the card for the row
		 	}
		 	std::cout<<std::endl;
		 	for (it = hand.begin(); it != hand.end(); it++){
		 		if((*it)->Getvalue() == 10){ 						//if statement keeps card edges in line
		 			std::cout << "|      ";
		 		}else{
		 			std::cout << "|       ";
		 		}
		 		(*it)->printValue(); 								//prints each card in the Dealer's hand
		 		std::cout << "|     ";
		 	}
		 	std::cout << std::endl;
		 	for (it = hand.begin(); it != hand.end(); it++){
		 		std::cout << "==========     "; 					// prints the bottom row of each card
		 	}
		 	std::cout<<std::endl;

		 }

};
