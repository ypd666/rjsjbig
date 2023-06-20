
#include "./forms.h"
#include "./error.h"



using namespace std::literals;

void EvalEnv::defineBinding(const std::string& s,ValuePtr v) {
    symbollist[s] = v;
}

ValuePtr EvalEnv::lookupBinding(const std::string& s) {
    //std::cout << s << "\n";
    EvalEnv* env{this};
    do {
        if (env->symbollist.count(s))
            return env->symbollist[s];
        else
            env = env->parent.get();
    } while (env);
    throw LispError("Do not find variation " + s + " !");
}
std::shared_ptr<EvalEnv> EvalEnv::createChild(const std::vector<std::string>& params, const std::vector<ValuePtr>& args) {
    if (args.size() != params.size()) throw LispError("arguments not matched");
    std::shared_ptr<EvalEnv> child{new EvalEnv};
    child->symbollist.clear();
    child->parent = this->shared_from_this();
    for (int i = 0; i < params.size(); i++) child->symbollist[params[i]] = args[i];
    return child;
}
ValuePtr EvalEnv::eval(ValuePtr expr) {
    //std::cout << expr->toString() << "\n";
    if (Value::isSelfEvaluating(expr)) {
        return expr;
    } else if (Value::isNil(expr)) {
        throw LispError("Evaluating nil is prohibited.");
    } 
    else if (typeid(*expr) == typeid(PairValue)) { 
        std::vector<ValuePtr> v = expr->toVector();
        auto vt = static_cast<PairValue*>(expr.get());
        while (typeid(*v[0]) == typeid(PairValue)) v[0] = eval(v[0]);
        if (auto name = v[0]->asSymbol()) {
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
        } else {
            ValuePtr proc = v[0];
            std::vector<ValuePtr> args = evalList(vt->right);
            return apply(proc, args);  // 最后用 EvalEnv::apply 实现调用
        }
        
    }  else if (auto name = expr->asSymbol()) {
        //std::cout << *name << "\n";
        if (auto value = lookupBinding(*name)) {
            return value;
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

ValuePtr EvalEnv::apply(ValuePtr proc, std::vector<ValuePtr> args) {
    if (typeid(*proc) == typeid(BuiltinProcValue)) {
        auto p = dynamic_cast<const BuiltinProcValue*>(proc.get());
        return p->run(args);
        // 调用内置过程
    } else if (typeid(*proc) == typeid(LambdaValue)) {
        auto p = dynamic_cast<const LambdaValue*>(proc.get());
        return p->apply(args);
    }
    else {
        throw LispError("Unimplemented");
    }
}

