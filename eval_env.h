#ifndef EVAL_ENV_H
#define EVAL_ENV_H
#include"./builtins.h"
#include"./error.h"
#include<unordered_map>
#include <algorithm>
#include <iterator>
#include<functional>
class EvalEnv;
//ValuePtr REDUCE(const std::vector<ValuePtr>& params, EvalEnv& env);
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
        symbollist["equal?"] = std::make_shared<BuiltinProcValue>(&equal);
        symbollist["even?"] = std::make_shared<BuiltinProcValue>(&even);
        symbollist["not"] = std::make_shared<BuiltinProcValue>(&NOT);
        symbollist["odd?"] = std::make_shared<BuiltinProcValue>(&odd);
        symbollist["abs"] = std::make_shared<BuiltinProcValue>(&Abs);
        symbollist["expt"] = std::make_shared<BuiltinProcValue>(&expt);
        symbollist["quotient"] = std::make_shared<BuiltinProcValue>(&quotient);
        symbollist["remainder"] = std::make_shared<BuiltinProcValue>(&mod);
        symbollist["modulo"] = std::make_shared<BuiltinProcValue>(&modulo);
        symbollist["cons"] = std::make_shared<BuiltinProcValue>(&cons);
        symbollist["newline"] = std::make_shared<BuiltinProcValue>(&newline);
        symbollist["display"] = std::make_shared<BuiltinProcValue>(&display);
        symbollist["displayln"] = std::make_shared<BuiltinProcValue>(&displayln);
        symbollist["error"] = std::make_shared<BuiltinProcValue>(&error);
        symbollist["exit"] = std::make_shared<BuiltinProcValue>(&Exit);
        symbollist["atom?"] = std::make_shared<BuiltinProcValue>(&is_atom);
        symbollist["integer?"] = std::make_shared<BuiltinProcValue>(&is_integer);
        symbollist["list?"] = std::make_shared<BuiltinProcValue>(&is_list);
        symbollist["boolean?"] = std::make_shared<BuiltinProcValue>(&is_boolean);
        symbollist["number?"] = std::make_shared<BuiltinProcValue>(&is_number);
        symbollist["null?"] = std::make_shared<BuiltinProcValue>(&is_null);
        symbollist["pair?"] = std::make_shared<BuiltinProcValue>(&is_pair);
        symbollist["procedure?"] = std::make_shared<BuiltinProcValue>(&is_procedure);
        symbollist["string?"] = std::make_shared<BuiltinProcValue>(&is_string);
        symbollist["symbol?"] = std::make_shared<BuiltinProcValue>(&is_symbol);
        symbollist["list"] = std::make_shared<BuiltinProcValue>(&LIST);
        symbollist["length"] = std::make_shared<BuiltinProcValue>(&length);
        symbollist["zero?"] = std::make_shared<BuiltinProcValue>(&zero);
        symbollist["append?"] = std::make_shared<BuiltinProcValue>(&append);
        symbollist["car"] = std::make_shared<BuiltinProcValue>(&car);
        symbollist["cdr"] = std::make_shared<BuiltinProcValue>(&cdr);
        symbollist["append"] = std::make_shared<BuiltinProcValue>(&append);
        symbollist["else"] = std::make_shared<BooleanValue>(true);
        /* symbollist["eval"] = std::make_shared<BuiltinProcValue>(
            [this](const std::vector<ValuePtr>& params) {
                return this->eval(params[0]);
            });*/
         this->defineBinding(
            "eval",
                  std::make_shared<BuiltinProcValue>([this](const std::vector<ValuePtr>& params) {
                                   return this->eval(params[0]);
                            }));
        this->defineBinding(
            "apply",
                            std::make_shared<BuiltinProcValue>(
                                 [this](const std::vector<ValuePtr>& params) {
                                     auto a=params[1];
                                     return this->apply(params[0],a->toVector() );
                                }));
         this->defineBinding(
             "map", std::make_shared<BuiltinProcValue>(
                          [this](const std::vector<ValuePtr>& params) {
                           if (params.size()  >= 2) {
                               std::vector<ValuePtr> res;
                               auto proc = params[0];
                               auto v = params[1]->toVector();
                               for (int i = 0; i < v.size() ; ++i) {
                                   std::vector<ValuePtr> V{v[i]};
                                   res.emplace_back(this->apply(proc, V));
                               }
                               return make_list(res);
                           } else
                               throw LispError("at least 2 arguments needed");
                          }));
       
        this->defineBinding(
             "filter", std::make_shared<BuiltinProcValue>(
                 [this](const std::vector<ValuePtr>& params) {
                     if (params.size()  >= 2) {
                         std::vector<ValuePtr> res;
                         auto proc = params[0];
                         auto v =params[1]->toVector();
                         for (int i = 0; i < v.size() ; ++i) {
                             std::vector<ValuePtr> V{v[i]};
                             if (auto b = this->apply(proc, V)->asBoolean(); *b)
                                 res.emplace_back(v[i]);
                         }
                         return make_list(res);
                     } else
                         throw LispError("at least 2 arguments needed");
                 }));
         this->defineBinding(
             "reduce",
                             std::make_shared<BuiltinProcValue>(
                                 [this](const std::vector<ValuePtr>& params) {
                                     if (params.size() != 2) throw LispError("2 arguments needed");
                                     if (typeid(params[1]) == typeid(NilValue)) throw LispError("list cannot be a Nil!");
                                     auto proc = params[0];
                                     if (params[1]->toVector().size() == 1)
                                     return *params[1]->toVector().begin();
        else {
           auto proc = params[0];
           auto L = params[1]->toVector();
           auto v = *L.rbegin();
           for (int i = L.size() - 2; i >= 0;--i) {
           std::vector<ValuePtr> vt{L[i], v};
               v = this->apply(proc, vt);
           }
           return v;
        }
                                 }));

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
    void defineBinding(const std::string& s, ValuePtr v);
};

/* ValuePtr REDUCE(const std::vector<ValuePtr>& params, EvalEnv& env) {
    if (params.size() == 2) {
         auto proc = env.eval(params[0]);
         if (auto ptr = dynamic_cast<PairValue*>(env.eval(params[1]).get())) {
             if (typeid(*ptr->getCdr()) == typeid(NilValue))
                 return ptr->getCar();
             else {
                 std::vector<ValuePtr> re{
                     std::make_shared<SymbolValue>("quote"), ptr->getCdr(),
                     std::make_shared<NilValue>()};

                 std::vector<ValuePtr> t = {params[0], make_list(re),
                                            std::make_shared<NilValue>()};
                 std::vector<ValuePtr> V{ptr->getCar(), REDUCE(t, env),
                                         std::make_shared<NilValue>()};

                 return env.apply(proc, V);
             }
         }
         throw LispError("Wrong type");
    } else
         throw LispError("1 proc and 1 list needed");
}*/

#endif
