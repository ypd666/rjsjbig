
#include "./eval_env.h"
#include "./error.h"



using namespace std::literals;

ValuePtr EvalEnv::eval(ValuePtr expr) {
    if (Value::isSelfEvaluating(expr)) {
        return expr;
    } else if (Value::isNil(expr)) {
        return expr;
        //throw LispError("Evaluating nil is prohibited.");
    } 
    else if (typeid(*expr) == typeid(PairValue)) { 
        std::vector<ValuePtr> v = expr->toVector();
        auto vt = static_cast<PairValue*>(expr.get());
        if (v[0]->asSymbol() == "define"s) {
            if (auto name = v[1]->asSymbol()) {
                symbollist[*name] =eval(v[2]) ;
                return std::make_shared<NilValue>();
            } else {
                throw LispError("Malformed define.");
            }
            
        }else if (v[0]->asSymbol() != "define"s) {
                ValuePtr proc = this->eval(v[0]);
                std::vector<ValuePtr> args = evalList(vt->right);
                return this->apply(proc, args);  // 最后用 EvalEnv::apply 实现调用
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
std::vector<ValuePtr> EvalEnv::evalList(ValuePtr expr) {
    std::vector<ValuePtr> result;
    auto v = expr->toVector();
    std::ranges::transform(v, std::back_inserter(result),
                           [this](ValuePtr v) { return this->eval(v); });
    return result;
}
ValuePtr EvalEnv::apply(ValuePtr proc, std::vector<ValuePtr> args) {
    if (typeid(*proc) == typeid(BuiltinProcValue)) {
        auto p = dynamic_cast<const BuiltinProcValue*>(proc.get());
        return p->run(args);
        // 调用内置过程
    } else {
        throw LispError("Unimplemented");
    }
}

