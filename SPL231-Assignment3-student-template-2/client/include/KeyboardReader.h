#pragma once

#include "../include/ConnectionHandler.h"
#include "../include/StompProtocol.h"


class KeyboardReader
{
public:
    KeyboardReader(ConnectionHandler &connectionHandler, StompProtocol &protocol);
    void Run();

private:
    ConnectionHandler &connectionHandler;
    bool shouldTerminate;
    StompProtocol &protocol;
};