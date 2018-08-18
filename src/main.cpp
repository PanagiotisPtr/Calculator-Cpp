#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <exception>
#include <stack>

#include "Calculator.h"

using namespace std;

// Compile the code with:
// g++ -std=c++11 -Wall main.cpp Parser.cpp Lexer.cpp -o Calculator
// And then run the program with:
// ./Calculator

int main(){
    string str;
    while(getline(cin, str)){
        if(str.empty())break;
        try{
            cout << "Result: " << Calculator<int>::calculate(str) << endl;
        }
        catch(const exception& e){
            std::cerr << e.what() << '\n';
        }
    }
}
