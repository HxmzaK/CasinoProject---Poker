#include "craps.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <limits>

using namespace std;

CrapsGame::CrapsGame()
{
    player.name = "unknown";
    player.amount = 0;
}

CrapsGame::CrapsGame(string my_name, double my_amount)
{
    player.name = my_name;
    player.amount = my_amount;
}

void CrapsGame::PlayGame()
{
    srand(time(0));
    cout << "Welcome to CRAPS " << player.name << endl << endl;
    double bet;
    int dice1, dice2, sumdice, old_sumdice;
    char answer;
    while (1)
    {
        cout << "You have " << player.amount << " $" << endl << endl;
        do
        {
            cout << "Please enter your bet : ";
            cin >> bet;
            if (bet > player.amount) cout << "You don't have enough money" << endl;
        } while (bet > player.amount);


        cout << "Do you want to roll?(y)";
        do
        {
            fflush(stdin);
            cin >> answer;
        } while (answer != 'y');


        dice1 = rand() % 6 + 1;
        dice2 = rand() % 6 + 1;
        sumdice = dice1 + dice2;
        cout << "Dice 1 : " << dice1 << " Dice 2 : " << dice2 << endl;
        cout << "Sum dice : " << sumdice << endl << endl;
        if (sumdice == 7 || sumdice == 11)
        {
            cout << "You won !!" << endl;
            player.amount += bet;
        }
        else if (sumdice == 2 || sumdice == 3 || sumdice == 12)
        {
            cout << "You lost !!" << endl;
            player.amount -= bet;
        }
        else
        {
            old_sumdice = sumdice;
            while (1)
            {
                cout << "Continue rolling dice" << endl;

                cout << "Do you want to roll?(y)";
                do
                {
                    fflush(stdin);
                    cin >> answer;
                } while (answer != 'y');

                dice1 = rand() % 6 + 1;
                dice2 = rand() % 6 + 1;
                sumdice = dice1 + dice2;

                cout << "Dice 1 : " << dice1 << " Dice 2 : " << dice2 << endl;
                cout << "Sum dice : " << sumdice << endl << endl;

                if (sumdice == old_sumdice)
                {
                    cout << "You won !!" << endl;
                    player.amount += bet;
                    break;
                }
                else if (sumdice == 7)
                {
                    cout << "You lost !!" << endl;
                    player.amount -= bet;
                    break;
                }
            }
        }
        cout << "Your amount is : " << player.amount << endl;
        cout << "Do you want to play again ?(y-Y/n-N)";
        do
        {
            fflush(stdin);
            cin >> answer;
        } while (answer != 'n' && answer != 'y' && answer != 'N' && answer != 'Y');
        if (answer == 'N' || answer == 'n') break;

    }
}