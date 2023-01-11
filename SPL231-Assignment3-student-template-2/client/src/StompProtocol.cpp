#include "../include/StompProtocol.h"
using namespace std;

StompProtocol::StompProtocol() {}

using std::string;
string StompProtocol::buildMessage(string userCommand) 
{
    // split the command by spaces and send to the right function:
    vector<string> parsedCommand = splitStringByChar(userCommand, ' ');
    string keyword = parsedCommand.at(0);
    string output = "";
    if(keyword == "login") 
    {
        // login 1.1.1.1:2000 meni films
        output = handleLogin(parsedCommand);

    } 
    else if (keyword == "logout")
    {

    } 
    else if (keyword == "join")
    {
        return "";

    } 
    else if (keyword == "report")
    {

    } 
    else if (keyword == "summary")
    {

    } 
    else if (keyword == "exit")
    {

    } 

    return output;
}

string StompProtocol::parseMessage(string message)
{
    vector<string> parsedCommand = splitStringByChar(message, '\n');
    string keyword = parsedCommand.at(0);
    string output = "";
    if(keyword == "CONNECTED") {
        output = "login successfully";
    }
    return output;
}

string StompProtocol::handleLogin(vector<string> vec)
{
    // login 1.1.1.1:2000 meni films
    return "CONNECT\naccept-version:1.2\nhost:stomp.cs.bgu.ac.il\nlogin:" + vec.at(2) + "\npasscode:" + vec.at(3) + "\n\n" + '\0';
} 

string StompProtocol::handleLogout(vector<string> vec)
{
    return "";
} 

string StompProtocol::handleJoin(vector<string> vec)
{
    return "";
} 


string StompProtocol::handleReport(vector<string> vec)
{
    return "";
} 

string StompProtocol::handleSummary(vector<string> vec)
{
    return "";
} 

string StompProtocol::handleExit(vector<string> vec)
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
