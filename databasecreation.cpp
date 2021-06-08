#include <iostream> 
#include <sqlite3.h>
#include <string> 

static int callback(void* data, int argc, char** argv, char** azColName){               
    int i; 
   
        for (i = 0; i < argc; i++) 
        { 
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 
        } 
  
        printf("\n"); 
        
        return 0; 
    }


int main(){
	
	sqlite3* DB;

	int exit = 0;
		
    exit = sqlite3_open("casinodata.db", &DB); //open the database
    if (exit) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return (-1);
    }
    else
        std::cout << "Opened Database Successfully!" << std::endl;

    // code creates a Course table if one does not already exist
    std::string table = "); "; 

    // execute the create table command
    // sqlite3_exec( pointer to database file, string for sql command, callback function (used to respond to queries, not used here), input to callback, error message address)
    // exit = sqlite3_exec(DB, table.c_str(), NULL, 0, &messageError); 
    // sqlite3_close(DB);//closes the database
        
    
        
        
    char* messageError; 