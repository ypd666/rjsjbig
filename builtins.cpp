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
ValuePtr subtraction(const std::vector<ValuePtr>& params) {
    if (params.size()  > 2) throw LispError("1 or 2 arguments needed");
    double result = 0.0;
    if (auto k1 = params.size()  == 2 ? params[0]->asNumber() : 0)
        if (auto k2 = params[params.size()  == 2 ? 1 : 0]->asNumber())
            result = *k1 - *k2;
    return std::make_shared<NumericValue>(result);
}
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
ValuePtr divided(const std::vector<ValuePtr>& params) {
    if (params.size()  > 2) throw LispError("1 or 2 arguments needed");
    double result = 0.0;
    if (auto k1 = params.size()  == 2 ? params[0]->asNumber() : 1)
        if (auto k2 = params[params.size()  == 2 ? 1 : 0]->asNumber()) {
            if (*k2)
                result = *k1 / *k2;
            else
                throw SyntaxError("Divided by zero!");
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
ValuePtr biggere(const std::vector<ValuePtr>& params) {
    if (params.size() != 2) throw LispError("can not bigger.");
    auto x = params[0]->asNumber();
    auto y = params[1]->asNumber();
    if (*x >= *y)
        return std::make_shared<BooleanValue>(1);
    else
        return std::make_shared<BooleanValue>(0);
}
ValuePtr smaller(const std::vector<ValuePtr>& params) {
    if (params.size() != 2) throw LispError("can not smaller.");
    auto x = params[0]->asNumber();
    auto y = params[1]->asNumber();
    if (*x < *y)
        return std::make_shared<BooleanValue>(1);
    else
        return std::make_shared<BooleanValue>(0);
}
ValuePtr smallere(const std::vector<ValuePtr>& params) {
    if (params.size() != 2) throw LispError("can not smaller.");
    auto x = params[0]->asNumber();
    auto y = params[1]->asNumber();
    if (*x <= *y)
        return std::make_shared<BooleanValue>(1);
    else
        return std::make_shared<BooleanValue>(0);
}
ValuePtr print(const std::vector<ValuePtr>& params){
        if (params.size() != 1) throw LispError("1 arguments needed");
        auto t = params[0];
        std::cout << t->toString() << "\n";
        return std::make_shared<NilValue>();
}
ValuePtr cons(const std::vector<ValuePtr>& params) {
        if (params.size()  != 2) throw LispError("2 arguments needed");
        return std::make_shared<PairValue>(params[0], params[1]);
}
ValuePtr Abs(const std::vector<ValuePtr>& params) {
        if (params.size()  != 1) throw LispError("1 arguments needed");
        if (auto k = params[0]->asNumber())
        return std::make_shared<NumericValue>(std::abs(*k));
        else
        throw LispError("Wrong type");
}
ValuePtr expt(const std::vector<ValuePtr>& params) {
        if (params.size()  != 2) throw LispError("2 arguments needed");
        double result = 0.0;
        if (auto k1 = params[0]->asNumber())
        if (auto k2 = params[1]->asNumber()) {
            if (*k2 || *k1)
                result = pow(*k1, *k2);
            else
                throw SyntaxError("pow(0,0) is not allowed !");
        }
        return std::make_shared<NumericValue>(result);
}
ValuePtr quotient(const std::vector<ValuePtr>& params) {
        if (params.size()  != 2) throw LispError("2 arguments needed");
        double result = 0.0;
        if (auto k1 = params[0]->asNumber())
        if (auto k2 = params[1]->asNumber()) {
            if (*k2)
                result = *k1 / *k2 >= 0 ? floor(*k1 / *k2) : ceil(*k1 / *k2);
            else
                throw SyntaxError("Divided by zero!");
        }
        return std::make_shared<NumericValue>(result);
}
ValuePtr modulo(const std::vector<ValuePtr>& params) {
        if (params.size()  != 2) throw LispError("2 arguments needed");
        double result = 0.0;
        if (auto k1 = params[0]->asNumber())
        if (auto k2 = params[1]->asNumber()) {
            if (*k2 && int(*k2) == *k2 && int(*k1) == *k1) {
                result = int(*k1) % int(*k2);
                if (result * (*k2) < 0) result += *k2;
            } else
                throw SyntaxError("non-zero integers needed!");
        }
        return std::make_shared<NumericValue>(result);
}
ValuePtr mod(const std::vector<ValuePtr>& params) {
        if (params.size()  != 2) throw LispError("2 arguments needed");
        double result = 0.0;
        if (auto k1 = params[0]->asNumber())
        if (auto k2 = params[1]->asNumber()) {
            if (*k2 && int(*k2) == *k2 && int(*k1) == *k1)
                result = int(*k1) % int(*k2);
            else
                throw SyntaxError("non-zero integers needed!");
        }
        return std::make_shared<NumericValue>(result);
}
ValuePtr eq(const std::vector<ValuePtr>& params) {
        if (params.size()  != 2) throw LispError("2 arguments needed");
        if (typeid(*params[0]) == typeid(StringValue) ||
            typeid(*params[0]) == typeid(PairValue)) {
        bool res = params[0] == params[1];
        return std::make_shared<BooleanValue>(res);
        } else
        return equal(params);
}
ValuePtr equal(const std::vector<ValuePtr>& params) {
        if (params.size()  != 2) throw LispError("2 arguments needed");
        //std::cout << params[0]->toString() << ' ' << params[1]->toString() << "\n";
        bool res = params[0]->toString() == params[1]->toString();
        return std::make_shared<BooleanValue>(res);
}
ValuePtr equal_num(const std::vector<ValuePtr>& params) {
        if (params.size()  != 2) throw LispError("2 arguments needed");
        bool res = 0;
        if (auto k1 = params[0]->asNumber()) {
        if (auto k2 = params[1]->asNumber()) {
            res = *k1 == *k2;
        } else
            throw LispError("numbers needed");
        } else
        throw LispError("numbers needed");
        return std::make_shared<BooleanValue>(res);
}
ValuePtr NOT(const std::vector<ValuePtr>& params) {
        if (params.size() != 1) throw LispError("1 arguments needed");
        if (auto b = params[0]->asBoolean())
        if (!*b) return std::make_shared<BooleanValue>(1);
        return std::make_shared<BooleanValue>(0);
}
ValuePtr even(const std::vector<ValuePtr>& params) {
        if (params.size()  != 1) throw LispError("1 arguments needed");
        bool res = 0;
        if (auto k = params[0]->asNumber()) {
        if (int(*k) == *k) {
            if (int(*k) % 2 == 0)
                res = 1;
            else
                res = 0;
        } else
            throw LispError("integer needed");
        } else
        throw LispError("numbers needed");
        return std::make_shared<BooleanValue>(res);
}
ValuePtr odd(const std::vector<ValuePtr>& params) {
        if (params.size() != 1) throw LispError("1 arguments needed");
        bool res = 0;
        if (auto k = params[0]->asNumber()) {
        if (int(*k) == *k) {
            if (int(*k) % 2 == 0)
                res = 0;
            else
                res = 1;
        } else
            throw LispError("integer needed");
        } else
        throw LispError("numbers needed");
        return std::make_shared<BooleanValue>(res);
}
ValuePtr zero(const std::vector<ValuePtr>& params) {
        if (params.size()  != 1) throw LispError("1 arguments needed");
        bool res = 0;
        if (auto k = params[0]->asNumber()) {
        res = *k == 0;
        } else
        throw LispError("numbers needed");
        return std::make_shared<BooleanValue>(res);
}
ValuePtr display(const std::vector<ValuePtr>& params) {
        if (params.size()  != 1) throw LispError("1 arguments needed");
        auto t = params[0];
        if (typeid(*t) == typeid(StringValue)) {
        auto s = dynamic_cast<const StringValue*>(t.get());
        std::cout << s->getStr() << "\n";
        } else
        std::cout << "'" << t->toString() << "\n";
        return std::make_shared<NilValue>();
}
ValuePtr displayln(const std::vector<ValuePtr>& params) {
        if (params.size()  != 1) throw LispError("1 arguments needed");
        auto t = params[0];
        if (typeid(*t) == typeid(StringValue)) {
        auto s = static_cast<const StringValue*>(t.get());
        std::cout << s->getStr() << "\n\n";
        } else
        std::cout << t->toString() << "\n\n";
        return std::make_shared<NilValue>();
}
ValuePtr newline(const std::vector<ValuePtr>& params) {
        if (params.size() != 0) throw LispError("more arguments than needed");
        std::cout << "\n";
        return std::make_shared<NilValue>();
}
[[noreturn]] ValuePtr Exit(const std::vector<ValuePtr>& params) {
        if (params.size()  == 0)
        exit(0);
        else {
        if (params.size() != 1)
            throw LispError("More arguments than needed");
        else if (auto t = params[0]->asNumber())
            exit(t.value());
        }
}
[[noreturn]] ValuePtr error(const std::vector<ValuePtr>& params) {
        if (params.size()  == 0)
        throw LispError(0);
        else {
        if (params.size()  != 1)
            throw LispError("More arguments than needed");
        else
            throw LispError(params[0]->toString());
        }
}
ValuePtr is_atom(const std::vector<ValuePtr>& params) {
        if (params.size() != 1) throw LispError("more arguments than needed");
        if (typeid(*params[0]) != typeid(BuiltinProcValue) &&typeid(*params[0]) != typeid(PairValue))
           return std::make_shared<BooleanValue>(1);
        else return std::make_shared<BooleanValue>(0);
}
ValuePtr is_boolean(const std::vector<ValuePtr>& params) {
        if (params.size() != 1) throw LispError("more arguments than needed");
        if (typeid(*params[0]) == typeid(BooleanValue))
           return std::make_shared<BooleanValue>(1);
        else
           return std::make_shared<BooleanValue>(0);
}
ValuePtr is_integer(const std::vector<ValuePtr>& params) {
        if (params.size() != 1) throw LispError("more arguments than needed");
        if (typeid(*params[0]) == typeid(NumericValue)) {
           auto t = params[0]->asNumber();
            if (ceil(*t)==floor(*t))
           return std::make_shared<BooleanValue>(1);
            else
           return std::make_shared<BooleanValue>(0);
        }   
        else
           return std::make_shared<BooleanValue>(0);
}
ValuePtr is_list(const std::vector<ValuePtr>& params) {
        if (params.size() != 1) throw LispError("more arguments than needed");
        auto s = params[0]->toString();
        if ((typeid(*params[0]) == typeid(PairValue) ||
             typeid(*params[0]) == typeid(NilValue)) &&
            s.find('.') == std::string::npos)
           return std::make_shared<BooleanValue>(1);
        else
           return std::make_shared<BooleanValue>(0);
}
ValuePtr is_number(const std::vector<ValuePtr>& params) {
        if (params.size() != 1) throw LispError("more arguments than needed");
        if (typeid(*params[0]) == typeid(NumericValue))
           return std::make_shared<BooleanValue>(1);
        else
           return std::make_shared<BooleanValue>(0);
}
ValuePtr is_null(const std::vector<ValuePtr>& params) {
        if (params.size() != 1) throw LispError("more arguments than needed");
        if (typeid(*params[0]) == typeid(NilValue))
           return std::make_shared<BooleanValue>(1);
        else
           return std::make_shared<BooleanValue>(0);
}
ValuePtr is_pair(const std::vector<ValuePtr>& params) {
        if (params.size() != 1) throw LispError("more arguments than needed");
        if (typeid(*params[0]) == typeid(PairValue))
           return std::make_shared<BooleanValue>(1);
        else
           return std::make_shared<BooleanValue>(0);
}
ValuePtr is_procedure(const std::vector<ValuePtr>& params) {
        if (params.size() != 1) throw LispError("more arguments than needed");
        if (typeid(*params[0]) == typeid(BuiltinProcValue)||typeid(*params[0])==typeid(LambdaValue))
           return std::make_shared<BooleanValue>(1);
        else
           return std::make_shared<BooleanValue>(0);
}
ValuePtr is_string(const std::vector<ValuePtr>& params) {
        if (params.size() != 1) throw LispError("more arguments than needed");
        if (typeid(*params[0]) == typeid(StringValue))
           return std::make_shared<BooleanValue>(1);
        else
           return std::make_shared<BooleanValue>(0);
}
ValuePtr is_symbol(const std::vector<ValuePtr>& params) {
        if (params.size() != 1) throw LispError("more arguments than needed");
        if (typeid(*params[0]) == typeid(SymbolValue))
           return std::make_shared<BooleanValue>(1);
        else
           return std::make_shared<BooleanValue>(0);
}
ValuePtr make_list(const std::vector<ValuePtr>& args) {
        if (args.size()  >= 0) {
           if (args.size()== 0) return std::make_shared<NilValue>();
           std::vector<ValuePtr> v(args.begin() + 1, args.end());
           return std::make_shared<PairValue>(args[0], make_list(v));
        } else
           throw LispError("at least 1 argument needed");
}
ValuePtr append(const std::vector<ValuePtr>& args) {
        if (args.size()  >= 1) {
           std::vector<ValuePtr> v;
           for (int i = 0; i < args.size(); ++i) {
           auto v1 = args[i]->toVector();
           std::copy(v1.begin(), v1.end(), std::back_inserter(v));
           }
           return make_list(v);
        } else
           return std::make_shared<NilValue>();
}
ValuePtr LIST(const std::vector<ValuePtr>& args) {
        if (args.size()  >= 0) {
           if (args.size()== 0) return std::make_shared<NilValue>();
           std::vector<ValuePtr> v(args.begin() + 1, args.end());
           return std::make_shared<PairValue>(args[0], LIST(v));
        } else
           throw LispError("at least 1 argument needed");
}
ValuePtr car(const std::vector<ValuePtr>& params) {
        if (params.size()  != 1) throw LispError("1 arguments needed");
        auto t = params[0];
        if (typeid(*t) == typeid(PairValue)) {
           auto s = static_cast<PairValue*>(t.get());
           return s->getCar();
        }
        throw LispError("Wrong type");
}
ValuePtr cdr(const std::vector<ValuePtr>& params) {
        if (params.size()  != 1) throw LispError("1 arguments needed");
        auto t = params[0];
        if (typeid(*t) == typeid(PairValue)) {
           auto s = static_cast<PairValue*>(t.get());
           return s->getCdr();
        }
        if (typeid(*t) == typeid(NilValue)) return std::make_shared<NilValue>();
        throw LispError("Wrong type");
}
ValuePtr length(const std::vector<ValuePtr>& params) {
        if (params.size() != 1) throw LispError("1 arguments needed");
        auto res = params[0]->toVector().size();
        return std::make_shared<NumericValue>(res);
}


