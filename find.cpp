//
// Created by Павел Пономарев on 2019-04-11.
//
#include "FindOptions.h"
#include "ParseUtils.h"
#include "ShellHelper.h"

#include <iostream>
#include <sstream>
#include <queue>
#include <map>
#include <dirent.h>
#include <sys/stat.h>

using arguments = std::vector<std::string>;

std::map<std::string, std::string> environment;
std::vector<std::string> result;
std::string rootPath;

void setDefaultEnvironmentalVars(char** envp) {
    std::vector<std::string> cur;
    for (int i = 0; *envp != nullptr; ++i) {
        std::string str(*(envp++));
        auto varInfo = ParseUtils::parseEnvironmentalVar(str);
        environment[varInfo.first] = varInfo.second;
    }
}

arguments getArguments(int argc, char* argv[]) {
    arguments args;
    args.reserve(static_cast<unsigned long>(argc));
    for (size_t i = 0; i < argc; ++i) {
        args.push_back(std::string(argv[i]));
    }
    return args;
}

void printHelp() {
    //TODO
}

bool parseArguments(arguments const& args, FindOptions& options) {
    if (args.size() <= 1 || args[1] == "-help") {
        printHelp();
        return false;
    }
   // rootPath = args[1];
    options.setRootPath(args[1]);
    if (rootPath.back() != '/') {
        rootPath += '/';
    }
    if (args.size() % 2 == 1) {
        return false;
    }

    for (size_t i = 2; i < args.size(); i += 2) {
        const auto& curArgument = args[i];
        const auto& curValue = args[i + 1];

        if (curArgument == "-name") {
            options.setName(curValue);
            continue;
        }

        if (curArgument == "-inum") {
            size_t inode;
            std::istringstream stream(curValue);
            if (stream >> inode) {
                options.setInode(inode);
            } else {
                std::cerr << "Not a valid inode: " << curValue << std::endl;
                return false;
            }
            continue;
        }

        if (curArgument == "-size") {
            std::string size = curValue;
            char last = size.front();
            if (last == '+') {
                options.setSizeType(MORE);
            } else if (last == '-') {
                options.setSizeType(LESS);
            } else {
                options.setSizeType(EXACT);
            }
            if (last == '=' || last == '+' || last == '-') {
                size = size.substr(1);
            }
            size_t realSize;
            std::istringstream stream(size);
            if (stream >> realSize) {
                options.setSize(realSize);
            } else {
                std::cerr << "Not a valid size argument: " << size << std::endl;
                return false;
            }
            continue;
        }

        if (curArgument == "-nlinks") {
            size_t links;
            std::istringstream stream(curValue);
            if (stream >> links) {
                options.setLinks(links);
            } else {
                std::cerr << "Not a valid number of links: " << curValue << std::endl;
                return false;
            }
            continue;
        }

        if (curArgument == "-exec") {
            options.setExecPath(curValue);
            continue;
        }


        std::cerr << "Unsupported argument: " << curArgument << std::endl;
        return false;

    }

    return true;
}


bool matchFile(std::string const& filename, struct stat const& info, FindOptions const& options) {
    if (options.ifHasName() && filename != options.getName()) {
        return false;
    }

    if (options.ifHasInode() && info.st_ino != options.getInode()) {
        return false;
    }

    if (options.ifHasSize()) {
        switch (options.getSizeType()) {
            case MORE: {
                if (options.getSize() >= info.st_size) {
                    return false;
                }
                break;
            }
            case LESS: {
                if (options.getSize() <= info.st_size) {
                    return false;
                }
                break;
            }
            default: {
                if (options.getSize() != info.st_size) {
                    return false;
                }
            }
        }
    }

    return !(options.ifHasLinks() && options.getLinks() != info.st_nlink);

}

bool hasDots(char const* filename) {
    return strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0;
}
void bfsSearch(FindOptions const& options) {

    std::queue<std::pair <DIR*, std::string>> queue;
    auto root = opendir(options.getRootPath().c_str());
    if (root == nullptr) {
        std::cerr << "Root directory can't be accessed: " << strerror(errno) << std::endl;
        return;
    }
    queue.emplace(root, options.getRootPath());

    while (!queue.empty()) {
        auto curDir = queue.front();
        queue.pop();

        while (auto file = readdir(curDir.first)) {
            struct stat info{};
            auto fileName = file->d_name;

            if (!fileName || hasDots(fileName)) { //TODO: dots
                continue;
            }

            std::string filePath = curDir.second + "/" + fileName;

            if (lstat(filePath.c_str(), &info) == -1) {
                std::cerr << "Can't access file " << filePath << ": "
                << strerror(errno) << std::endl;
                continue;
            }

            if (S_ISDIR(info.st_mode)) {
                auto directory = opendir(filePath.c_str());
                if (directory != nullptr) {
                    queue.emplace(directory, filePath);
                }
            } else if (matchFile(std::string(fileName), info, options)) {
                result.push_back(filePath);
            }

        }
        closedir(curDir.first);
    }
}



int main(int argc, char* argv[], char* envp[]) {
//    for (int i = 0; i < argc; i++) {
//        std::cout << argv[i] <<std::endl;
//    }
    setDefaultEnvironmentalVars(envp);
    arguments args = getArguments(argc, argv);
    FindOptions options;
    bool isOk = parseArguments(args, options);
    if (!isOk) {
        return EXIT_FAILURE;
    }
    if (options.ifHasExecPath()) {
        result.push_back(options.getExecPath());
    }
    bfsSearch(options);

    if (!options.ifHasExecPath()) {
        for (auto const& file : result) {
            std::cout << file << std::endl;
        }
        return EXIT_SUCCESS;
    }

    ShellHelper::execute(result, environment);


    return EXIT_SUCCESS;
}