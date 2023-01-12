
#include "../include/Game.h"
#include <fstream>

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

void Game::summerizeGame(string userName,string fileName)
{
    string output = "";
    string eventsAsString = "";
    // auto works? why vector doesnt work?
    for (auto & v : events)
    {
        if( userName == v[3]){
            eventsAsString += v[0] + " - " + v[1] + ":\n\n" + v[2] + "\n\n";
        }
    }
    // maybe to write directly to the file
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

    // \0 needed?

    std::ofstream outfile;
    outfile.open(fileName); // opens the file for writing create it if doesnt exists
    outfile << output; // writes the content to the file
    outfile.close(); // close the file
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
