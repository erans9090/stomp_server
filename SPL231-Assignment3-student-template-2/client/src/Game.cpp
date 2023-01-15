
#include "../include/Game.h"
#include <fstream>



using std::string;
using std::vector;

Game::Game(): Game("","")
{
}

Game::~Game()
{
    events.clear();
}

Game::Game(string teamA, string teamB) : teamA(teamA), teamAGoals("0"), teamAPosession("0"), teamB(teamB), teamBGoals("0"), teamBPosession("0"), events()
{
}

// void Game::updateGame(string body)
// {
//     Event event = StompParser::parseEvent(body);
//     // update game stats
//     std::map<string, string> teamAUpdates = event.get_team_a_updates();
//     std::map<string, string> teamBUpdates = event.get_team_b_updates();
//     std::map<string, string> gameUpdates = event.get_game_updates();

//     // parse user name from body
//     size_t pos = body.find("user:");
//     string userName = body.substr(pos + 5, body.find("\n", pos) - pos - 5);
//     std::cout << "user name: " << userName << std::endl;

//     if(teamAUpdates.has_key("goals"))
//         teamAGoals = teamAUpdates["goals"];
//     if(teamAUpdates.has_key("possession"))
//         teamAPosession = teamAUpdates["possession"];
//     if(teamBUpdates.has_key("goals"))
//         teamBGoals = teamBUpdates["goals"];
//     if(teamBUpdates.has_key("possession"))
//         teamBPosession = teamBUpdates["possession"];

//     // update events
//     vector<string> eventToPush;

//     eventToPush.push_back(std::to_string(event.get_time()));
//     eventToPush.push_back(event.get_name());
//     eventToPush.push_back(event.get_discription()); // make sure that the field fit
//     eventToPush.push_back(userName);
    

//     events.push_back(eventToPush);
    

// }

void Game::updateGame(string body)
{
    string settings = body.substr(0, body.find("general"));
    string team_a_updates = body.substr(body.find("team a updates:")+15, body.find("team b"));
    string team_b_updates = body.substr(body.find("team a updates:")+15, body.find("description"));
    string description = body.substr(body.find("description:")+12);

    if (team_a_updates.find("goals:") != std::string::npos)
        teamAGoals = team_a_updates.substr(team_a_updates.find("goals:"), team_a_updates.find((team_a_updates.find("goals:"), '\n')));
    if (team_a_updates.find("possession:") != std::string::npos)
        teamAPosession = team_a_updates.substr(team_a_updates.find("possession:"), team_a_updates.find((team_a_updates.find("possession:"), '\n')));
    if (team_b_updates.find("goals:") != std::string::npos)
        teamBGoals = team_b_updates.substr(team_b_updates.find("goals:"), team_b_updates.find((team_b_updates.find("goals:"), '\n')));
    if (team_b_updates.find("possession:") != std::string::npos)
        teamBPosession = team_b_updates.substr(team_b_updates.find("possession:"), team_b_updates.find((team_b_updates.find("possession:"), '\n')));

    // update events
    vector<string> eventToPush;
    string time = settings.substr(settings.find("time:") + 6, settings.find("\n", settings.find("time:")) - settings.find("time:") - 6);
    string name = settings.substr(settings.find("name:") + 5, settings.find("\n", settings.find("name:")) - settings.find("name:") - 5);
    string user = settings.substr(settings.find("user:") + 6, settings.find("\n", settings.find("user:")) - settings.find("user:") - 6);
    
    eventToPush.push_back(time);
    eventToPush.push_back(name);
    eventToPush.push_back(description);
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
    //  make sure '/' before destenation doesnt get inside team a name
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
