#pragma once

#include <string>
#include <vector>
#include "../include/ConnectionHandler.h"

using std::string;
using std::vector;

class User
{
    private:
        int subIdMaker;
        int receiptIdMaker;
        string userName;
        string password;
        bool connected;
        vector<vector<string>> games;
        ConnectionHandler connectionHandler;


    public:
        User();
        int getsubId();
        int getReceiptId();
        string getUserName();
        void setUserName(std::string name);
        string getPassword();
        void setPassword(std::string password);
        bool isConnected();
        void setConnected(bool connected);

        // void addGame(std::vector<std::string> game);
};