#pragma once
#include <iostream>
#include <string>
using namespace std;

class Player {
    protected:
        int id;
        string name;
        int wins;
        int losses;
        int gamesPlayed; 
        float amountWon;
		    float amountLost;
        float bankAccount;

    public:

        Player(int id, string name){
            this -> id = id;
            this -> name = name;
            this-> bankAccount = 1000;
        }

        //Set Functions: Games PLayed, Wins, Losses, Amount Won, Amount Lost

        void setWins(int inputWins){
            wins = inputWins;
        }

        void setLosses(int inputLosses){
            losses = inputLosses;
        }

        void setGamesPlayed(int inputGamesPlayed){
            gamesPlayed = inputGamesPlayed;
        }
        void setAmountWon(float inputAmountWon){
            amountWon = inputAmountWon;
        }

        void setAmountLost(float inputAmountLost){
            amountLost = inputAmountLost;
        }
        void setBankAccount(float inputBankAccount){
            bankAccount = inputBankAccount;
        }

        //Get Functions: All Attributes
        int getID(){
            return id;
        }

        string getName(){
            return name;
        }
        
        int getWins(){
            return wins;
        }

        int getLosses(){
            return losses;
        }

        int getGamePlayed(){
            return gamesPlayed;
        }

        float getAmountWon(){
            return amountWon;
        }

        float getAmountLost(){
            return amountLost;
        }

        float getBankAccount(){
            return bankAccount;
        }

};



class Game {
private:
    int ID;
    string name;
    int wins;
    int losses;
    int gamesPlayed;
    float amountWon;
    float amountLost;
    float maxBet;
    float minBet;
    
    
    
public:
    
    Game(){
        wins = 0;
        losses = 0;
        gamesPlayed = 0;
        amountWon = 0;
        amountLost = 0;
        maxBet = 0;
        minBet = 0;
        }
    void SetID(int ID){
        this->ID = ID;
    }
    void SetName(string name){
        this->name = name;
    }
    void SetWins(int wins){
        this->wins = wins;
    }
    void Setlosses(int losses){
        this->losses = losses;
    }
    void SetgamesPlayed(int gp){
        this->gamesPlayed = gp;
    }
    void SetAmountWon(float amount){
        this->amountWon = amount;
    }
    void SetAmountLossed(float amount){
        this->amountLost = amount;
    }
    void SetMaxBet(float bet){
        this->maxBet = bet;
    }
    void SetMinBet(float bet){
        this->minBet = bet;
    }

    int getID(){
        return this->ID;
    }
    string getName()
    {
        return this->name;
    }
    int getWins(){
        return this->wins;
    }
    int getLosses(){
        return this->losses;
    }
    int getGamesPlayed(){
        return this->gamesPlayed;
    }
    float getAmountWon(){
        return this->amountWon;
    }
    float getAmountLost(){
        return this->amountLost;
    }
    float getMaxBet(){
        return this->maxBet;
    }
    float getMinBet(){
        return this->minBet;
    }
};

class Admin:public Player {
    public:
        void adjustGameAttributes(){

        }
        void printCheaters(){
            
        }
        Admin(int Id, string n):Player(id, name){
            Id = id;
            n = name;
            
        }
        ~Admin(){
        }
};

class Dealer:public Player {
    private: 
        string assignedGame;
    public:
        void distribution(){
            
        }
        Dealer(int Id, string n):Player(id, name){
            Id = id;
            n = name;
        }
        ~Dealer() {
            
        }
};