#include "./error.h"
#include "./value.h"
#include<string>
#include <iomanip>
#include <sstream>


std::optional<std::string> SymbolValue::asSymbol() const {
    return name;
}
std::optional<double> NumericValue::asNumber() const {
    return value;
}
std::optional<bool> BooleanValue::asBoolean() const {
    return value;
}

std::vector<ValuePtr> Value::toVector() {
    std::vector<ValuePtr> v;
        addtoVector(v);
    if (!v.empty())
        return v;
    else
        throw toVectorError("to vector fault");//right nullptr throw?
}

void BooleanValue::addtoVector(std::vector<ValuePtr>& v) {
    v.emplace_back(std::make_shared<BooleanValue>(value));
}

void NumericValue::addtoVector(std::vector<ValuePtr>& v) {
    v.emplace_back(std::make_shared<NumericValue>(value));
}

void StringValue::addtoVector(std::vector<ValuePtr>& v) {
    v.emplace_back(std::make_shared<StringValue>(value));
}

void SymbolValue::addtoVector(std::vector<ValuePtr>& v) {
    v.emplace_back(std::make_shared<SymbolValue>(name));
}

void NilValue::addtoVector(std::vector<ValuePtr>& v) {
    return;
}

void PairValue::addtoVector(std::vector<ValuePtr>& v) {
    v.emplace_back(left);
    if (right != nullptr) right->addtoVector(v);
}

bool Value::isNil(ValuePtr& value) {
    return typeid(*value) == typeid(NilValue) ?  true : false;
}

bool Value::isSelfEvaluating(ValuePtr value) {
    if (typeid(*value) == typeid(BooleanValue))
        return true;
    else if (typeid(*value) == typeid(NumericValue))
        return true;
    else if (typeid(*value) == typeid(StringValue))
        return true;
    else
        return false;
}


std::string BooleanValue::toString() const {
    return value ? "#t" : "#f";
}
std::string NumericValue::toString() const {
    return (std::ceil(value) == std::floor(value)) ? std::to_string(int(value)): std::to_string(value);
}
std::string StringValue::toString() const {
    std::ostringstream ss;
    ss<<std::quoted(value);
    return ss.str();
}
std::string NilValue::toString() const {
    return "()";
}
std::string SymbolValue::toString() const {
    return name;
}
std::string PairValue::toString() const {
    if (typeid(*right) == typeid(NilValue)) {
        return left->toString();
    } 
    else if (typeid(*right) != typeid(PairValue)) {
        return left->toString() + " . "+ right->toString();
    } 
    else {std::string s;
        if (!iff) {
            iff = 1;
            s = "(" +((typeid(*left) == typeid(PairValue))? "(" + left->toString() + ")": left->toString()) +' ' +right->toString() + ")";
            iff = 0;
            return s;
        } else {
            s = ((typeid(*left) == typeid(PairValue))? "(" + left->toString() + ")": left->toString()) +' ' + right->toString();
            return s;
        }
    }
}
std::string BuiltinProcValue::toString() const {
    return "#<procedure>";
}

std::ostream& operator<<(std::ostream& os, const Value& value) {
    return os << value.toString();
}
