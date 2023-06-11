#include"./builtins.h"
#include "./error.h"



ValuePtr add(const std::vector<ValuePtr>& params) {
    double result = 0.0;
    for (const auto& i : params) {
        if (!i->isNumber()) {
            throw LispError("Cannot add a non-numeric value.");
        }
        result += *(i->asNumber());
    }
    return std::make_shared<NumericValue>(result);
}
/* ValuePtr add(const std::vector<ValuePtr>& params) {
    double result = 0.0;
    for (int i = 0; i < params.size();++i) {
        if (auto k=params[i]->asNumber())
            result += *k;
        else throw LispError("Cannot add a non-numeric value.");
    }
    return std::make_shared<NumericValue>(result);
}*/
ValuePtr times(const std::vector<ValuePtr>& params) {
    double result = 1.0;
    for (const auto& i : params) {
        if (!i->isNumber()) {
            throw LispError("Cannot time a non-numeric value.");
        }
        result =result* (*(i->asNumber()));
    }
    return std::make_shared<NumericValue>(result);
}
ValuePtr bigger(const std::vector<ValuePtr>& params) {
    if (params.size() != 2) throw LispError("can not bigger.");
    auto x = params[0]->asNumber();
    auto y = params[1]->asNumber();
    if (*x > *y) return std::make_shared<BooleanValue>(1);
    else
        return std::make_shared<BooleanValue>(0);
}
ValuePtr smaller(const std::vector<ValuePtr>& params) {
    if (params.size() != 2) throw LispError("can not smaller.");
    auto x = params[0]->asNumber();
    auto y = params[1]->asNumber();
    if (*x > *y)
        return std::make_shared<BooleanValue>(0);
    else
        return std::make_shared<BooleanValue>(1);
}
ValuePtr print(const std::vector<ValuePtr>& params){
        if (params.size() != 1) throw LispError("1 arguments needed");
        auto t = params[0];
        std::cout << t->toString() << "\n";
        return std::make_shared<NilValue>();
}
