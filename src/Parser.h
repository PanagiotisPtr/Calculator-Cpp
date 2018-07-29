#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <stack>
#include <stack>

#include "Token.h"

class Parser{
public:
    Parser(std::vector<Token> const &v) : tokens(v) {}
    std::vector<Token> getPostfix(); // Dijkstra's Shunting Yard
private:
    std::vector<Token> tokens;

    bool validSyntax();
    Token extract(std::stack<Token> &s){ Token rv = s.top(); s.pop(); return rv; }
};

#endif