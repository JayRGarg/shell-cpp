#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

std::string get_valid_path(std::string command) {
    std::string env_p = std::getenv("PATH");
    std::string path = "";
    std::string test_path = "";
    std::string out = "";

    std::stringstream ss(env_p);

    if (!env_p.empty()) {
        while (std::getline(ss, path, ':')) {
            test_path = path + "/" + command;
            if (std::filesystem::exists(test_path)) {
                return test_path;
            }
        }
        //std::cout << "your path is " << env_p << std::endl;
        //return std::string("found path ") + env_p;
    }
    return "";
}