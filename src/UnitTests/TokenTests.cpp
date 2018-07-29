#include "catch.hpp"

#include "../Token.h"

TEST_CASE("Token class tests", "[Token]"){
    Token add(Type::Add, "+");
    Token sub(Type::Sub, "-");
    Token mul(Type::Mul, "*");
    Token div(Type::Div, "/");
    Token num(Type::Number, "1234567890");
    Token lpr(Type::leftPar, "(");
    Token rpr(Type::rightPar, ")");
    Token emp(Type::Empty, "");
    
    SECTION("Tokens should know if they are operators"){
        REQUIRE(add.isOperator() == true);
        REQUIRE(sub.isOperator() == true);
        REQUIRE(mul.isOperator() == true);
        REQUIRE(div.isOperator() == true);
        REQUIRE(lpr.isOperator() == false);
        REQUIRE(rpr.isOperator() == false);
        REQUIRE(num.isOperator() == false);
        REQUIRE(emp.isOperator() == false);
    }

    SECTION("Operator precedence"){
        REQUIRE(add.precedence == sub.precedence);
        REQUIRE(mul.precedence == div.precedence);

        REQUIRE(add.precedence < mul.precedence);
        REQUIRE(add.precedence < div.precedence);
        
        REQUIRE(sub.precedence < mul.precedence);
        REQUIRE(sub.precedence < div.precedence);

        REQUIRE(lpr.precedence == 0);
        REQUIRE(rpr.precedence == 0);
        REQUIRE(num.precedence == 0);
        REQUIRE(emp.precedence == 0);
    }
}