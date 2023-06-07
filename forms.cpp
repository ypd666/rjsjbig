#include"./forms.h"
#include"./error.h"
ValuePtr defineForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    if (auto name = args[0]->asSymbol()) {
        env.symbollist[*name]= args[1];
    } else {
        throw LispError("Unimplemented");
    }
} 
ValuePtr quoteForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    if (args.size() == 1) {
        return args[0];
    } else
        throw LispError("1 argument needed");
}
const std::unordered_map<std::string, SpecialFormType*> SPECIAL_FORMS{
    {"define", defineForm}, 
    {"quote",quoteForm},
};
