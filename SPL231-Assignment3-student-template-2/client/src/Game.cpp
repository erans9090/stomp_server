
#include "../include/Game.h"

using std::string;
using std::vector;

Game::Game() : teamA(""), teamB(""), events()
{
}

Game::~Game()
{
}

Game::Game(string teamA, string teamB) : teamA(teamA),  teamB(teamB), events()
{
}

void Game::updateGame(std::unordered_map<std::string, std::string> updates)
{

}

