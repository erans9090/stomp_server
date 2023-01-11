#include "../include/User.h"

User::User() : receiptIdMaker(0), userName(""), password(""), connected(false), games()
{
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

void User::setConnected(bool con)
{
    connected = con;
}

