#ifndef LEXER_H
#define LEXER_H

#include <sstream>
#include <string>
#include <vector>

#include "Token.h"

class Lexer{
public:
    Lexer(std::string const &str) : stream(str) {}
    void tokenize();
    std::vector<Token> getTokens(){ return tokens; }
private:
    std::istringstream stream;
    std::vector<Token> tokens;

    std::string getNumber();
    bool validOperator(char c);
};

#endif