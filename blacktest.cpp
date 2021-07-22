#include "deckofcards.h"
#include "player.h"
#include "gamefuncs_bj.h"
#include <iostream>
#include <vector> 
#include <algorithm> // for random random_shuffle
#include <random>
#include <time.h>
using namespace std;




void TestSplit(){
	vector<Card*> deck;
	Makedeck(deck);
	int uin;//user input varible 
	Player player1("Tester");
	char suit[4] = {'C','S','H','D'};//the 4 suits represented by caps
	char face[4] = {'J','Q','K','A'};// the 4 symbols to represent each face card
	
	int bet = 0;
	while (bet==0){
		//AJ
		// continues to ask palyer to enter bet until it is acceptable
			bet = player1.Placebet();
		}
	std::cout << "same value: ";
	player1.delt(new Card(2,suit[0])); // creates the number cards for the suit starts at 2
	player1.delt(new Card(2,suit[1]));
	player1.Showhand();
	if(player1.CheckSplit()){
		std::cout << "True\n\n";
	}
	else{std::cout << "False\n\n";}
	player1.clearhand();

	std::cout << "different value: ";
	player1.delt(new Card(2,suit[0])); // creates the number cards for the suit starts at 2
	player1.delt(new Card(3,suit[1]));
	player1.Showhand();
	if(player1.CheckSplit()){
		std::cout << "True\n\n";
	}
	else{std::cout << "False\n\n";}
	player1.clearhand();


	std::cout << "same face: ";
	player1.delt(new FaceCard(face[0],suit[2]));
	player1.delt(new FaceCard(face[0],suit[3]));
	player1.Showhand();
	if(player1.CheckSplit()){
		std::cout << "True\n\n";
	}
	else{std::cout << "False\n\n";}
	player1.clearhand();

	std::cout << "different face: ";
	player1.delt(new FaceCard(face[0],suit[2]));
	player1.delt(new FaceCard(face[0],suit[3]));
	player1.Showhand();
	if(player1.CheckSplit()){
		std::cout << "True\n\n";
		std::cout << "Would you like to split enter 1 for yes 0 for no\n"; 
		std::cin >> uin;
		if(uin==1){
			player1.Split();
		}
	}
	else{std::cout << "False\n\n";}
	player1.clearhand();


	std::cout << "same face: ";
	player1.delt(new FaceCard(face[0],suit[2]));
	player1.delt(new FaceCard(face[0],suit[3]));
	player1.Showhand();
	if(player1.CheckSplit()){
		std::cout << "True\n\n";
		std::cout << "Would you like to split enter 1 for yes 0 for no\n"; 
		std::cin >> uin;
		if(uin==1){
			player1.Split();
		}
	}
	else{std::cout << "False\n\n";}
	player1.clearhand();
	int uInput; 														// user input variable
	while(uInput != 2 && checkWinLoss(player1) == true){					//repeat until the user choses to stay
		std::cout << "\n\nWhat would you like to do:" << std::endl;
		std::cout << "\t1. Hit" << std::endl;
		std::cout << "\t2. Stay" << std::endl;
		std::cin >> uInput;
		switch(uInput){ 												//switch statement does different actions dependent on user input
			case 1:
				std::cout<<std::endl;
				std::cout<<"hit! ";
				Deal(deck, player1);
				player1.Showhand();
				//std::cout << std::endl;
			break;
			case 2:
				break;
		}
	}

}


void Testriggedbj(){
	char suit[4] = {'C','S','H','D'};//the 4 suits represented by caps
	char face[4] = {'J','Q','K','A'};// the 4 symbols to represent each face card

	int keepPlaying = 1;
	int bet = 0; 										// initializes bet to 0 so so bet loop will start
	bool split = false; 	//initializes split as false									
	string name;
	std::cout << "Enter your name: ";
	std::getline(cin, name); 							// user input for their name
	Player player1(name);
	Dealer deal("Dealer"); 								// creates a dealer named dealer
	vector <Card*> deck;								// initiates vector that will become the deck
	Makedeck(deck);										//adds all the cards to the deck

	while(keepPlaying == 1){ // loop that the user can break when done playong 

			if (deck.size() < 20){ // reshuffles deck when there is less than 20 cards in the deck
				//AJ
				std::cout << "Reshuffling the Deck\n";
				Deletedeck(deck); // deletes what is left from old deck
				Makedeck(deck); //make a whole new deck 
			}
		
		
		Shuffle(deck); //shuffles the deck before each round 
		player1.Printaccount();//tell player how much they have before they bet 
		
		while (bet==0){
		//AJ
		// continues to ask palyer to enter bet until it is acceptable
			bet = player1.Placebet();
		}
		
		//deals first to cards to player and dealer 
		deal.delt(new Card(2,suit[0])); // creates the number cards for the suit starts at 2
		deal.delt(new Card(2,suit[1]));
		player1.delt(new FaceCard(face[0],suit[2]));
		player1.delt(new FaceCard(face[0],suit[3]));

	
		if (player1.sumofhand()==21){
			//AJ
			player1.Showhand();
			std::cout << "Congratulations you got a Blackjack!!\n";
			Betcalc(player1,bet,3); //distributes winnings to the player
			player1.Printaccount(); // prints the money that the player has now
		}
		else{
			//Nick
			std::cout<<std::endl;
			std::cout <<"Dealer showing: " << std::endl;
			deal.Showhand();
			std::cout << std::endl;
			std::cout << std::endl;
			player1.Showhand();
			std::cout << std::endl;

			if(player1.CheckSplit()){
				std::cout << "Would you like to split (y/n)\n";
				char schoice;
				std::cin>> schoice;
				switch(schoice){
					case 'y': {
						std::cout << "splitting\n";
						player1.Split();
						Deal(deck, player1, true);
						Deal(deck, player1);
						split = true;
						break;

					}
					case 'n': {
						break;
					}
					default:{
						std::cout << "invalid input your not splitting\n";
						break;
					}

				}
			}//ends check split if

			if(split){
				userTurn(deck,player1,true);
				cout << "finished turn 1\n";
				userTurn(deck,player1,false);
				cout << "finished turn 2\n";
				
			}
			else{
				userTurn(deck,player1,false);
			}
			
			//dealerTurn(deck,deal);


			//Nick
			if((checkWinLoss(player1) == false) || (checkWinLoss(player1,split) == false) ){						//if player1 < 21 dealer takes their turn
			}else{
				dealerTurn(deck,deal);
			}
			if(checkWinLoss(deal) == false){						// if dealer didnt bust determine winner
				deal.showAll();
				std::cout<<std::endl;
				std::cout<<"Dealer Busted" <<std::endl;
				std::cout << "You Win!" << std::endl;
				Betcalc(player1,bet,1); //distributes winnings to the player
				if(split){
					Betcalc(player1,bet,1);//gives second hand money too
				}
				player1.Printaccount(); // prints the money that the player has now
			}else if (checkWinLoss(deal) == true){
				determineWinner(player1,deal,bet,split);
			}



			if (player1.Getaccount()<2){
				//AJ
				//if player is out of money then it ends the program
				std::cout << "You have run out of so you cant play anymore\n";  
				
			}
		}

		
		//Nick

		std::cout << "Do you want to play again?" << std::endl;
		std::cout << "\t1. Yes" << std::endl;
		std::cout << "\t2. Cash out" << std::endl;
		std::cin >> keepPlaying;
		player1.clearhand();
		deal.clearhand();
		bet = 0; // resets bet to 0


	}

	if (player1.Getaccount()>= 500){ // checks if player won or lost money
		//AJ
		std::cout << "Congratulations you won $" << player1.Getaccount()-500 << std::endl;
	}
	else{
		std::cout << "You finished with $" << player1.Getaccount() << " in your account\n";
	}
}


int main(){
	
	Testriggedbj();
	return 0;
}