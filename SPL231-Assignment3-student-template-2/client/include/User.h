#pragma once

#include <string>
#include <vector>
#include "../include/ConnectionHandler.h"
#include "../include/Game.h"
#include <unordered_map>
#include <map>
#include <hash_map>


using std::string;
using std::vector;
using std::unordered_map;
using std::map;


class User
{
    private:
        int receiptIdMaker;
        int subIdMaker;
        string userName;
        string password;
        bool isConnectionHandlerConnected;
        bool isLogedIn;
        vector<string> gameNames;
        vector<Game> games;
        // map<string,Game> games;
        map<int, string> receiptIdToMessage;
        ConnectionHandler connectionHandler;



    public:
        User();
        int getSubId();
        int getReceiptId(string receiptOutput);
        string getUserName();
        void setUserName(std::string name);
        string getPassword();
        void setPassword(std::string password);
        bool isConnected();
        void setConnected(std::vector<std::string> &parsedCommand);
        bool isLoggedIn();
        void setLoggedIn(bool logedIn);
        ConnectionHandler &getConnectionHandler();
        void subscribe(string gameName);
        void unsubscribe(string gameName);
        void unsubscribeAll();
        void disconnect();
        void addReceiptIdToMessage(int receiptId, string message);
        string getReceiptOutput(int receiptId);
        void updateGame(string gameName,string body,string user);
        void send(string message);
        void summreizeGame(string gameName,string userName,string fileName);
        int indexOf(string gameName);

        

        // void addGame(std::vector<std::string> game);
};