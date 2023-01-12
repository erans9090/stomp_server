#include "../include/SocketReader.h"

SocketReader::SocketReader(StompProtocol &protocol,User &user) : protocol(protocol), user(user), shouldTerminate(false) 
{}

void SocketReader::Run()
{
    while(!shouldTerminate)
    {
        std::string response;

        // get a response from the server:
        if (!user.getConnectionHandler().getLine(response)) {
            std::cout << ">>> Disconnected" << std::endl;
            std::cout << ">>> EXIT" << std::endl;
            break;
        }
        
        // parse the response:
        std::string output = protocol.handleStompMessageFromServer(response);

		// print the response:
        std::cout << ">>> Recived from server " << output.length() << " bytes:" << std::endl;
        std::cout << output <<  std::endl;
        if (output == "ERROR") {
            std::cout << ">>> Exit" << std::endl;
        }
    }
}