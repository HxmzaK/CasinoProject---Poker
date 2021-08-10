#include <iostream> 
#include <stdio.h>
#include <sqlite3.h>
#include <string> 
#include "baseclass.h"
#include "blackjack.h"
#include "Keno_Main.h"
#include "Roulette.h"
#include "craps.h"
#include "slots.h"
#include "poker.h"
#include "bingo_final_1.h"
using namespace std;

static int callbacklogin(void* data, int argc, char** argv, char** azColName) {
    //AJ        
    int i;
    for (i = 0; i < argc; i++)
    {
        //https://stackoverflow.com/questions/60811670/how-do-i-store-into-a-c-variables-using-sqlite3
        auto& container = *static_cast<std::vector<std::string>*>(data);
        container.push_back(argv[i]); // stores the return of the selection to the container(4th arg of exec)
    }

    return 0;
}

Player login() {
    // AJ
    Player player(0, "", "");
    int id;
    std::cout << "Please enter your ID\n";
    std::cin >> id;

    sqlite3* DB;
    char* messageError;
    int exit = 0;
    std::vector<std::string> container;// iniitializes vector for the selection to put results
    exit = sqlite3_open("casinodata.db", &DB);   //open the database

    std::string cmd("SELECT * FROM PLAYERS WHERE ID =" + std::to_string(id) + ";");

    exit = sqlite3_exec(DB, cmd.c_str(), callbacklogin, &container, &messageError);

    //container[0] = id container[1] = firstname container[2] = lastname  
    if (!container.empty()) {
        player = Player(std::stoi(container[0]), container[1], container[2]);
    }
    return (player);
}

int GetNextid() {
    // AJ
    sqlite3* DB;
    char* messageError;
    int exit = 0;
    int currentid = 0;
    std::vector<std::string> container;// iniitializes vector for the selection to put results
    exit = sqlite3_open("casinodata.db", &DB);   //open the database

    std::string cmd("SELECT max( ID ) FROM PLAYERS;");//get the largest id

    exit = sqlite3_exec(DB, cmd.c_str(), callbacklogin, &container, &messageError);
    sqlite3_close(DB);

    if (!container.empty()) {
        currentid = std::stoi(container[0]);//converts the response from db to an integer
    }

    currentid++;
    return (currentid);

}

Player NewUser() {
    //AJ

    std::string firstname;
    std::string lastname;


    cout << "Enter your First Name\n";
    cin >> firstname;
    cout << "Enter your Last Name\n";
    cin >> lastname;
    int id = GetNextid();
    cout << "next id " << id << "\n";
    Player newPlayer(id, firstname, lastname);
    cout << "made player\n";
    newPlayer.add2DB();

    return(newPlayer);

}


int main() {
    int uin; // user input variable 
    int mainLoop = 1;
    int exit = 1; // will loop until the user chooses to stop it 
    int type = 0;//initializes type as 0
    Player player1(0, "", "");
    //Login information for test:



    //Process 1: Log In/Create New Account

    while (type == 0)
    {
        cout << "To login press '0', to create a new account press '1'  \n";
        int log;
        cin >> log;

        switch (log)
        {
        case 0: {
            //Log-in Funtion
            player1 = login();
            type = 1;//breaks input loop
            break;
        }
        case 1: {
            player1 = NewUser(); //Create a new account function
            type = 1;//breaks input loop
            break;
        }
        default: {
            cout << "Enter a valid input. \n";
            break;
        }
        }
    }
    while (exit != 0)
    {
        std::cout << "\nWelcome To the Casino " << player1.getName() << "!\n";
        int Choice;
        cout << "You currently have $" << player1.GetBalancedb() << "\n";
        if (player1.GetBalancedb() >= 2){ //ensures the player has enough money to play a game 
            cout << "Casino Menu: \n";
            cout << "Enter '0' To Exit Menu\nEnter '1' for Blackjack\nEnter '2' for Keno\n"
                "Enter '3' for Poker\nEnter '4' for Roulette\nEnter '5' for Slots\n"
                "Enter '6' for Bingo\nEnter '7' for Craps\nEnter '8' to deposit/withdraw cash\n";
            cin >> Choice;
        }
        else{ // if player doesnt have enough money to play they are automatically brought to the ATM 
            Choice = 8;
            std::cout << "You must add money to your account to be able to play a game\n";
        }
        switch (Choice)
        {
        case 0:
        {
            cout << "Menu exited!\n";
            exit = 0;
            break;
        }
        case 1:
        {
            blackjack(player1);
            break;

        }
        case 2:
        {
            Keno(player1);
            break;
        }
        case 3:
        {
            Pokergame(player1);
            break;
        }
        case 4:
        {
            PlayRoulette(player1);
            break;
        }
        case 5:
        {
            //Slots
            gameplay(player1);
            break;
        }
        case 6:
        {
            Bingo(player1);
            break;
        }
        case 7: {
            cout << "Craps is coming soon\n";
            //Note: Craps Code causing errors in MAIN 
            //CrapsGame cgame("hadi", 500.00);
            // cgame.PlayGame();
            break;
        }
        case 8: { // Craigon Confer, Deposit/Withdraw functionality
            std::cout << "Your current Balance is: " << player1.GetBalancedb() << std::endl;
            std::cout << "Enter '0' to exit, input '1' to deposit cash,'2' to withdraw cash:" << std::endl;
            int y; 
            std::cin >> y;
            switch(y){
                case 0: // Exit deposit/withdraw menu
                {
                    cout << "Menu exited!\n";
                    exit = 0;
                    break;
                }
                case 1: // Deposit money and update balance
                {
                    float depositMoney;
                    std::cout << "Deposit selected\n";
                    std::cout << "Max Deposit is $10,000. Enter deposit value: ";
                    std::cin >> depositMoney;
                    float tempBal = player1.GetBalancedb(); // Stores current balance
                    if ((depositMoney <= 0) || (depositMoney > 100000)){
                        std::cout << "Invalid deposit amount\n";
                        break;
                    }
                    float tempDeposit = player1.GetDepositBalancedb(); // Stores current deposit balance
                    player1.UpdateDeposit(depositMoney+tempDeposit); // Updates deposit database entry
                    player1.setBankAccount(tempBal+depositMoney); // Sets new balance with deposit value
                    player1.UpdateBalance(player1.getBankAccount()); // Updates database balance
                    break;

                }
                case 2: // Withdraw money and update balance
                {
                    float withdrawMoney;
                    std::cout << "Withdraw selected\n";
                    std::cout << "Enter withdrawl value: ";
                    std::cin >> withdrawMoney;
                    float tempBal = player1.GetBalancedb();
                    if ((withdrawMoney > tempBal) || (withdrawMoney <= 0)){
                        std::cout << "Invalid withdraw amount\n";
                        break;
                    }
                    float tempWithdraw = player1.GetWithdrawBalancedb(); // Stores current withdraw balance
                    player1.UpdateWithdraw(tempWithdraw+withdrawMoney); // Updates withdraw database entry
                    player1.setBankAccount(tempBal-withdrawMoney); // Sets new balance with withdrawl
                    player1.UpdateBalance(player1.getBankAccount()); // Updates database balance
                    break;
                }
            }
            break;
        }
        default: std::cout << "Invalid input\n";
        }
    }


    return 0;
}