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
    std::unordered_map<std::string, ValuePtr> symbollist;
    EvalEnv() {
        symbollist["+"] = std::make_shared<BuiltinProcValue>(&add);
        symbollist["-"] = std::make_shared<BuiltinProcValue>(&subtraction);
        symbollist["print"] = std::make_shared<BuiltinProcValue>(&print);
        symbollist["*"] = std::make_shared<BuiltinProcValue>(&times);
        symbollist["/"] = std::make_shared<BuiltinProcValue>(&divided);
        symbollist[">"] = std::make_shared<BuiltinProcValue>(&bigger);
        symbollist[">="] = std::make_shared<BuiltinProcValue>(&biggere);
        symbollist["<"] = std::make_shared<BuiltinProcValue>(&smaller);
        symbollist["<="] = std::make_shared<BuiltinProcValue>(&smallere);
        symbollist["="] = std::make_shared<BuiltinProcValue>(&equal_num);
        symbollist["eq?"] = std::make_shared<BuiltinProcValue>(&eq);
        symbollist["equal?"] = std::make_shared<BuiltinProcValue>(&eq);
        symbollist["even?"] = std::make_shared<BuiltinProcValue>(&even);
        symbollist["not?"] = std::make_shared<BuiltinProcValue>(&NOT);
        symbollist["odd?"] = std::make_shared<BuiltinProcValue>(&odd);
        symbollist["abs"] = std::make_shared<BuiltinProcValue>(&Abs);
        symbollist["expt"] = std::make_shared<BuiltinProcValue>(&expt);
        symbollist["quotient"] = std::make_shared<BuiltinProcValue>(&quotient);
        symbollist["remainder"] = std::make_shared<BuiltinProcValue>(&mod);
        symbollist["modulo"] = std::make_shared<BuiltinProcValue>(&modulo);
        symbollist["cons"] = std::make_shared<BuiltinProcValue>(&cons);
        
    }
    
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
