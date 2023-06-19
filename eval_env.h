#ifndef EVAL_ENV_H
#define EVAL_ENV_H
#include"./builtins.h"
#include<unordered_map>
#include <algorithm>
#include <iterator>

//ValuePtr addVal = std::make_shared<BuiltinProcValue>(&add);
//ValuePtr printVal = std::make_shared<BuiltinProcValue>(&print);
class EvalEnv : public std::enable_shared_from_this<EvalEnv> {
private:
    
public: 
    EvalEnv() {
        symbollist["+"] = std::make_shared<BuiltinProcValue>(&add);
        symbollist["-"] = std::make_shared<BuiltinProcValue>(&subtraction);
        symbollist["print"] = std::make_shared<BuiltinProcValue>(&print);
        symbollist["*"] = std::make_shared<BuiltinProcValue>(&times);
        symbollist[">"] = std::make_shared<BuiltinProcValue>(&bigger);
        
    }
    std::unordered_map<std::string, ValuePtr> symbollist;
    std::shared_ptr<EvalEnv> parent;
    ValuePtr eval (ValuePtr expr);
    //static std::shared_ptr<EvalEnv> createGlobal(); 
    std::vector<ValuePtr> evalList(ValuePtr expr);
    std::shared_ptr<EvalEnv> createChild(
        const std::vector<std::string>& params,
        const std::vector<ValuePtr>& args);
    ValuePtr lookupBinding(const std::string&);
    ValuePtr apply(ValuePtr proc, std::vector<ValuePtr> args);
    
};



#endif
