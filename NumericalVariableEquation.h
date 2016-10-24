//
// Created by altair on 20.02.16.
//

#ifndef LAB4VAR3_NUMERICALVARIABLEEQUATION_H
#define LAB4VAR3_NUMERICALVARIABLEEQUATION_H


#include "NumericalConstEquation.h"

class NumericalVariableEquation: public NumericalConstEquation {

    mydouble getA(mydouble l);
    mydouble getB(mydouble l);
    mydouble getC(mydouble l);
    mydouble getD(mydouble l);

    bool isRound(size_t l) {
        return NumericalConstEquation::isRound(l * h * 10);
    }


public:
    virtual ListPoints getSolution() override;
};


#endif //LAB4VAR3_NUMERICALVARIABLEEQUATION_H
