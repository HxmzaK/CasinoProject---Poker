#ifndef SYSTEM_FUNCTIONS_H
#define SYSTEM_FUNCTIONS_H

#include <iostream>
#include <string>
#include <sqlite3.h>
#include "Keno.h"

static int callback(void* data, int argc, char** argv, char** azColName){               
    int i; 
   
        for (i = 0; i < argc; i++) 
        { 
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 
        } 
  
        printf("\n"); 
        
        return 0; 
    }


/*
--------------------------------------------------------------------------------------------------
EDIT TABLE FUNCTION:

ARGUMENTS: pointer to database, sql command passed as a string, target table passed as a string

Description: editTable() function will take in a database, and edit the database based off the command
             that was passed through. Ensure the command is correct syntax.

--------------------------------------------------------------------------------------------------
*/


void editTable(sqlite3 * db, string command, string target)
{
    int exit = 0;
    char * messageError;
    string sql(command);

        exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError); 

        if (exit != SQLITE_OK) 
        { 
            cout << "--------------------------------------------------------- \n";
            cout << "System Message: Error Editing " + target << std::endl; 
            sqlite3_free(messageError); 
        } 
        else
        {
            cout << "--------------------------------------------------------- \n";            
            cout << "System Message: "<< target +" Edited Successfully" << std::endl; 
        }
}


/*
--------------------------------------------------------------------------------------
Function: winningNumbers()
    -arguments: int spots, int * resultArray
    -return value: n/a
    -description: validates randomized input of numbers ranging from 1-80 and stores 
    numbers in an array. The array of numbers can be accessed outside of the function
    through the pointer array being passed through.
    -based on selectNumbers() function in ticket class

--------------------------------------------------------------------------------------
*/

void winningNumbers(int spots, int * resultArray){

    //Variables
    int numChoice;
    std::vector<int> winningNumbers; //winning numbers vector
    bool checkRepeat = true;

    //fill array with valid user input
    for (int i = 0; i < spots; i++)
        {
            numChoice = 1 + rand() % 81; //generate random number value between 1-80

            if (numChoice < 1 || numChoice > MAXGRIDNUMBER) //validate the number selected is within range (1-80)
            {   
                i--; 
            }
            else
            {
                for (int j = 0; j < i; j++) //iterate through entire array
                {
                    if (numChoice == winningNumbers[j]) //determine if number selected is already present in the array
                    {
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
                        winningNumbers.push_back(numChoice); //Add new number to vector
                }
            }
        }

    //Print Selected Numbers To screen
    for (int i = 0; i < spots; i++)
    {
        resultArray[i] = winningNumbers[i]; //store numbers in pointer of resultArray to be called outside of function
        std::cout << winningNumbers[i] << ", ";
    }
    std::cout << "\n";
}

/*
-------------------------------------------------------------------------------
Function: prizeCalculator()
    -arguments: targetTicket, matches, wagerAmount
    -return value: winAmount
    -description: input a target ticket, number of matches from the searchMatch()
    function to run through a series of case statements that determines the amount won
    based on the amount of numbers selected, number of matches and the wager amount
    as a multiplier. Base numbers are based on 1$ wager amounts. 
    -prizes based on Massachusetts Keno prizes

-------------------------------------------------------------------------------
*/

float prizeCalculator(Ticket targetTicket, int matches, float wagerAmount){

    float winAmount; //store amount won based on prize and wager multiplier

   switch (targetTicket.getNumberofSpots())
   {
   case 1: //1 Numbers Selected
       
       switch (matches) 
       {
       case 0: //No Matches
            winAmount = 0;
           std::cout << "No Money Won \n";
           break;
        case 1: //1 Match
            winAmount = 2 * wagerAmount; //$2 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
       default:
           break;
       }
    break;

    case 2: //2 Numbers Selected

       switch (matches) 
       {
       case 0: //No Matches
            winAmount = 0;
           std::cout << "No Money Won \n";
           break;
        case 1: //1 Match
            winAmount = 2 * wagerAmount; //$2 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 2: //2 Matches
            winAmount = 10 * wagerAmount; //$2 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
       default:
           break;
       }
    break;

    case 3: //3 Numbers Selected

       switch (matches) 
       {

        case 2: //1 Match
            winAmount = 2 * wagerAmount; //$2 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 3: //3 Matches
            winAmount = 25 * wagerAmount; //$2 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
       default: //No Matches
           winAmount = 0;
           std::cout << "No Money Won \n";
           break;
       }
    break;

    case 4: //4 Numbers Selected

       switch (matches) 
       {
        case 2: //1 Match
            winAmount = 1 * wagerAmount; //$1 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 3: //3 Matches
            winAmount = 5 * wagerAmount; //$5 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 4: //3 Matches
            winAmount = 50 * wagerAmount; //$50 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
       default:
            winAmount = 0;
            std::cout << "No Money Won \n";
           break;
       }
    break;

    case 5: //5 Numbers Selected

       switch (matches) 
       {
        case 3: //3 Matches
            winAmount = 2 * wagerAmount; //$2 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 4: //4 Matches
            winAmount = 15 * wagerAmount; //$15 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 5: //5 Matches
            winAmount = 500 * wagerAmount; //$500 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
       default:
            winAmount = 0;
            std::cout << "No Money Won \n";
           break;
       }
    break;

    case 6: //6 Numbers Selected

       switch (matches) 
       {
        case 3: //3 Matches
            winAmount = 1 * wagerAmount; //$1 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 4: //4 Matches
            winAmount = 5 * wagerAmount; //$5 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 5: //5 Matches
            winAmount = 50 * wagerAmount; //$50 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 6: //6 Matches
            winAmount = 1500 * wagerAmount; //$1500 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
       default:
            winAmount = 0;
            std::cout << "No Money Won \n";
           break;
       }
    break;

    case 7: //7 Numbers Selected
       switch (matches) 
       {
        case 3: //3 Matches
            winAmount = 1 * wagerAmount; //$2 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 4: //4 Matches
            winAmount = 2 * wagerAmount; //$15 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 5: //5 Matches
            winAmount = 15 * wagerAmount; //$500 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 6: //6 Matches
            winAmount = 150 * wagerAmount; //$500 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 7: //7 Matches
            winAmount = 5000 * wagerAmount; //$500 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
       default:
            winAmount = 0;
            std::cout << "No Money Won \n";
           break;
       }
    break;

    case 8: //8 Numbers Selected
       switch (matches) 
       {
        case 4: //4 Matches
            winAmount = 2 * wagerAmount; //$2 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 5: //5 Matches
            winAmount = 10 * wagerAmount; //$15 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 6: //6 Matches
            winAmount = 10 * wagerAmount; //$500 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 7: //7 Matches
            winAmount = 400 * wagerAmount; //$500 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 8: //8 Matches
            winAmount = 15000 * wagerAmount; //$500 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
       default:
            winAmount = 0;
            std::cout << "No Money Won \n";
           break;
       }
    break;

    case 9: //9 Numbers Selected
       switch (matches) 
       {
        case 4: //4 Matches
            winAmount = 1 * wagerAmount; //$2 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 5: //5 Matches
            winAmount = 4 * wagerAmount; //$15 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 6: //6 Matches
            winAmount = 25 * wagerAmount; //$500 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 7: //7 Matches
            winAmount = 200 * wagerAmount; //$500 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 8: //8 Matches
            winAmount = 2500 * wagerAmount; //$500 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 9: //9 Matches
            winAmount = 25000 * wagerAmount; //$500 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
       default:
            winAmount = 0;
            std::cout << "No Money Won \n";
           break;
       }
    break;

    case 10: //10 Numbers Selected
       switch (matches) 
       {
        case 0: //0 Matches
            winAmount = 3 * wagerAmount; //$2 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 5: //5 Matches
            winAmount = 3 * wagerAmount; //$3 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 6: //6 Matches
            winAmount = 10 * wagerAmount; //$10 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 7: //7 Matches
            winAmount = 50 * wagerAmount; //$50 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 8: //8 Matches
            winAmount = 500 * wagerAmount; //$500 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 9: //9 Matches
            winAmount = 10000 * wagerAmount; //$10000 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
        case 10: //10 Matches
            winAmount = 200000 * wagerAmount; //$200000 dollar prize with a wager amount multiplier
            std::cout << "Prize: $" << winAmount << "!\n";
            break;
       default:
            winAmount = 0;
            std::cout << "No Money Won \n";
           break;
       }
    break;

   default:
       break;
   }

return winAmount;
}

#endif