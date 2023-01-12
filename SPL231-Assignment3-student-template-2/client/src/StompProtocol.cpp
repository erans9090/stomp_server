#include "../include/StompProtocol.h"
#include <unordered_map>
using namespace std;
using std::string;

StompProtocol::StompProtocol(User &_user) : user(_user)
{
    parser = StompParser(); 
}

std::string StompProtocol::handleStompMessageFromServer(string message)
{
    // parse the message:
    std::unordered_map<std::string, std::string> parsedCommand = parser.parse_stomp_message(message);
    std::string command = parsedCommand["title"];
    std::string output = "";

    // handle the message:


    // return the output:
    return output;
}


string StompProtocol::buildFrameFromKeyboardCommand(std::string command)
{
    std::vector<std::string> parsedCommand = parser.parseCommand(command);
    std::string command = parsedCommand.at(0);
    std::string output = "";

    if(command == "login") 
    {
        output = handleLogin(parsedCommand);
    } 
    else if (command == "logout")
    {

    } 
    else if (command == "join")
    {
        return "";

    } 
    else if (command == "report")
    {

    } 
    else if (command == "summary")
    {

    } 
    else if (command == "exit")
    {

    } 

    return output;
}

string StompProtocol::handleLogin(std::vector<std::string> parsedCommand)
{

    // send error if user is already logged in
    if(user.isConnected())
    {
        return "ERROR\nmessage:User is already logged in\n\n\0"
    }
    
    user.setConnected(parsedCommand);

    return "CONNECT\naccept-version:1.2\nhost:stomp.cs.bgu.ac.il\nlogin:" + user.getUsername() + "\npasscode:" + user.getPassword() + "\n\n";

string StompProtocol::handleLogout(std::vector<std::string> parsedCommand)
{
    return "";
} 

string StompProtocol::handleJoin(std::vector<std::string> parsedCommand)
{
    return "SUBSCRIBE\ndestination:/" + parsedCommand.at(1) + "\nid:" + user.getsubId() + "\nreceipt:" + user.getReceiptId() + "\n\n";
}


string StompProtocol::handleReport(std::vector<std::string> parsedCommand)
{
    int subId = user.getSubIdOfGame(parsedCommand.at(1));
    if(subId == -1)
        return "ERROR\nmessage:User is not subscribed to this game\n\n\0";
    
    return "UNSUBSCRIBE\nid:" + subId + "\nreceipt:" + user.getReceiptId() + "\n\n";
} 

string StompProtocol::handleSummary(std::vector<std::string> parsedCommand)
{
    return "";
} 

string StompProtocol::handleExit(std::vector<std::string> parsedCommand)
{
    return "";
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

