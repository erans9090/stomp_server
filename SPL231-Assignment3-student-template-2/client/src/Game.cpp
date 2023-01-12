
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

void Game::updateGame(string body,string user)
{
    Event event = StompParser::parseEvent(body);
    // update game stats
    std::map<string, string> teamAUpdates = event.get_team_a_updates();
    std::map<string, string> teamBUpdates = event.get_team_b_updates();
    std::map<string, string> gameUpdates = event.get_game_updates();

    teamAGoals = std::stoi(teamAUpdates["goals"]);
    teamAPosession = teamAUpdates["possession"];
    teamBGoals = std::stoi(teamBUpdates["goals"]);
    teamBPosession = teamBUpdates["possession"];

    // update events
    vector<string> eventToPush;

    eventToPush.push_back(std::to_string(event.get_time()));
    eventToPush.push_back(event.get_name());
    eventToPush.push_back(event.get_discription());
    eventToPush.push_back(user);
    

    events.push_back(eventToPush);
    

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
