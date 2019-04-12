//
// Created by Павел Пономарев on 2019-03-31.
//

#pragma once

#include <vector>
#include <string>
#include <map>

class ShellHelper {
public:
    ShellHelper() = default;
    ~ShellHelper() = default;
    static void execute(std::vector<std::string>&, std::map<std::string, std::string>&);

    static std::vector<char*> getCharVector(std::vector<std::string>&);
    static std::vector<std::string> getEnvironmentVector(std::map<std::string, std::string> const&);
    static std::string getCommand(std::vector<std::string> const&, std::string const&);
private:
    static void printErrorMessage(std::string const&);

};


