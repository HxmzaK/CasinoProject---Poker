#ifndef KENO_MAIN_H
#define KENO_MAIN_H

/*
-------------------------------------------------

                    KENO

-------------------------------------------------
*/

#include <stdio.h>
#include <cmath>
#include <time.h>
#include <vector>
#include "baseclass.h"
#include "Keno.h"
#include "System_Functions.h"

/*
----------------------------------------------------------
                        MAIN
----------------------------------------------------------
*/

int Keno(Player player1){

    //Player & Game Variable
    Game Keno(2);
    Keno.SetName("Keno");

    //Player: set initial values of games played, wins, losses, amount won, and amount lost to 0
    // player1.setGamesPlayed(0);
    // player1.setWins(0);
    // player1.setLosses(0);
    player1.setAmountWon(0); //amountWon tracks player winnings during a session
    player1.setAmountLost(0); //amountLost tracks player losses during a session
    // player1.setDeposit(0);
    // player1.setWithdraw(0);
    //player1.setBankAccount(1000);

    //OPEN DATABASE
    sqlite3* DB; 
	int exit = 0;		
    exit = sqlite3_open("casinodata.db", &DB); //open the database

    //Add Game & Player to Database
    // string addGame = "INSERT INTO GAMES VALUES(" + std::to_string(Keno.getID()) + ", '"+ Keno.getName() +"', " + std::to_string(Keno.getWins()) +", " + std::to_string(Keno.getLosses()) +", " + std::to_string(Keno.getGamesPlayed()) +", " + std::to_string(Keno.getAmountWon()) +", " + std::to_string(Keno.getAmountLost()) +" );";
    // editTable(DB, addGame, "Casino Database");

    //string addPlayer = "INSERT INTO PLAYERS VALUES("+ std::to_string(player1.getID()) +", '"+ player1.getName() +"', '" + player1.getName() +"', " + std::to_string(player1.getBankAccount()) + ", "+ std::to_string(player1.getDeposit()) +", "+ std::to_string(player1.getWithdraw()) +", "+ std::to_string(player1.getGamePlayed()) +", "+ std::to_string(player1.getWins()) +", "+ std::to_string(player1.getLosses()) +", NULL)";
    //editTable(DB, addPlayer, "Casino Database");


    //Process 1: begin game (bank account starts with $1000, print player Info: ID, Name, Account Balance)

    //Warm Welcome :)
    std::cout << "██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗    ████████╗ ██████╗     ██╗  ██╗███████╗███╗   ██╗ ██████╗ \n"
    "██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝    ╚══██╔══╝██╔═══██╗    ██║ ██╔╝██╔════╝████╗  ██║██╔═══██╗\n"
    "██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗         ██║   ██║   ██║    █████╔╝ █████╗  ██╔██╗ ██║██║   ██║\n"
    "██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝         ██║   ██║   ██║    ██╔═██╗ ██╔══╝  ██║╚██╗██║██║   ██║\n"
    "╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗       ██║   ╚██████╔╝    ██║  ██╗███████╗██║ ╚████║╚██████╔╝\n"
    " ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝       ╚═╝    ╚═════╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝ \n"
    "                                                                                                                           \n";

    //Print Player's Info to screen
    std::cout << "--------------------------------------------------------------------------------------------------------------- \n";
    std::cout << "Player Info: \nPlayer ID: " << player1.getID() << "\nPlayer Name: " << player1.getName() << "\nAccount Balance: $" << player1.GetBalancedb() << std::endl; 
    std::cout << "------------------------------------------------ \n";

    int loopGame = 1;
    while (loopGame != 0)
    {
            //Proccess 2: Bank Account -> Withdraw amount
            float withdrawAmount;
            float accountBalance;
            float amountWon = 0;
            float spendAmount;
            int bankInput = 1;
            int exit = 0;
            int validAmount = 0;
            int costChoice = 0;
            int newBalance = 0;
            int profit = 0;

            while (bankInput != 0)
            {
                std::cout << "Let's Start By Taking Out Money. Here's Your Bank Account. \n";
                std::cout <<"Account Balance: $" << player1.GetBalancedb() << "\nHow much would you like to withdraw?\n";
                std::cin >> withdrawAmount;
                player1.setWithdraw(withdrawAmount);
                player1.UpdateWithdraw(withdrawAmount); //update withdraw amount in database

                if (withdrawAmount > player1.GetBalancedb()) //check if user has enough money in their bankaccount. If they do not then the user is prompted to exit
                {
                    std::cout << "You do not have enough in your account. Press '1' to return to the menu or '2' to try again. \n";
                    std::cin >> exit; 
                    if (exit == 1)
                    {
                        return 0; //ends code
                    }
                    else
                    {
                        bankInput = 1; //resets while loop to start at beginning
                    }
                }
                else if (withdrawAmount <= 0) //validates the user did not try to withdraw $0
                {
                    std::cout << "You do not have enough money to play. You must withdraw more. \n";
                    bankInput = 1;
                }
                else
                {
                    spendAmount = withdrawAmount; //set spending amount (amount able to play with during session) equal to the withdrawAmount
                    accountBalance = player1.GetBalancedb() - withdrawAmount; //update new account balance
                    player1.setBankAccount(accountBalance);
                    string uptBalance = "UPDATE PLAYERS SET BALANCE = "+ std::to_string(accountBalance) + " WHERE ID = "+ std::to_string(player1.getID()) + ";"; //update the account balance in database
                    editTable(DB, uptBalance, "Players Table"); //run edit table function from System_Functions

                    std::cout << "Great you have $" << spendAmount << " spending money! Use it wisely. \n";
                    bankInput = 0; //break while loop
                }
            }
            
            std::cout << "------------------------------------------------ \n";

            std::cout << "Press '1' to begin\n";
            int uin; //User Input
            std::cin >> uin;
            
            while (uin != 0)
            {
                //Print player Record: Games Played, Wins to Losses, and Amount Won/Lost (during session)
                std::cout << "------------------------------------------------ \n";
                std::cout << "Record: \nGames Played: " << player1.getGamePlayed() << "\nRecord: " << player1.getWins() << " - " << player1.getLosses() << "\nAmount Won in Session: " << player1.getAmountWon() << "\nAmount Lost in Session: " << player1.getAmountLost() << std::endl;
                std::cout << "------------------------------------------------- \n";

                //Print Player Account: Amount Withdrawn, Account Balance, Spending Amount
                std::cout <<"Bank Account: \n";
                std::cout << "Amount Withdrawn: $" << withdrawAmount << std::endl;
                std::cout <<"Account Balance: $" << accountBalance << std::endl;
                std::cout << "Spending Amount: $" << spendAmount << std::endl;
                std::cout << "------------------------------------------------ \n";

                std::cout << "Which ticket would you like to play with?\n1) Straight Ticket\n2) Split Ticket\n3) Way Ticket \n";
                int ticketType = 0; //Choose Ticket: 1 = Straight Ticket, 2 = Split Ticket, 3 = Way Ticket
                std::cin >> ticketType;

                switch (ticketType) //large case statement that specifically runs script dependent on type of ticket
                {
                    case 1: //STRAIGHT TICKET GAME
                    {
                        //Process 3: Fill In Ticket: Choose ticket type, Pick Number of Spots per Draw (1-10), Wager per draw ($1-10)
                        int numberofSpots = 0; //numbers to be selected
                        float wagerAmount = 0; //dollar wager
                        
                        //Validate Input
                        while (validAmount = 0)
                        {
                            std::cout << "How many spots would you like (Number between 1-10)?\n";
                            std::cin >> numberofSpots;
                            std::cout << "How much would you like to wager per draw ($1-10)\n";
                            std::cin >> wagerAmount;
                            int cost = numberofSpots*wagerAmount;

                            if (cost > spendAmount)
                            {
                                std::cout << "Ticket costs more than amount available would you like to try again or return to the menu? (press '1' to try again or '2' to return to the menu).\n";
                                std::cin >> costChoice;
                                if (costChoice == 0)
                                {
                                    validAmount = 0;
                                }
                                else
                                {
                                    newBalance = player1.GetBalancedb() + spendAmount;
                                    player1.UpdateBalance(newBalance); //update player account with remaining spending amount
                                    return 0;
                                }
                                
                            }
                            else
                            {
                                validAmount = 1;
                            }
                            
                        }
                        
                        straightTicket ticket1(numberofSpots,wagerAmount); //Create Straight Ticket Object with inputs (inputs to be changed to user inputs)

                        spendAmount = spendAmount - ticket1.getTicketCost(); //update spending amount 

                        std::cout << ticket1.getTicketName() + " Has Been Chosen\n"; //Print Ticket Type to Screen
                        std::cout << "Number of Spots: " << ticket1.getNumberofSpots() << std::endl; //Print Number of Spots Selected
                        std::cout << "Wager Selected: $" << ticket1.getwagerAmount() << std::endl; //Print Wager Amount
                        std::cout << "Ticket Cost: $" << ticket1.getTicketCost() << std::endl; //Print Ticket Cost
                        std::cout << "Spending Amount: $" << spendAmount<< std::endl; //Print spend amount balance
                        std::cout << "------------------------------------------------ \n";

                        //Process 4: pick numbers between 1-maxGridNumber based on # of spots selected
                        std::cout << "Select " << ticket1.getNumberofSpots() << " numbers between 1 and 80. Repeats are not allowed.\n";


                        int * selectedNumberResult = new int[ticket1.getNumberofSpots()]; //array size is NOT constant so dynamic array created at runtime to avoid memory allocation errors 

                        ticket1.selectNumbers(ticket1.getNumberofSpots(),selectedNumberResult); //call select numbers function and pass through ticket spots and store them in selectedNumberResult array
                        std::cout << "------------------------------------------------ \n";

                        //Process 7: draw 20 random numbers from 1-80
                        std::cout << "Winning Numbers: \n";

                        int winResult[MAXWINNINGNUMBERS]; //winResult array for winning numbers to be stored

                        srand(time(0)); //reset seed for randomly generated numbers
                        winningNumbers(MAXWINNINGNUMBERS, winResult); //generate winning numbers and store them in winResult array


                        std::cout << "------------------------------------------------ \n";

                        //Process 8: Search Matches
                        int matches = ticket1.searchMatches(selectedNumberResult, winResult, ticket1); //matches equal to functions returned value (counter)

                        if (matches != 0)
                        {
                            std::cout << "Number of Matches: " << matches << "\n";
                        }
                        else
                        {
                            std::cout << "There were no matches :( \n";
                        }
                        
                        //Process 9: Calculate Prizes, Amount Won, Amount Lost payout based on # of matches
                        float moneyWon = prizeCalculator(ticket1, matches, wagerAmount); //assign prize value to amount of money won

                        //add to gamesPlayed and update gamesPlayed
                        int addGames = player1.getGamePlayed() + 1; //store new value of Games Played for PLAYERS db table
                        int addGames_Games = Keno.getGamesPlayed() + 1; //store new value of Games Played for GAMES db table
                        player1.setGamesPlayed(addGames);
                        string uptGamesPlayed_Games = "UPDATE GAMES SET GAMESPLAYED = "+ std::to_string(addGames_Games) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";"; //update gamesplayed GAMES db
                        string uptGamesPlayed_Players = "UPDATE PLAYERS SET GAMESPLAYED = "+ std::to_string(addGames) + " WHERE ID = "+ std::to_string(player1.getID()) + ";"; //update gameplayed PLAYERS db
                        editTable(DB, uptGamesPlayed_Games, "Games Table");
                        editTable(DB, uptGamesPlayed_Players, "Players Table");

                        profit = moneyWon - ticket1.getTicketCost(); //calculate profit

                        if (profit < 0)
                        {
                            std::cout << "You lost $" << std::abs(profit) << "\n";
                        }
                        else
                        {
                            std::cout << "You won is $" << profit << std::endl; //print profit
                        }

                        if (moneyWon > ticket1.getTicketCost()) //if the money won is greater than the cost of the ticket update amountWon, update Games Won 
                        {

                            //set new amountWon for player 1
                            amountWon = Keno.GetAmountWondb() + moneyWon; 
                            player1.setAmountWon(amountWon); 
                            string uptAmountWon = "UPDATE GAMES SET AMOUNT_WON = "+ std::to_string(amountWon) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            editTable(DB, uptAmountWon, "Games Table");

                            //set new win count
                            int addWins = player1.GetWinsdb() + 1;
                            int addWinsGame = Keno.GetWinsdb() + 1;
                            player1.setWins(addWins);
                            string uptWin_Games = "UPDATE GAMES SET WINS = "+ std::to_string(addWinsGame) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            string uptWin_Players = "UPDATE PLAYERS SET WINS = "+ std::to_string(addWins) + " WHERE ID = "+ std::to_string(player1.getID()) + ";";
                            editTable(DB, uptWin_Games, "Games Table");
                            editTable(DB, uptWin_Players, "Players Table");

                            spendAmount = spendAmount + moneyWon; //update and add money won to spending amount

                        }
                        else // if money won is less or equal to the cost of ticket
                        {
                            //set new amountLost for player 1
                            float amountLost = Keno.GetAmountLostdb() + ticket1.getTicketCost();
                            player1.setAmountLost(amountLost);
                            string uptAmountLost = "UPDATE GAMES SET AMOUNT_LOST = "+ std::to_string(amountLost) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            editTable(DB, uptAmountLost, "Games Table");
                            
                            //set new loss count
                            int addLoss = player1.GetLossesdb() + 1;
                            int addLossGame = Keno.GetLossesdb() + 1;
                            player1.setLosses(addLoss);
                            string uptLost_Games = "UPDATE GAMES SET LOSSES = "+ std::to_string(addLossGame) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            string uptLost_Players = "UPDATE PLAYERS SET LOSSES = "+ std::to_string(addLoss) + " WHERE ID = "+ std::to_string(player1.getID()) + ";";
                            editTable(DB, uptLost_Games, "Games Table");
                            editTable(DB, uptLost_Players, "Players Table");

                            spendAmount = spendAmount + moneyWon;
                        }

                        //check if there's enough spending money 
                        if (spendAmount <= 0)
                        {
                            int withdrawChoice;            
                            std::cout << "You do not have enough spending money would you like to withdraw more or exit (press '1' to withdraw more or '0' to exit)?\n";
                            std::cin >> withdrawChoice;
                            if (withdrawChoice == 1)
                            {
                                break;
                            }
                            else if (withdrawChoice == 0)
                            {
                                return 0;
                            }
                        }
                        else
                        {
                            //Play Again?
                            std::cout << "Would you like to play again (click '1' to play again or click '0' to exit)?\n";
                            int choice;

                            std::cin >> choice; 
                            if (choice == 0)
                            {
                                newBalance = player1.GetBalancedb() + spendAmount;
                                player1.UpdateBalance(newBalance); //update player account with remaining spending amount
                                return 0;
                            }                    
                        }
                    break;
                    }
                        
                    case 2: //SPLIT TICKET GAME
                    {
                        //Process 3: Fill In TWO Tickets: Pick Number of Spots per Draw (1-10), Wager per draw ($1-10)

                        //Ticket 1 Inputs
                        int numberofSpots1 = 0; //numbers to be selected
                        float wagerAmount1 = 0; //dollar wager

                        //Ticket 2 Inputs
                        int numberofSpots2 = 0;
                        float wagerAmount2 = 0;

                        //Validate Input
                        //Process 3: Fill In Ticket: Choose ticket type, Pick Number of Spots per Draw (1-10), Wager per draw ($1-10)
                        int numberofSpots = 0; //numbers to be selected
                        float wagerAmount = 0; //dollar wager
                        
                        //Validate Input
                        while (validAmount = 0)
                        {
                            std::cout << "How many spots would you like for the first ticket (Number between 1-10)?\n";
                            std::cin >> numberofSpots1;
                            std::cout << "How much would you like to wager per draw for the first ticket ($1-10)\n";
                            std::cin >> wagerAmount1;


                            std::cout << "How many spots would you like for the second ticket (Number between 1-10)?\n";
                            std::cin >> numberofSpots2;
                            std::cout << "How much would you like to wager per draw for the second ticket ($1-10)\n";
                            std::cin >> wagerAmount2;

                            int cost = (numberofSpots1*wagerAmount1) + (numberofSpots2*wagerAmount2);

                            if (cost > spendAmount)
                            {
                                std::cout << "Ticket costs more than amount available would you like to try again or return to the menu? (press '1' to try again or '2' to return to the menu).\n";
                                std::cin >> costChoice;
                                if (costChoice == 0)
                                {
                                    validAmount = 0;
                                }
                                else
                                {
                                    newBalance = player1.GetBalancedb() + spendAmount;
                                    player1.UpdateBalance(newBalance); //update player account with remaining spending amount
                                    return 0;
                                }
                            }
                            else
                            {
                                validAmount = 1;
                            }
                            
                        }

                        splitTicket ticket1(numberofSpots1, numberofSpots2, wagerAmount1, wagerAmount2); //Create Split Ticket Object with inputs (inputs to be changed to user inputs)

                        spendAmount = spendAmount - ticket1.getTicketCost(); //update spending amount

                        std::cout << ticket1.getTicketName() + " Has Been Chosen\n"; //Print Ticket Type to Screen
                        std::cout << "TICKET 1 INFO: \n";
                        std::cout << "Number of Spots: " << ticket1.getNumberofSpots1() << std::endl; //Print Number of Spots Selected
                        std::cout << "Wager Selected: $" << ticket1.getWagerAmount1() << std::endl; //Print Wager Amount
                        std::cout << "Ticket 1 Cost: $" << ticket1.getTicketCost1() << std::endl; //Print Cost of First Ticket
                        std::cout << "------------------------------------------------ \n";
                        std::cout << "TICKET 2 INFO: \n";
                        std::cout << "Number of Spots: " << ticket1.getNumberofSpots2() << std::endl; //Print Number of Spots Selected
                        std::cout << "Wager Selected: $" << ticket1.getWagerAmount2() << std::endl; //Print Wager Amount
                        std::cout << "Ticket 2 Cost: $" << ticket1.getTicketCost2() << std::endl; //Print Cost of Second Ticket
                        std::cout << "\n";
                        std::cout << "Total Ticket Cost: $" << ticket1.getTicketCost() << std::endl; //Print Ticket Cost
                        std::cout << "Spending Amount: $" << spendAmount << std::endl; //Print spend amount balance
                        std::cout << "------------------------------------------------ \n";

                        //Process 4: pick numbers between 1-maxGridNumber based on # of spots selected

                        //Select numbers for first ticket
                        std::cout << "Choose Numbers for Ticket 1: \n";
                        std::cout << "Select " << ticket1.getNumberofSpots1() << " numbers between 1 and 80. Repeats are not allowed.\n";
                        
                        int * selectedNumberResult1 = new int[ticket1.getNumberofSpots()]; //array size is NOT constant so dynamic array created at runtime to avoid memory allocation errors 
                        ticket1.selectNumbers(ticket1.getNumberofSpots1(),selectedNumberResult1); //call select numbers function from Base Ticket Class to create initial ticket

                        std::cout << "\n";

                        //Select numbers for second ticket
                        std::cout << "Choose Numbers for Ticket 2: \n";
                        std::cout << "Select " << ticket1.getNumberofSpots2() << " numbers between 1 and 80. Repeats are not allowed.\n";

                        int * selectedNumberResult2 = new int[ticket1.getNumberofSpots()]; //array size is NOT constant so dynamic array created at runtime to avoid memory allocation errors 
                        ticket1.selectNumbers_split(ticket1.getNumberofSpots2(),ticket1.getNumberofSpots1(),selectedNumberResult2, selectedNumberResult1); //call selectNumbers function specified for SPlit Ticket class to pass through prev & new ticket spots, prev ticket values, and store valid inputs in selectedNumberResult2 array

                        std::cout << "------------------------------------------------ \n";

                        //Process 7: draw 20 random numbers from 1-80
                        std::cout << "Winning Numbers: \n";

                        int winResult[MAXWINNINGNUMBERS];

                        srand(time(0)); //reset seed
                        winningNumbers(MAXWINNINGNUMBERS, winResult); //generate winning numbers and store them in winResult array

                        std::cout << "------------------------------------------------ \n";

                        //Process 8: Search Matches for First and Second Ticket 
                        int matches1 = ticket1.searchMatches(selectedNumberResult1, winResult, ticket1);

                        if (matches1 != 0)
                        {
                            std::cout << "Number of Matches in Ticket 1: " << matches1 << "\n";
                        }
                        else
                        {
                            std::cout << "Ticket 1: There were no matches :( \n";
                        }

                        int matches2 = ticket1.searchMatches(selectedNumberResult2, winResult, ticket1);

                        if (matches2 != 0)
                        {
                            std::cout << "Number of Matches in Ticket 2: " << matches2 << "\n";
                        }
                        else
                        {
                            std::cout << "Ticket 2: There were no matches :( \n";
                        }

                        //Process 9: Calculate Prizes, Amount Won, Amount Lost payout based on # of matches from each ticket

                        float moneyWon = prizeCalculator(ticket1, matches1, wagerAmount1) + prizeCalculator(ticket1, matches2, wagerAmount2); //set moneyWon to sum of prizes from both tickets

                        //add to gamesPlayed and update gamesPlayed
                        int addGames = player1.getGamePlayed() + 1;
                        int addGames_Games = Keno.getGamesPlayed() + 1;
                        player1.setGamesPlayed(addGames);
                        string uptGamesPlayed_Games = "UPDATE GAMES SET GAMESPLAYED = "+ std::to_string(addGames_Games) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                        string uptGamesPlayed_Players = "UPDATE PLAYERS SET GAMESPLAYED = "+ std::to_string(addGames) + " WHERE ID = "+ std::to_string(player1.getID()) + ";";
                        editTable(DB, uptGamesPlayed_Games, "Games Table");
                        editTable(DB, uptGamesPlayed_Players, "Players Table");

                        profit = moneyWon - ticket1.getTicketCost(); //calculate profit

                        if (profit < 0)
                        {
                            std::cout << "You lost $" << std::abs(profit) << "\n";
                        }
                        else
                        {
                            std::cout << "You won is $" << profit << std::endl; //print profit
                        }

                        if (moneyWon > ticket1.getTicketCost()) //if the money won is greater than the cost of the ticket add to bank account, update amountWon, update Games Won 
                        {

                            //set new amountWon for player 1
                            amountWon = Keno.GetAmountWondb() + moneyWon; 
                            player1.setAmountWon(amountWon);
                            string uptAmountWon = "UPDATE GAMES SET AMOUNT_WON = "+ std::to_string(amountWon) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            editTable(DB, uptAmountWon, "Games Table"); 

                            //set new win count
                            int addWins = player1.GetWinsdb() + 1;
                            int addWinsGame = Keno.GetWinsdb() + 1;
                            player1.setWins(addWins);
                            string uptWin_Games = "UPDATE GAMES SET WINS = "+ std::to_string(addWinsGame) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            string uptWin_Players = "UPDATE PLAYERS SET WINS = "+ std::to_string(addWins) + " WHERE ID = "+ std::to_string(player1.getID()) + ";";
                            editTable(DB, uptWin_Games, "Games Table");
                            editTable(DB, uptWin_Players, "Players Table");

                            spendAmount = spendAmount + moneyWon; //update and add money to spending amount

                        }
                        else // if money won is less or equal to the cost of
                        {
                            //set new amountLost for player 1
                            float amountLost = Keno.GetAmountLostdb() + ticket1.getTicketCost();
                            player1.setAmountLost(amountLost);
                            string uptAmountLost = "UPDATE GAMES SET AMOUNT_LOST = "+ std::to_string(amountLost) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            editTable(DB, uptAmountLost, "Games Table");

                            //set new loss count
                            int addLoss = player1.GetLossesdb() + 1;
                            int addLossGame = Keno.GetLossesdb() + 1;
                            player1.setLosses(addLoss);
                            string uptLost_Games = "UPDATE GAMES SET LOSSES = "+ std::to_string(addLossGame) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            string uptLost_Players = "UPDATE PLAYERS SET LOSSES = "+ std::to_string(addLoss) + " WHERE ID = "+ std::to_string(player1.getID()) + ";";
                            editTable(DB, uptLost_Games, "Games Table");
                            editTable(DB, uptLost_Players, "Players Table");
                            spendAmount = spendAmount + moneyWon;
                        }

                        //check if there's enough spending money
                        if (spendAmount <= 0)
                        {
                            int withdrawChoice;            
                            std::cout << "You do not have enough spending money would you like to withdraw more or exit (press '1' to withdraw more or '0' to exit)?\n";
                            std::cin >> withdrawChoice;
                            if (withdrawChoice == 1)
                            {
                                break;
                            }
                            else if (withdrawChoice == 0)
                            {
                                return 0;
                            }
                        }
                        else
                        {
                            //Play Again?
                            std::cout << "Would you like to play again (click '1' to play again or click '0' to exit)?\n";
                            int choice;

                            std::cin >> choice; 
                            if (choice == 0)
                            {
                                newBalance = player1.GetBalancedb() + spendAmount;
                                player1.UpdateBalance(newBalance); //update player account with remaining spending amount
                                return 0;
                            }                    
                        }
                    break;    
                    }

                    case 3: //WAY TICKET GAME
                    {

                    //Process 3: Fill In Ticket: Choose ticket type, Pick Number of Spots per Draw (1-10), Wager per draw ($1-10)
                    float moneyWon = 0;
                    int numberofTickets = 0; //user input of number of tickets the user would like to play with
                    int numberofSpots = 0; //numbers to be selected
                    float wagerAmount = 0; //dollar wager

                    std::cout << "How many tickets would you like to play with?\n";
                    std::cin >> numberofTickets;

                    std::vector<wayTicket> ticketVect; //initialize wayTicket vector to store all tickets 

                    for (int i = 1; i < numberofTickets; i++) //iterate until reaches number of tickets requested by the user
                    {

                        std::cout << "How many spots would you like for Ticket" << i << " (Number between 1-10)?\n";
                        std::cin >> numberofSpots;
                        std::cout << "How much would you like to wager per draw for Ticket" << i << " ($1-10)?\n";
                        std::cin >> wagerAmount;                        

                        //validate cost is within spending amount
                        if (numberofSpots*wagerAmount > spendAmount)
                        {
                            int continueTicket = 0;
                            std::cout << "You do not have enough spending money. Would you like to try again, play with current amount of tickets, or return to the menu?\n(Press '1' to try again, '2' to play with current amount, '3' return to menu)\n";
                            std::cin >> continueTicket;

                            if (continueTicket == 1)
                            {
                                i--; //set i to previous iteration
                                break;
                            }
                            else if (continueTicket == 2)
                            {
                                break; //exit for loop
                            }
                            else
                            {
                                newBalance = player1.GetBalancedb() + spendAmount;
                                player1.UpdateBalance(newBalance); //update player account with remaining spending amount
                                return 0;
                            }
                            
                        }
                        
                        wayTicket newTicket(numberofSpots,wagerAmount); //Create Ticket with user inputs 
                        ticketVect.push_back(newTicket); //Add new ticket to vector
                        spendAmount = spendAmount - ticketVect[i].getTicketCost(); //update spending amount

                        std::cout << "Ticket " << i << " Info:" << std::endl; //Print Ticket Info
                        std::cout << "Number of Spots: " << ticketVect[i].getNumberofSpots() << std::endl; //Print Number of Spots Selected
                        std::cout << "Wager Selected: $" << ticketVect[i].getwagerAmount() << std::endl; //Print Wager Amount
                        std::cout << "Ticket Cost: $" << ticketVect[i].getTicketCost() << std::endl; //Print Ticket Cost
                        std::cout << "Spending Amount: $" << spendAmount<< std::endl; //Print spend amount balance
                        std::cout << "------------------------------------------------ \n";

                    }

                    //Process 4: pick numbers between 1-maxGridNumber based on # of spots selected

                    for (int i = 0; i < ticketVect.size(); i++) //iterate through each ticket (similar to straight ticket process)
                    {
                        int * selectedNumberResult = new int[ticketVect[i].getNumberofSpots()]; //dynamic array selectedNumberResult - created at runtime to avoid memory allocation errors

                        std::cout << "Select Numbers for Ticket " << i << ":\n";
                        std::cout << "Select " << ticketVect[i].getNumberofSpots() << " numbers between 1 and 80. Repeats are not allowed.\n";
                        ticketVect[i].selectNumbers(ticketVect[i].getNumberofSpots(), selectedNumberResult);

                        std::cout << "------------------------------------------------ \n";

                        //Process 7: draw 20 random numbers from 1-80
                        std::cout << "Winning Numbers For Ticket " << i << ": \n";

                        int winResult[MAXWINNINGNUMBERS];

                        srand(time(0)); //reset seed
                        winningNumbers(MAXWINNINGNUMBERS, winResult); //generate winning numbers and store them in winResult array

                        std::cout << "------------------------------------------------ \n";

                        //Process 8: Search Matches
                        int matches = ticketVect[i].searchMatches(selectedNumberResult, winResult, ticketVect[i]);

                        if (matches != 0)
                        {
                            std::cout << "Number of Matches: " << matches << "\n";
                        }
                        else
                        {
                            std::cout << "There were no matches :( \n";
                        }

                        //Process 9: Calculate Prizes, Amount Won, Amount Lost payout based on # of matches
                        moneyWon = moneyWon + prizeCalculator(ticketVect[i], matches, ticketVect[i].getwagerAmount()); //update money won by adding prev value to prize output
                    }

                        //add to gamesPlayed and update gamesPlayed
                        int addGames = player1.getGamePlayed() + 1;
                        int addGames_Games = Keno.getGamesPlayed() + 1;
                        player1.setGamesPlayed(addGames);
                        string uptGamesPlayed_Games = "UPDATE GAMES SET GAMESPLAYED = "+ std::to_string(addGames_Games) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                        string uptGamesPlayed_Players = "UPDATE PLAYERS SET GAMESPLAYED = "+ std::to_string(addGames) + " WHERE ID = "+ std::to_string(player1.getID()) + ";";
                        editTable(DB, uptGamesPlayed_Games, "Games Table");
                        editTable(DB, uptGamesPlayed_Players, "Players Table");

                        //calculate ticket cost and win/losses
                        int totalticketCost = 0;
                        
                        for (int i = 0; i < ticketVect.size(); i++) 
                        {
                            totalticketCost = totalticketCost + ticketVect[i].getTicketCost(); //iterate through each ticket and update previous ticket cost to find total
                        }
                        
                        profit = moneyWon - totalticketCost; //calculate profit

                        if (profit < 0)
                        {
                            std::cout << "You lost $" << std::abs(profit) << "\n";
                        }
                        else
                        {
                            std::cout << "You won is $" << profit << std::endl; //print profit
                        }

                        if (moneyWon > totalticketCost) //if the money won is greater than the cost of the ticket add to bank account, update amountWon, update Games Won 
                        {

                            //set new amountWon for player 1
                            amountWon = Keno.GetAmountWondb() + moneyWon; 
                            player1.setAmountWon(amountWon); 
                            string uptAmountWon = "UPDATE GAMES SET AMOUNT_WON = "+ std::to_string(amountWon) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            editTable(DB, uptAmountWon, "Games Table");

                            //set new win count
                            int addWins = player1.GetWinsdb() + 1;
                            int addWinsGame = Keno.GetWinsdb() + 1;
                            player1.setWins(addWins);
                            string uptWin_Games = "UPDATE GAMES SET WINS = "+ std::to_string(addWinsGame) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            string uptWin_Players = "UPDATE PLAYERS SET WINS = "+ std::to_string(addWins) + " WHERE ID = "+ std::to_string(player1.getID()) + ";";
                            editTable(DB, uptWin_Games, "Games Table");
                            editTable(DB, uptWin_Players, "Players Table");

                            spendAmount = spendAmount + moneyWon; //update and add money to spending amount

                        }
                        else // if money won is less or equal to the cost of
                        {
                            //set new amountLost for player 1
                            float amountLost = Keno.GetAmountLostdb() + totalticketCost;
                            player1.setAmountLost(amountLost);
                            string uptAmountLost = "UPDATE GAMES SET AMOUNT_LOST = "+ std::to_string(amountLost) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            editTable(DB, uptAmountLost, "Games Table");

                            //set new loss count
                            int addLoss = player1.GetLossesdb() + 1;
                            int addLossGame = Keno.GetLossesdb() + 1;
                            player1.setLosses(addLoss);
                            string uptLost_Games = "UPDATE GAMES SET LOSSES = "+ std::to_string(addLossGame) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            string uptLost_Players = "UPDATE PLAYERS SET LOSSES = "+ std::to_string(addLoss) + " WHERE ID = "+ std::to_string(player1.getID()) + ";";
                            editTable(DB, uptLost_Games, "Games Table");
                            editTable(DB, uptLost_Players, "Players Table");

                            spendAmount = spendAmount + moneyWon;
                        }

                        

                        //check if there's enough spending money
                        if (spendAmount <= 0)
                        {
                            int withdrawChoice;            
                            std::cout << "You do not have enough spending money would you like to withdraw more or exit (press '1' to withdraw more or '0' to exit)?\n";
                            std::cin >> withdrawChoice;
                            if (withdrawChoice == 1)
                            {
                                break;
                            }
                            else if (withdrawChoice == 0)
                            {
                                return 0;
                            }
                        }
                        else
                        {
                            //Play Again?
                            std::cout << "Would you like to play again (click '1' to play again or click '0' to exit)?\n";
                            int choice;

                            std::cin >> choice; 
                            if (choice == 0)
                            {
                                newBalance = player1.GetBalancedb() + spendAmount;
                                player1.UpdateBalance(newBalance); //update player account with remaining spending amount
                                return 0;
                            }                    
                        }                    
                        break;
                    }
                    
                    default:
                        break;
                }
            }
    }

return 0;
}

#endif