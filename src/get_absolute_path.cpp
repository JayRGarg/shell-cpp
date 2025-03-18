#include "get_absolute_path.h"
#include <sstream>
#include <iostream>

std::filesystem::path get_absolute_path(const std::filesystem::path& working_dir, const std::string& relative_path) {
    std::filesystem::path abs_path;
    std::stringstream ss(relative_path);
    std::string token;
    if (relative_path.front() == '/') {
        abs_path = std::filesystem::path("/");
    } else {
        abs_path = std::filesystem::path(working_dir);
    }
    while (std::getline(ss, token, '/')) {
        if (token == "." or (abs_path.string() == "/" and token == "..")) {
            // do nothing
        } else if (token == "..") {
            abs_path = abs_path.parent_path();
        } else {
            abs_path = abs_path / token;
        }
    }
    return abs_path;
} 