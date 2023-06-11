#ifndef EVAL_ENV_H
#define EVAL_ENV_H
#include"./builtins.h"
#include<unordered_map>
#include <algorithm>
#include <iterator>

//ValuePtr addVal = std::make_shared<BuiltinProcValue>(&add);
//ValuePtr printVal = std::make_shared<BuiltinProcValue>(&print);
class EvalEnv  {
public: 
    std::unordered_map<std::string, ValuePtr> symbollist;
    ValuePtr eval (ValuePtr expr);
    EvalEnv() {
        symbollist["+"] = std::make_shared<BuiltinProcValue>(&add);
        symbollist["print"] = std::make_shared<BuiltinProcValue>(&print);
        symbollist["*"] = std::make_shared<BuiltinProcValue>(&times);
        symbollist[">"] = std::make_shared<BuiltinProcValue>(&bigger);

    }
    std::vector<ValuePtr> evalList(ValuePtr expr);
    ValuePtr apply(ValuePtr proc, std::vector<ValuePtr> args);
};



#endif
