#ifndef PARSER_H
#define PARSER_H

#include"value.h"
#include<deque>
#include"token.h"


class Parser {
public:
    std::deque<TokenPtr> tokens;
    Parser(std::deque<TokenPtr> tokens) : tokens(std::move(tokens)) {}
    ValuePtr parse();
    ValuePtr parseTails();
};
#endif
