#pragma once

#include <string>
#include <vector>
#include "../include/ConnectionHandler.h"
#include "../include/Game.h"
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

class User
{
    private:
        int receiptIdMaker;
        int subIdMaker;
        string userName;
        string password;
        bool isConnectionHandlerConnected;
        bool isLogedIn;
        unordered_map<string, Game> games;
        unordered_map<int, string> receiptIdToMessage;
        ConnectionHandler connectionHandler;



    public:
        User();
        int getSubId();
        int getReceiptId();
        string getUserName();
        void setUserName(std::string name);
        string getPassword();
        void setPassword(std::string password);
        bool isConnected();
        void setConnected(std::vector<std::string> &parsedCommand);
        bool isLoggedIn();
        void setLoggedIn(bool logedIn);
        ConnectionHandler &getConnectionHandler();
        void unsubscribe(string gameName);
        void addReceiptIdToMessage(int receiptId, string message);
        string getReceiptOutput(int receiptId);

        // void addGame(std::vector<std::string> game);
};