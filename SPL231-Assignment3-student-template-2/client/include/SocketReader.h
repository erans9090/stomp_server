#pragma once

#include "../include/ConnectionHandler.h"
#include "../include/StompProtocol.h"

class SocketReader
{
public:
    SocketReader(ConnectionHandler &connectionHandler, StompProtocol &protocol);
    void Run();

private:
    ConnectionHandler &connectionHandler;
    bool shouldTerminate;
    StompProtocol &protocol;

};
