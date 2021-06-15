#include "deckofcards.h"
#include "player.h"
#include <iostream>
#include <vector> 
#include <algorithm> // for random random_shuffle
#include <random>
#include <time.h>
using namespace std;


void Deal(vector<Card*>& deck, Player& player){
	//AJ
	player.delt(deck.back());//gives player card from the back of the deck
	deck.pop_back(); // removes card delt  card from deck
}
void TestSplit(){
	Player player1("Tester");
	char suit[4] = {'C','S','H','D'};//the 4 suits represented by caps
	char face[4] = {'J','Q','K','A'};// the 4 symbols to represent each face card
	// for (int j=0;j<3;j++){ // itterates for each suit 
	// 	for(int i=2;i<10;i++){ // iterates for each normal card value
	// 		player1.delt(new Card(i,suit[j])); // creates the number cards for the suit starts at 2
	// 		player1.delt(new Card(i,suit[j]));
	// 	}
	// 	for (int i=0;i<4;i++){ // iterates for each facecard symbol
	// 		deck.push_back(new FaceCard(face[i],suit[j])); // creates each face card for the suit
	// 	}
	// }
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
	player1.delt(new FaceCard(face[1],suit[3]));
	player1.Showhand();
	if(player1.CheckSplit()){
		std::cout << "True\n\n";
	}
	else{std::cout << "False\n\n";}
	player1.clearhand();
}

int main(){
	TestSplit();
	return 0;
}