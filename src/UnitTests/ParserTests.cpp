#include "catch.hpp"

#include "../Parser.h"
#include "../Exceptions.h"

TEST_CASE("Parser class tests", "[Parser]"){
    SECTION("Check empty vector"){
        Parser parser(std::vector<Token>{});
        REQUIRE(parser.getPostfix().size() == 0);
    }
    SECTION("Check Empty Tokens"){
        std::vector<Token> v = {Token(Type::Empty, ""), Token(Type::Empty, ""), Token(Type::Empty, ""), Token(Type::Empty, ""), Token(Type::Empty, "")};
        Parser parser(v);
        REQUIRE(parser.getPostfix().size() == 0);
    }
    SECTION("Unclosed parentheses error"){
        std::vector<Token> v = {Token(Type::leftPar, "("), Token(Type::leftPar, "("), Token(Type::rightPar, "(")}; // "(()"
        Parser parser(v);
        REQUIRE_THROWS_WITH(parser.getPostfix(), Catch::Matchers::Contains("Syntax Error"));
    }
    SECTION("Multiple operator error"){
        std::vector<Token> v = {Token(Type::leftPar, "("), Token(Type::Number, "1231"), Token(Type::Add, "+"), Token(Type::Add, "+"), Token(Type::rightPar, "(")}; // "(1231 +  +)"
        Parser parser(v);
        REQUIRE_THROWS_WITH(parser.getPostfix(), Catch::Matchers::Contains("Syntax Error"));
    }
    SECTION("Missing numbers error"){
        std::vector<Token> v = {Token(Type::leftPar, "("), Token(Type::Number, "1231"), Token(Type::Add, "+"), Token(Type::rightPar, "(")}; // "(1231 + )"
        Parser parser = Parser(v);
        REQUIRE_THROWS_WITH(parser.getPostfix(), Catch::Matchers::Contains("Syntax Error"));
    }
}