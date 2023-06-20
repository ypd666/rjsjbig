#include"parser.h"
#include"error.h"
#include<unordered_map>



using ValuePtr = std::shared_ptr<Value>;
ValuePtr Parser::parse() {
    auto& token = tokens.front();
    if (token->getType() == TokenType::NUMERIC_LITERAL) {
        auto value = static_cast<NumericLiteralToken&>(*token).getValue();
        tokens.pop_front();
        return std::make_shared<NumericValue>(value);
    } 
    else if (token->getType() == TokenType::BOOLEAN_LITERAL) {
        auto value = static_cast<BooleanLiteralToken&>(*token).getValue();
        tokens.pop_front();
        return std::make_shared<BooleanValue>(value);
    } 
    else if (token->getType() == TokenType::STRING_LITERAL) {
        auto value = static_cast<StringLiteralToken&>(*token).getValue();
        tokens.pop_front();
        return std::make_shared<StringValue>(value);
    } 
    else if (token->getType() == TokenType::IDENTIFIER) {
        auto value = static_cast<IdentifierToken&>(*token).getName();
        tokens.pop_front();
        return std::make_shared<SymbolValue>(value);
    } 
    else if (token->getType() == TokenType::LEFT_PAREN) {
        tokens.pop_front();
        return this->parseTails();  // 调用parseTails
    }
    else if(token->getType() == TokenType::QUOTE) {
        tokens.pop_front();
        return std::make_shared<PairValue>(
            std::make_shared<SymbolValue>("quote"),
            std::make_shared<PairValue>(this->parse(),
                                        std::make_shared<NilValue>()));
    } 
    else if (token->getType() == TokenType::QUASIQUOTE) {
        tokens.pop_front();
        return std::make_shared<PairValue>(
            std::make_shared<SymbolValue>("quasiquote"),
            std::make_shared<PairValue>(this->parse(),
                                        std::make_shared<NilValue>()));
    } 
    else if (token->getType() == TokenType::UNQUOTE) {
        tokens.pop_front();
        return std::make_shared<PairValue>(
            std::make_shared<SymbolValue>("unquote"),
            std::make_shared<PairValue>(this->parse(),
                                        std::make_shared<NilValue>()));
    }
    else
        throw SyntaxError("Wrong Value");
}
ValuePtr Parser::parseTails() {
    if (tokens.front()->getType() == TokenType::RIGHT_PAREN) {
            tokens.pop_front();
            return std::make_shared<NilValue>();
    }
        auto car = this->parse();
        if (tokens.front()->getType() == TokenType::DOT) {
            tokens.pop_front();
            auto cdr = this->parse();
            if (!tokens.empty()&&tokens.front()->getType() == TokenType::RIGHT_PAREN)
                tokens.pop_front();
            else
                throw MatchError(") has not a match (");
            return std::make_shared<PairValue>(car, cdr);
        } 
        else {
            auto cdr = this->parseTails();
            return std::make_shared<PairValue>(car, cdr);
        }
}
