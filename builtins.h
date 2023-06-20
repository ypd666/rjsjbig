#ifndef BUILTINS_H
#define BUILTINS_H
#include "./value.h"
//核心库、
ValuePtr print(const std::vector<ValuePtr>& params);
ValuePtr display(const std::vector<ValuePtr>& params);
ValuePtr newline(const std::vector<ValuePtr>& params);
ValuePtr displayln(const std::vector<ValuePtr>& params);
ValuePtr error(const std::vector<ValuePtr>& params);
ValuePtr Exit(const std::vector<ValuePtr>& params);

//类型检查库
ValuePtr is_atom(const std::vector<ValuePtr>& params);
ValuePtr is_boolean(const std::vector<ValuePtr>& params);
ValuePtr is_integer(const std::vector<ValuePtr>& params);
ValuePtr is_list(const std::vector<ValuePtr>& params);
ValuePtr is_number(const std::vector<ValuePtr>& params);
ValuePtr is_null(const std::vector<ValuePtr>& params);
ValuePtr is_pair(const std::vector<ValuePtr>& params);
ValuePtr is_procedure(const std::vector<ValuePtr>& params);
ValuePtr is_string(const std::vector<ValuePtr>& params);
ValuePtr is_symbol(const std::vector<ValuePtr>& params);

//对子与列表操作库
ValuePtr cons(const std::vector<ValuePtr>& params);
ValuePtr make_list(const std::vector<ValuePtr>& args);
ValuePtr append(const std::vector<ValuePtr>& args);
ValuePtr LIST(const std::vector<ValuePtr>& args);
ValuePtr car(const std::vector<ValuePtr>& params);
ValuePtr cdr(const std::vector<ValuePtr>& params);
ValuePtr length(const std::vector<ValuePtr>& params);
ValuePtr reduce(const std::vector<ValuePtr>& params);



//算术运算库
ValuePtr add(const std::vector<ValuePtr>& params);
ValuePtr subtraction(const std::vector<ValuePtr>& params);
ValuePtr times(const std::vector<ValuePtr>& params);
ValuePtr divided(const std::vector<ValuePtr>& params);
ValuePtr Abs(const std::vector<ValuePtr>& params);
ValuePtr expt(const std::vector<ValuePtr>& params);
ValuePtr quotient(const std::vector<ValuePtr>& params);
ValuePtr modulo(const std::vector<ValuePtr>& params);
ValuePtr mod(const std::vector<ValuePtr>& params);

//比较库

ValuePtr bigger(const std::vector<ValuePtr>& params);
ValuePtr biggere(const std::vector<ValuePtr>& params);
ValuePtr smaller(const std::vector<ValuePtr>& params);
ValuePtr smallere(const std::vector<ValuePtr>& params);
ValuePtr eq(const std::vector<ValuePtr>& params);
ValuePtr equal(const std::vector<ValuePtr>& params);
ValuePtr NOT(const std::vector<ValuePtr>& params);
ValuePtr equal_num(const std::vector<ValuePtr>& params);
ValuePtr even(const std::vector<ValuePtr>& params);
ValuePtr odd(const std::vector<ValuePtr>& params);
ValuePtr zero(const std::vector<ValuePtr>& params);

#endif
