
#include "../include/Game.h"

using std::string;
using std::vector;

Game::Game(): Game("","")
{
}

Game::Game(string teamA, string teamB) : teamA(teamA), teamAGoals(0), teamAPosession(0), teamB(teamB), teamBGoals(0), teamBPosession(0), events()
{
}

void Game::updateGame(std::unordered_map<std::string, std::string> updates)
{
}


//     string teamA;
//     string teamAGoals;
//     string teamAPosession;

//     string teamB;
//     string teamBGoals;
//     string teamBPosession;

//     vector<vector<string>> events; 
