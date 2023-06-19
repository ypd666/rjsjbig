#ifndef VALUE_H
#define VALUE_H
#include<string>
#include<iostream>
#include<memory>
#include<vector>
#include<optional>
#include<functional>
class Value;
class EvalEnv;
using ValuePtr = std::shared_ptr<Value>;
class Value {
public:
    Value() = default;
    virtual ~Value() = default;
    virtual std::string toString() const=0;
    static bool isNil(ValuePtr& value);
    static bool isSelfEvaluating(ValuePtr value);
    std::vector<ValuePtr> toVector();
    bool isNumber() const;
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
    std::string toString() const override;
    ~BooleanValue() = default;
    std::optional<bool> asBoolean() const override;
};
class NumericValue : public Value {
private:
    double value;

public:
    
    NumericValue(double value) : Value(), value(value) {}
    std::string toString() const override;
    
    ~NumericValue() = default;
    std::optional<double> asNumber() const override;
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
    std::optional<std::string> asSymbol() const override;
};
class PairValue : public Value {
private:
    

public:
    ValuePtr left;
    ValuePtr right;
    inline static bool iff ;
    PairValue(std::shared_ptr<Value> left, std::shared_ptr<Value> right): Value(), left(left), right(right) {}
    ValuePtr getCar() {
        return left;
    }
    ValuePtr getCdr() {
        return right;
    }
    std::string toString() const override;
    ~PairValue() = default;
};

using BuiltinFuncType = ValuePtr(const std::vector<ValuePtr>&);
class BuiltinProcValue : public Value {
    std::function<BuiltinFuncType>func;

public:
    BuiltinProcValue(std::function<ValuePtr(const std::vector<ValuePtr>& params)>t): Value() {
        auto a = [t](const std::vector<ValuePtr>& params) { return t(params); };
         func =a;
    }

    // 直接返回 #<procedure> 就可以，我们不做更多要求。
    std::string toString() const override;
    ValuePtr run(std::vector<ValuePtr>& v) const {
        return func(v);
    }
};
class LambdaValue : public Value {
private:
    std::vector<std::string> params;
    std::vector<ValuePtr> body;
    std::shared_ptr<EvalEnv> env;
    // [...]
public:
    LambdaValue() : Value(),env(nullptr) {}
    LambdaValue(const std::vector<std::string>& p,
                const std::vector<ValuePtr>& v, std::shared_ptr<EvalEnv>e)
        : Value(), params(p), body(v),env(e) {}
    std::string toString() const override;  // 如前所述，返回 #<procedure> 即可
    ValuePtr apply(const std::vector<ValuePtr>& args)const;
};
#endif  // !VALUE_H
