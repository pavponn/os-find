//
// Created by Павел Пономарев on 2019-03-31.
//

#include "ShellHelper.h"
#include "ParseUtils.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <iostream>
#include <algorithm>
#include <string.h>

std::string ShellHelper::getCommand(std::vector<std::string> const& paths, std::string const& file) {
    for (auto const& path: paths) {
        std::string possiblePath = path;
        possiblePath.append("/");
        possiblePath.append(file);
        if (!access(possiblePath.c_str(), 1)) {
            return possiblePath;
        }
    }
    return file;
}

std::vector<char*> ShellHelper::getCharVector(std::vector<std::string>& cmd) {
    std::vector<char*> arguments;
    arguments.reserve(cmd.size());
    for (auto& str: cmd) {
        arguments.push_back(&str.front());
    }
    arguments.push_back(nullptr);

    return arguments;
}

std::vector<std::string> ShellHelper::getEnvironmentVector(std::map<std::string, std::string> const& env) {
    std::vector<std::string> result;
    std::transform(env.begin(), env.end(), std::back_inserter(result),
                   [](std::pair<std::string, std::string> const& p) {
                       return p.first + "=" + p.second;
                   });
    return result;
}

void ShellHelper::setDefaultEnvironmentalVars(char** envp, std::map<std::string, std::string>& environment) {
    std::vector<std::string> cur;
    for (int i = 0; *envp != nullptr; ++i) {
        std::string str(*(envp++));
        auto varInfo = ParseUtils::parseEnvironmentalVar(str);
        environment[varInfo.first] = varInfo.second;
    }
}

void ShellHelper::execute(std::vector<std::string>& cmd, std::map<std::string, std::string>& environment) {
    int status;
    pid_t pid;
    pid = fork();

    if (pid == -1) {
        printErrorMessage("fork failed.");
    }

    if (pid == 0) {
        // We are in a child
        std::vector<std::string> paths = ParseUtils::parsePath(environment["PATH"]);
        std::string execCommand = ShellHelper::getCommand(paths, cmd[0]);
        std::vector<char*> arguments = ShellHelper::getCharVector(cmd);
        std::vector<std::string> tempEnv = ShellHelper::getEnvironmentVector(environment);
        std::vector<char*> env = ShellHelper::getCharVector(tempEnv);
        if (execve(execCommand.c_str(), arguments.data(), env.data()) == -1) {
            printErrorMessage("execution failed.");
            exit(EXIT_FAILURE);
        }
    } else {
        // We are in a parent
        if (waitpid(pid, &status, 0) == -1) {
            printErrorMessage("error while executing.");
        }
    }
}

void ShellHelper::printErrorMessage(std::string const& message) {
    std::cerr << "Error occurred: " << message << " Code: " << strerror(errno) << std::endl;
}
