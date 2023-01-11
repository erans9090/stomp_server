#pragma once

#include "../include/ConnectionHandler.h"
#include <string>
#include <vector>

class StompProtocol
{
private:
    bool shouldTerminate;
    std::string handleLogin(std::vector<std::string> vec);
    std::string handleLogout(std::vector<std::string> vec);
    std::string handleJoin(std::vector<std::string> vec);
    std::string handleReport(std::vector<std::string> vec);
    std::string handleSummary(std::vector<std::string> vec);
    std::string handleExit(std::vector<std::string> vec);
    std::vector<std::string> splitStringByChar(std::string s, char del);

public:
    StompProtocol();
    std::string buildMessage(std::string command);
    std::string parseMessage(std::string message);
    bool getShouldTerminate();
    void setShouldTerminate(bool value);
};
