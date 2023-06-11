
#include "./forms.h"
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
        auto vt = static_cast<PairValue*>(expr.get());
        if (auto name = vt->getCar()->asSymbol()) {
            //std::cout << *name << "------\n";
            if (SPECIAL_FORMS.contains(*name)) {
                return SPECIAL_FORMS[*name](vt->getCdr()->toVector(), *this);
            }else   {
                ValuePtr proc = this->eval(v[0]);
                std::vector<ValuePtr> args = evalList(vt->right);
                return this->apply(proc, args);  // 最后用 EvalEnv::apply 实现调用
            }
            //else 
                //throw LispError("404 not found");
        }     
        
    }  else if (auto name = expr->asSymbol()) {
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
    std::ranges::transform(expr->toVector(), std::back_inserter(result),
                           [this](ValuePtr v) { return this->eval(v); });
    return result;
}
/* std::vector<ValuePtr> EvalEnv::evalList(ValuePtr expr) {
    std::vector<ValuePtr> result;
    auto v = expr->toVector();
    std::ranges::transform(v, std::back_inserter(result),
                           [this](ValuePtr v) { return this->eval(v); });
    return result;
}*/
ValuePtr EvalEnv::apply(ValuePtr proc, std::vector<ValuePtr> args) {
    if (typeid(*proc) == typeid(BuiltinProcValue)) {
        auto p = dynamic_cast<const BuiltinProcValue*>(proc.get());
        return p->run(args);
        // 调用内置过程
    } else {
        throw LispError("Unimplemented");
    }
}

