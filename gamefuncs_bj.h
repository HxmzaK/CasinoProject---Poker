#pragma once
#include "deckofcards.h"
#include "player_bj.h"
#include <iostream>
#include <vector> 
#include <algorithm> // for random random_shuffle
#include <random>
#include <time.h>
#include "baseclass.h"
using namespace std;

class Blackjack: public Game{
public:

	Blackjack(int id):Game(id){}
	
	void Makedeck(vector<Card*>& deck){ //passed by reference so it changes the original vector 
		//AJ
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
		//AJ
		vector<Card*>::iterator it; //iterator to iterate through deck vector
		 	for (it = deck.begin(); it != deck.end(); it++){
		 		delete *it; // deletes each pointer in deck
		 	}
		 	deck.clear(); // clears deck 
	}

	void Deal(vector<Card*>& deck, Player_BJ& player, bool split = false){
		//AJ
		if(split){
			player.delt(deck.back(),true);//gives player card from the back of the deck
			deck.pop_back(); // removes card delt  card from deck
		}
		else{
			player.delt(deck.back());//gives player card from the back of the deck
			deck.pop_back(); // removes card delt  card from deck
		}
	}
	void Shuffle(vector<Card*>& deck){
		//AJ
		srand(time(0)); // seeds random so there is a different shuffle every time prgm is run
		// auto rng = std::default_random_engine {};
		random_shuffle(deck.begin(), deck.end()); // randomly shuffels the deck
	}

	//Nick
	bool checkWinLoss(Player_BJ& player, bool split = false){		//determines if hand is over 21
		int test;
		if (split){
			test = player.sumofhand(split); //gets the sum of a players hand to compare to 21
		}
		else{
			test = player.sumofhand(); //gets the sum of a players hand to compare to 21
		}
		if(test > 21){
			return false;
		}else if(test == 21){
			return true;
		}else{
			return true;
		}
	}
	//Nick
	void userTurn(vector<Card*>& deck, Player_BJ& player, bool split = false){
		int uInput = 0;
		if(split){ 	

			player.Showhand(split); // shows split hand 													// user input variable
			while(uInput != 2 && checkWinLoss(player,split) == true){					//repeat until the user choses to stay
				std::cout << "\n\nWhat would you like to do:" << std::endl;
				std::cout << "\t1. Hit" << std::endl;
				std::cout << "\t2. Stay" << std::endl;
				std::cin >> uInput;
				switch(uInput){ 												//switch statement does different actions dependent on user input
					case 1:
						std::cout<<std::endl;
						std::cout<<"hit! ";
						Deal(deck, player, split);
						player.Showhand(split);
						//std::cout << std::endl;
						break;
					case 2:
						break;
				}
			}//ends while loop
		}//ends split if statement
		else{
			player.Showhand(); // shows hain hand
			while(uInput != 2 && checkWinLoss(player) == true){					//repeat until the user choses to stay
				std::cout << "\n\nWhat would you like to do:" << std::endl;
				std::cout << "\t1. Hit" << std::endl;
				std::cout << "\t2. Stay" << std::endl;
				std::cin >> uInput;
				switch(uInput){ 												//switch statement does different actions dependent on user input
					case 1:
						std::cout<<std::endl;
						std::cout<<"hit! ";
						Deal(deck, player);
						player.Showhand();
						//std::cout << std::endl;
					break;
					case 2:
						break;
				}//ends switch
			}//ends while loop
		}//ends split else statement
		
		
	}

	//Nick
	void dealerTurn(vector<Card*>& deck, Player_BJ& player){ 
		while(player.sumofhand() <= 16){									//the dealer has to hit if <= 16
					std::cout <<std::endl<<"Dealer hit! Now showing: " << player.sumofhand() <<std::endl;
					Deal(deck, player);
					player.Showhand(); 										// shows the dealers hand
					std::cout << std::endl;
		}
	}

	void Betcalc(Player_BJ& player, int amount,int result){
		//AJ
		switch(result){
			case 0:{
				player.AddLossPlayer();// adds a loss to the players record
				AddWin();
				AddAmountwon(amount); //adds amount won to the game's total
				break;
			} 
			case 1:{
				player.Securebag(amount*2); //doubles the players bet
				player.AddWinPlayer(); //adds a win to the counter
				AddLoss();//adds a loss to the game total
				AddAmountLost(amount); //takes out the amount the house lost 
				break;
			}
			case 2:{
				player.Securebag(amount); // gives the player their money back if push
				break;
			}
			case 3:{
				player.Securebag(amount*2.5); //if player gets a natural they get 2.5x their money back
				player.AddWinPlayer(); //adds a win to the counter
				AddLoss();//adds a loss to the game total
				AddAmountLost(amount*1.5); // house loses 1.5x the bet amount on a natural
				break;
			}
		}
	}

	//Nick
	void determineWinner(Player_BJ& player,Dealer_BJ& dealer, int bet, bool split = false){			//determines who has the higher value under 21
		dealer.showAll();
		player.Showhand(split);
		std::cout<<std::endl;
		//does this first if statement no matter if splitting or not 
		if(player.sumofhand(split) > dealer.sumofhand() && dealer.sumofhand() <= 21 && player.sumofhand(split) <= 21){
				std::cout << "You win!" << std::endl;
				Betcalc(player,bet,1);										//distributes winnings to the player
			}else if(player.sumofhand(split) < dealer.sumofhand()){
				std::cout << "Dealer Wins, you lose!" << std::endl;
				Betcalc(player,bet,0); 										//does nothing taking the players money
			}else if(player.sumofhand(split) == dealer.sumofhand()){
				std::cout << "push" << std::endl;
				Betcalc(player,bet,2); 										//gives player their money back
			}else{
				if(checkWinLoss(player,split) == false){
					std::cout << "You busted, you lose!" << std::endl;
					Betcalc(player,bet,0); 									//does nothing taking the players money
				}else if(player.sumofhand(split) < 21){
					std::cout << "Dealer busted, you WIN!" << std::endl;
					Betcalc(player,bet,1); 									//distributes winnings to the player
				}
		}
		if(split){ // if spliting then the function will determine the winner of the other hand aswell 
			player.Showhand();
			std::cout<<std::endl;
			if(player.sumofhand() > dealer.sumofhand() && dealer.sumofhand() <= 21 && player.sumofhand() <= 21){
					std::cout << "You win!" << std::endl;
					Betcalc(player,bet,1);										//distributes winnings to the player
				}else if(player.sumofhand() < dealer.sumofhand()){
					std::cout << "Dealer Wins, you lose!" << std::endl;
					Betcalc(player,bet,0); 										//does nothing taking the players money
				}else if(player.sumofhand() == dealer.sumofhand()){
					std::cout << "push" << std::endl;
					Betcalc(player,bet,2); 										//gives player their money back
				}else{
					if(checkWinLoss(player) == false){
						std::cout << "You busted, you lose!" << std::endl;
						Betcalc(player,bet,0); 									//does nothing taking the players money
					}else if(player.sumofhand() < 21){
						std::cout << "Dealer busted, you WIN!" << std::endl;
						Betcalc(player,bet,1); 									//distributes winnings to the player
					}
			}
		}//end of if split

		player.Printaccount();  // prints the money that the player has now
	}


};
