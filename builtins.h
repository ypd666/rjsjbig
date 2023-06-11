#ifndef BUILTINS_H
#define BUILTINS_H
#include "./value.h"

ValuePtr add(const std::vector<ValuePtr>& params);
ValuePtr print(const std::vector<ValuePtr>& params);
ValuePtr times(const std::vector<ValuePtr>& params);
ValuePtr bigger(const std::vector<ValuePtr>& params);
ValuePtr smaller(const std::vector<ValuePtr>& params);



#endif
