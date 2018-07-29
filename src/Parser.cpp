#include "Parser.h"
#include "Exceptions.h"

// There is probably a better way to check the syntax but I am not aware of it.
bool Parser::validSyntax(){
    int openPar = 0;
    bool operation = false;
    if(tokens.size() > 0 && tokens[0].isOperator())return false;
    for(unsigned i = 0; i < tokens.size(); i++){
        if(tokens[i].type == Type::Empty)continue;
        if(tokens[i].isOperator())
            if(operation)return false;
            else operation = true;
        else if(tokens[i].type != Type::rightPar)operation = false;
        if(i > 0 && tokens[i].type==Type::Number && tokens[i-1].type==Type::Number)return false;
        if(tokens[i].type == Type::leftPar && i > 0 && tokens[i-1].type==Type::Number)return false; // e.g 5(2 * 3)
        if(tokens[i].type == Type::leftPar)openPar++;
        if(tokens[i].type == Type::rightPar)openPar--;
        if(openPar < 0)return false;
    }
    return (openPar==0 && operation==false);
}

std::vector<Token> Parser::getPostfix(){
    if(!validSyntax())
        throw SyntaxError("Invalid Syntax");
    // The following code assumes valid syntax
    std::vector<Token> rv;
    std::stack<Token> ops;
    for(unsigned i = 0; i < tokens.size(); i++){
        if(tokens[i].type == Type::Empty)continue;
        if(tokens[i].type == Type::Number)rv.push_back(tokens[i]);
        else if(tokens[i].type == Type::leftPar){
            ops.push(tokens[i]);
            if(i < tokens.size()-1 && (tokens[i+1].type == Type::Add || tokens[i+1].type == Type::Sub))rv.push_back(Token(Type::Number, "0")); // Allow for negative numbers ( eg. 8*(-1) )
        }
        else if(tokens[i].type == Type::rightPar){
            while(ops.top().type != Type::leftPar)
                rv.push_back(extract(ops));
            ops.pop();
        }
        else{
            while(!ops.empty() && ops.top().precedence >= tokens[i].precedence)
                rv.push_back(extract(ops));
            ops.push(tokens[i]);
        }
    }
    while(!ops.empty())
        rv.push_back(extract(ops));
    return rv;
}