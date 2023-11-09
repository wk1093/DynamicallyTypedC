#pragma once
#ifndef DTC_VARMATH_H
#define DTC_VARMATH_H

#include "Variable.h"

Variable var_add_i(Variable a, Variable b);
Variable var_sub_i(Variable a, Variable b);
Variable var_mul_i(Variable a, Variable b);
Variable var_div_i(Variable a, Variable b);

Variable var_add_f(Variable a, Variable b);
Variable var_sub_f(Variable a, Variable b);
Variable var_mul_f(Variable a, Variable b);
Variable var_div_f(Variable a, Variable b);

Variable var_f2i(Variable a);
Variable var_i2f(Variable a);

#endif //DTC_VARMATH_H
