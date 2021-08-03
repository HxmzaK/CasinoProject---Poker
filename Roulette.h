// Craigon Confer, Roulette Casino Game
#ifndef ROULETTE_H // Header File Wrapper
#define ROULETTE_H
// Include Paths
#include <stdlib.h>
#include <time.h>
#include <sqlite3.h>
#include <vector>
#include "baseclass.h"
#include <stdlib.h>

class Roulette // Roulette Class Declaration, inherits Player and Game Classes
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
        // Did not use grid
        // void prettyDisplay(){
        // // First let's draw the top "wall", which is a solid 
        // // row of 80 stars, one at a time
        // for (int column = 0; column < 96; ++column)
        // {
        //     if (column == 0){
        //         std::cout << " ";
        //     }else{
        //         std::cout << "*";
        //     }

        // }
        // // now print a carraige return, so we can start printing on the next line
        // std::cout << "\n";

        // // Now we're going to print the sides.
        // // There are 8 rows here.  Each row is a star, followed by
        // // 78 spaces, followed by another star and a carraige return.
        // for (int row = 0; row < 11; ++row)
        // {
        //     // print the left "wall"
        //     std::cout << "*";
        //     // Print 96 spaces
        //     for (int column = 0; column < 96; ++column)
        //     {
        //         if ((row == 3) || (row == 7)){
        //             std::cout << "*";
        //         }
        //         else if ((column%8 == 0) && (column != 0)){
        //             std::cout << "*";
        //         }
        //         else std::cout << " ";
        //         // addNumbersDisplay();
        //     }
        //     // finally print the right "wall" and a carraige return
        //     std::cout << "*\n";
        //     // continue the for loop to print the next row
        // }

        // // Once the loop is done, we can print the bottom wall the same way we printed the top one.
        // for (int column = 0; column < 96; ++column)
        // {
        //     if (column == 0){
        //         std::cout << " ";
        //     }else{
        //         std::cout << "*";
        //     }

        // }
        // // now print a carraige return, so we can start printing on the next line
        // std::cout << "\n";
        // }
        // void addNumbersDisplay(){
        //     for (int row = 0; row < 11; ++row)
        // {
        //     for (int column = 0; column < 96; ++column)
        //     {
        //         if (row == 0){
        //             if ((column == 0) || (column == 9) || (column == 17) || (column == 25) || (column == 33) || (column == 41) || (column == 49) || (column == 57) || (column == 65) || (column == 73) || (column == 81) || (column == 90)){
        //                 std::cout << "1";
        //             }
        //         }
        //     }
        // }
        // }
        // Roulette(int gameID, int ID, std::string n, std::string ln):Game(gameID),Player(ID, n, ln){ // Constructor for base Roulette object

        // }
        Roulette(){

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
    Roulette playerRoulette;
    Game Roulette(4);
   // Roulette playerRoulette(4, ID, name, lname); // Default Game ID of 4
    int x; // Switch case for Roulette menu
    float betAmount, tempBal, newBal; // Bet manipulation variables 
    bool gameOn = true; // Condition for continuous play 
    std::cout << "Welcome to Roulette: " << name << " " << lname << "!\n"; // Welcome message
    while ((gameOn != false)){ // Loop while game is not exited by user 
        float playerBal = player.getBankAccount(); // Stores player balance and is printed to console
        std::cout << "Balance: " << playerBal << std::endl;
        std::cout << "Select 1 to place a color bet, 2 for a number bet, 3 for a column bet, or 0 to exit: ";  // Roulette selector
        std::cin >> x;
        switch(x){ // Switch case for Roulette options
            case 0: { // Player leaves game
                std::cout <<"Thanks for playing Roulette!\n";
                // Updates player/games wins, losses, games played, and balances to Database
                player.UpdateWins();
                player.UpdateLosses();
                player.UpdateGamesplayed();
                player.UpdateBalance(player.getBankAccount());
                Roulette.UpdateGamesplayed();
                Roulette.UpdateAmountwon();
                Roulette.UpdateAmountLost();
                Roulette.UpdateGamesplayed();
                Roulette.UpdateWins();
                Roulette.UpdateLosses();
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
                    // std::string s(1, dealerColor);
                    // std::string printColor = "\033[0;34;49m" + s + "\033[0m";
                    // std::cout << "Winning color is: " << printColor << std::endl;
                    if (playerRoulette.getColorBet() == dealerColor){
                        std::string s(1, dealerColor);
                        std::string printColor = "\033[0;34;49m" + s + "\033[0m";
                        std::cout << "Winning color is: " << printColor << std::endl;
                        std::cout << "You Won!\n";
                        newBal = (betAmount*2) + tempBal;
                        // PLAYER: Upon a win: Updates balance, adds a win, and adds a game played
                        player.setBankAccount(newBal);
                        player.AddWinPlayer();
                        player.AddGameplayedPlayer();
                        // GAME Upon a win: adds to win amount, adds a win, and adds a game played
                        Roulette.AddWin();
                        Roulette.AddGameplayed();
                        Roulette.AddAmountwon((betAmount*2)-betAmount);
                    }else {
                        std::string s(1, dealerColor);
                        std::string printColor = "\033[0;31;49m" + s + "\033[0m";
                        std::cout << "Winning color is: " << printColor << std::endl;
                        std::cout << "You Lost! Better luck next time\n";
                        // PLAYER Upon a loss: Adds loss and adds a game played
                        player.AddLossPlayer();
                        player.AddGameplayedPlayer();
                        // GAME Upon a loss: Adds to loss amount, adds a loss, and adds a game played
                        Roulette.AddLoss();
                        Roulette.AddAmountLost(betAmount);
                        Roulette.AddGameplayed(); 
                    }
                    break;
                }
                if (playerRoulette.getColorBet() == 'R'){ // Check for player input red and if they won
                    std::cout << "Red selected, goodluck!\n";
                    if (playerRoulette.getColorBet() == dealerColor){
                        std::string s(1, dealerColor);
                        std::string printColor = "\033[0;31;49m" + s + "\033[0m";
                        std::cout << "Winning color is: " << printColor << std::endl;
                        std::cout << "You Won!\n";
                        newBal = (betAmount*2) + tempBal;
                        // PLAYER: Upon a win: Updates balance, adds a win, and adds a game played
                        player.setBankAccount(newBal);
                        player.AddWinPlayer();
                        player.AddGameplayedPlayer();
                        // GAME Upon a win: adds to win amount, adds a win, and adds a game played
                        Roulette.AddWin();
                        Roulette.AddGameplayed();
                        Roulette.AddAmountwon((betAmount*2)-betAmount);
                    }else {
                        std::string s(1, dealerColor);
                        std::string printColor = "\033[0;34;49m" + s + "\033[0m";
                        std::cout << "Winning color is: " << printColor << std::endl;
                        std::cout << "You Lost! Better luck next time\n";
                        // PLAYER Upon a loss: Adds loss and adds a game played
                        player.AddLossPlayer();
                        player.AddGameplayedPlayer();
                        // GAME Upon a loss: Adds to loss amount, adds a loss, and adds a game played
                        Roulette.AddLoss();
                        Roulette.AddAmountLost(betAmount);
                        Roulette.AddGameplayed(); 
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
                    if (playerRoulette.getNumberBet() == dealerNumber){
                        std::string s = to_string(dealerNumber);
                        std::string printColor = "\033[0;36;49m" + s + "\033[0m";
                        std::cout << "Winning number is: " << printColor << std::endl;
                        std::cout << "You won!\n";
                        newBal = (betAmount*35) + tempBal;
                        // PLAYER: Upon a win: Updates balance, adds a win, and adds a game played
                        player.setBankAccount(newBal);
                        player.AddWinPlayer();
                        player.AddGameplayedPlayer();
                        // GAME Upon a win: adds to win amount, adds a win, and adds a game played
                        Roulette.AddWin();
                        Roulette.AddGameplayed();
                        Roulette.AddAmountwon((betAmount*35)-betAmount);
                    }else {
                        std::string s = to_string(dealerNumber);
                        std::string printColor = "\033[0;36;49m" + s + "\033[0m";
                        std::cout << "Winning number is: " << printColor << std::endl;
                        std::cout << "You lost! Better luck next time\n";
                        // PLAYER Upon a loss: Adds loss and adds a game played
                        player.AddLossPlayer();
                        player.AddGameplayedPlayer();
                        // GAME Upon a loss: Adds to loss amount, adds a loss, and adds a game played
                        Roulette.AddLoss();
                        Roulette.AddAmountLost(betAmount);
                        Roulette.AddGameplayed(); 
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
                        std::string s = to_string(dealerNumber);
                        std::string printColor = "\033[0;36;49m" + s + "\033[0m";
                        std::cout << "Winning Number is: " << printColor << " in Column 1\n";
                    }
                    if (columnValues2[i] == dealerNumber){
                        std::string s = to_string(dealerNumber);
                        std::string printColor = "\033[0;36;49m" + s + "\033[0m";
                        std::cout << "Winning Number is: " << printColor << " in Column 2\n";
                    }
                    if (columnValues3[i] == dealerNumber){
                        std::string s = to_string(dealerNumber);
                        std::string printColor = "\033[0;36;49m" + s + "\033[0m";
                        std::cout << "Winning Number is: " << printColor << " in Column 3\n";
                    }
                    if (dealerNumber == 0){
                        std::string s = to_string(dealerNumber);
                        std::string printColor = "\033[0;36;49m" + s + "\033[0m";
                        std::cout << "Winning Number is: " << printColor << std::endl;
                    }
                }
                if (playerRoulette.getNumberBet() == 1){ // Check first column for a winner
                    int columnValues[12] = {1,4,7,10,13,16,19,22,25,28,31,34};
                    for (int i = 0; i<12; i++){
                        if (columnValues[i] == dealerNumber){
                            std::cout << "Congratulations, you won!\n";
                            newBal = (betAmount*3) + tempBal;
                            // PLAYER: Upon a win: Updates balance, adds a win, and adds a game played
                            player.setBankAccount(newBal);
                            player.AddWinPlayer();
                            player.AddGameplayedPlayer();
                            // GAME Upon a win: adds to win amount, adds a win, and adds a game played
                            Roulette.AddWin();
                            Roulette.AddGameplayed();
                            Roulette.AddAmountwon((betAmount*3)-betAmount);
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
                            // PLAYER: Upon a win: Updates balance, adds a win, and adds a game played
                            player.setBankAccount(newBal);
                            player.AddWinPlayer();
                            player.AddGameplayedPlayer();
                            // GAME Upon a win: adds to win amount, adds a win, and adds a game played
                            Roulette.AddWin();
                            Roulette.AddGameplayed();
                            Roulette.AddAmountwon((betAmount*3)-betAmount);
                            columnFlag += 1;
                        }
                    }
                }
                if (playerRoulette.getNumberBet() == 3){ // Check third column for a winner
                    int columnValues[12] = {3,6,9,12,15,18,21,24,27,30,33,36};
                    for (int i = 0; i<12; i++){
                        if (columnValues[i] == dealerNumber){
                            std::cout << "Congratulations, you won!\n";
                            // PLAYER: Upon a win: Updates balance, adds a win, and adds a game played
                            player.setBankAccount(newBal);
                            player.AddWinPlayer();
                            player.AddGameplayedPlayer();
                            // GAME Upon a win: adds to win amount, adds a win, and adds a game played
                            Roulette.AddWin();
                            Roulette.AddGameplayed();
                            Roulette.AddAmountwon((betAmount*3)-betAmount);
                            columnFlag += 1;
                        }
                    }
                }
                if (columnFlag == 0){ // Column bet loss message
                    std::cout << "You lost! Better luck next time\n";
                        // PLAYER Upon a loss: Adds loss and adds a game played
                        player.AddLossPlayer();
                        player.AddGameplayedPlayer();
                        // GAME Upon a loss: Adds to loss amount, adds a loss, and adds a game played
                        Roulette.AddLoss();
                        Roulette.AddAmountLost(betAmount);
                        Roulette.AddGameplayed(); 
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
            player.UpdateGamesplayed();
            player.UpdateBalance(player.getBankAccount());
            Roulette.UpdateGamesplayed();
            Roulette.UpdateAmountwon();
            Roulette.UpdateAmountLost();
            Roulette.UpdateGamesplayed();
            Roulette.UpdateWins();
            Roulette.UpdateLosses();
            gameOn= false;
        }
    }
}
#endif