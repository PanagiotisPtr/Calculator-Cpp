#include "Lexer.h"
#include "Exceptions.h"

bool Lexer::validOperator(char c){
    std::string operators = "+-*/()";
    for(char i : operators)if(i==c)return true;
    return false;
}

std::string Lexer::getNumber(){
    std::string rv;
    bool decimal = false;
    char c;
    while(stream.good()){
        c = stream.peek();
        if(c!='.' && !isdigit(c))break;
        c = stream.get();
        if(c=='.'){
            if(decimal)
                throw SyntaxError("Multiple dots on number");
            else decimal = true;
        }
        rv += c;
    }
    return rv;
}

void Lexer::tokenize(){
    char c = stream.peek(); // This is important ( check note at the bottom)
    while(stream.good()){
        if(isdigit(c) || c=='.')
            tokens.push_back(Token(Type::Number, getNumber()));
        else{
            stream.get(c);
            if(isspace(c))
                while(stream.good() && isspace(stream.peek()))stream.get();
            else if(validOperator(c))
                tokens.push_back(Token(static_cast<Type>(c), {c}));
            else
                throw SyntaxError("Invalid character");
        }
        c = stream.peek(); // Important!
        // from cppreference: std::basic_ios::good: Returns true if the THE MOST recent I/O operation on the stream completed successfully.
        // Thus if peek() fails the loop will stop. If I didn't have peek() at the end then the last operation would be a successful get()
        // as a result good() would return true despite now being at eof().
    }
}