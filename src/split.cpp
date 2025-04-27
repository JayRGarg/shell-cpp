#include <string>
#include <vector>
#include <iostream>
#include <sstream>


std::vector<std::string> split(std::string str) {
    std::vector<std::string> result;
    std::string token;
    /*std::stringstream ss(str);*/
    /*while (ss >> token) {*/
    /*    res.push_back(token);*/
    /*}*/
    /*return res;*/
	bool in_quote = false;
	char q_char = '\0';
	
	for (char c: str) {
		if (in_quote) {
			if (c == q_char) {
				in_quote = false;
				q_char = '\0';
				/*result.push_back(token);*/
				/*token.clear();*/
			} else {
				token += c;
			}
		} else {
			if (c == '\'') {
				in_quote = true;
				q_char = '\'';
			} else if (c == '"') {
				in_quote = true;
				q_char = '"';
			} else if (c == ' ') {
				if (token.length() > 0) {
					result.push_back(token);
					token.clear();
				}
			} else {
				token += c;
			}
		}
		//std::cout << token << std::endl;
	}

	/*for (std::string s: result) {*/
	/*	std::cout << s << " ";*/
	/*}*/
	/*std::cout << std::endl;*/

	if (in_quote) {
		std::cerr << "Error: Unfinished Quote!" << std::endl;
		return std::vector<std::string>();
	} else {
		result.push_back(token);
		return result;
	}
}
