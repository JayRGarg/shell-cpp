#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>
#include <filesystem>
#include "get_valid_path.h"
#include "split.h"
#include "exec.h"

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
    std::string cmd_path = "";

    std::filesystem::path WORKING_DIR = std::filesystem::current_path();

    std::unordered_set<std::string> builtin = {"exit", "echo", "type", "pwd", "cd"};

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
                        cmd_path = get_valid_path(args[i]);
                        if (!cmd_path.empty()) {
                            std::cout << args[i] << " is " << cmd_path << std::endl;
                        } else {
                            std::cout << args[i] << ": not found" << std::endl;
                        }
                    }
                }
            } else if (args[0] == "pwd") {
                if (args.size() > 1) {
                    std::cout << too_many_args(args) << std::endl;
                } else {
                    std::cout << WORKING_DIR.string() << std::endl;
                }
            } else if (args[0] == "cd") {
                if (args.size() > 2) {
                    std::cout << too_many_args(args) << std::endl;
                } else {
                    if (args[1][0] == '/') {
                        if (args[1].size() > 1 and args[1].back() == '/') {
                            args[1].pop_back();
                        }
                        std::filesystem::path dir_path(args[1]);
                        if (std::filesystem::is_directory(dir_path)) {
                            WORKING_DIR = dir_path;
                        } else {
                            std::cout << "cd: " << dir_path.string() << ": No such file or directory" << std::endl;
                        }
                    } else {
                        std::cout << "cd: relative paths not implemented yet" << std::endl;
                    }
                }
            } //else if (args[0] == "ls")
        } else {
            cmd_path = get_valid_path(args[0]);
            if (!cmd_path.empty()) {
                std::string output = exec(input.c_str());
                std::cout << output;
            } else {
                std::cout << input << ": command not found" << std::endl;
            }
        }
        std::cout << "$ ";
    }
    return exit_status;
}
