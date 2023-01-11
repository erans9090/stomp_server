#include "../include/ConnectionHandler.h"
#include "../include/StompProtocol.h"
#include "../include/KeyboardReader.h"
#include "../include/SocketReader.h"
#include "../include/User.h"

#include <stdlib.h>
#include <thread>

using namespace std;

int main(int argc, char *argv[]) {

	// maybe host is -  std::string host = "stomp.cs.bgu.ac.il";
	std::string host = "127.0.0.1";
	short port = 7777;

    // try to connect to the server:
    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "ERROR: can't connect to " << host << ":" << port << std::endl;
        return 1;
    }

	// create the user:
	User user();

	// create the protocol and the readers:
	StompProtocol protocol;
	KeyboardReader keyboardReader(connectionHandler, protocol);
	SocketReader socketReader(connectionHandler, protocol);

	// run the threads:
	std::thread keyboardThread(&KeyboardReader::Run, &keyboardReader);
	std::thread socketThread(&SocketReader::Run, &socketReader);

	// wait for the threads to finish:
	keyboardThread.join();
	socketThread.join();

	return 0;
}