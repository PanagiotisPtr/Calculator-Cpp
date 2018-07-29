#define CATCH_CONFIG_MAIN

#include "TokenTests.cpp"
#include "LexerTests.cpp"
#include "ParserTests.cpp"
#include "ASTTests.cpp"

// I do not test the calculator because it only acts as an interface between the rest of the classes

// Run the test by running:
// g++ -std=c++11 -Wall -o UnitTests Tests.cpp ../Lexer.cpp ../Parser.cpp
// And then executing ./UnitTests