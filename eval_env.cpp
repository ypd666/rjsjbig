#include "./value.h"
#include "./eval_env.h"
#include "./error.h"


using namespace std::literals;

ValuePtr EvalEnv::eval(ValuePtr expr) {
    if (Value::isSelfEvaluating(expr)) {
        return expr;
    } else if (Value::isNil(expr)) {
        throw LispError("Evaluating nil is prohibited.");
    } 
    else if (typeid(*expr) == typeid(PairValue)) { 
        std::vector<ValuePtr> v = expr->toVector();
        if (v[0]->asSymbol() == "define"s) {
            if (auto name = v[1]->asSymbol()) {
                symbollist[*name] =eval(v[2]) ;
                return std::make_shared<NilValue>();
            } 
            else {
                throw LispError("Malformed define.");
            }
        }
    } else if (auto name = expr->asSymbol()) {
        if (symbollist.contains(*name)) {
            return symbollist[*name];
        } else {
            throw LispError("Variable " + *name + " not defined.");
        }
    }  
    else {
        throw LispError("Unimplemented");
    }
}
