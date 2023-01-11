#include "../include/SocketReader.h"

SocketReader::SocketReader(ConnectionHandler &connectionHandler, StompProtocol &protocol) : connectionHandler(connectionHandler), protocol(protocol), shouldTerminate(false) 
{}

void SocketReader::Run()
{
    while(!shouldTerminate)
    {
        std::string response;

        // get a response from the server:
        if (!connectionHandler.getLine(response)) {
            std::cout << ">>> Disconnected" << std::endl;
            std::cout << ">>> EXIT" << std::endl;
            break;
        }
        
        // parse the response:
        response = protocol.parseMessage(response);
		int len = response.length();

		// print the response:
        std::cout << ">>> Recived from server " << len << " bytes:" << std::endl;
        std::cout << response <<  std::endl;
        if (response == "ERROR") {
            std::cout << ">>> Exit" << std::endl;
        }
    }
}