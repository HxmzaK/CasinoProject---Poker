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
    // Player player1(1001, "Keno Player 1");
    Game Keno;
    
    //Player: set initial values of games played, wins, losses, amount won, and amount lost to 0
    player1.setGamesPlayed(0);
    player1.setWins(0);
    player1.setLosses(0);
    player1.setAmountWon(0);
    player1.setAmountLost(0);
    player1.setDeposit(0);
    player1.setWithdraw(0);
    //player1.setBankAccount(1000);

    //Game: set initial values id, name
    Keno.SetName("Keno");
    Keno.SetID(2);

    //DATABASE
    sqlite3* DB;

	int exit = 0;
    char * messageError;
		
    exit = sqlite3_open("casinodata.db", &DB); //open the database

    //Add Game & Player to Database
    // string addGame = "INSERT INTO GAMES VALUES(" + std::to_string(Keno.getID()) + ", '"+ Keno.getName() +"', " + std::to_string(Keno.getWins()) +", " + std::to_string(Keno.getLosses()) +", " + std::to_string(Keno.getGamesPlayed()) +", " + std::to_string(Keno.getAmountWon()) +", " + std::to_string(Keno.getAmountLost()) +" );";
    // editTable(DB, addGame, "Casino Database");

    string addPlayer = "INSERT INTO PLAYERS VALUES("+ std::to_string(player1.getID()) +", '"+ player1.getName() +"', '" + player1.getName() +"', " + std::to_string(player1.getBankAccount()) + ", "+ std::to_string(player1.getDeposit()) +", "+ std::to_string(player1.getWithdraw()) +", "+ std::to_string(player1.getGamePlayed()) +", "+ std::to_string(player1.getWins()) +", "+ std::to_string(player1.getLosses()) +", NULL)";
    editTable(DB, addPlayer, "Casino Database");



    //Process 1: begin game (bank account starts with $1000, print player Info: ID, Name, Account Balance)
    std::cout << "██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗    ████████╗ ██████╗     ██╗  ██╗███████╗███╗   ██╗ ██████╗ \n"
    "██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝    ╚══██╔══╝██╔═══██╗    ██║ ██╔╝██╔════╝████╗  ██║██╔═══██╗\n"
    "██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗         ██║   ██║   ██║    █████╔╝ █████╗  ██╔██╗ ██║██║   ██║\n"
    "██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝         ██║   ██║   ██║    ██╔═██╗ ██╔══╝  ██║╚██╗██║██║   ██║\n"
    "╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗       ██║   ╚██████╔╝    ██║  ██╗███████╗██║ ╚████║╚██████╔╝\n"
    " ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝       ╚═╝    ╚═════╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝ \n"
    "                                                                                                                           \n";
    std::cout << "--------------------------------------------------------------------------------------------------------------- \n";
    std::cout << "Player Info: \nPlayer ID: " << player1.getID() << "\nPlayer Name: " << player1.getName() << "\nAccount Balance: $" << player1.getBankAccount() << std::endl; 
    std::cout << "------------------------------------------------ \n";

    int loopGame = 1;
    while (loopGame != 0)
    {
            //Proccess 2: Bank Account -> Withdraw amount
            float withdrawAmount;
            float accountBalance;
            float amountWon = 0; //initialize at 0
            float spendAmount;
            int bankInput = 1;

            while (bankInput != 0)
            {
                std::cout << "Let's Start By Taking Out Money. Here's Your Bank Account. \n";
                std::cout <<"Account Balance: $" << player1.getBankAccount() << "\nHow much would you like to withdraw?\n";
                std::cin >> withdrawAmount;
                player1.setWithdraw(withdrawAmount);
                if (withdrawAmount > player1.getBankAccount())
                {
                    std::cout << "You do not have enough in your account. Try Again. \n";
                    bankInput = 1;
                }
                else if (withdrawAmount <= 0)
                {
                    std::cout << "You do not have enough money to play. You must withdraw more. \n";
                    bankInput = 1;
                }
                else
                {
                    spendAmount = withdrawAmount;
                    accountBalance = player1.getBankAccount() - withdrawAmount;
                    player1.setBankAccount(accountBalance);
                    string uptBalance = "UPDATE PLAYERS SET BALANCE = "+ std::to_string(accountBalance) + " WHERE ID = "+ std::to_string(player1.getID()) + ";";
                    editTable(DB,uptBalance,"Players Table");

                    std::cout << "Great you have $" << spendAmount << " spending money! Use it wisely. \n";
                    bankInput = 0;
                }
            }
            
            std::cout << "------------------------------------------------ \n";


            std::cout << "Press '1' to begin '0' to exit \n";
            int uin; //User Input
            std::cin >> uin;
            

            while (uin != 0)
            {
                std::cout << "------------------------------------------------ \n";
                std::cout << "Record: \nGames Played: " << player1.getGamePlayed() << "\nRecord: " << player1.getWins() << " - " << player1.getLosses() << "\nAmount Won: " << player1.getAmountWon() << "\nAmount Lost: " << player1.getAmountLost() << std::endl;
                std::cout << "------------------------------------------------- \n";

                std::cout <<"Bank Account: \n";
                std::cout << "Amount Withdrawn: $" << withdrawAmount << std::endl;
                std::cout <<"Account Balance: $" << accountBalance << std::endl;
                std::cout << "Spending Amount: $" << spendAmount << std::endl;
                std::cout << "------------------------------------------------ \n";

                std::cout << "Which ticket would you like to play with?\n1) Straight Ticket\n2) Split Ticket\n3) Way Ticket \n";
                int ticketType = 0; //Choose Ticket: 1 = Straight Ticket, 2 = Split Ticket, 3 = Way Ticket
                std::cin >> ticketType;

                switch (ticketType)
                {
                    case 1: //STRAIGHT TICKET GAME
                    {
                        //Process 3: Fill In Ticket: Choose ticket type, Pick Number of Spots per Draw (1-10), Wager per draw ($1-10)
                        int numberofSpots = 0; //numbers to be selected
                        float wagerAmount = 0; //dollar wager

                        std::cout << "How many spots would you like (Number between 1-10)?\n";
                        std::cin >> numberofSpots;
                        std::cout << "How much would you like to wager per draw ($1-10)\n";
                        std::cin >> wagerAmount;

                        //Validate Input

                        straightTicket ticket1(numberofSpots,wagerAmount); //Create Ticket with inputs (inputs to be changed to user inputs)

                        spendAmount = spendAmount - ticket1.getTicketCost(); //update spending amount

                        std::cout << ticket1.getTicketName() + " Has Been Chosen\n"; //Print Ticket Type to Screen
                        std::cout << "Number of Spots: " << ticket1.getNumberofSpots() << std::endl; //Print Number of Spots Selected
                        std::cout << "Wager Selected: $" << ticket1.getwagerAmount() << std::endl; //Print Wager Amount
                        std::cout << "Ticket Cost: $" << ticket1.getTicketCost() << std::endl; //Print Ticket Cost
                        std::cout << "Spending Amount: $" << spendAmount<< std::endl; //Print spend amount balance
                        std::cout << "------------------------------------------------ \n";

                        //Process 4: pick numbers between 1-maxGridNumber based on # of spots selected
                        std::cout << "Select " << ticket1.getNumberofSpots() << " numbers between 1 and 80. Repeats are not allowed.\n";

                        int selectedNumberResult[ticket1.getNumberofSpots()];

                        ticket1.selectNumbers(ticket1.getNumberofSpots(),selectedNumberResult); //call select numbers function and pass through ticket spots and store them in selectedNumberResult arrat
                        std::cout << "------------------------------------------------ \n";

                        //Process 7: draw 20 random numbers from 1-80
                        std::cout << "Winning Numbers: \n";

                        int winResult[MAXWINNINGNUMBERS];

                        srand(time(0)); //reset seed
                        winningNumbers(MAXWINNINGNUMBERS, winResult); //generate winning numbers and store them in winResult array


                        std::cout << "------------------------------------------------ \n";

                        //Process 8: Search Matches
                        int matches = ticket1.searchMatches(selectedNumberResult, winResult, ticket1);

                        if (matches != 0)
                        {
                            std::cout << "Number of Matches: " << matches << "\n";
                        }
                        else
                        {
                            std::cout << "There were no matches :( \n";
                        }
                        
                        //Process 9: Calculate Prizes, Amount Won, Amount Lost payout based on # of matches
                        float moneyWon = prizeCalculator(ticket1, matches, wagerAmount);

                        //add to gamesPlayed and update gamesPlayed
                        int addGames = player1.getGamePlayed() + 1;
                        player1.setGamesPlayed(addGames);
                        string uptGamesPlayed_Games = "UPDATE GAMES SET GAMESPLAYED = "+ std::to_string(addGames) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                        string uptGamesPlayed_Players = "UPDATE PLAYERS SET GAMESPLAYED = "+ std::to_string(addGames) + " WHERE ID = "+ std::to_string(player1.getID()) + ";";
                        editTable(DB, uptGamesPlayed_Games, "Games Table");
                        editTable(DB, uptGamesPlayed_Players, "Players Table");

                        std::cout << "Your Profit is $" << moneyWon - ticket1.getTicketCost() << std::endl;

                        if (moneyWon > ticket1.getTicketCost()) //if the money won is greater than the cost of the ticket add to bank account, update amountWon, update Games Won 
                        {

                            //set new amountWon for player 1
                            amountWon = player1.getAmountWon() + moneyWon; 
                            player1.setAmountWon(amountWon); 
                            string uptAmountWon = "UPDATE GAMES SET AMOUNT_WON = "+ std::to_string(amountWon) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            editTable(DB, uptAmountWon, "Games Table");

                            //set new win count
                            int addWins = player1.getWins() + 1;
                            player1.setWins(addWins);
                            string uptWin_Games = "UPDATE GAMES SET WINS = "+ std::to_string(addWins) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            string uptWin_Players = "UPDATE PLAYERS SET WINS = "+ std::to_string(addWins) + " WHERE ID = "+ std::to_string(player1.getID()) + ";";
                            editTable(DB, uptWin_Games, "Games Table");
                            editTable(DB, uptWin_Players, "Players Table");

                            spendAmount = spendAmount + moneyWon; //update and add money to spending amount

                            //update accountbalance

                        }
                        else // if money won is less or equal to the cost of
                        {
                            //set new amountLost for player 1
                            float amountLost = ticket1.getTicketCost();
                            player1.setAmountLost(amountLost);
                            string uptAmountLost = "UPDATE GAMES SET AMOUNT_LOST = "+ std::to_string(amountLost) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            editTable(DB, uptAmountLost, "Games Table");
                            
                            //set new loss count
                            int addLoss = player1.getLosses() + 1;
                            player1.setLosses(addLoss);
                            string uptLost_Games = "UPDATE GAMES SET LOSSES = "+ std::to_string(addLoss) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            string uptLost_Players = "UPDATE PLAYERS SET LOSSES = "+ std::to_string(addLoss) + " WHERE ID = "+ std::to_string(player1.getID()) + ";";
                            editTable(DB, uptLost_Games, "Games Table");
                            editTable(DB, uptLost_Players, "Players Table");

                            spendAmount = spendAmount + moneyWon;
                        }

                        //check if there's enough spending money
                        if (spendAmount <= 0)
                        {
                            int withdrawChoice;            
                            std::cout << "You do not have enough spending money would you like to withdraw more (press '1' to withdraw more or '0' to exit)?\n";
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

                        std::cout << "How many spots would you like for the first ticket (Number between 1-10)?\n";
                        std::cin >> numberofSpots1;
                        std::cout << "How much would you like to wager per draw for the first ticket ($1-10)\n";
                        std::cin >> wagerAmount1;

                        //Validate Input

                        std::cout << "How many spots would you like for the second ticket (Number between 1-10)?\n";
                        std::cin >> numberofSpots2;
                        std::cout << "How much would you like to wager per draw for the second ticket ($1-10)\n";
                        std::cin >> wagerAmount2;

                        //Validate Input

                        splitTicket ticket1(numberofSpots1, numberofSpots2, wagerAmount1, wagerAmount2); //Create First Ticket with inputs (inputs to be changed to user inputs)

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
                        
                        int emptyArray[0];
                        int selectedNumberResult1[ticket1.getNumberofSpots1()];
                        ticket1.selectNumbers(ticket1.getNumberofSpots1(),0,selectedNumberResult1, emptyArray); //call select numbers function and pass through ticket spots and store them in selectedNumberResult array

                        std::cout << "\n";

                        //Select numbers for second ticket
                        std::cout << "Choose Numbers for Ticket 2: \n";
                        std::cout << "Select " << ticket1.getNumberofSpots2() << " numbers between 1 and 80. Repeats are not allowed.\n";

                        int selectedNumberResult2[ticket1.getNumberofSpots2()];
                        ticket1.selectNumbers(ticket1.getNumberofSpots2(),ticket1.getNumberofSpots1(),selectedNumberResult2, selectedNumberResult1); //call select numbers function and pass through ticket spots and store them in selectedNumberResult array

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
                            std::cout << "There were no matches :( \n";
                        }

                        int matches2 = ticket1.searchMatches(selectedNumberResult2, winResult, ticket1);

                        if (matches2 != 0)
                        {
                            std::cout << "Number of Matches in Ticket 2: " << matches2 << "\n";
                        }
                        else
                        {
                            std::cout << "There were no matches :( \n";
                        }

                        //Process 9: Calculate Prizes, Amount Won, Amount Lost payout based on # of matches

                        float moneyWon = prizeCalculator(ticket1, matches1, wagerAmount1) + prizeCalculator(ticket1, matches2, wagerAmount2);

                        //add to gamesPlayed and update gamesPlayed
                        int addGames = player1.getGamePlayed() + 1;
                        player1.setGamesPlayed(addGames);
                        string uptGamesPlayed_Games = "UPDATE GAMES SET GAMESPLAYED = "+ std::to_string(addGames) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                        string uptGamesPlayed_Players = "UPDATE PLAYERS SET GAMESPLAYED = "+ std::to_string(addGames) + " WHERE ID = "+ std::to_string(player1.getID()) + ";";
                        editTable(DB, uptGamesPlayed_Games, "Games Table");
                        editTable(DB, uptGamesPlayed_Players, "Players Table");

                        std::cout << "Your Profit is $" << moneyWon - ticket1.getTicketCost() << std::endl;

                        if (moneyWon > ticket1.getTicketCost()) //if the money won is greater than the cost of the ticket add to bank account, update amountWon, update Games Won 
                        {

                            //set new amountWon for player 1
                            amountWon = player1.getAmountWon() + moneyWon; 
                            player1.setAmountWon(amountWon);
                            string uptAmountWon = "UPDATE GAMES SET AMOUNT_WON = "+ std::to_string(amountWon) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            editTable(DB, uptAmountWon, "Games Table"); 

                            //set new win count
                            int addWins = player1.getWins() + 1;
                            player1.setWins(addWins);
                            string uptWin_Games = "UPDATE GAMES SET WINS = "+ std::to_string(addWins) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            string uptWin_Players = "UPDATE PLAYERS SET WINS = "+ std::to_string(addWins) + " WHERE ID = "+ std::to_string(player1.getID()) + ";";
                            editTable(DB, uptWin_Games, "Games Table");
                            editTable(DB, uptWin_Players, "Players Table");

                            spendAmount = spendAmount + moneyWon; //update and add money to spending amount

                            //update accountbalance

                        }
                        else // if money won is less or equal to the cost of
                        {
                            //set new amountLost for player 1
                            float amountLost = ticket1.getTicketCost();
                            player1.setAmountLost(amountLost);
                            string uptAmountLost = "UPDATE GAMES SET AMOUNT_LOST = "+ std::to_string(amountLost) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            editTable(DB, uptAmountLost, "Games Table");

                            //set new loss count
                            int addLoss = player1.getLosses() + 1;
                            player1.setLosses(addLoss);
                            string uptLost_Games = "UPDATE GAMES SET LOSSES = "+ std::to_string(addLoss) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            string uptLost_Players = "UPDATE PLAYERS SET LOSSES = "+ std::to_string(addLoss) + " WHERE ID = "+ std::to_string(player1.getID()) + ";";
                            editTable(DB, uptLost_Games, "Games Table");
                            editTable(DB, uptLost_Players, "Players Table");

                            spendAmount = spendAmount + moneyWon;
                        }

                        //check if there's enough spending money
                        if (spendAmount <= 0)
                        {
                            int withdrawChoice;            
                            std::cout << "You do not have enough spending money would you like to withdraw more (press '1' to withdraw more or '0' to exit)?\n";
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
                                return 0;
                            }                    
                        }
                    break;    
                    }

                    case 3:
                    {

                    //Process 3: Fill In Ticket: Choose ticket type, Pick Number of Spots per Draw (1-10), Wager per draw ($1-10)
                    float moneyWon = 0;
                    int numberofTickets = 0;
                    int numberofSpots = 0; //numbers to be selected
                    float wagerAmount = 0; //dollar wager

                    std::cout << "How many tickets would you like to play with?\n";
                    std::cin >> numberofTickets;

                    std::vector<wayTicket> ticketVect; //initialize wayTicket vector to store all tickets

                    for (int i = 0; i < numberofTickets; i++)
                    {


                        std::cout << "How many spots would you like for Ticket" << i << " (Number between 1-10)?\n";
                        std::cin >> numberofSpots;
                        std::cout << "How much would you like to wager per draw for Ticket" << i << " ($1-10)?\n";
                        std::cin >> wagerAmount;
                        
                        //Validate Input

                        //validate cost is within spending amount
                        if (numberofSpots*wagerAmount > spendAmount)
                        {
                            std::cout << "You do not have enough spending money \n";
                            i--;
                            break;
                        }
                        
                        wayTicket newTicket(numberofSpots,wagerAmount); //Create Ticket with inputs (inputs to be changed to user inputs)
                        ticketVect.push_back(newTicket); //Add new ticket to vector
                        spendAmount = spendAmount - ticketVect[i].getTicketCost(); //update spending amount

                        std::cout << "Ticket " << i << " Info:" << std::endl; //Print Ticcket Info
                        std::cout << "Number of Spots: " << ticketVect[i].getNumberofSpots() << std::endl; //Print Number of Spots Selected
                        std::cout << "Wager Selected: $" << ticketVect[i].getwagerAmount() << std::endl; //Print Wager Amount
                        std::cout << "Ticket Cost: $" << ticketVect[i].getTicketCost() << std::endl; //Print Ticket Cost
                        std::cout << "Spending Amount: $" << spendAmount<< std::endl; //Print spend amount balance
                        std::cout << "------------------------------------------------ \n";

                    }

                    //Process 4: pick numbers between 1-maxGridNumber based on # of spots selected

                    for (int i = 0; i < numberofTickets; i++)
                    {
                        int selectedNumberResult[ticketVect[i].getNumberofSpots()];
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
                        moneyWon = moneyWon + prizeCalculator(ticketVect[i], matches, ticketVect[i].getwagerAmount());
                    }
                        
                        //add to gamesPlayed and update gamesPlayed
                        int addGames = player1.getGamePlayed() + 1;
                        player1.setGamesPlayed(addGames);
                        string uptGamesPlayed_Games = "UPDATE GAMES SET GAMESPLAYED = "+ std::to_string(addGames) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                        string uptGamesPlayed_Players = "UPDATE PLAYERS SET GAMESPLAYED = "+ std::to_string(addGames) + " WHERE ID = "+ std::to_string(player1.getID()) + ";";
                        editTable(DB, uptGamesPlayed_Games, "Games Table");
                        editTable(DB, uptGamesPlayed_Players, "Players Table");

                        //calculate ticket cost and win/losses
                        int totalticketCost = 0;
                        
                        for (int i = 0; i < numberofTickets; i++)
                        {
                            totalticketCost = totalticketCost + ticketVect[i].getTicketCost();
                        }
                        
                        int profit = moneyWon - totalticketCost;

                        std::cout << "Your Profit is $" << profit << std::endl;

                        if (moneyWon > totalticketCost) //if the money won is greater than the cost of the ticket add to bank account, update amountWon, update Games Won 
                        {

                            //set new amountWon for player 1
                            amountWon = player1.getAmountWon() + moneyWon; 
                            player1.setAmountWon(amountWon); 
                            string uptAmountWon = "UPDATE GAMES SET AMOUNT_WON = "+ std::to_string(amountWon) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            editTable(DB, uptAmountWon, "Games Table"); 

                            //set new win count
                            int addWins = player1.getWins() + 1;
                            player1.setWins(addWins);
                            string uptWin_Games = "UPDATE GAMES SET WINS = "+ std::to_string(addWins) + " WHERE ID = "+ std::to_string(Keno.getID()) + ";";
                            string uptWin_Players = "UPDATE PLAYERS SET WINS = "+ std::to_string(addWins) + " WHERE ID = "+ std::to_string(player1.getID()) + ";";
                            editTable(DB, uptWin_Games, "Games Table");
                            editTable(DB, uptWin_Players, "Players Table");

                            spendAmount = spendAmount + moneyWon; //update and add money to spending amount

                            //update accountbalance

                        }
                        else // if money won is less or equal to the cost of
                        {
                            //set new amountLost for player 1
                            float amountLost = totalticketCost;
                            player1.setAmountLost(amountLost);

                            //set new loss count
                            int addLoss = player1.getLosses() + 1;
                            player1.setLosses(addLoss);

                            spendAmount = spendAmount + moneyWon;
                        }

                        //check if there's enough spending money
                        if (spendAmount <= 0)
                        {
                            int withdrawChoice;            
                            std::cout << "You do not have enough spending money would you like to withdraw more (press '1' to withdraw more or '0' to exit)?\n";
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