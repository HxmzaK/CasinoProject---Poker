// Craigon Confer, Roulette Casino Game
#ifndef ROULETTE_H // Header File Wrapper
#define ROULETTE_H
// Include Paths
#include <stdlib.h>
#include <time.h>
#include <sqlite3.h>
#include <vector>
#include "baseclass.h"

class Roulette:public Game, public Player // Roulette Class Declaration, inherits Player and Game Classes
{
    private:
        int number; // Number selection from 0-36
        char color; // Color selection (black or red) 

    public: // Mutators 
        void setNumberBet(int num){
            number = num;
        }
        void setColorBet(char c){
            color = c;
        }
        int getNumberBet(){
            return number;
        }
        char getColorBet(){
            return color;
        }
        char dealColor(){ // Randomize Red or Black selection
            char selection;
            int color = rand()%2 + 1;
            if (color == 1){
                selection = 'B';
            }else {
                selection = 'R';
            }
            return selection;
        }
        int dealNumber(){ // Randomize number selection 0-36
            int selection = rand()%36;
            return selection;
        }
        Roulette(int gameID, int ID, std::string n, std::string ln):Game(gameID),Player(ID, n, ln){ // Constructor for base Roulette object

        }
        ~Roulette(){ // Destructor

        } 
};

void PlayRoulette(Player &player){ // Main Game Function
    srand(time(NULL)); // Random seed for dealer selections
    // Player attributes are passed to Roulette class object
    int ID = player.getID();
    std::string name = player.getName();
    std::string lname = player.getLname();
    Roulette playerRoulette(4, ID, name, lname); // Default Game ID of 4
    int x; // Switch case for Roulette menu
    int betAmount, tempBal, newBal; // Bet manipulation variables 
    bool gameOn = true; // Condition for continuous play 
    std::cout << "Welcome to Roulette: " << name << " " << lname << "!\n"; // Welcome message
    while ((gameOn != false)){ // Loop while game is not exited by user 
        int playerBal = player.getBankAccount(); // Stores player balance and is printed to console
        std::cout << "Balance: " << playerBal << std::endl;
        std::cout << "Select 1 to place a color bet, 2 for a number bet, 3 for a column bet, or 0 to exit: ";  // Roulette selector
        std::cin >> x;
        switch(x){ // Switch case for Roulette options
            case 0: { // Player leaves game
                std::cout <<"Thanks for playing Roulette!\n";
                // Updates player wins, losses, games played, and balance to Database
                player.UpdateWins();
                player.UpdateLosses();
                player.UpdateGamesplayed();
                player.UpdateBalance(player.getBankAccount());
                gameOn = false; // Ends game loop
                break;
            }
            case 1: { // Color bet, 1:1 payout
                std::cout << "Color bet selected\n";
                std::cout << "Enter a bet amount: ";
                std::cin >> betAmount;
                if (betAmount <= 0){ // Check for invalid bet amount 
                    std::cout << "Invalid Bet Amount\n";
                    break;                   
                }
                if (betAmount> player.getBankAccount()){ // Check for invalid bet amount with respect to player balance
                    std::cout << "Invalid Bet Amount. Not enough money to bet in your balance\n";
                    break;
                }
                tempBal = player.getBankAccount()-betAmount; // Updates player balance
                player.setBankAccount(tempBal);
                std::cout << "\nEnter 'B' for black and 'R' for red: ";
                char colorSelection;
                std::cin >> colorSelection;
                playerRoulette.setColorBet(towupper(colorSelection));
                if ((playerRoulette.getColorBet() == 'B' || playerRoulette.getColorBet() == 'R')){ // Continue if valid
                }else { // Invalid color selection 
                    std::cout << "Invalid color selection\n";
                    tempBal = player.getBankAccount() + betAmount; // Return bet money to player
                    player.setBankAccount(tempBal);
                    break;
                }
                char dealerColor = playerRoulette.dealColor(); // Gets color 
                if (playerRoulette.getColorBet() == 'B'){ // Check for player input black and if they won
                    std::cout << "Black selected, goodluck!\n";
                    std::cout << "Winning color is: " << dealerColor << std::endl;
                    if (playerRoulette.getColorBet() == dealerColor){
                        std::cout << "You Won!\n";
                        newBal = (betAmount*2) + tempBal;
                        // Upon a win: Updates player balance, adds a win, and adds a game played
                        player.setBankAccount(newBal);
                        player.AddWinPlayer();
                        player.AddGameplayedPlayer();
                    }else {
                        std::cout << "You Lost! Better luck next time\n";
                        // Upon a loss: Adds loss and adds a game played
                        player.AddLossPlayer();
                        player.AddGameplayedPlayer();
                    }
                    break;
                }
                if (playerRoulette.getColorBet() == 'R'){ // Check for player input red and if they won
                    std::cout << "Red selected, goodluck!\n";
                    std::cout << "Winning color is: " << dealerColor << std::endl;
                    if (playerRoulette.getColorBet() == dealerColor){
                        std::cout << "You Won!\n";
                        newBal = (betAmount*2) + tempBal;
                        player.setBankAccount(newBal);
                        player.AddWinPlayer();
                        player.AddGameplayedPlayer();
                    }else {
                        std::cout << "You Lost! Better luck next time\n";
                        player.AddLossPlayer();
                        player.AddGameplayedPlayer();
                    }
                    break;
                }
                break;
            }
            case 2: { // Number bet, 1:35 payout
                std::cout << "Number bet selected\n";
                std::cout << "Enter a bet amount: ";
                std::cin >> betAmount;
                if (betAmount <= 0){
                    std::cout << "Invalid Bet Amount\n";
                    break;                   
                }
                if (betAmount > player.getBankAccount()){
                    std::cout << "Invalid Bet Amount. Not enough money to bet in your balance\n";
                    break;
                }
                tempBal = player.getBankAccount()-betAmount;
                player.setBankAccount(tempBal);
                std::cout << "Enter a number from 0-36:";
                int numberSelection;
                std::cin >> numberSelection;
                playerRoulette.setNumberBet(numberSelection);
                int dealerNumber = playerRoulette.dealNumber();
                if (playerRoulette.getNumberBet()<0 || playerRoulette.getNumberBet()>36 ){ // Check for invalid number selection
                    std::cout << "Invalid number selection. Please input a value within the range of 0-36\n";
                    tempBal = player.getBankAccount() + betAmount;
                    player.setBankAccount(tempBal);
                    break;
                }
                else{
                    std::cout << "Bet placed with number selection: " << playerRoulette.getNumberBet() << "\nGoodluck!\n";
                    std::cout << "Winning number is: " << dealerNumber << std::endl;
                    if (playerRoulette.getNumberBet() == dealerNumber){
                        std::cout << "You won!\n";
                        newBal = (betAmount*35) + tempBal;
                        player.setBankAccount(newBal);
                        player.AddWinPlayer();
                        player.AddGameplayedPlayer();
                    }else {
                        std::cout << "You lost! Better luck next time\n";
                        player.AddLossPlayer();
                        player.AddGameplayedPlayer();
                    }
                }
                break;
            }
            case 3: { // Column bet, 2:1 payout
                std::cout << "Column bet selected\n";
                std::cout << "Enter a bet amount: ";
                std::cin >> betAmount;
                if (betAmount <= 0){
                    std::cout << "Invalid Bet Amount\n";
                    break;                   
                }
                if (betAmount> player.getBankAccount()){
                    std::cout << "Invalid Bet Amount. Not enough money to bet in your balance\n";
                    break;
                }
                tempBal = player.getBankAccount()-betAmount;
                player.setBankAccount(tempBal);
                std::cout << "Below are the column bet options:\n";
                std::cout << "Column 1= {1,4,7,10,13,16,19,22,25,28,31,34}\n";
                std::cout << "Column 2= {2,5,8,11,14,17,20,23,26,29,32,35}\n";
                std::cout << "Column 3= {3,6,9,12,15,18,21,24,27,30,33,36}\n";
                std::cout << "Select a column: ";
                int columnSelection;
                std::cin >> columnSelection;
                playerRoulette.setNumberBet(columnSelection);
                if ((playerRoulette.getNumberBet()< 1) || (playerRoulette.getNumberBet() > 3)){ // Check if column selection is out of range
                    std::cout << "Invalid Column Selection\n";
                    tempBal = player.getBankAccount() + betAmount;
                    player.setBankAccount(tempBal);
                    break;
                }
                std::cout << "Column " << columnSelection << " Selected\n";
                std::cout << "Good Luck!\n";   
                int dealerNumber = playerRoulette.dealNumber();
                int columnFlag;
                // Dummy column values to identify winning number and number
                int columnValues1[12] = {1,4,7,10,13,16,19,22,25,28,31,34};
                int columnValues2[12] = {2,5,8,11,14,17,20,23,26,29,32,35};
                int columnValues3[12] = {3,6,9,12,15,18,21,24,27,30,33,36};
                for (int i = 0; i<12; i++){
                    if (columnValues1[i] == dealerNumber){
                        std::cout << "Winning Number is: " << dealerNumber << " in Column 1\n";
                    }
                    if (columnValues2[i] == dealerNumber){
                        std::cout << "Winning Number is: " << dealerNumber << " in Column 2\n";
                    }
                    if (columnValues3[i] == dealerNumber){
                        std::cout << "Winning Number is: " << dealerNumber << " in Column 3\n";
                    }
                    if (dealerNumber == 0){
                        std::cout << "Winning Number is: " << dealerNumber << std::endl;
                    }
                }
                if (playerRoulette.getNumberBet() == 1){ // Check first column for a winner
                    int columnValues[12] = {1,4,7,10,13,16,19,22,25,28,31,34};
                    for (int i = 0; i<12; i++){
                        if (columnValues[i] == dealerNumber){
                            std::cout << "Congratulations, you won!\n";
                            newBal = (betAmount*3) + tempBal;
                            player.setBankAccount(newBal);
                            player.AddWinPlayer();
                            player.AddGameplayedPlayer();
                            columnFlag += 1;
                        }
                    }
                }
                if (playerRoulette.getNumberBet() == 2){ // Check second column for a winner
                    int columnValues[12] = {2,5,8,11,14,17,20,23,26,29,32,35};
                    for (int i = 0; i<12; i++){
                        if (columnValues[i] == dealerNumber){
                            std::cout << "Congratulations, you won!\n";
                            newBal = (betAmount*3) + tempBal;
                            player.setBankAccount(newBal);
                            player.AddWinPlayer();
                            player.AddGameplayedPlayer();
                            columnFlag += 1;
                        }
                    }
                }
                if (playerRoulette.getNumberBet() == 3){ // Check third column for a winner
                    int columnValues[12] = {3,6,9,12,15,18,21,24,27,30,33,36};
                    for (int i = 0; i<12; i++){
                        if (columnValues[i] == dealerNumber){
                            std::cout << "Congratulations, you won!\n";
                            newBal = (betAmount*2) + tempBal;
                            player.setBankAccount(newBal);
                            player.AddWinPlayer();
                            player.AddGameplayedPlayer();
                            columnFlag += 1;
                        }
                    }
                }
                if (columnFlag <= 0){ // Column bet loss message
                    std::cout << "You lost! Better luck next time\n";
                    player.AddLossPlayer();
                    player.AddGameplayedPlayer();
                }else{
                    columnFlag = 0; // Reset flag
                }
                break;             
            }
            default:break;
        }
        if (player.getBankAccount() <= 0){ // Check if player has a balance remaining, if not, end game loop
            std::cout << "You're out of money!\n";
            std::cout <<"Thanks for playing Roulette!\n";
            player.UpdateWins();
            player.UpdateLosses();
            player.UpdateBalance(player.getBankAccount());
            gameOn= false;
        }
    }
}
// int main(){
    // srand(time(NULL)); // Random seed for dealer selections
    // Player player(1234, "Craigon", "Confer");
    // player.add2DB();
    // PlayRoulette(player);
// }
#endif