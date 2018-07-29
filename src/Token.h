#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class Type : char{
    Number = 'n',
    Add = '+',
    Sub = '-',
    Mul = '*',
    Div = '/',
    leftPar = '(',
    rightPar = ')',
    Empty = 'e'
};

struct Token{
    Type type;
    std::string value;
    int precedence;
    Token(Type t, std::string v) : type(t), value(v), precedence(0) {
        if(t == Type::Div || t == Type::Mul)precedence = 2;
        if(t == Type::Add || t == Type::Sub)precedence = 1;
    }
    // Helper
    bool isOperator(){
        return ( type!=Type::Number 
              && type != Type::rightPar
              && type != Type::leftPar
              && type != Type::Empty ); 
    }
};

#endif