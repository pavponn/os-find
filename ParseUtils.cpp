//
// Created by Павел Пономарев on 2019-03-31.
//

#include "ParseUtils.h"
#include <sstream>

std::vector<std::string> ParseUtils::splitString(std::string const& str) {
    std::istringstream stream(str);
    std::vector<std::string> result{ std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>()};
    return result;
}

std::pair<std::string, std::string> ParseUtils::parseEnvironmentalVar(std::string const& str) {
    std::string var;
    std::string value;
    if (std::count(str.begin(), str.end(), '=') > 1) {
        return std::make_pair("", "");
    }
    if (str[0] == '=' || (!isalpha(str[0]) && (str[0] != '_'))) {
        return std::make_pair("", "");
    }
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '=') {
            var = str.substr(0, i);
            value = str.substr(i + 1);
            break;
        }
    }
    if (var.empty()) {
        var = str;
    }
    return std::make_pair(var, value);
}

std::vector<std::string> ParseUtils::parsePath(std::string const& str) {
    std::stringstream buffer(str);
    std::string part;
    std::vector<std::string> result;
    while (std::getline(buffer, part, ':')) {
        result.push_back(part);
    }
    return result;
}

std::vector<std::string> ParseUtils::getArguments(int argc, char* argv[]) {
    std::vector<std::string> args;
    args.reserve(static_cast<unsigned long>(argc));
    for (size_t i = 0; i < argc; ++i) {
        args.emplace_back(argv[i]);
    }
    return args;
}
