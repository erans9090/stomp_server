#include "../include/ConnectionHandler.h"
#include "../include/StompProtocol.h"
#include "../include/KeyboardReader.h"
#include "../include/SocketReader.h"
#include "../include/User.h"

#include <stdlib.h>
#include <thread>

using namespace std;

int main(int argc, char *argv[]) {

	std::cout << "Starting client" << std::endl;
	
	
	User user;

	StompProtocol protocol(user);

	KeyboardReader keyboardReader(protocol, user);
	std::thread keyboardThread(&KeyboardReader::Run, &keyboardReader);
	



	// wait for the threads to finish:
	keyboardThread.join();

	return 0;
}