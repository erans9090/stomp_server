#include "../include/StompProtocol.h"
#include "../include/SocketReader.h"

#include <thread>
#include <unordered_map>
using namespace std;
using std::string;

StompProtocol::StompProtocol(User &_user) : user(_user)
{
}

std::string StompProtocol::handleStompMessageFromServer(string message)
{
    // parse the message:
    std::unordered_map<std::string, std::string> parsedResponse = parser.parse_stomp_message(message);
    std::string command = parsedResponse["title"];
    std::string output = "";

    // handle the message:
    if(command == "CONNECTED")
    {
        user.setLoggedIn(true);
        output = "Login successful";
    }
    else if (command == "ERROR")
    {
        // get the error message:
        std::string errorMessage = parsedResponse["message"];

        // print the error message:
        output = errorMessage + "\n";
    }
    else if (command == "RECEIPT")
    {
        // get the receipt id:
        int receiptId = std::stoi(parsedResponse["receipt-id"]);
        output = user.getReceiptOutput(receiptId);
    } 
    else if (command == "MESSAGE")
    {
        // // get the game name:
        // std::string gameName = parsedResponse["destination"];
        // gameName = gameName.substr(1, gameName.length() - 1);

        // // get the body:
        // std::string body = parsedResponse["body"];

        // // get the game:
        // Game *game = user.getGame(gameName);

        // // if the game is not null:
        // if(game != nullptr)
        // {
        //     // update the game:
        //     game->updateGame(body);
        // }
        // else
        // {
        //     // create a new game:
        //     game = new Game(gameName, user.getUserName());
        //     game->updateGame(body);
        //     user.addGame(game);
        // }

        // // print the game:
        // output = game->toString();
    } 
    
    

    // return the output:
    return output;
}


string StompProtocol::buildFrameFromKeyboardCommand(std::string userCommand)
{
    std::vector<std::string> parsedCommand = parser.parseCommand(userCommand,' ');
    std::string command = parsedCommand.at(0);
    std::string output = "";

    if(command == "login") 
    {
        output = handleLogin(parsedCommand);
    } 
    else if (command == "logout")
    {

    } 
    else if (command == "join")
    {
        return "";

    } 
    else if (command == "report")
    {

    } 
    else if (command == "summary")
    {

    } 
    else if (command == "exit")
    {
        output = handleExit(parsedCommand);
    } 

    return output;
}

string StompProtocol::handleLogin(std::vector<std::string> parsedCommand)
{

    // send error if user is already logged in
    if(user.isConnected())
    {
        return "ERROR\nmessage:User is already logged in\n\n" + '\0';
    }
    
    user.setConnected(parsedCommand);

    return "CONNECT\naccept-version:1.2\nhost:stomp.cs.bgu.ac.il\nlogin:" + user.getUserName() + "\npasscode:" + user.getPassword() + "\n\n" + '\0';
}

string StompProtocol::handleLogout(std::vector<std::string> parsedCommand)
{
    return "";
} 

string StompProtocol::handleJoin(std::vector<std::string> parsedCommand)
{
    // 
    return "SUBSCRIBE\ndestination:/" + parsedCommand.at(1) + "\nid:" + std::to_string(user.getSubId()) + "\nreceipt:" + std::to_string(user.getReceiptId()) + "\n\n";
}


string StompProtocol::handleReport(std::vector<std::string> parsedCommand)
{
    // int subId = user.getSubIdOfGame(parsedCommand.at(1));
    // if(subId == -1)
    //     return "ERROR\nmessage:User is not subscribed to this game\n\n\0";
    
    // return "UNSUBSCRIBE\nid:" + subId + "\nreceipt:" + user.getReceiptId() + "\n\n";

    return "";
} 

string StompProtocol::handleSummary(std::vector<std::string> parsedCommand)
{
    return "";
} 

string StompProtocol::handleExit(std::vector<std::string> parsedCommand)
{
    user.unsubscribe(parsedCommand.at(1));
    return "DISCONNECT\nreceipt:" + std::to_string(user.getReceiptId()) + "\n\n" + '\0';
} 


std::vector<string> StompProtocol::splitStringByChar(string s, char div)
{
    std::vector<string> vector;

    stringstream ss(s);
    string word;
    while(!ss.eof()) 
    {
        std::getline(ss, word, div);
        vector.push_back(word);
    }

    return vector;
}

bool StompProtocol::getShouldTerminate()
{
    return shouldTerminate;
}

void StompProtocol::setShouldTerminate(bool value)
{
    shouldTerminate = value;
}   

