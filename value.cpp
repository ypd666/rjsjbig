#include"./value.h"
#include <iomanip>
#include <sstream>



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
            s = "(" + left->toString() +' '+ right->toString() + ")";
            iff = 0;
            return s;
        } else {
            s = left->toString() +' ' + right->toString();
            return s;
        }
    }
}
std::ostream& operator<<(std::ostream& os, const Value& value) {
    return os << value.toString();
}
