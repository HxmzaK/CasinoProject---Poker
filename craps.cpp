#include "craps.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <limits>

using namespace std;

void win(int bet, int& balance, Player& player, Game& Craps)
{
    cout << "You won !!" << endl;
    balance += bet;
    player.AddWinPlayer();
    player.setAmountWon(player.getAmountWon() + bet);
    Craps.AddAmountwon(bet);
    Craps.AddWin();
}

void loss(int bet, int& balance, Player& player, Game& Craps)
{
    cout << "You lost !!" << endl;
    balance -= bet;
    player.AddLossPlayer();
    player.setAmountLost(player.getAmountLost() + bet);
    Craps.AddAmountLost(bet);
    Craps.AddLoss();
}

void PlayCraps(Player& player) 
{
    srand(time(0));
    Game Craps(7);
    cout << "Welcome to CRAPS " << player.getName() << endl << endl;
    double bet;
    int dice1, dice2, sumdice, old_sumdice;
    char answer;
    auto balance = player.GetBalancedb();
    while (1)
    {
        cout << "You have " << balance << " $" << endl << endl;
        do
        {
            cout << "Please enter your bet : ";
            cin >> bet;
            if (bet > balance) cout << "You don't have enough money" << endl;
        } while (bet > balance);


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
            
            win(bet, balance, player, Craps);
        }
        else if (sumdice == 2 || sumdice == 3 || sumdice == 12)
        {
            loss(bet, balance, player, Craps);

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
                    win(bet, balance, player, Craps);

                    break;
                }
                else if (sumdice == 7)
                {
                    loss(bet, balance, player, Craps);

                    break;
                }
            }
        }
        cout << "Your amount is : " << balance << endl;
        player.AddGameplayedPlayer();
        Craps.AddGameplayed();
        cout << "Do you want to play again ?(y-Y/n-N)";
        do
        {
            fflush(stdin);
            cin >> answer;
        } while (answer != 'n' && answer != 'y' && answer != 'N' && answer != 'Y');
        if (answer == 'N' || answer == 'n') break;

    }

    player.UpdateBalance(balance);
    player.UpdateLosses();
    player.UpdateWins();
    player.UpdateGamesplayed();
    Craps.UpdateAmountLost();
    Craps.UpdateAmountwon();
    Craps.UpdateGamesplayed();
    Craps.UpdateLosses();
    Craps.UpdateWins();
}