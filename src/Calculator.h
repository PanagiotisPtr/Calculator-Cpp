#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>

#include "Lexer.h"
#include "Parser.h"
#include "AST.h"

template<class T>
class Calculator{
public:
    static T calculate(std::string const &str);
private:
    Calculator() {} // This is a static class
};

template<class T>
T Calculator<T>::calculate(std::string const &str){
    Lexer lexer(str);
    lexer.tokenize();
    Parser parser(lexer.getTokens());
    AST<T> tree;
    tree.build(parser.getPostfix());
    return tree.evaluate();
}

#endif