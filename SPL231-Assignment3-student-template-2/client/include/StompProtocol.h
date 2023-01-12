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
    std::string handleLogin(std::unordered_map<std::string, std::string> parrsedMessage);
    std::string handleLogout(std::unordered_map<std::string, std::string> parrsedMessage);
    std::string handleJoin(std::unordered_map<std::string, std::string> parrsedMessage);
    std::string handleReport(std::unordered_map<std::string, std::string> parrsedMessage);
    std::string handleSummary(std::unordered_map<std::string, std::string> parrsedMessage);
    std::string handleExit(std::unordered_map<std::string, std::string> parrsedMessage);
    std::vector<std::string> splitStringByChar(std::string s, char del);

public:
    StompProtocol(User &_user);
    std::string parseMessage(std::string message);
    std::string handleMessage(std::unordered_map<std::string, std::string> parrsedMessage);
    bool getShouldTerminate();
    void setShouldTerminate(bool value);
};
