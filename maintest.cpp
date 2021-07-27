#include <iostream> 
#include <stdio.h>
#include <sqlite3.h>
#include <string> 
#include "blackjack.h"
using namespace std;


static int callbacklogin(void* data, int argc, char** argv, char** azColName){       
//AJ        
    int i; 
        for (i = 0; i < argc; i++) 
        { 
        	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
            //https://stackoverflow.com/questions/60811670/how-do-i-store-into-a-c-variables-using-sqlite3
            auto &container = *static_cast<std::vector<std::string>*>(data);
            container.push_back(argv[i]); // stores the return of the selection to the container(4th arg of exec)
        } 
        printf("\n"); 
        
        return 0; 
}

int GetNextid(){
    sqlite3* DB;
    char* messageError;
    int exit = 0;
    int currentid = 0;
    std::vector<std::string> container;// iniitializes vector for the selection to put results
    exit = sqlite3_open("casinodata.db", &DB);   //open the database

    std::string cmd("SELECT max( ID ) FROM PLAYERS;");//get the largest id

    exit = sqlite3_exec(DB, cmd.c_str(), callbacklogin, &container, &messageError);
    sqlite3_close(DB);

    if(!container.empty()){
        currentid = std::stoi(container[0]);//converts the response from db to an integer
    }

    currentid++;
    return (currentid);
    
}

Player login(){
    Player player(0,"no name","");
    int id;
    std::cout << "Please enter your ID\n";
    std::cin >> id;

    sqlite3* DB;
    char* messageError;
    int exit = 0;
    std::vector<std::string> container;// iniitializes vector for the selection to put results
    exit = sqlite3_open("casinodata.db", &DB);   //open the database

    std::string cmd("SELECT * FROM PLAYERS WHERE ID ="+std::to_string(id)+";");

    exit = sqlite3_exec(DB, cmd.c_str(), callbacklogin, &container, &messageError);

    //container[0] = id container[1] = firstname container[2] = lastname  
    if(!container.empty()){
        player = Player(std::stoi(container[0]),container[1],container[2]);
        cout << "0: " << container[0] << " 1: " << container[1] << " 2: " << container[2] << endl;
    }
    return (player);
}


int main(){
	
	// Testriggedbj();
	Player player = login();
	cout << player.getName() <<std::endl;
	return 0;
}