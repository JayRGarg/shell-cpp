#include "get_absolute_path.h"
#include <sstream>

std::filesystem::path get_absolute_path(const std::filesystem::path& working_dir, const std::string& relative_path) {
    std::filesystem::path abs_path(working_dir);
    std::stringstream ss(relative_path);
    std::string token;
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