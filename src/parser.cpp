
#include "../include/parser.h"

#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>

std::vector<std::vector<std::string>> Parser::parse() {

    std::string line = "";
    std::vector<std::vector<std::string>> gates; //todo: put class around vector of strings
    std::ifstream file(fn);

    if (!file)
        throw std::runtime_error("Error opening file ");
    else {
        while (getline(file, line))
        {
            std::vector<std::string> aGate; //todo: class
            boost::algorithm::split(aGate, line, boost::is_any_of(delimeter));//standard split??
            gates.push_back(aGate);
        }

        file.close();
        return gates;
    }
}
