#include "../include/StompParser.h"
#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include "../include/json.hpp"

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
        // add body
        if (data.size() > 0) {
            result["body"] = data;
        }
    }
    result["title"] = title;
    return result;
}

std::vector<std::string> StompParser::parseCommand(const std::string& command, char del) {
    std::vector<std::string> result;
    std::string current_word;
    for (const char c : command) {
        if (c == del) {
            result.push_back(current_word);
            current_word.clear();
        } else {
            current_word += c;
        }
    }
    result.push_back(current_word);
    return result;
}

std::string StompParser::getStringFromMap(std::map<std::string, std::string> map) 
{
    std::string result;
    for (auto it = map.begin(); it != map.end(); ++it) {
        result += "    " + it->first + ":" + it->second + "\n";
    }
    return result;
}
// 
Event StompParser::parseEvent(std::string body)
{
    nlohmann::json event = nlohmann::json::parse(body);

    //use the code from even.cpp parse events for one event
    std::string team_a_name = event["team a"];
    std::string team_b_name = event["team b"];

    std::string name = event["event name"];
    int time = event["time"];
    std::string description = event["description"];
    std::map<std::string, std::string> game_updates;
    std::map<std::string, std::string> team_a_updates;
    std::map<std::string, std::string> team_b_updates;
    for (auto &update : event["general game updates"].items())
    {
        if (update.value().is_string())
            game_updates[update.key()] = update.value();
        else
            game_updates[update.key()] = update.value().dump();
    }

    for (auto &update : event["team a updates"].items())
    {
        if (update.value().is_string())
            team_a_updates[update.key()] = update.value();
        else
            team_a_updates[update.key()] = update.value().dump();
    }

    for (auto &update : event["team b updates"].items())
    {
        if (update.value().is_string())
            team_b_updates[update.key()] = update.value();
        else
            team_b_updates[update.key()] = update.value().dump();
    }
    
    return Event(team_a_name, team_b_name, name, time, game_updates, team_a_updates, team_b_updates, description);

}

std::unordered_map<std::string, std::string> StompParser::parse_stomp_report(std::string& message) 
{
    std::unordered_map<std::string, std::string> result;
    std::string title;
    std::size_t pos = message.find('\n');
    if (pos != std::string::npos) {
        title = message.substr(0, pos);
        std::string data = message.substr(pos + 1);
        for (int i = 0; i < 3; i++) {
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
        // add body
        if (data.size() > 0) {
            result["body"] = data;
        }
    }
    result["destination"] = result["destination"].substr(1);
    result["title"] = title;
    return result;
}



    