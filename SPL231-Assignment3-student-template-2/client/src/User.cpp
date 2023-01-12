#include "../include/User.h"
#include "../include/StompParser.h"

#include <string>
#include <vector>

User::User() : receiptIdMaker(0), subIdMaker(0), userName(""), password(""), connected(false), games(), connectionHandler()
{
}

int User::getSubId()
{
    return subIdMaker++;
}

int User::getReceiptId()
{
    return receiptIdMaker++;
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
    return connected;
}

void User::setConnected(std::vector<std::string> &parsedCommand)
{

    // maybe host is -  std::string host = "stomp.cs.bgu.ac.il";
    std::vector<std::string> host_port = StompParser::parseCommand(parsedCommand.at(1),':');
	std::string host = host_port.at(0);
	short port = std::stoi(host_port.at(1));

    // try to connect to the server:
    connectionHandler = ConnectionHandler(host, port);

    if (!connectionHandler.connect()) {
        std::cerr << "ERROR: can't connect to " << host << ":" << port << std::endl;
        // connectionHandler = nullptr;
    }
    else{
        connected = true;
        userName = parsedCommand.at(2);
        password = parsedCommand.at(3);
    }
}

ConnectionHandler &User::getConnectionHandler()
{
    return connectionHandler;
}
