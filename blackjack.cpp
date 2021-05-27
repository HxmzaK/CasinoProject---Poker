//
//
//
//Blackjack
//Written by AJ McMartin & Nick Ferrara
//
//
#include "deckofcards.h"
#include "player.h"
#include <iostream>
#include <vector> 
#include <algorithm> // for random random_shuffle
#include <random>
using namespace std;


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

void Deal(vector<Card*>& deck, Player& player){
	//AJ
	player.delt(deck.back());//gives player card from the back of the deck
	deck.pop_back(); // removes card delt  card from deck
}
void Shuffle(vector<Card*>& deck){
	//AJ
	// srand(ftime(0)); // seeds random so there is a different shuffle every time prgm is run
	auto rng = std::default_random_engine {};
	shuffle(deck.begin(), deck.end(), rng); // randomly shuffels the deck
}

//Nick
bool checkWinLoss(Player& player){		//determines if hand is over 21
	int test = player.sumofhand(); //gets the sum of a players hand to compare to 21
	if(test > 21){
		return false;
	}else if(test == 21){
		return true;
	}else{
		return true;
	}
}
//Nick
void userTurn(vector<Card*>& deck, Player& player){
	int uInput; 														// user input variable
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
		}
	}
}

//Nick
void dealerTurn(vector<Card*>& deck, Player& player){ 
	while(player.sumofhand() <= 16){									//the dealer has to hit if <= 16
				std::cout <<std::endl<<"Dealer hit! Now showing: " << player.sumofhand() <<std::endl;
				Deal(deck, player);
				player.Showhand(); 										// shows the dealers hand
				std::cout << std::endl;
	}
}

void Betcalc(Player& player, int amount,int result){
	//AJ
	switch(result){
		case 0: break;
		case 1:{
			player.Securebag(amount*2); //doubles the players bet
			break;
		}
		case 2:{
			player.Securebag(amount); // gives the player their money back if push
			break;
		}
		case 3:{
			player.Securebag(amount*2.5); //if player gets a natural they get 2.5x their money back
		}
	}
}

//Nick
void determineWinner(Player& player,Dealer& dealer, int bet){			//determines who has the higher value under 21
	dealer.showAll();
	player.Showhand();
	std::cout<<std::endl;
	if(player.sumofhand() > dealer.sumofhand() && dealer.sumofhand() <= 21 && player.sumofhand() <= 21){
			std::cout << "You win!" << std::endl;
			Betcalc(player,bet,1);										//distributes winnings to the player
			player.Printaccount(); 										// prints the money that the player has now
		}else if(player.sumofhand() < dealer.sumofhand()){
			std::cout << "Dealer Wins, you lose!" << std::endl;
			Betcalc(player,bet,0); 										//does nothing taking the players money
			player.Printaccount(); 										// prints the money that the player has now
		}else if(player.sumofhand() == dealer.sumofhand()){
			std::cout << "push" << std::endl;
			Betcalc(player,bet,2); 										//gives player their money back
			player.Printaccount();										// prints the money that the player has now
		}else{
			if(checkWinLoss(player) == false){
				std::cout << "You busted, you lose!" << std::endl;
				Betcalc(player,bet,0); 									//does nothing taking the players money
				player.Printaccount(); 									// prints the money that the player has now
			}else if(player.sumofhand() < 21){
				std::cout << "dealer busted, you WIN!" << std::endl;
				Betcalc(player,bet,1); 									//distributes winnings to the player
				player.Printaccount(); 									// prints the money that the player has now
			}
	}
}



int main(){
	int keepPlaying = 1;
	int bet = 0; 										// initializes bet to 0 so so bet loop will start
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
			std::cout << "Congratulations you got a natural\n";
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

			userTurn(deck,player1);
			//dealerTurn(deck,deal);


			//Nick
			if(checkWinLoss(player1) == false){						//if player1 < 21 dealer takes their turn
			}else{
				dealerTurn(deck,deal);
			}
			if(checkWinLoss(deal) == false){						// if dealer didnt bust determine winner
				deal.showAll();
				std::cout<<std::endl;
				std::cout<<"Dealer Busted" <<std::endl;
				std::cout << "You Win!" << std::endl;
				Betcalc(player1,bet,1); //distributes winnings to the player
				player1.Printaccount(); // prints the money that the player has now
			}else if (checkWinLoss(deal) == true){
				determineWinner(player1,deal,bet);
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



		
