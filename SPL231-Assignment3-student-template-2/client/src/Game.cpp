
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

string Game::summarizeGame()
{
    string output = "";
    string eventsAsString = "";
    for (vector & v : events)
    {
        eventsAsString += v[0] + " - " + v[1] + ":\n\n" + v[2] + "\n\n";
    }
    output = teamA + " vs " + teamB +
            "Game stats: \n" +
            "General stats: \n" +
            teamA + " stats: \n" +
            "goals: " + teamAGoals + "\n" +
            "possession: " + teamAPosession + "%\n" +
            teamB + " stats: \n" +
            "goals: " + teamBGoals + "\n" +
            "possession: " + teamBPosession + "%\n" +
            "Game event reports: \n" + 
            eventsAsString + '\0';
    return output;

    // \0 needed?
}

/*
germany vs japan
Game stats:
General stats:
active: false
before halftime: false
germany stats:
goals: 1
possession: 51%
japan stats:
goals: 2
possession: 49%

*/
