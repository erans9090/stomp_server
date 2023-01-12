#include "../include/KeyboardReader.h"

KeyboardReader::KeyboardReader(StompProtocol &protocol, User &_user): connectionHandler(), shouldTerminate(false), protocol(protocol)
{

}

void KeyboardReader::Run()
{
    while(!shouldTerminate)
    {
        // get a command from keyboard:
        std::cout << "Please enter command" << std::endl;

        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
		std::string line(buf);
		int len=line.length();

        // protocol get line and the keyboarReader
        std::string message = protocol.handleMessage(line);
        // TODO ----> delete these comments
        //execute sendLine only!! if the command is correct and frame was built
        //for example if there was an error on client side, createframe will return "" and sendLIne wont be executed
        if (!connectionHandler.sendLine(message)) {
            std::cout << ">>> Disconnected" << std::endl;
            std::cout << ">>> EXIT" << std::endl;
            // shouldTerminate = true;
        }
		// connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        std::cout << ">>> Sent to server " << len+1 << " bytes:" << std::endl;
        std::cout << message <<  std::endl;
    }
  
}

void keyboardReader::login(ConnectionHandler &_connectionHandler)
{
    connectionHandler = _connectionHandler;
}