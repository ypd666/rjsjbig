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
    if (auto k1 = params.size() - 1 == 2 ? params[0]->asNumber() : 1)
        if (auto k2 = params[params.size() - 1 == 2 ? 1 : 0]->asNumber()) {
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
    if (*x > *y)
        return std::make_shared<BooleanValue>(0);
    else
        return std::make_shared<BooleanValue>(1);
}
ValuePtr smallere(const std::vector<ValuePtr>& params) {
    if (params.size() != 2) throw LispError("can not smaller.");
    auto x = params[0]->asNumber();
    auto y = params[1]->asNumber();
    if (*x >= *y)
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
ValuePtr remainder(const std::vector<ValuePtr>& params) {
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
        if (params.size()  != 1) throw LispError("1 arguments needed");
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
