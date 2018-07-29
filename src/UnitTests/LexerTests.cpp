#include "catch.hpp"

#include "../Lexer.h"
#include "../Exceptions.h"

TEST_CASE("Lexer class tests", "[Lexer]"){
    SECTION("Check empty"){
        Lexer lexer("");
        lexer.tokenize();
        REQUIRE(lexer.getTokens().size() == 0);
    }
    SECTION("Double dot error"){
        Lexer lexer("1.1 + 9 - 12.12.1");
        REQUIRE_THROWS_WITH(lexer.tokenize(), Catch::Matchers::Contains("Syntax Error"));
    }
    SECTION("Invalid character error"){
        Lexer lexer("1 +2 - 1 !");
        REQUIRE_THROWS_WITH(lexer.tokenize(), Catch::Matchers::Contains("Syntax Error"));
    }
}