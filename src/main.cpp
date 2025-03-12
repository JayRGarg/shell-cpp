#include <iostream>
#include <unordered_set>

int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    std::string input, rest;

    std::unordered_set<std::string> valid_commands = {"exit", "echo", "type"};

    bool exit = false;
    int exit_status = 0;

    std::cout << "$ ";

    while (std::getline(std::cin, input)) {
        if (input.find("exit ") == 0) {
            exit_status = std::stoi(input.substr(5, std::string::npos));
            break;
        } else if (input.find("echo ") == 0) {
            std::cout << input.substr(5, std::string::npos) << std::endl;
        } else if (input.find("type ") == 0) {
            rest = input.substr(5, std::string::npos);
            if (valid_commands.contains(rest)) {
                std::cout << rest << " is a shell builtin" << std::endl;
            } else {
                std::cout << rest << ": not found";
            }
        } else {
            std::cout << input << ": command not found\n";
        }
        std::cout << "$ ";
    }
    return exit_status;
}
