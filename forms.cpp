#include"./forms.h"
#include"./error.h"
ValuePtr defineForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    if (auto name = args[0]->asSymbol()) {
        env.symbollist[*name]= args[1];
    } else {
        throw LispError("Unimplemented");
    }
} 
const std::unordered_map<std::string, SpecialFormType*> SPECIAL_FORMS{
    {"define", defineForm},
};
