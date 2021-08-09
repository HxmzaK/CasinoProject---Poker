#ifndef KENO_H
#define KENO_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define MAXGRIDNUMBER 80
#define MAXWINNINGNUMBERS 20


/*
-------------------------------------------------

KENO HEADER FILE
Author: Julian

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

    protected: //protected variables only accessed by members within the class/derived classes
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

        //Get Functions:
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

        //Class Methods:
        virtual void printTicket()
        {
            //print KENO Ticket
            cout << "\n\n\n\n-----------------------------------------------------------------------------------\n";
            cout << "|                                KENO TICKET                                      |\n";
            cout << "-----------------------------------------------------------------------------------\n";
            cout << "| 1. HOW MANY SPOTS (NUMBERS) DO YOU WANT TO PLAY?                                |\n|";
            cout << "                                                                                 |\n";
            for (int i = 1; i < 11; i++)
            {
                cout << "|  " << i << "  ";
            }
            cout << "|                    |\n-----------------------------------------------------------------------------------\n";
            cout << "| 2. HOW MUCH DO YOU WANT TO WAGER PER DRAW?                                      |\n|";
            cout << "                                                                                 |\n";
            for (int i = 1; i < 11; i++)
            {
                cout << "|  $" << i << "  ";
            }
            cout << "|          |\n-----------------------------------------------------------------------------------\n";
            cout << "| 3. PICK YOUR OWN SPOTS?                                                         |\n|";
            cout << "                                                                                 |\n";
            for (int i = 1; i < 81; i++)
            {
                cout << "| " << i << " |";
                if (i == 10) printf("                               |");
                if( i % 10 == 0 && i != 0 ) printf("                      |\n");
            }
            cout << "-----------------------------------------------------------------------------------\n\n\n\n";        
        }

        virtual void printTicketColor(Ticket targetTicket, int * numberChoices)
        {
            //print KENO Ticket
            cout << "\n\n\n\n-----------------------------------------------------------------------------------\n";
            cout << "|                                KENO TICKET                                      |\n";
            cout << "-----------------------------------------------------------------------------------\n";
            cout << "| 1. HOW MANY SPOTS (NUMBERS) DO YOU WANT TO PLAY?                                |\n|";
            cout << "                                                                                 |\n";
            for (int i = 1; i < 11; i++)
            {
                if (targetTicket.getNumberofSpots() == i)
                {
                    cout << "|  ";
                    printf("\033[0;31m"); //print red text to terminal
                    cout << i;
                    printf("\033[0;37m"); //revert back to white
                    cout << "  ";   
                }
                else
                {
                    cout << "|  " << i << "  ";
                }
            }

            cout << "|                    |\n-----------------------------------------------------------------------------------\n";
            cout << "| 2. HOW MUCH DO YOU WANT TO WAGER PER DRAW?                                      |\n|";
            cout << "                                                                                 |\n";
            for (int i = 1; i < 11; i++)
            {
                if (targetTicket.getwagerAmount() == i)
                {
                    
                    cout << "|  ";
                    printf("\033[0;31m"); //print red text to terminal
                    cout << " $"<<i;
                    printf("\033[0;37m"); //revert back to white
                    cout << "  ";
                }
                else
                {
                    cout << "|  $" << i << "  ";
                }
            }

            cout << "|         |\n-----------------------------------------------------------------------------------\n";
            cout << "| 3. PICK YOUR OWN SPOTS?                                                         |\n|";
            cout << "                                                                                 |\n";
            for (int i = 1; i < 81; i++)
            {
                int counter = 0;

                for (int j = 0; j < targetTicket.getNumberofSpots(); j++)
                {
                    if (numberChoices[j] == i && counter == 0)
                    {
                        counter++;
                        cout << "| ";
                        printf("\033[0;36m"); //print cyan text to terminal
                        cout<< i;
                        printf("\033[0;37m"); //revert back to white
                        cout << " |";
                        if (i == 10) printf("                               |");
                        if( i % 10 == 0 && i != 0 ) printf("                      |\n");
                    }
                }

                if(counter == 0)
                    {
                        cout << "| " << i << " |";
                        if (i == 10) printf("                               |");
                        if( i % 10 == 0 && i != 0 ) printf("                      |\n");
                    }
            }
            cout << "-----------------------------------------------------------------------------------\n\n\n\n";  
        }

        virtual void selectNumbers(int spots, int * resultArray) //passes in number of ticket spots, and a pointer to pass the address of an array initialized outside the function call
        {

            //Variables
            int numChoice; //user input of a selected number
            std::vector<int> selectedNumbers; //vector of numbers selected by a user
            bool checkRepeat = true;

            //fill array with valid user input
            for (int i = 0; i < spots; i++)
            {
                std::cin >> numChoice; //input number value

                if (numChoice < 1 || numChoice > MAXGRIDNUMBER) //validate the number selected is within range (1-80)=
                {   
                    std::cout << "Number Out Of Range. Try Again \n";
                    i--; 
                }
                else
                {
                    for (int j = 0; j < i; j++) //iterate through entire vector to determine if there are any repeating values
                    {
                        if (numChoice == selectedNumbers[j]) //determine if number selected is already present in the vector
                        {
                            std::cout << "Repeating Value. Try Again \n";
                            checkRepeat = false; //set checkRepeat to false
                            i--; //set i to previous iteration
                            break;
                        }
                        else
                        {
                            checkRepeat = true; //if number selected is a new number set checkRepeat to true
                        }
                    }
                    if (checkRepeat == true) //if checkRepeat is true add numChoice to selectedNumbers vector
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
                resultArray[i] = selectedNumbers[i]; //store vector values into pointer address to be accessed outside the function
                std::cout << selectedNumbers[i] << ", ";
            }
            std::cout << "\n";
        }

        virtual int searchMatches(int playerNumbers[], int winningNumbers[MAXWINNINGNUMBERS], Ticket targetTicket)
        {
        
            int counter = 0; //indicates number of matches

            //iterates through two arrays to determine like elements, if like elements are found then add 1 to the counter
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


        void selectNumbers(int spots, int * resultArray) //same as selectNumbers() in ticket parent class, included in its own class to be adapted later if need be
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
                resultArray[i] = selectedNumbers[i];
                std::cout << selectedNumbers[i] << ", ";
            }
            std::cout << "\n";
        }

};


/*
------------------------------------------------------------------------------------
SPLIT TICKET
-Rules: With a keno split ticket, 
        you can play two keno games in one session. 
        A single ticket is divided between the numbers you will use for each game.
        Numbers can be have different wager amounts. The drawback here is you CANNOT 
        use the same number on both bets.

-Method: Account for two tickets in the istantiation of one object 
 
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

        //Get Functions: 

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

        void selectNumbers_split(int spots, int prevSpots, int * resultArray, int prevArray[]) //pass in number of ticket spots, number of spots from a previous ticket, pointer to pass the address of an array, and previous array of selected numbers 
        {

            //Variables
            int numChoice; //user input of a selected number
            std::vector<int> selectedNumbers; //vector of numbers selected by a user
            std::vector<int>::iterator it; //vector iterator

            //fill array with valid user input
            for (int i = 0; i < spots; i++)
            {
                int valid = 0;
                std::cin >> numChoice; //input number value

                if (numChoice < 1 || numChoice > MAXGRIDNUMBER) //validate the number selected is within range (1-80)
                {   
                    std::cout << "Number Out Of Range. Try Again \n";
                    i--; //set i to previous iteration
                }
                else
                {
                    for (int j = 0; j < prevSpots; j++) //iterate through previous ticket numbers
                    {
                        if (numChoice == prevArray[j]) //determine if number selected is already present in the previous ticket (NO DUPLICATES)
                        {
                            std::cout << "Repeating Value. Try Again \n";
                            valid = 1; //set valid to 1 
                            i--; //set i to previous iteration
                            break;                                    
                        }             
                    }

                    if (valid == 0) //check if the number selected passed the initial loop
                    {
                        if(selectedNumbers.empty()) //check if vector is empty if so add the user's choice to avoid pointing to an empty vector (Segmentation fault will occur if this is removed)
                        {
                            selectedNumbers.push_back(numChoice); //Add new number to vector
                            std::cout << "Number selected successfully \n";
                        }
                        else
                        {

                            //find function: Arguments - beginnning and end position iterators of a vector, and a constant interger value.  
                            //Return value: Compares iterator value to const int value passed in and returns iterator of first value in vector equal to the int value. 
                            //If int value is NOT found function it returns the end position (reference: https://www.cplusplus.com/reference/algorithm/find/)

                            it = std::find(selectedNumbers.begin(), selectedNumbers.end(), numChoice); 
    
                            if (it != selectedNumbers.end()) //determine iterator position is NOT at the end of the vector
                            {
                                std::cout << "Repeating Value. Try Again \n";
                                i--;                                    
                            }
                            else
                            {
                                selectedNumbers.push_back(numChoice); //Add new number to vector
                                std::cout << "Number selected successfully \n";
                            }

                        }
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

        void printTicketColor(splitTicket targetTicket, int * numberChoices1, int * numberChoices2)
        {
            //print KENO Ticket
            cout << "\n\n\n\n-----------------------------------------------------------------------------------\n";
            cout << "|                                KENO TICKET                                      |\n";
            cout << "-----------------------------------------------------------------------------------\n";
            cout << "| 1. HOW MANY SPOTS (NUMBERS) DO YOU WANT TO PLAY?                                |\n|";
            cout << "                                                                                 |\n";
            for (int i = 1; i < 11; i++)
            {
                if (targetTicket.getNumberofSpots1() == i)
                {
                    cout << "|  ";
                    printf("\033[0;31m"); //print red text to terminal
                    cout << i;
                    printf("\033[0;37m"); //revert back to white
                    cout << "  ";   
                }
                else if (targetTicket.getNumberofSpots2() == i)
                {
                    cout << "|  ";
                    printf("\033[0;32m"); //print green text to terminal
                    cout << i;
                    printf("\033[0;37m"); //revert back to white
                    cout << "  ";   
                }
                else
                {
                    cout << "|  " << i << "  ";
                }
            }

            cout << "|                    |\n-----------------------------------------------------------------------------------\n";
            cout << "| 2. HOW MUCH DO YOU WANT TO WAGER PER DRAW?                                      |\n|";
            cout << "                                                                                 |\n";
            for (int i = 1; i < 11; i++)
            {
                if (targetTicket.getWagerAmount1() == i)
                {
                    
                    cout << "|  ";
                    printf("\033[0;31m"); //print red text to terminal
                    cout << " $"<<i;
                    printf("\033[0;37m"); //revert back to white
                    cout << "  ";
                }
                else if (targetTicket.getWagerAmount2() == i)
                {
                    
                    cout << "|  ";
                    printf("\033[0;32m"); //print green text to terminal
                    cout << " $"<<i;
                    printf("\033[0;37m"); //revert back to white
                    cout << "  ";
                }
                else
                {
                    cout << "|  $" << i << "  ";
                }
            }

            cout << "|         |\n-----------------------------------------------------------------------------------\n";
            cout << "| 3. PICK YOUR OWN SPOTS?                                                         |\n|";
            cout << "                                                                                 |\n";
            for (int i = 1; i < 81; i++)
            {
                int counter = 0;

                for (int j = 0; j < targetTicket.getNumberofSpots1(); j++)
                {
                    if (numberChoices1[j] == i && counter == 0)
                    {
                        counter++;
                        cout << "| ";
                        printf("\033[0;36m"); //print cyan text to terminal
                        cout<< i;
                        printf("\033[0;37m"); //revert back to white
                        cout << " |";
                        if (i == 10) printf("                               |");
                        if( i % 10 == 0 && i != 0 ) printf("                      |\n");
                    }
                }

                for (int j = 0; j < targetTicket.getNumberofSpots2(); j++)
                {
                    if (numberChoices2[j] == i && counter == 0)
                    {
                        counter++;
                        cout << "| ";
                        printf("\033[0;36m"); //print cyan text to terminal
                        cout<< i;
                        printf("\033[0;37m"); //revert back to white
                        cout << " |";
                        if (i == 10) printf("                               |");
                        if( i % 10 == 0 && i != 0 ) printf("                      |\n");
                    }
                }

                if(counter == 0)
                    {
                        cout << "| " << i << " |";
                        if (i == 10) printf("                               |");
                        if( i % 10 == 0 && i != 0 ) printf("                      |\n");
                    }
            }
            cout << "-----------------------------------------------------------------------------------\n\n\n\n";  
        }

};



/*
---------------------------------------------------------------------------------------------------
WAY TICKET
-Rules: Way tickets let you play more than one keno ticket at the same time. 
        A player can bet on their chosen numbers at once without needing to buy multiple tickets.

-Method: Have user select number of tickets they would like to play in one sitting, store into a vector,
        and iterate/call specific funtcions in main
        (For simplicity create multiple Straight Tickets on a larger scale)
---------------------------------------------------------------------------------------------------
*/

class wayTicket : public Ticket 
{

    public:

        wayTicket(int numberofSpots, float wagerAmount) : Ticket(numberofSpots, wagerAmount){
            this -> ticketName = "Way Ticket";
        }

        void selectNumbers(int spots, int * resultArray){

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
};

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

#endif