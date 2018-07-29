#include "catch.hpp"

#include "../AST.h"
#include "../Parser.h"
#include "../Exceptions.h"

TEST_CASE("AST class tests", "[Parser]"){
    SECTION("Check empty tree"){
        AST<float> tree;
        REQUIRE(tree.evaluate() == 0);
    }
    SECTION("Check empty tokens"){
        AST<float> tree;
        std::vector<Token> v = {Token(Type::Empty, ""), Token(Type::Empty, "")};
        tree.build(v);
        REQUIRE(tree.evaluate() == 0);
    }
    SECTION("Check negative numbers"){
        AST<int> tree;
        std::vector<Token> v = {Token(Type::Number, "8"),Token(Type::Mul, "*"),Token(Type::leftPar, "("),Token(Type::Sub, "-"),Token(Type::Number, "1"),Token(Type::rightPar, ")")};
        Parser parser(v);
        tree.build(parser.getPostfix());
        REQUIRE(tree.evaluate() == -8);
    }
    SECTION("Check base case with double"){
        AST<double> tree;
        std::vector<Token> v = {Token(Type::Number, "1.1234"), Token(Type::Number, "2.00"), Token(Type::Mul, "*")};
        tree.build(v);
        REQUIRE(tree.evaluate() == (double)(1.1234*2));
    }
}