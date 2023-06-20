#include"./forms.h"
#include"./error.h"
ValuePtr defineForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    if (auto name = args[0]->asSymbol()) {
        //std::cout << *name << "\n";
        env.symbollist[*name]= env.eval(args[1]);
        
        return std::make_shared<NilValue>();
    } 
    if (auto ptr = dynamic_cast<PairValue*>(args[0].get())) {
        std::vector<ValuePtr> v{ptr->getCdr()};
        for (int i = 1; i < args.size(); i++) v.emplace_back(args[i]);
        env.symbollist[ptr->getCar()->toString()] = lambdaForm(v, env);
        return std::make_shared<NilValue>();
    }
    throw LispError("Wrong format");
} 
ValuePtr quoteForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    if (args.size() == 1) {
        return args[0];
    } else
        throw LispError("1 argument needed");
}
ValuePtr ifForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    //std::cout << args.size() << std::endl;
    if (args.size() == 3) {
        auto condition = env.eval(args[0]);
        if (auto con = condition->asBoolean()) {
            if (!*con) {
                return env.eval(args[2]);
            }
            
        }return env.eval(args[1]);
    } else if (args.size() == 2) {
        auto condition = env.eval(args[0]);
        if (auto con = condition->asBoolean()) {
            if (!*con) {
                return std::make_shared<NilValue>();
            }
            
        }return env.eval(args[1]);
    }
    
    throw LispError("....");
}
ValuePtr andForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    if (args.size() >= 1) {
        ValuePtr v;
        for (int i = 0; i < args.size(); i++) {
            v = env.eval(args[i]);
            if (auto con = v->asBoolean())
                if (!*con) return std::make_shared<BooleanValue>(0);
        }
        return v;
    }else
        return std::make_shared<BooleanValue>(1);
}
ValuePtr orForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    if (args.size()  >= 1) {
        for (int i = 0; i < args.size() ; ++i) {
            auto v = env.eval(args[i]);
            if (auto con = v->asBoolean()) {
                if (!*con)
                    continue;
                else
                    return v;
            } else
                return v;
        }
        return std::make_shared<BooleanValue>(0);
    } else
        return std::make_shared<BooleanValue>(0);
}
ValuePtr lambdaForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    if (args.size() >= 1) {
        auto p1 = args[0]->toVector();
        std::vector<std::string> _p1;
        std::transform(p1.begin(), p1.end(), std::back_inserter(_p1),
                       [](ValuePtr p) { return p->toString(); });
        std::vector<ValuePtr> p2(args.begin()+1, args.end());
        //auto a = env.shared_from_this();
        //std::cout << a->symbollist.size() << "\n";
        return std::make_shared<LambdaValue>(_p1, p2,env.shared_from_this());
    } else
        throw LispError("more arguments needed");
}
ValuePtr letForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    if (args.size()  >= 2) {
        auto relation = args[0]->toVector();
        std::vector<std::string> v1;
        std::vector<ValuePtr> v2;
        for (int i = 0; i < relation.size(); ++i) {
            auto v = relation[i]->toVector();
            v1.emplace_back(v[0]->toString());
            v2.emplace_back(env.eval(v[1]));
        }
        auto E = env.createChild(v1, v2);
        ValuePtr res;
        for (int i = 1; i < args.size() ; ++i) res = E->eval(args[i]);
        return res;
    } else
        throw LispError("More arguments needed");
}
ValuePtr condForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    if (args.size()  >= 2) {
        ValuePtr res;
        for (int i = 0; i < args.size(); ++i) {
            auto relation = args[i]->toVector();
            if (relation.size() == 1) return relation[0];
            if (*env.eval(relation[0])->asBoolean()) {
                res = env.eval(relation[1]);
                break;
            }
        }
        return res;
    } else
        throw LispError("More arguments needed");
}
ValuePtr beginForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    if (args.size()  >= 1) {
        ValuePtr v;
        for (int i = 0; i < args.size(); ++i) v = env.eval(args[i]);
        return v;
    } else
        throw LispError("at least 1 argument needed");
}
ValuePtr quasiquoteForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    if (args.size()  == 1) {
        if (typeid(*args[0]) == typeid(PairValue)) {
            auto v1 = args[0]->toVector();
            if (auto a = v1[0]->asSymbol())
                if (a.value() == "unquote") return env.eval(v1[1]);
            for (auto& i : v1)
                if (auto p = dynamic_cast<PairValue*>(i.get()))
                    if (auto s = p->getCar()->asSymbol())
                        if (*s == "unquote") {
                            if (auto pr = dynamic_cast<PairValue*>(p->getCdr().get()))
                                i = env.eval(pr->getCar());
                            else
                                throw LispError("wrong unquote");
                        }
            return make_list(v1);
        } else
            return args[0];
    } else
        throw LispError("1 argument needed");
}

std::unordered_map<std::string, SpecialFormType*> SPECIAL_FORMS{
    {"define", defineForm}, 
    {"quote",quoteForm}, 
    {"if", ifForm},
    {"and", andForm},
    {"or", orForm},       
    {"lambda",lambdaForm},
    {"cond", condForm}, 
    {"let", letForm},
    {"begin", beginForm},
    {"quasiquote", quasiquoteForm},
    {"unquote",quoteForm},
};
