#ifndef VALUE_H
#define VALUE_H
#include"./token.h"
class Value;
using ValuePtr = std::shared_ptr<Value>;
class Value {
public:
    Value() = default;
    virtual ~Value() = default;
    virtual std::string toString() const=0;
};
class BooleanValue : public Value {
private:
    bool value;
public:
    BooleanValue(bool value):Value(),value(value){}
    std::string toString() const override;
    ~BooleanValue() = default;
};
class NumericValue : public Value {
private:
    double value;

public:
    NumericValue(double value) : Value(), value(value) {}
    std::string toString() const override;
    ~NumericValue() = default;
};
class StringValue : public Value {
private:
    const std::string value;

public:
    StringValue(std::string value) : Value(), value(value) {}
    std::string toString() const override;
    ~StringValue() = default;
};
class NilValue : public Value {
public:
    std::string toString() const override;
};
class SymbolValue : public Value {
private:
    std::string name;

public:
    SymbolValue(std::string name) : Value(), name(name) {}
    std::string toString() const override;
    ~SymbolValue() = default;
};
class PairValue : public Value {
private:
    std::shared_ptr<Value> left;
    std::shared_ptr<Value> right;
public:
    inline static int iff = 0;
    PairValue(ValuePtr left, ValuePtr right): Value(), left(left), right(right) {}
    std::string toString() const override;
    ~PairValue() = default;
};
#endif  // !VALUE_H
