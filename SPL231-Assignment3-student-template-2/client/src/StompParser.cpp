#include "../include/StompParser.h"
#include <iostream>
#include <unordered_map>
#include <string>

StompParser::StompParser() {}

std::unordered_map<std::string, std::string> StompParser::parse_stomp_message(std::string& message) {
    std::unordered_map<std::string, std::string> result;
    std::string title;
    std::size_t pos = message.find('\n');
    if (pos != std::string::npos) {
        title = message.substr(0, pos);
        std::string data = message.substr(pos + 1);
        while (data.size() > 0) {
            pos = data.find('\n');
            std::string line = data.substr(0, pos);
            data = data.substr(pos + 1);
            pos = line.find(':');
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                result[key] = value;
            }
        }
    }
    result["title"] = title;
    return result;
}
