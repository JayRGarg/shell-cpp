#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>
#include "get_valid_path.h"
#include "split.h"

std::string too_few_args(std::vector<std::string> arguments) {
    return arguments[0] + ": too few arguments";
}

std::string too_many_args(std::vector<std::string> arguments) {
    return arguments[0] + ": too many arguments";
}

int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    std::string input, rest;
    std::vector<std::string> args;

    std::unordered_set<std::string> builtin = {"exit", "echo", "type"};

    bool exit = false;
    int exit_status = 0;

    std::cout << "$ ";

    while (std::getline(std::cin, input)) {
        args = split(input); //splits arguments into vector, by space
        if (builtin.contains(args[0])) {
            if (args[0] == "exit") {
                if (args.size() < 2) {
                    std::cout << too_few_args(args) << std::endl;
                } else if (args.size() > 2) {
                    std::cout << too_many_args(args) << std::endl;
                } else {
                    exit_status = std::stoi(args[1]);
                    break;
                }
            } else if (args[0] == "echo") {
                for (int i=1; i<args.size(); i++) {
                    std::cout << args[i] << " ";
                }
                std::cout << std::endl;
            } else if (args[0] == "type") {
                for (int i=1; i<args.size(); i++) {
                    if (builtin.contains(args[i])) {
                        std::cout << args[i] << " is a shell builtin" << std::endl;
                    } else {
                        std::string cmd_path = "";
                        cmd_path = get_valid_path(args[i]);
                        if (!cmd_path.empty()) {
                            std::cout << args[i] << " is " << cmd_path << std::endl;
                        } else {
                            std::cout << args[i] << ": not found" << std::endl;
                        }
                    }
                }
            }
        } else {
            std::cout << input << ": command not found" << std::endl;
        }
        std::cout << "$ ";
    }
    return exit_status;
}
