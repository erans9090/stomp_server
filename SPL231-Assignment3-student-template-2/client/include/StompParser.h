#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class StompParser
{
private:

public:
    StompParser();
    std::unordered_map<std::string, std::string> parse_stomp_message(std::string& message);
};
