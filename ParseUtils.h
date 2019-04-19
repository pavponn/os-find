//
// Created by Павел Пономарев on 2019-03-31.
//

#pragma once

#include <vector>
#include <string>
class ParseUtils {
public:
    ParseUtils() = default;
    ~ParseUtils() = default;

    static std::vector<std::string> splitString(std::string const&);
    static std::pair<std::string, std::string> parseEnvironmentalVar(std::string const&);
    static std::vector<std::string> parsePath(std::string const&);
    static std::vector<std::string> getArguments(int, char**);

};



