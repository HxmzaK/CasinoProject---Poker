//
//
//
//Blackjack
//Written by AJ McMartin & Nick Ferrara
//
//
#include "deckofcards.h"
#include "player.h"
#include "gamefuncs_bj.h"
#include <iostream>
#include <vector> 
#include <algorithm> // for random random_shuffle
#include <random>
#include <time.h>
using namespace std;





int main(){
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

	//Nick
	//got the ASCII wording from this generator
	//http://patorjk.com/software/taag/#p=display&f=3D%20Diagonal&t=Type%20Something%20
	std::cout<<std::endl;
	std::cout<<"   ________   ___        ________   ________   ___  __           ___   ________   ________   ___  __"<<std::endl;
	std::cout<<"  |\\   __  \\ |\\  \\      |\\   __  \\ |\\   ____\\ |\\  \\|\\  \\        |\\  \\ |\\   __  \\ |\\   ____\\ |\\  \\|\\  \\" <<std::endl;
	std::cout<<"  \\ \\  \\|\\ /_\\ \\  \\     \\ \\  \\|\\  \\\\ \\  \\___| \\ \\  \\/  /|_      \\ \\  \\\\ \\  \\|\\  \\\\ \\  \\___| \\ \\  \\/  /|_"<<std::endl;
	std::cout<<"   \\ \\   __  \\\\ \\  \\     \\ \\   __  \\\\ \\  \\     \\ \\   ___  \\   __ \\ \\  \\\\ \\   __  \\\\ \\  \\     \\ \\   ___  \\ "<<std::endl;
	std::cout<<"    \\ \\  \\|\\  \\\\ \\  \\____ \\ \\  \\ \\  \\\\ \\  \\____ \\ \\  \\\\ \\  \\ |\\  \\\\_\\  \\\\ \\  \\ \\  \\\\ \\  \\____ \\ \\  \\\\ \\  \\"<<std::endl;
	std::cout<<"     \\ \\_______\\\\ \\_______\\\\ \\__\\ \\__\\\\ \\_______\\\\ \\__\\\\ \\__\\\\ \\________\\\\ \\__\\ \\__\\\\ \\_______\\\\ \\__\\\\ \\__\\"<<std::endl;
	std::cout<<"      \\|_______| \\|_______| \\|__|\\|__| \\|_______| \\|__| \\|__| \\|________| \\|__|\\|__| \\|_______| \\|__| \\|__|"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"       ___        ___   _   _     _ _  _       _   "<<std::endl;
	std::cout<<"      | . > _ _  | . | | | < >   | \\ |<_> ___ | |__"<<std::endl;
	std::cout<<"      | . \\| | | |   |_| | /.\\/  |   || |/ | '| / /"<<std::endl;
	std::cout<<"      |___/`_. | |_|_|\\__/ \\_/\\  |_\\_||_|\\_|_.|_\\_\\"<<std::endl;
	std::cout<<"           <___'  "<<std::endl;

	//instructions
	std::cout<<std::endl;
	std::cout << "\n\nWelcome to Black Jack! The rules are simple try to get as close as possible to 21 without goingover.";
	std::cout << " Before every game you must make a bet. The minimm bet is $2 and the maximum is $500. If you win you double your money if you lose you lose it all.";
	std::cout << " if you are delt an Ace and a Face card on the first deal you get a natural and will win 1.5x your bet.";
	std::cout << " You have $500 to start. Good luck!\n\n\n";

	
	while(keepPlaying == 1){ // loop that the user can break when done playong 

		split = false; //needs to reset split at the start of each loop
			
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
		Deal(deck,player1);
		Deal(deck,deal);
		Deal(deck,player1);
		Deal(deck,deal);

	
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
						player1.Split();
						split = true;
						Deal(deck, player1, true); // dealsa a card to each hand
						Deal(deck, player1);
						userTurn(deck,player1,split);
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

			userTurn(deck,player1);
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
				return 0;
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
	
	return 0;
}



		
