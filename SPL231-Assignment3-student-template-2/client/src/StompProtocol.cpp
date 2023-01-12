#include "../include/StompProtocol.h"
#include <unordered_map>
using namespace std;
using std::string;

StompProtocol::StompProtocol(User &_user) : user(_user)
{
    parser = StompParser(); 
}

std::string StompProtocol::parseMessage(string message)
{
    std::unordered_map<std::string, std::string> parrsedMessage = parser.parse_stomp_message(message);
    return handleMessage(parrsedMessage);
}

string StompProtocol::handleMessage(std::unordered_map<std::string, std::string> parrsedMessage, User &user)
{
    std::string command = parrsedMessage["title"];
    std::string output = "";

    if(command == "login") 
    {
        output = handleLogin(parrsedMessage);
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





string StompProtocol::handleLogin(std::unordered_map<std::string, std::string> parrsedMessage)
{
    return "CONNECT\naccept-version:1.2\nhost:stomp.cs.bgu.ac.il\nlogin:" + parrsedMessage["name"] + "\npasscode:" + parrsedMessage["npasscode"] + "\n\n" + '\0';
} 

string StompProtocol::handleLogout(std::unordered_map<std::string, std::string> parrsedMessage)
{
    return "";
} 

string StompProtocol::handleJoin(std::unordered_map<std::string, std::string> parrsedMessage)
{
    return "";
} 


string StompProtocol::handleReport(std::unordered_map<std::string, std::string> parrsedMessage)
{
    return "";
} 

string StompProtocol::handleSummary(std::unordered_map<std::string, std::string> parrsedMessage)
{
    return "";
} 

string StompProtocol::handleExit(std::unordered_map<std::string, std::string> parrsedMessage)
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
