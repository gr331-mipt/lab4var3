//
// Created by altair on 16.02.16.
//

#ifndef LAB4VAR3_NUMERICALCONSTEQUATION_H
#define LAB4VAR3_NUMERICALCONSTEQUATION_H


#include "AnaliticalConstEquation.h"

class NumericalConstEquation: public AnaliticalConstEquation {

protected:

    mydouble eps =  1e-8;

    virtual mydouble getA(mydouble l);
    virtual mydouble getB(mydouble l);
    virtual mydouble getC(mydouble l);
    virtual mydouble getD(mydouble l);
public:
    virtual bool isRound(size_t l) {
        return isRound(l * h * 10);
    }

    bool isRound(mydouble x) {
        assert(0 < x);
        assert(x < 10);
        return std::abs(roundl(std::abs(x)) - std::abs(x)) < h;
    }

    mydouble h = 1e-6;

    mydouble getKl(size_t l) {
        return getK(l * h);
    }

    mydouble getQl(size_t l) {
        return getQ(l * h);
    }

    mydouble getFl(size_t l) {
        return getF(l * h);
    }

public:
    virtual ListPoints getSolution() override;

    void initH(mydouble _h) {
        assert(h > eps);
        h = _h;
    }
};


#endif //LAB4VAR3_NUMERICALCONSTEQUATION_H
