#include "get_absolute_path.h"
#include <sstream>
#include <iostream>

std::filesystem::path get_absolute_path(const std::filesystem::path& working_dir, const std::string& relative_path) {
    std::filesystem::path abs_path;
    std::stringstream ss(relative_path);
    std::string token;

    if (!relative_path.empty()) {
        if (relative_path.front() == '~') {
            abs_path = std::filesystem::path(std::getenv("HOME"));
            /*std::cout << "abs_path: " << abs_path.string() << std::endl;*/
            if (ss.str().size() > 1 and ss.str()[1] == '/') {
                ss.str(relative_path.substr(2)); // Skip the ~ and / characters
            } else if (ss.str().size() > 1 and ss.str()[1] != '/') {
                return std::filesystem::path("");
            } else {
                ss.str(relative_path.substr(1));  // Skip the ~ character
            }
        } else if (relative_path.front() == '/') {
            abs_path = std::filesystem::path("/");
            ss.str(relative_path.substr(1));  // Skip the / character
        } else {
            abs_path = std::filesystem::path(working_dir);
        }
    } else {
        abs_path = std::filesystem::path(working_dir);
    }
    /*std::cout << "ss: " << ss.str() << std::endl;*/
    while (std::getline(ss, token, '/')) {
        /*std::cout << "token: " << token << std::endl;*/
        if (token == "." or (abs_path.string() == "/" and token == "..")) {
            // do nothing
        } else if (token == "..") {
            /*std::cout << "abs_path: " << abs_path.string() << std::endl;*/
            abs_path = abs_path.parent_path();
            /*std::cout << "abs_path: " << abs_path.string() << std::endl;*/
        } else {
            abs_path = abs_path / token;
        }
    }
    return abs_path;
} 
