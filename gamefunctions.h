#pragma once
#include "deckofcards.h"
#include "player.h"
#include <iostream>
#include <vector> 
#include <algorithm> // for random random_shuffle
#include <random>
#include <time.h>
using namespace std;

void Deal(vector<Card*>& deck, Player& player, bool split = false){
	if(split){
		player.delt(deck.back(),true);//gives player card from the back of the deck
		deck.pop_back(); // removes card delt  card from deck
	}
	else{
		player.delt(deck.back());//gives player card from the back of the deck
		deck.pop_back(); // removes card delt  card from deck
	}
}
bool checkWinLoss(Player& player, bool split = false){		//determines if hand is over 21
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

void determineWinner(Player& player,Dealer& dealer, int bet, bool split = false){			//determines who has the higher value under 21
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