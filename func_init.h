//
// Created by altair on 14.02.16.
//

#ifndef LAB4VAR3_FUNC_INIT_H
#define LAB4VAR3_FUNC_INIT_H

#include "types.h"
#include "cmath"

mydouble ka(mydouble x) {
    double x0 = 1 / sqrt(10);
    return x * x + 0.5;
}

mydouble kb(mydouble x) {
    double x0 = 1 / sqrt(10);
    return x * x + 0.5;
}

mydouble Qa(mydouble x) {
    return 1;
}

mydouble Qb(mydouble x) {
    return std::exp(-x * x);
}

mydouble Fa(mydouble x) {
    double x0 = 1 / sqrt(10);
    return 1;
}

mydouble Fb(mydouble x) {
    return std::cos(x);
}

#endif //LAB4VAR3_FUNC_INIT_H
