#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class User
{
    private:
        int receiptIdMaker;
        string userName;
        string password;
        bool connected;
        vector<vector<string>> games;

    public:
        User();
        int getReceiptId();
        string getUserName();
        void setUserName(std::string name);
        string getPassword();
        void setPassword(std::string password);
        bool isConnected();
        void setConnected(bool connected);
        // void addGame(std::vector<std::string> game);
};