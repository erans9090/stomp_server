#pragma once

#include "../include/ConnectionHandler.h"
#include "../include/StompProtocol.h"


class KeyboardReader
{
public:
    KeyboardReader(StompProtocol &protocol, User &_user);
    void Run();
    void login(ConnectionHandler &_connectionHandler);

private:
    ConnectionHandler &connectionHandler;
    bool shouldTerminate;
    StompProtocol &protocol;
};