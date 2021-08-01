#ifndef KENO_H
#define KENO_H

#include <iostream>
#include <string>
#include <algorithm>    
#include <vector>

#define MAXGRIDNUMBER 80
#define MAXWINNINGNUMBERS 20


/*
-------------------------------------------------

KENO HEADER FILE

Contents:

Player Class (Base)
    -attributes: id, name, wins, losses, gamesPlayed, amountWon, amountLost, betAmount, bankAccount
    -functions: class constructor, corresponding get functions for each attribute

Ticket Class (Base)
    -attributes: ticketName, ticketCost, maxGridNumber
    -functions: ticket constructor, corresponding get functions for each attribute


-------------------------------------------------
*/


class Ticket {

    protected:
        std::string ticketName;
        int numberofSpots;
        float wagerAmount;
        float ticketCost;

    public:

        Ticket(int numberofSpots, float wagerAmount){
            this -> numberofSpots = numberofSpots;
            this ->wagerAmount = wagerAmount;
            this -> ticketCost = numberofSpots*wagerAmount;
        }

        std::string getTicketName(){
            return ticketName;
        }

        int getNumberofSpots(){
            return numberofSpots;
        }

        float getwagerAmount(){
            return wagerAmount;
        }

        float getTicketCost(){
            return ticketCost;
        }

        virtual void printTicket(){
            std::cout << "printTicket function was called \n";
        }

        virtual int searchMatches(vector <int> playerNumbers, int winningNumbers[MAXWINNINGNUMBERS], Ticket targetTicket){
        
            int counter = 0; //indicates number of matches
            for (int i = 0; i < MAXWINNINGNUMBERS; i++)
            {
                for (int j = 0; j < targetTicket.getNumberofSpots(); j++)
                {
                    if (winningNumbers[i] == playerNumbers[j])
                    {
                        //std::cout << winningNumbers[i] << " ";
                        counter++;
                    }
                }
            }

            //https://www.cplusplus.com/reference/algorithm/sort/
            //https://www.geeksforgeeks.org/how-to-find-common-elements-between-two-vector-using-stl-in-c/

            // int counter = 0; //indicates number of matches
            // vector <int> resultVector(playerNumbers.size() + winningNumbers.size());
            // vector<int>::iterator it, end;

            // sort(playerNumbers.begin(), playerNumbers.end());
            // sort(winningNumbers.begin(), winningNumbers.end());

            // it = set_intersection(playerNumbers.begin(), playerNumbers.end(), winningNumbers.begin(), winningNumbers.end(), resultVector.begin());

            // for (end = resultVector.begin(); end != it; end++){
            //     std::cout << *it << " ";
            //     counter++;
            // }
            

        return counter;
        }

};


/*
----------------------------------------------------------------------------------------------------------
STRAIGHT TICKET
-Rules: straight bet is a bet with a specific amount of numbers chosen. 
        You will then have to hit all or some of your selected numbers, 
        depending on how many you’ve chosen, in order to win.
        The more numbers you pick, the more you have to pay and the harder it is to hit all of them. 
        You also choose how much to bet. 

----------------------------------------------------------------------------------------------------------
*/

class straightTicket : public Ticket 
{    

    public:

        straightTicket(int numberofSpots, float wagerAmount) : Ticket(numberofSpots, wagerAmount){
            this -> ticketName = "Straight Ticket";
        }


        void selectNumbers(int spots, vector <int> resultArray){

            //Variables
            int numChoice;
            std::vector<int> selectedNumbers;
            bool checkRepeat = true;

            //fill array with valid user input
            for (int i = 0; i < spots; i++)
            {
                std::cin >> numChoice; //input number value

                if (numChoice < 1 || numChoice > MAXGRIDNUMBER) //validate the number selected is within range (1-80)
                {   
                    std::cout << "Number Out Of Range. Try Again \n";
                    i--; 
                }
                else
                {
                    for (int j = 0; j < i; j++) //iterate through entire array
                    {
                        if (numChoice == selectedNumbers[j]) //determine if number selected is already present in the vector
                        {
                            std::cout << "Repeating Value. Try Again \n";
                            checkRepeat = false;
                            i--;
                            break;
                        }
                        else
                        {
                            checkRepeat = true; //if number selected is a new number set checkRepeat to true
                        }
                    }
                    if (checkRepeat == true) //if checkRepeat is true set number in array to User's Choice
                    {
                        selectedNumbers.push_back(numChoice); //Add new number to vector
                        std::cout << "Number selected successfully \n";
                    }
                }
            }
            
            //Print Selected Numbers To screen
            std::cout << "You have selected the numbers: ";
            for (int i = 0; i < spots; i++)
            {
                resultArray.push_back(selectedNumbers[i]);
                std::cout << selectedNumbers[i] << ", ";
            }
            std::cout << "\n";
        }

};


/*
------------------------------------------------------------------------------------
SPLIT TICKET
-Rules: With a keno split ticket, 
        you can play two keno games in one. 
        A single ticket is divided between the numbers you will use for each game. 
        The drawback here is you cannot use the same number on both bets. 
 
------------------------------------------------------------------------------------
*/

class splitTicket : public Ticket 
{
    protected:
        int numberofSpots1;
        int numberofSpots2;
        float wagerAmount1;
        float wagerAmount2;
        float ticketCost1;
        float ticketCost2;

    public:

        splitTicket(int numberofSpots1, int numberofSpots2, float wagerAmount1, float wagerAmount2) : Ticket(numberofSpots, wagerAmount)
        {
            this -> ticketName = "Split Ticket";

            this -> numberofSpots1 = numberofSpots1;
            this -> numberofSpots2 = numberofSpots2;
            this -> numberofSpots = numberofSpots1 + numberofSpots2;

            this -> wagerAmount1 = wagerAmount1;
            this -> wagerAmount2 = wagerAmount2;

            this -> ticketCost1 = numberofSpots1*wagerAmount1;
            this -> ticketCost2 = numberofSpots2*wagerAmount2;
            this -> ticketCost = ticketCost1 + ticketCost2; 
        }

        int getNumberofSpots1(){
            return numberofSpots1;
        }

        int getNumberofSpots2(){
            return numberofSpots2;
        }

        float getWagerAmount1(){
            return wagerAmount1;
        }

        float getWagerAmount2(){
            return wagerAmount2;
        }

        float getTicketCost1(){
            return ticketCost1;
        }

        float getTicketCost2(){
            return ticketCost2;
        }

        void selectNumbers(int spots, int prevSpots, vector <int> resultArray, vector <int> prevArray)
        {
            //Variables
            int numChoice;
            std::vector<int> selectedNumbers;
            bool checkRepeat = true;

            //fill array with valid user input
            for (int i = 0; i < spots; i++)
            {
                std::cin >> numChoice; //input number value

                if (numChoice < 1 || numChoice > MAXGRIDNUMBER) //validate the number selected is within range (1-80)
                {   
                    std::cout << "Number Out Of Range. Try Again \n";
                    i--; 
                }
                else
                {
                    for (int j = 0; j < prevSpots; j++) //iterate thrpugh previous ticket numbers
                    {
                        if (numChoice == prevArray[j]) //determine if number selected is already present in the previous ticket
                        {
                            std::cout << "Repeating Value. Try Again \n";
                            checkRepeat = false;
                            i--;
                            break;                                    
                        }                     
                    }
                    
                    for (int l = 0; l < i; l++) //iterate through entire array
                    {

                        if (numChoice == selectedNumbers[l]) //determine if number selected is already present in the array
                        {
                            std::cout << "Repeating Value. Try Again \n";
                            checkRepeat = false;
                            i--;
                            break;                                    
                        }
                        else
                        {
                            checkRepeat = true; //if number selected is a new number set checkRepeat to true
                        }
                    }
                    if (checkRepeat == true) //if checkRepeat is true set number in array to User's Choice
                    {
                        selectedNumbers.push_back(numChoice); //Add new number to vector
                        std::cout << "Number selected successfully \n";
                    }
                }
            }
            
            //Print Selected Numbers To screen and allocate memory for numbers to be accesed outside of the function call
            std::cout << "You have selected the numbers: ";
            for (int i = 0; i < spots; i++)
            {
                resultArray.push_back(selectedNumbers[i]);
                std::cout << selectedNumbers[i] << ", ";
            }
            std::cout << "\n";
        }

};



/*
---------------------------------------------------------------------------------------------------
WAY TICKET
-Rules: Way tickets let you play more than one keno ticket at the same time. 
        A player can bet on their chosen numbers at once without needing to buy multiple tickets.
---------------------------------------------------------------------------------------------------
*/

class wayTicket : public Ticket 
{

    public:

        wayTicket(int numberofSpots, float wagerAmount) : Ticket(numberofSpots, wagerAmount){
            this -> ticketName = "Way Ticket";
        }

        void selectNumbers(int spots, vector <int> resultArray){

            //Variables
            int numChoice;
            std::vector<int> selectedNumbers;
            bool checkRepeat = true;

            //fill array with valid user input
            for (int i = 0; i < spots; i++)
            {
                std::cin >> numChoice; //input number value

                if (numChoice < 1 || numChoice > MAXGRIDNUMBER) //validate the number selected is within range (1-80)
                {   
                    std::cout << "Number Out Of Range. Try Again \n";
                    i--; 
                }
                else
                {
                    for (int j = 0; j < i; j++) //iterate through entire array
                    {
                        if (numChoice == selectedNumbers[j]) //determine if number selected is already present in the array
                        {
                            std::cout << "Repeating Value. Try Again \n";
                            checkRepeat = false;
                            i--;
                            break;
                        }
                        else
                        {
                            checkRepeat = true; //if number selected is a new number set checkRepeat to true
                        }
                    }
                    if (checkRepeat == true) //if checkRepeat is true set number in array to User's Choice
                    {
                        selectedNumbers.push_back(numChoice); //Add new number to vector
                        std::cout << "Number selected successfully \n";
                    }
                }
            }
            
            //Print Selected Numbers To screen
            std::cout << "You have selected the numbers: ";
            for (int i = 0; i < spots; i++)
            {
                resultArray[i] = selectedNumbers[i];
                std::cout << selectedNumbers[i] << ", ";
            }
            std::cout << "\n";
        }


// class Player {
//     protected:
//         int id;
//         std::string name;
//         int wins;
//         int losses;
//         int gamesPlayed;
//         float amountWon;
//         float amountLost;
//         float bankAccount;

//     public:

//         Player(int id, std::string name){
//             this -> id = id;
//             this -> name = name;
//         }

//         //Set Functions: Games PLayed, Wins, Losses, Amount Won, Amount Lost

//         void setWins(int inputWins){
//             wins = inputWins;
//         }

//         void setLosses(int inputLosses){
//             losses = inputLosses;
//         }

//         void setGamesPlayed(int inputGamesPlayed){
//             gamesPlayed = inputGamesPlayed;
//         }
//         void setAmountWon(float inputAmountWon){
//             amountWon = inputAmountWon;
//         }

//         void setAmountLost(float inputAmountLost){
//             amountLost = inputAmountLost;
//         }
//         void setBankAccount(float inputBankAccount){
//             bankAccount = inputBankAccount;
//         }

//         //Get Functions: All Attributes
//         int getID(){
//             return id;
//         }

//         std::string getName(){
//             return name;
//         }

//         int getWins(){
//             return wins;
//         }

//         int getLosses(){
//             return losses;
//         }

//         int getGamePlayed(){
//             return gamesPlayed;
//         }

//         float getAmountWon(){
//             return amountWon;
//         }

//         float getAmountLost(){
//             return amountLost;
//         }

//         float getBankAccount(){
//             return bankAccount;
//         }

// };


};



#endif