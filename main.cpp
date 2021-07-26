#include <iostream> 
#include <stdio.h>
#include <sqlite3.h>
#include <string> 
using namespace std;

static int callbacklogin(void* data, int argc, char** argv, char** azColName){       
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

Player login(){
    std::string id;
    std::cout << "Please enter your ID\n";
    std::cin >> id;

    sqlite3* DB;
    char* messageError;
    int exit = 0;
    std::vector<std::string> container;// iniitializes vector for the selection to put results
    exit = sqlite3_open("casinodata.db", &DB);   //open the database

    std::string cmd("SELECT * FROM PLAYERS WHERE ID ="+id+");");

    exit = sqlite3_exec(DB, cmd.c_str(), callbacklogin, &container, &messageError);

    //container[0] = id container[1] = firstname container[2]   

    Player player(container[0],container[1],container[2]);

    return (player);
}

int GetNextid(){
    sqlite3* DB;
    char* messageError;
    int exit = 0;
    std::vector<std::string> container;// iniitializes vector for the selection to put results
    exit = sqlite3_open("casinodata.db", &DB);   //open the database

    std::string cmd("SELECT max( ID ) FROM PLAYERS;");//get the largest id

    exit = sqlite3_exec(DB, cmd.c_str(), callbacklogin, &container, &messageError);

    int currentid = std::stoi(container[0]);//converts the response from db to an integer
    return (currentid+1);
    
}

Player NewUser(){
//AJ

    std::string firstname;
    std::string lastname;


    whilenotype = 0;// will stop while loop after following code runs
    cout<< "Enter your First Name\n";
    cin >> firstname;
    cout<< "Enter your Last Name\n";
    cin >> lastname;
    
    std::string id = std::to_string(GetNextid());
    Player newPlayer(id, firstname, lastname);
    newPlayer.add2DB();
    
}


int main(){
    int uin; // user input variable 
    int mainLoop = 1;
    int exit = 1; // will loop until the user chooses to stop it 
    

    while (mainLoop == 1)
    {
        //Login information for test:
       


        //Process 1: Log In/Create New Account
        int type = 0;
        while(type == 0)
        {
            cout << "To login press '0', to create a new account press '1'  \n";
            int log;
            cin >> log;

                switch (log)
                {
                    case 0:{
                        //Log-in Funtion
                         Player player = login();
                        
                            break;
                }
                case 1:{
                    NewUser(); //Create a new account function
                    break;
                }
                default:{
                    cout << "Enter a valid input. \n";
                    break;
                }
            }
        }
        while (exit != 0)
        {
            std::cout << "Welcome To the Casino!\n";
            int Choice;
                    cout << "Casino Menu: \n";
                    cout << "Enter '0' To Exit Menu\nEnter '1' for Blackjack\nEnter '2' for Keno\nEnter '3' for Poker\nEnter '4' for Roulette\nEnter '5' for Slots\nEnter '6' for Bingo\n";
                    cin >> Choice;

                    switch (Choice)
                    {
                        case 0:
                        {
                            cout << "Menu exited!\n";
                            exit = 0;
                            break;
                        }
                        case 1: 
                        {
                            cout << "Welcome to Blackjack!\n";
                              
                        }
                        case 2:
                        {
                            cout << "Welcome to Keno!\n";
                        }
                        case 3:
                        {
                            cout << "Welcome to Poker!\n";
                        }
                        case 4:
                        {
                            cout << "Welcome to Roulette!\n";
                        }
                        case 5:
                        {
                            cout << "Welcome to Slots!\n";
                        }
                        case 6: 
                        {
                            cout << "Welcome to Bingo\n";
                        }
                        

    return 0;
}