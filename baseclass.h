#pragma once
#include <iostream>
#include <string>
#include <sqlite3.h>
using namespace std;

class Player {
    protected:
        int id;
        std::string name;
        std::string lname;
        int wins;
        int losses;
        int gamesPlayed; 
        float amountWon;
        float amountLost;
        float bankAccount;

    public:

        Player(int id, std::string name, std::string lname){
            this-> id = id;
            this-> name = name;
            this-> lname = lname;
            // initializes attributes with what is currently in the db at the time of creation
            this-> bankAccount = GetBalancedb();
            this->wins = GetWinsdb();
            this->losses = GetLossesdb();
            this->gamesPlayed = GetGamesPlayeddb();
            
        }
        // count functions
        // AJ
        void AddWin(){
            wins++;
        }
        void AddLoss(){
            losses++;
        }
        void AddGameplayed(){
            gamesPlayed++;
        }

        //db functions
        //AJ
        static int callbackUpdate(void* data, int argc, char** argv, char** azColName){               
            int i; 
   
            for (i = 0; i < argc; i++) 
            { 
                printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 
            } 
      
            printf("\n"); 
            
            return 0; 
        }

        static int callbackSelect(void* data, int argc, char** argv, char** azColName){       
            //AJ        
            int i; 
            for (i = 0; i < argc; i++) 
            { 
                // https://stackoverflow.com/questions/60811670/how-do-i-store-into-a-c-variables-using-sqlite3
                auto &container = *static_cast<std::vector<std::string>*>(data);
                container.push_back(argv[i]); // stores the return of the selection to the container(4th arg of exec)
            } 
            
            return 0; 
        } 

        void add2DB(){
            //AJ
            sqlite3* DB;
            char* messageError;
            int exit = 0;
            std::vector<std::string> container;// iniitializes vector for the selection to put results
            exit = sqlite3_open("casinodata.db", &DB);   //open the database

            std::string sql("INSERT INTO PLAYERS VALUES("+std::to_string(id)+",'"+name+"','"+lname+"',1000.0,0.0,0.0,0,0,0,0);");

            exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

            if (exit != SQLITE_OK) 
            {
                std::cerr << "Error Insert" << std::endl;
                sqlite3_free(messageError);
            }
            else{
                std::cout << "Records created Successfully!" << std::endl;
            }
            sqlite3_close(DB);
        }

        int GetBalancedb(){
            sqlite3* DB;
            char* messageError;
            int exit = 0;
            int number = 0; //initializes number as 0
            exit = sqlite3_open("casinodata.db", &DB); //open the database
            std::string cmd("SELECT BALANCE FROM PLAYERS WHERE ID = "+std::to_string(id)+";");
            std::vector<std::string> container;

            exit = sqlite3_exec(DB, cmd.c_str(), callbackSelect, &container, &messageError);
            sqlite3_close(DB);

            if(!container.empty()){
                number = std::stoi(container[0]);
            }
            
            return(number);
        }

        int GetWinsdb(){
            sqlite3* DB;
            char* messageError;
            int exit = 0;
            exit = sqlite3_open("casinodata.db", &DB); //open the database
            std::string cmd("SELECT WINS FROM PLAYERS WHERE ID = "+std::to_string(id)+";");
            std::vector<std::string> container;

            exit = sqlite3_exec(DB, cmd.c_str(), callbackSelect, &container, &messageError);
            sqlite3_close(DB);

            int number = 0; //initializes number as 0
            if(!container.empty()){
                number = std::stoi(container[0]);
            }
            
            return(number);
        }

        int GetLossesdb(){
            sqlite3* DB;
            char* messageError;
            int exit = 0;
            exit = sqlite3_open("casinodata.db", &DB); //open the database
            std::string cmd("SELECT LOSSES FROM PLAYERS WHERE ID = "+std::to_string(id)+";");
            std::vector<std::string> container;

            exit = sqlite3_exec(DB, cmd.c_str(), callbackSelect, &container, &messageError);
            sqlite3_close(DB);

            int number = 0; //initializes number as 0
            if(!container.empty()){
                number = std::stoi(container[0]);
            }
            
            return(number);
        }

        int GetGamesPlayeddb(){
            sqlite3* DB;
            char* messageError;
            int exit = 0;
            exit = sqlite3_open("casinodata.db", &DB); //open the database
            std::string cmd("SELECT GAMESPLAYED FROM PLAYERS WHERE ID = "+std::to_string(id)+";");
            std::vector<std::string> container;

            exit = sqlite3_exec(DB, cmd.c_str(), callbackSelect, &container, &messageError);
            sqlite3_close(DB);
            
            int number = 0; //initializes number as 0
            if(!container.empty()){
                number = std::stoi(container[0]);
            }
            
            return(number);
        }



        void UpdateBalance(int value){
            sqlite3* DB;
            char* messageError;
            int exit = 0;
            exit = sqlite3_open("casinodata.db", &DB); //open the database

            std::string cmd("UPDATE PLAYERS SET BALANCE = "+std::to_string(value)+" WHERE ID = "+std::to_string(id)+";");
            std::vector<std::string> container;

            exit = sqlite3_exec(DB, cmd.c_str(), callbackUpdate, NULL, &messageError);
            sqlite3_close(DB);
        }

        void UpdateDeposit(float value){
            sqlite3* DB;
            char* messageError;
            int exit = 0;
            exit = sqlite3_open("casinodata.db", &DB); //open the database

            std::string cmd("UPDATE PLAYERS SET DEPOSIT = "+std::to_string(value)+" WHERE ID = "+std::to_string(id)+";");
            std::vector<std::string> container;

            exit = sqlite3_exec(DB, cmd.c_str(), callbackUpdate, NULL, &messageError);
            sqlite3_close(DB);
        }

        void UpdateWithdraw(float value){
            sqlite3* DB;
            char* messageError;
            int exit = 0;
            exit = sqlite3_open("casinodata.db", &DB); //open the database

            std::string cmd("UPDATE PLAYERS SET WITHDRAW = "+std::to_string(value)+" WHERE ID = "+std::to_string(id)+";");
            std::vector<std::string> container;

            exit = sqlite3_exec(DB, cmd.c_str(), callbackUpdate, NULL, &messageError);
            sqlite3_close(DB);
        }

        void UpdateWins(){
            sqlite3* DB;
            char* messageError;
            int exit = 0;
            exit = sqlite3_open("casinodata.db", &DB); //open the database

            std::string cmd("UPDATE PLAYERS SET WINS = "+std::to_string(wins)+" WHERE ID = "+std::to_string(id)+";");
            std::vector<std::string> container;

            exit = sqlite3_exec(DB, cmd.c_str(), callbackUpdate, NULL, &messageError);
            sqlite3_close(DB);
        }

        void UpdateLosses(){
            sqlite3* DB;
            char* messageError;
            int exit = 0;
            exit = sqlite3_open("casinodata.db", &DB); //open the database

            std::string cmd("UPDATE PLAYERS SET LOSSES = "+std::to_string(losses)+" WHERE ID = "+std::to_string(id)+";");
            std::vector<std::string> container;

            exit = sqlite3_exec(DB, cmd.c_str(), callbackUpdate, NULL, &messageError);
            sqlite3_close(DB);
        }

        void UpdateGamesplayed(){
            sqlite3* DB;
            char* messageError;
            int exit = 0;
            exit = sqlite3_open("casinodata.db", &DB); //open the database

            std::string cmd("UPDATE PLAYERS SET GAMESPLAYED = "+std::to_string(gamesPlayed)+" WHERE ID = "+std::to_string(id)+";");
            std::vector<std::string> container;

            exit = sqlite3_exec(DB, cmd.c_str(), callbackUpdate, NULL, &messageError);
            sqlite3_close(DB);
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

        std::string getName(){
            return name;
        }
        std::string getLname(){
            return lname;
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
    std::string name;
    int wins;
    int losses;
    int gamesPlayed;
    int amountWon;
    int amountLost;
    float maxBet;
    float minBet;
    
    
    
public:
    
    Game(int id){
        this->ID = id;
        // initializes atrributes to current db values 
        this->wins = GetWinsdb();
        this->losses = GetLossesdb();
        this->gamesPlayed = GetGamesPlayeddb();
        this->amountWon = GetAmountWondb();
        this->amountLost = GetAmountLostdb();
        maxBet = 0;
        minBet = 0;
        }
    void SetID(int ID){
        this->ID = ID;
    }
    void SetName(std::string name){
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

    //update functions
    //AJ
    void AddWin(){
        wins++;
    }
    void AddLoss(){
        losses++;
    }
    void AddGameplayed(){
        gamesPlayed++;
    }
    void AddAmountwon(int value){
        amountWon += value;
    }
    void AddAmountLost(int value){
        amountLost += value;
    }

    //dbfunctions
    //AJ
    static int callbackUpdate(void* data, int argc, char** argv, char** azColName){               
        int i; 
   
        for (i = 0; i < argc; i++) 
        { 
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 
        } 
  
        printf("\n"); 
        
        return 0; 
    }

    static int callbackSelect(void* data, int argc, char** argv, char** azColName){       
            //AJ        
            int i; 
            for (i = 0; i < argc; i++) 
            { 
                // https://stackoverflow.com/questions/60811670/how-do-i-store-into-a-c-variables-using-sqlite3
                auto &container = *static_cast<std::vector<std::string>*>(data);
                container.push_back(argv[i]); // stores the return of the selection to the container(4th arg of exec)
            } 
            
            return 0; 
    }

    int GetWinsdb(){
            sqlite3* DB;
            char* messageError;
            int exit = 0;
            exit = sqlite3_open("casinodata.db", &DB); //open the database
            std::string cmd("SELECT WINS FROM GAMES WHERE ID = "+std::to_string(ID)+";");
            std::vector<std::string> container;

            exit = sqlite3_exec(DB, cmd.c_str(), callbackSelect, &container, &messageError);
            sqlite3_close(DB);

            int number = 0; //initializes number as 0
            if(!container.empty()){
                number = std::stoi(container[0]);
            }
            
            return(number);
        }

    int GetLossesdb(){
        sqlite3* DB;
        char* messageError;
        int exit = 0;
        exit = sqlite3_open("casinodata.db", &DB); //open the database
        std::string cmd("SELECT LOSSES FROM GAMES WHERE ID = "+std::to_string(ID)+";");
        std::vector<std::string> container;

        exit = sqlite3_exec(DB, cmd.c_str(), callbackSelect, &container, &messageError);
        sqlite3_close(DB);

        int number = 0; //initializes number as 0
            if(!container.empty()){
                number = std::stoi(container[0]);
            }
            
            return(number);
    }

    int GetGamesPlayeddb(){
        sqlite3* DB;
        char* messageError;
        int exit = 0;
        exit = sqlite3_open("casinodata.db", &DB); //open the database
        std::string cmd("SELECT GAMESPLAYED FROM GAMES WHERE ID = "+std::to_string(ID)+";");
        std::vector<std::string> container;

        exit = sqlite3_exec(DB, cmd.c_str(), callbackSelect, &container, &messageError);
        sqlite3_close(DB);

        int number = 0; //initializes number as 0
            if(!container.empty()){
                number = std::stoi(container[0]);
            }
            
            return(number);
    }

    int GetAmountWondb(){
        sqlite3* DB;
        char* messageError;
        int exit = 0;
        exit = sqlite3_open("casinodata.db", &DB); //open the database
        std::string cmd("SELECT AMOUNT_WON FROM GAMES WHERE ID = "+std::to_string(ID)+";");
        std::vector<std::string> container;

        exit = sqlite3_exec(DB, cmd.c_str(), callbackSelect, &container, &messageError);
        sqlite3_close(DB);

        int number = 0; //initializes number as 0
            if(!container.empty()){
                number = std::stoi(container[0]);
            }
            
            return(number);
    }

    int GetAmountLostdb(){
        sqlite3* DB;
        char* messageError;
        int exit = 0;
        exit = sqlite3_open("casinodata.db", &DB); //open the database
        std::string cmd("SELECT AMOUNT_LOST FROM GAMES WHERE ID = "+std::to_string(ID)+";");
        std::vector<std::string> container;

        exit = sqlite3_exec(DB, cmd.c_str(), callbackSelect, &container, &messageError);
        sqlite3_close(DB);

        int number = 0; //initializes number as 0
            if(!container.empty()){
                number = std::stoi(container[0]);
            }
            
            return(number);
    }

    void UpdateWins(){
        sqlite3* DB;
        char* messageError;
        int exit = 0;
        exit = sqlite3_open("casinodata.db", &DB); //open the database

        std::string cmd("UPDATE GAMES SET WINS = "+std::to_string(wins)+" WHERE ID = "+std::to_string(ID)+";");
        std::vector<std::string> container;

        exit = sqlite3_exec(DB, cmd.c_str(), callbackUpdate, NULL, &messageError);
        sqlite3_close(DB);
    }

    void UpdateLosses(){
        sqlite3* DB;
        char* messageError;
        int exit = 0;
        exit = sqlite3_open("casinodata.db", &DB); //open the database

        std::string cmd("UPDATE GAMES SET LOSSES = "+std::to_string(losses)+" WHERE ID = "+std::to_string(ID)+";");
        std::vector<std::string> container;

        exit = sqlite3_exec(DB, cmd.c_str(), callbackUpdate, NULL, &messageError);
        sqlite3_close(DB);
    }

    void UpdateGamesplayed(){
        sqlite3* DB;
        char* messageError;
        int exit = 0;
        exit = sqlite3_open("casinodata.db", &DB); //open the database

        std::string cmd("UPDATE GAMES SET GAMESPLAYED = "+std::to_string(gamesPlayed)+" WHERE ID = "+std::to_string(ID)+";");
        std::vector<std::string> container;

        exit = sqlite3_exec(DB, cmd.c_str(), callbackUpdate, NULL, &messageError);
        sqlite3_close(DB);
    }

    void UpdateAmountwon(){
        sqlite3* DB;
        char* messageError;
        int exit = 0;
        exit = sqlite3_open("casinodata.db", &DB); //open the database

        std::string cmd("UPDATE GAMES SET AMOUNT_WON = "+std::to_string(gamesPlayed)+" WHERE ID = "+std::to_string(ID)+";");
        std::vector<std::string> container;

        exit = sqlite3_exec(DB, cmd.c_str(), callbackUpdate, NULL, &messageError);
        sqlite3_close(DB);
    }

    void UpdateAmountLost(){
        sqlite3* DB;
        char* messageError;
        int exit = 0;
        exit = sqlite3_open("casinodata.db", &DB); //open the database

        std::string cmd("UPDATE GAMES SET AMOUNT_LOST = "+std::to_string(amountWon)+" WHERE ID = "+std::to_string(ID)+";");
        std::vector<std::string> container;

        exit = sqlite3_exec(DB, cmd.c_str(), callbackUpdate, NULL, &messageError);
        sqlite3_close(DB);
    }



};

    


class Admin:public Player {
    public:
        Admin(int id, std::string name, std::string lname):Player(id,name,lname){

        }
        ~Admin(){
            
        }
        void adjustGameAttributes(){

        }
        void printCheaters(){
            
        }
        
};

class Dealer:public Player {
    private: 
        string assignedGame;
    public:
        Dealer(int id, std::string name, std::string lname):Player(id, name,lname){

        }
        ~Dealer() {
            
        }
        void distribution(){
            
        }
        
};