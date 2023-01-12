#pragma once

#include "../include/ConnectionHandler.h"
#include "../include/User.h"
#include "../include/StompParser.h"

#include <string>
#include <vector>
#include <unordered_map>

class StompProtocol
{
private:
    bool shouldTerminate;
    StompParser parser;
    User &user;
    

public:
    StompProtocol(User &_user);
    std::string handleStompMessageFromServer(string message);
    string buildFrameFromKeyboardCommand(std::string userCommand);
    bool getShouldTerminate();
    void setShouldTerminate(bool value);
    std::string handleLogin(std::vector<std::string> parsedCommand);
    std::string handleLogout(std::vector<std::string> parsedCommand);
    std::string handleJoin(std::vector<std::string> parsedCommand);
    std::string handleReport(std::vector<std::string> parsedCommand);
    std::string handleSummary(std::vector<std::string> parsedCommand);
    std::string handleExit(std::vector<std::string> parsedCommand);
    std::vector<std::string> splitStringByChar(std::string s, char del);
};
