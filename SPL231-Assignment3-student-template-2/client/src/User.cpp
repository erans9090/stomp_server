#include "../include/User.h"
#include "../include/StompParser.h"
#include "../include/ConnectionHandler.h"
#include "../include/Game.h"

#include <string>
#include <vector>
#include <unordered_map>


User::User() : receiptIdMaker(0), subIdMaker(0), userName(""), password(""), isConnectionHandlerConnected(false), isLogedIn(false), games(), receiptIdToMessage(), connectionHandler()
{
}

int User::getSubId()
{
    return subIdMaker++;
}

int User::getReceiptId(string receiptOutput)
{
    receiptIdMaker++;
    receiptIdToMessage[receiptIdMaker] = receiptOutput;
    return receiptIdMaker;
}

std::string User::getUserName() 
{
    return userName;
}

void User::setUserName(std::string name)
{
    userName = name;
}

std::string User::getPassword()
{
    return password;
}

void User::setPassword(std::string pass)
{
    password = pass;
}

bool User::isConnected()
{
    return isConnectionHandlerConnected;
}

void User::setConnected(std::vector<std::string> &parsedCommand)
{

    // maybe host is -  std::string host = "stomp.cs.bgu.ac.il";
    std::vector<std::string> host_port = StompParser::parseCommand(parsedCommand.at(1),':');
	std::string host = host_port.at(0);
	short port = std::stoi(host_port.at(1));

    // try to connect to the server:
    connectionHandler.setHostAndPort(host, port);
    // connectionHandler = ConnectionHandler(host, port);


    if (!connectionHandler.connect()) {
        std::cerr << "ERROR: can't connect to " << host << ":" << port << std::endl;
        // connectionHandler = nullptr;
    }
    else{
        isConnectionHandlerConnected = true;
        userName = parsedCommand.at(2);
        password = parsedCommand.at(3);
    }
}

bool User::isLoggedIn()
{
    return isLogedIn;
}

void User::setLoggedIn(bool loggedIn)
{
    isLogedIn = loggedIn;
}

ConnectionHandler &User::getConnectionHandler()
{
    return connectionHandler;
}

void User::subscribe(string gameName)
{
    vector<string> parsedNames = StompParser::parseCommand(gameName,'_');
    games[gameName] = Game(parsedNames.at(0),parsedNames.at(1));
}

void User::unsubscribe(string gameName)
{
    games.erase(gameName);
}

void User::unsubscribeAll()
{
    games.clear();
}

void User::disconnect()
{
    connectionHandler.close();
    isConnectionHandlerConnected = false;
    isLogedIn = false;
    games.clear();
    receiptIdToMessage.clear();
    userName = "";
    password = "";
}

void User::addReceiptIdToMessage(int receiptId, string message)
{
    receiptIdToMessage[receiptId] = message;
}

std::string User::getReceiptOutput(int receiptId)
{
    return receiptIdToMessage[receiptId];
}

void User::updateGame(string gameName, std::unordered_map<std::string, std::string> body)
{
    if(games.find(gameName) == games.end())
    {
        // game not found
    }
    else
    {
        games[gameName].updateGame(body);
    }
}
void User::send(string message)
{   
    if(message == "")
        {
            std::cout << ">>> Invalid command" << std::endl;
            return;
        }
        if (!connectionHandler.sendLine(message)) {
            std::cout << ">>> Disconnected" << std::endl;
            std::cout << ">>> EXIT" << std::endl;
            // shouldTerminate = true;
        }
}

string User::summreizeGame(string gameName)
{
    return games[gameName].summreizeGame();
}