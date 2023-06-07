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
 

ValuePtr print(const std::vector<ValuePtr>& params){
        if (params.size() != 1) throw LispError("1 arguments needed");
        auto t = params[0];
        std::cout << t->toString() << "\n";
        return std::make_shared<NilValue>();
}
