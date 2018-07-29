# Calculator
Simple Calculator in C++. It uses an Abstract Syntax Tree and the Shunting yard algorithm to parse mathematical expressions.

### What the project is about
This project is about building a simple calculator in C++. Although it might be a bit harder than you might think. Parsing the user input and then calculating the result is not exactly an easy task. In this project I implemented a lexer that converts the user input into tokens that the rest of the classes/components can understand. Then, using the parser, the tokens are converted from infix to postfix notation and fed into an AST class that builds an Abstract Syntax Tree. Finally the Calculator is a static class that wraps all previous classes and is used as an interface.

### Software Design concepts and Algorithms applied on this project
In this project I wanted to experiment with the [Abstract Syntax Tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree) data structure and the [Shunting yard algorithm](https://en.wikipedia.org/wiki/Shunting-yard_algorithm). Also I used concepts such as inheritance to make code easier to read and maintain. What is more, I used exceptions and wrote unit tests ( Using the Catch2 Library for C++) to ensure that my code is as stable as possible (Although I could have probably written a few more unit tests).

### How to run the code
To run the calculator app you will need to first compile the C++ code. To do that run
```
g++ -std=c++11 -Wall main.cpp Parser.cpp Lexer.cpp -o Calculator
```
on your terminal/command line and then just run the program using `./Calculator` (on Unix systems) or `Calculator.exe` on Windows.

### How to run the unit tests
Running the unit tests is also very simple. Open the terminal/command line in the UnitTests directory and then run
```
g++ -std=c++11 -Wall -o UnitTests Tests.cpp ../Lexer.cpp ../Parser.cpp
``` 
to first compile the Unit test code and then `./UnitTests` (On Unix Systems) or `UnitTests.exe` to run the unit tests. The unit tests are written using the greatest C++ test framework, [Catch2](https://github.com/catchorg/Catch2)

I hope that you will find the code on this project useful. 
