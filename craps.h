#include <iostream>

using namespace std;

typedef struct CrapsPlayer
{
    string name;
    double amount;
}cpl;

class CrapsGame
{

private:
    cpl player;

public:
    CrapsGame();
    CrapsGame(string, double);
    void PlayGame();

}; 
