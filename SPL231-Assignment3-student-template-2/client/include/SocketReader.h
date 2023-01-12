#pragma once

#include "../include/ConnectionHandler.h"
#include "../include/StompProtocol.h"
#include "../include/User.h"

class SocketReader
{
public:

    SocketReader(StompProtocol &protocol,User &user);
    void Run();

private:
    bool shouldTerminate;
    StompProtocol &protocol;
    User &user;

};
