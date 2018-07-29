#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class CalculatorException : public std::exception{
public:
    CalculatorException(std::string const &errT, std::string const &msg) :  message(msg), errorType(errT) {}
    const char* what() const throw(){
        return (errorType + ": " + message).c_str();
    }
private:
    std::string message;
    std::string errorType;
};

class SyntaxError : public CalculatorException{
public:
    SyntaxError(std::string const &msg) : CalculatorException("Syntax Error", msg) {}
};

class DataTypeError : public CalculatorException{
public:
    DataTypeError(std::string const &msg) : CalculatorException("Data Type Error", msg) {}
};

class InternalError : public CalculatorException{
public:
    InternalError(std::string const &msg) : CalculatorException("Internal Error", msg) {}
};

#endif