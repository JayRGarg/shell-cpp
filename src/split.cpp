#include <string>
#include <vector>
#include <iostream>
#include <sstream>


std::vector<std::string> split(std::string str) {
    std::stringstream ss(str);
    std::vector<std::string> res;
    std::string token;
    while (ss >> token) {
        res.push_back(token);
    }
    return res;
}