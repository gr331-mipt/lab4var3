//
// Created by altair on 14.02.16.
//

#ifndef LAB4VAR3_CONSTEQUATION_H
#define LAB4VAR3_CONSTEQUATION_H

#include "types.h"
#include <ctype.h>
#include <cstdlib>
#include <cassert>
#include <cmath>

using std::exp;

class AnaliticalConstEquation {
private:

protected:
    mydouble (*Ka)(mydouble) = NULL;
    mydouble (*Qa)(mydouble) = NULL;
    mydouble (*Fa)(mydouble) = NULL;
    mydouble (*Kb)(mydouble) = NULL;
    mydouble (*Qb)(mydouble) = NULL;
    mydouble (*Fb)(mydouble) = NULL;

    mydouble x0;
    mydouble U0, U1;

    mydouble getK(mydouble x) {
        assert(x >= 0);
        assert(x <= 1);
        if(x > x0) {
            return Kb(x);
        }
        return Ka(x);
    }

    mydouble getQ(mydouble x) {
        assert(x >= 0);
        assert(x <= 1);
        if(x > x0) {
            return Qb(x);
        }
        return Qa(x);
    }

    mydouble getF(mydouble x) {
        assert(x >= 0);
        assert(x <= 1);
        if(x > x0) {
            return Fb(x);
        }
        return Fa(x);
    }

    virtual MapCoefficients calcCoefficients() {
        MapCoefficients coefficients;
        mydouble ka = Ka(x0);
        mydouble kb = Kb(x0);
        mydouble la = coefficients["LambdaA"] = std::sqrt(Qa(x0) / ka);
        mydouble lb = coefficients["LambdaB"] = std::sqrt(Qb(x0) / kb);
        mydouble ma = coefficients["MuA"] = Fa(x0) / Qa(x0);
        mydouble mb = coefficients["MuB"] = Fb(x0) / Qb(x0);
        mydouble a11 = exp(- la * x0) - exp(la * x0);
        mydouble a12 = exp(lb * (2 - x0)) - exp(lb * x0);
        mydouble a21 = (ka * la) * (exp(la * x0) + exp(-la * x0));
        mydouble a22 = (kb * lb) * (exp(lb * (2 - x0)) + exp(lb * x0));
        mydouble b1 = mb - ma + (ma - U0) * exp(la * x0) - (mb - U1) * exp(lb * (1 - x0));
        mydouble b2 = ka * la * (U0 - ma) * exp(la * x0) + kb * lb * (U1 - mb) * exp(lb * (1 - x0));
        coefficients["C1"] = ( ((U0 - ma) * a11 - b1) * a22 - ((U0 - ma) * a21 - b2) * a12 ) / (a11 * a22 - a12 * a21);
        coefficients["C2"] = (b1 * a22 - b2 * a12) / (a11 * a22 - a12 * a21);
        coefficients["C3"] = (b2 * a11 - b1 * a21) / (a11 * a22 - a12 * a21);
        coefficients["C4"] = (U1 - mb) * exp(lb) - coefficients["C3"] * exp(2 * lb);
        return coefficients;
    }

public:
    void initFuncK(mydouble (*_Ka)(mydouble), mydouble (*_Kb)(mydouble)) {
        assert(_Ka != NULL);
        assert(_Kb != NULL);
        Ka = _Ka;
        Kb = _Kb;
    }

    void initFuncQ(mydouble (*_Qa)(mydouble), mydouble (*_Qb)(mydouble)) {
        assert(_Qa != NULL);
        assert(_Qb != NULL);
        Qa = _Qa;
        Qb = _Qb;
    }

    void initFuncF(mydouble (*_Fa)(mydouble), mydouble (*_Fb)(mydouble)) {
        assert(_Fa != NULL);
        assert(_Fb != NULL);
        Fa = _Fa;
        Fb = _Fb;
    }

    void initX0(mydouble _x0) {
        x0 = _x0;
    }

    void initU0U1(mydouble _u0, mydouble _u1) {
        U0 = _u0;
        U1 = _u1;
    }

    virtual ListPoints getSolution() {
        MapCoefficients map = calcCoefficients();
        mydouble la = map["LambdaA"],
                 lb = map["LambdaB"],
                 c1 = map["C1"],
                 c2 = map["C2"],
                 c3 = map["C3"],
                 c4 = map["C4"],
                 ma = map["MuA"],
                 mb = map["MuB"];
        ListPoints list;
        mydouble u = 0;
        for(mydouble x = 0; x <= 1; x += 0.1) {
            if(IS_ZERO(x))
                continue;
            if(x < x0) {
                u = c1 * exp(la * x) + c2 * exp(-la * x) + ma;
            } else {
                u = c3 * exp(lb * x) + c4 * exp(-lb * x) + mb;
            }
            list.push_back(Point(x, u));
        }
        return list;
    }
};


#endif //LAB4VAR3_CONSTEQUATION_H
