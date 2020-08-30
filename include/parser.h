
#ifndef BRISTOLFASHION_PARSER_H
#define BRISTOLFASHION_PARSER_H

#include <vector>
#include <string>

class Parser {

private:
    std::string fn;
    std::string delimeter;

public:
    Parser(){};
    Parser(std::string file_path, std::string del = " ") : fn(file_path), delimeter(del) {}
    std::vector<std::vector<std::string>> parse();
};

#endif //BRISTOLFASHION_PARSER_H
