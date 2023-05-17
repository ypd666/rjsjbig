#ifndef PARSER_H
#define PARSER_H
#include"./token.h"
#include"./value.h"
#include<deque>


class Parser {
public:
    std::deque<TokenPtr> tokens;
    Parser(std::deque<TokenPtr> tokens) : tokens(std::move(tokens)) {}
    ValuePtr parse();
    ValuePtr parseTails();
};
#endif
