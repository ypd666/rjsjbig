#ifndef VALUE_H
#define VALUE_H
#include<string>
#include<iostream>
#include<memory>
#include<vector>
#include<optional>
class Value;
using ValuePtr = std::shared_ptr<Value>;
class Value {
public:
    Value() = default;
    virtual ~Value() = default;
    virtual std::string toString() const=0;
    virtual void addtoVector(std::vector<ValuePtr>& v) = 0;
    virtual std::vector<ValuePtr> toVector();
    static bool isNil(ValuePtr& value);
    static bool isSelfEvaluating(ValuePtr value);
   std::vector<ValuePtr> toVector(ValuePtr value);
    virtual std::optional<std::string> asSymbol() const {
        return std::nullopt;
    }
    virtual std::optional<double> asNumber() const {
        return std::nullopt;
    }
    virtual std::optional<bool> asBoolean() const {
        return std::nullopt;
    }
};
class BooleanValue : public Value {
private:
    bool value;
public:
    BooleanValue(bool value):Value(),value(value){}
    void addtoVector(std::vector<ValuePtr>& v) override;
    std::string toString() const override;
    ~BooleanValue() = default;
    std::optional<bool> asBoolean() const override;
};
class NumericValue : public Value {
private:
    double value;

public:
    NumericValue(double value) : Value(), value(value) {}
    void addtoVector(std::vector<ValuePtr>& v) override;
    std::string toString() const override;
    ~NumericValue() = default;
    std::optional<double> asNumber() const override;
};
class StringValue : public Value {
private:
    const std::string value;

public:
    StringValue(std::string value) : Value(), value(value) {}
    void addtoVector(std::vector<ValuePtr>& v) override;
    std::string toString() const override;
    ~StringValue() = default;
};
class NilValue : public Value {
public:
    std::string toString() const override;
    void addtoVector(std::vector<ValuePtr>& v) override;
};
class SymbolValue : public Value {
private:
    std::string name;

public:
    SymbolValue(std::string name) : Value(), name(name) {}
    void addtoVector(std::vector<ValuePtr>& v) override;
    std::string toString() const override;
    ~SymbolValue() = default;
    std::optional<std::string> asSymbol() const override;
};
class PairValue : public Value {
private:
    

public:
    ValuePtr left;
    ValuePtr right;
    inline static bool iff ;
    PairValue(std::shared_ptr<Value> left, std::shared_ptr<Value> right): Value(), left(left), right(right) {}
    void addtoVector(std::vector<ValuePtr>& v) override;
    std::string toString() const override;
    ~PairValue() = default;
};

using BuiltinFuncType = ValuePtr(const std::vector<ValuePtr>&);
class BuiltinProcValue : public Value {
    BuiltinFuncType* func;
    void addtoVector(std::vector<ValuePtr>& v) override {}

public:
    BuiltinProcValue(BuiltinFuncType* t) : Value(), func(t) {}
    // 直接返回 #<procedure> 就可以，我们不做更多要求。
    std::string toString() const override;
    ValuePtr run(std::vector<ValuePtr>& v) const {
        return func(v);
    }
};
#endif  // !VALUE_H
