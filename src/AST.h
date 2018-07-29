#ifndef AST_H
#define AST_H

#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "Token.h"
#include "Exceptions.h"

// An abstract syntax tree is also used as an Abstract Syntax Tree Node
// This helps at using recursion for operations.

template<class T>
class AST{
public:
    AST() : token(Token(Type::Empty, "")), value(0), left(nullptr), right(nullptr) {}
    AST(Token t) : token(t), value(0), left(nullptr), right(nullptr) {}
    void print(){ printAST(std::shared_ptr<AST<T> >(this)); std::cout << std::endl; }
    void build(std::vector<Token> postfix); // Notice how I make a copy of tokens and then pass that copy by reference. This way the original vector<Token> stays unchanged while the 
                                            // algorithm proceeds normally.
    T evaluate();
private:
    Token token;
    T value;
    std::shared_ptr<AST<T> > left;
    std::shared_ptr<AST<T> > right;

    bool isFull(){ return (left!=nullptr && right!=nullptr); }
    void populate(std::shared_ptr<AST<T> > n, std::shared_ptr<AST<T> > m);
    void printAST(std::shared_ptr<AST<T> > n);
    T toNumber(std::string str);
    std::shared_ptr<AST<T> > buildAST(std::vector<Token> &postfix);
};

// I really don't like having the functions defined in the header file but I really
// cannot stand explicit instantiations at the .cpp file... Image needing a version 
// for long, long long, unsigned, int, unsigned long long, double, long double.... etc... etc...

template<class T>
void AST<T>::populate(std::shared_ptr<AST<T> > n, std::shared_ptr<AST<T> > m){
    if(n->right == nullptr)n->right = m;
    else if(n->left == nullptr) n->left = m;
    else throw InternalError("Node is full. Cannot add child"); // Hopefully this should never happen
}

template<class T>
void AST<T>::printAST(std::shared_ptr<AST<T> > n){
    if(n->left!=nullptr && n->right!=nullptr)std::cout << '(';
    if(n->left!=nullptr)printAST(n->left);
    std::cout << n->token.value;
    if(n->right!=nullptr)printAST(n->right);
    if(n->left!=nullptr && n->right!=nullptr)std::cout << ')';
}

template<class T>
void AST<T>::build(std::vector<Token> postfix){
    std::shared_ptr<AST<T> > n = buildAST(postfix);
    this->token = n->token;
    this->right = n->right;
    this->left = n->left;
}

template<class T>
std::shared_ptr<AST<T> > AST<T>::buildAST(std::vector<Token> &postfix){
    std::shared_ptr<AST<T> > root(new AST<T>(postfix.back()));
    postfix.pop_back();
    while(!postfix.empty()){
        if(postfix.back().isOperator())
            populate(root, buildAST(postfix));
        else{
            populate(root, std::shared_ptr<AST<T> >(new AST<T>(postfix.back())));
            postfix.pop_back();
        }
        if(root->isFull())
            return root;
    }
    return root;
}

template<class T>
T AST<T>::toNumber(std::string str){
    std::stringstream ss(str);
    T rv; ss >> rv;
    if(ss.fail())
        throw DataTypeError("Conversion from string to number failed. Check the data type of the AST.");
    return rv;
}

template<class T>
T AST<T>::evaluate(){
    if(token.type == Type::Number)return toNumber(token.value);
    if(token.type == Type::Empty)return 0;
    switch (token.type){
        // Order is important; left->eval() - right->eval != right->eval() - left->eval()
        case Type::Add : return left->evaluate() + right->evaluate();
        case Type::Sub : return left->evaluate() - right->evaluate();
        case Type::Mul : return left->evaluate() * right->evaluate();
        case Type::Div : return left->evaluate() / right->evaluate();
        default : throw InternalError("A node with children can only be an operator");
    }
    return 0; // is either an empty node or paretheses ( although it this should never be the case if the syntax is correct )
}

#endif