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
        std::string output = protocol.parseStompMessageFromServer(response);

		// print the response:
        std::cout << ">>> Recived from server " << output.length() << " bytes:" << std::endl;
        std::cout << output <<  std::endl;
        if (output == "ERROR") {
            std::cout << ">>> Exit" << std::endl;
        }
    }
}