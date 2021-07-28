#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "baseclass.h"

using namespace std;

double singleRow();
double doubleRow();
double checkForMatches(string s1, string s2, string s3);


int gameplay(Player player1)
	{

		int choice = 0, repeat = 1, catchEnter = 0;;

		int balance = Player::GetBalancedb();

		while (repeat == 1)
		{
			cout << "Welcome to Slots!\n\nMenu:\n1. Single row\n2. Double row\n3. Player statistics\n4. How to play\n5. Exit\n\nMake a selection: ";
			cin >> choice;

			switch (choice)
			{
			case 1:

				winnings += singleRow();
				Player::UpdateBalance(int(balance + winnings));

				break;
			case 2:

				winnings += doubleRow();
				Player::UpdateBalance(int(balance + winnings));

				break;
			case 3:

				cout << "Player Statistics:\n\nWins: " << Player::GetWinsdb() << "\nLosses: " << Player::GetLossesdb() << "\nGames Played: " << Player::GetGamesPlayeddb() << "\nBalance: " << Player::GetBalancedb() << "\n\n==================\n" << endl;

				break;
			case 4:

				cout << "\n===== SLOTS =====\n\nIn the game of slots, the goal of the game is to pull the\nlever, which will roll random numbers. If these numbers\nline up with a specific combination, an award will be given,\ndepending on what the combination is.\n\n";

				break;

			case 5:
				exit(0);
				break;

			default:
				break;

			}

			cout << endl;
		}

		cout << "See you later! Thanks for playing slots!\n\n";


		// Updates database as game exits
		Game::UpdateAmountLost();
		Game::UpdateAmountWon();
		Game::UpdateGamesplayed();
		Game::UpdateLosses();
		Game::UpdateWins();
		
		Player::UpdateWins();
		Player::UpdateLosses();
		Player::UpdateGamesplayed();

		return 0;
	}

	double singleRow()
	{
		string symbols[5] = { "Cherries", "Bar", "Oranges", "Melons", "Plums" };
		string spins[3];

		double award = 0;

		int repeat = 1, playcount = 0;

		while (repeat == 1)
		{
			playcount++;
			cout << endl;

			for (int i = 0; i < 3; i++)
			{
				int spin = rand() % 5;
				cout << "Spin #" << i + 1 << ": " << symbols[spin] << endl;
				spins[i] = symbols[spin];

			}

			award += checkForMatches(spins[0], spins[1], spins[2]);

			Player::AddGameplayedPlayer();
			Game::AddGameplayed();

			cout << "Continue playing? (1 for yes, 0 for no): ";
			cin >> repeat;

		}


		cout << "\nYou have earned $" << award << " while playing double row slots. Exiting to main menu...\n\n";
		return award;

	}


	double doubleRow()
	{
		string symbols[5] = { "Cherries", "Bar", "Oranges", "Melons", "Plums" };
		string spins[3][2];

		double award = 0;

		int repeat = 1, playcount = 0;

		while (repeat == 1)
		{
			playcount++;
			cout << endl;

			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					int spin = rand() % 5;
					cout << "Spin #" << i + 1 << ": " << symbols[spin] << endl;
					spins[i][j] = symbols[spin];
				}

				cout << endl;

			}

			award += checkForMatches(spins[0][0], spins[0][1], spins[0][2]);
			award += checkForMatches(spins[1][0], spins[1][1], spins[1][2]);

			Player::AddGameplayedPlayer();
			Game::AddGameplayed();

			cout << "Continue playing? (1 for yes, 0 for no): ";
			cin >> repeat;

		}

		cout << "\nYou have earned $" << award << " while playing double row slots. Exiting to main menu...\n\n";
		return award;


	}


	double checkForMatches(string spin1, string spin2, string spin3)
	{
		double award = 0;
		string symbols[5] = { "Cherries", "Bar", "Oranges", "Melons", "Plums" };

		lossCount = 0;

		cout << "\nChecking for matches...\n\n";

		bool matching = false;

		if (spin1 == symbols[0] && spin2 == symbols[0] && spin3 == symbols[0])
		{
			cout << "Winner! You spun three cherries. Your award is $250" << endl;
			award += 250;
			Game::AddLoss();
			Player::AddWinPlayer();
			
		}
		else if (spin1 == symbols[1] && spin2 == symbols[1] && spin3 == symbols[1])
		{
			cout << "Winner! You spun three bars. Your award is $5000" << endl;
			award += 5000;
			Game::AddLoss();
			Player::AddWinPlayer();

		}
		else if (spin1 == symbols[2] && spin2 == symbols[2] && spin3 == symbols[2])
		{
			cout << "Winner! You spun three oranges. Your award is $500" << endl;
			award += 500; 
			Game::AddLoss();
			Player::AddWinPlayer();

		}
		else if (spin1 == symbols[3] && spin2 == symbols[3] && spin3 == symbols[3])
		{
			cout << "Winner! You spun three melons. Your award is $750" << endl;
			award += 750;
			Game::AddLoss();
			Player::AddWinPlayer();

		}
		else if (spin1 == symbols[4] && spin2 == symbols[4] && spin3 == symbols[4])
		{
			cout << "Winner! You spun three plums. Your award is $300" << endl;
			award += 300;
			Game::AddLoss();
			Player::AddWinPlayer();

		}
		else
		{
			cout << "No matching symbols were spun, no award given.\n";
			losscount++;
			Game::AddWin();
			Player::AddLossPlayer();

		}

		Game::AddAmountLost(award);
		Game::AddAmountWon(lossCount * 5);

		return award;
	}