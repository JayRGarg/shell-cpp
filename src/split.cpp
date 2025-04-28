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
	bool esc_char = false;

	for (char c: str) {
		//std::cout << c << " " << std::endl;
		if (in_quote) {
			if (esc_char) {
				if (c == 'n') {
					token.pop_back();
					token += '\n';
				} else if (c == '$') {
					token.pop_back();
					token += '$';
				} else if (c == '"') {
					token.pop_back();
					token += '\"';
				} else if (c == '\\') {
					token.pop_back();
					token += '\\';
				} else {
					token += c;
					if (c == '\'' && q_char == '\'') {
						in_quote = false;
						q_char = '\0';
					}
				}
				esc_char = false;
			} else {
				if (c == q_char) {
					in_quote = false;
					q_char = '\0';
				} else {
					if (c == '\\') {
						//std::cout << "backslash encountered: " << std::endl;
						esc_char = true;
					}
					token += c;
				}
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
