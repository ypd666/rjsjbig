#ifndef  FORMS_H
#define FORMS_H


#include"./eval_env.h"

using SpecialFormType = ValuePtr(const std::vector<ValuePtr>&, EvalEnv&);
extern const std::unordered_map<std::string, SpecialFormType*> SPECIAL_FORMS;
ValuePtr defineForm(const std::vector<ValuePtr>& args, EvalEnv& env);
ValuePtr quoteForm(const std::vector<ValuePtr>& args, EvalEnv& env);

#endif  // ! FORMS_H
