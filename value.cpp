#include "./error.h"
#include "./value.h"
#include"eval_env.h"
#include<string>
#include <iomanip>
#include <sstream>

ValuePtr LambdaValue::apply(const std::vector<ValuePtr>& args) const{
    auto kid = this->env->createChild(this->params, args);
    ValuePtr v;
    for (const auto& i : this->body) v = kid->eval(i);
    return v;
}

bool Value::isNumber() const {
    return  (typeid(*this)==typeid(NumericValue))? true:false;
}

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
    if (typeid(*this) == typeid(PairValue)) {
        auto vt = static_cast<PairValue*>(this);
        v.emplace_back(vt->left);
        while (typeid(*(vt->right)) != typeid(NilValue)) {
            if (typeid(*(vt->right)) != typeid(PairValue))
                throw toVectorError("to vector fault");
            else {
                vt = static_cast<PairValue*>((vt->right).get());
                v.emplace_back(vt->left);
            }
        }
        return v;
    } else if (typeid(*this) == typeid(NilValue)) {
        return {};
    }else
        throw toVectorError("to vector fault");
     
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
    /* if (typeid(*right) == typeid(NilValue)) {
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
    }*/
    if (typeid(*right) == typeid(NilValue)) {
        if (iff)
            return ((typeid(*left) == typeid(PairValue))? "(" + left->toString() + ")": left->toString());
        else {
            iff = 1;
            std::string s = "(" +((typeid(*left) == typeid(PairValue))? "(" + left->toString() + ")": left->toString()) +")";
            iff = 0;
            return s;
        }
    } else if (typeid(*right) != typeid(PairValue)) {
        if (iff)
            return ((typeid(*left) == typeid(PairValue))? "(" + left->toString() + ")": left->toString()) + " . " + right->toString();
        else {
            iff = 1;
            std::string s = "(" +((typeid(*left) == typeid(PairValue))? "(" + left->toString() + ")": left->toString()) + " . " + right->toString() + ")";
            iff = 0;
            return s;
        }
    } else {
        if (!iff) {
            iff = 1;
            std::string s = "(" + ((typeid(*left) == typeid(PairValue))? "(" + left->toString() + ")": left->toString()) +" " + right->toString() + ")";
            iff = 0;
            return s;
        } else
            return ((typeid(*left) == typeid(PairValue)) ? "(" + left->toString() + ")" : left->toString()) + " " + right->toString();
    }
}
std::string BuiltinProcValue::toString() const {
    return "#<procedure>";
}
std::string LambdaValue::toString() const {
    return "#<procedure>";
}

std::ostream& operator<<(std::ostream& os, const Value& value) {
    return os << value.toString();
}
