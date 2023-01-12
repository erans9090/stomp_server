#include "../include/StompProtocol.h"
#include "../include/SocketReader.h"

#include <thread>
#include <unordered_map>
using namespace std;
using std::string;

StompProtocol::StompProtocol(User &_user) : user(_user)
{
}

std::string StompProtocol::handleStompMessageFromServer(string message)
{
    // parse the message:
    std::unordered_map<std::string, std::string> parsedResponse = parser.parse_stomp_message(message);
    std::string command = parsedResponse["title"];
    std::string output = "";

    // handle the message:
    if(command == "CONNECTED")
    {
        user.setLoggedIn(true);
        output = "Login successful";
    }
    else if (command == "ERROR")
    {
        output = parsedResponse["message"];
    }
    else if (command == "RECEIPT")
    {
        int receiptId = std::stoi(parsedResponse["receipt-id"]);
        output = user.getReceiptOutput(receiptId);
    } 
    else if (command == "MESSAGE")
    {
        std::string gameName = parsedResponse["destination"];
        user.updateGame(gameName, parsedResponse);
    } 

    // return the output:
    return output;
}


string StompProtocol::buildFrameFromKeyboardCommand(std::string userCommand)
{
    std::vector<std::string> parsedCommand = parser.parseCommand(userCommand,' ');
    std::string command = parsedCommand.at(0);
    std::string output = "";

    if(command == "login") 
    {
        output = handleLogin(parsedCommand);
    } 
    else if (command == "logout")
    {
        output = handleLogout(parsedCommand);
    } 
    else if (command == "join")
    {
        output = handleJoin(parsedCommand);
    } 
    else if (command == "report")
    {
        output = handleReport(parsedCommand);
    } 
    else if (command == "summary")
    {
        output = handleSummary(parsedCommand);
    } 
    else if (command == "exit")
    {
        output = handleExit(parsedCommand);
    } 

    return output;
}

string StompProtocol::handleLogin(std::vector<std::string> parsedCommand)
{

    // send error if user is already logged in
    if(user.isConnected())
    {
        std::cout << "User is already logged in" << std::endl;
        return "";
    }
    
    user.setConnected(parsedCommand);

    return "CONNECT\naccept-version:1.2\nhost:stomp.cs.bgu.ac.il\nlogin:" + user.getUserName() + "\npasscode:" + user.getPassword() + "\n\n" + '\0';
}

string StompProtocol::handleLogout(std::vector<std::string> parsedCommand)
{
    user.disconnect();
    int receiptId = user.getReceiptId("");
    return "DISCONNECT\nreceipt:" + std::to_string(receiptId) + "\n\n" + '\0';
} 

string StompProtocol::handleJoin(std::vector<std::string> parsedCommand)
{
    user.subscribe(parsedCommand.at(1));
    int receiptId = user.getReceiptId("Joined channel " + parsedCommand.at(1));
    return "SUBSCRIBE\ndestination:/" + parsedCommand.at(1) + "\nid:" + std::to_string(user.getSubId()) + "\nreceipt:" + std::to_string(receiptId) + "\n\n";
}

string StompProtocol::handleReport(std::vector<std::string> parsedCommand)
{
    names_and_events gameEvents = parseEventsFile(parsedCommand.at(1));

    string teamA = gameEvents.team_a_name;
    string teamB = gameEvents.team_b_name;
    for (Event& e : gameEvents.events)
    {
        map<string,string> genral_game_updates = e.get_game_updates();
        map<string,string> team_a_updates = e.get_team_a_updates();
        map<string,string> team_b_updates = e.get_team_b_updates();
        string output = "SEND\ndestination:/" + parsedCommand.at(2) +
                        "user: " + user.getUserName() + "\n" +
                        "teamA: " + teamA + "\n" + 
                        "teamB: " + teamB + "\n" +
                        "time: " + std::to_string(e.get_time()) + "\n" +
                        "event name :" + e.get_name() + "\n" +
                        "general game updates: \n" + StompParser::getStringFromMap(e.get_game_updates()) + "\n" +
                        "team a updates: \n" + StompParser::getStringFromMap(e.get_team_a_updates()) + "\n" +
                        "team b updates: \n" + StompParser::getStringFromMap(e.get_team_b_updates()) + "\n" +
                        "description: " + e.get_discription() + '\0';
        user.send(output);
    }

    return "";
} 

string StompProtocol::handleSummary(std::vector<std::string> parsedCommand)
{
    // assuming the game stats updated proprly
    string gameName = parsedCommand.at(1);

    user.printGameSummary(user.summreizeGame(gameName));

    return "";
} 

// exits from a game send unsubscribe frame
string StompProtocol::handleExit(std::vector<std::string> parsedCommand)
{
    user.unsubscribe(parsedCommand.at(1));
    int receiptId = user.getReceiptId("Exited channel " + parsedCommand.at(1));
    return "DISCONNECT\nreceipt:" + std::to_string(receiptId) + "\n\n" + '\0';
} 


std::vector<string> StompProtocol::splitStringByChar(string s, char div)
{
    std::vector<string> vector;

    stringstream ss(s);
    string word;
    while(!ss.eof()) 
    {
        std::getline(ss, word, div);
        vector.push_back(word);
    }

    return vector;
}

bool StompProtocol::getShouldTerminate()
{
    return shouldTerminate;
}

void StompProtocol::setShouldTerminate(bool value)
{
    shouldTerminate = value;
}   

