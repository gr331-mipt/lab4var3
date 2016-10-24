//
// Created by altair on 20.02.16.
//

#include "NumericalVariableEquation.h"

ListPoints NumericalVariableEquation::getSolution() {
    ListPoints listPoints;
    size_t L = (size_t) std::round(1.0 / h);
    //Инициализация параметров при l = 1
    mydouble
        alfa_a = -getA(1) / getB(1),
        beta_a = (getD(1) - getC(1) * U0) / getB(1),
    //Инициализация при l = L - 1
        alfa_b = -getC(L - 1) / getB(L - 1),
        beta_b = (getD(L - 1) - getC(L - 1) * U1) / getB(L - 1);
    size_t la, lb;
    for(la = 0; (la + 1) * h < x0; la++);
    for(lb = L; (lb - 1) * h > x0; lb--);
    for(size_t l = 2; l < la; l++) {
        beta_a = (getD(l) - getC(l) * beta_a) / (getB(l) + getC(l) * alfa_a);
        alfa_a = - (getA(l)) / (getB(l) + getC(l) * alfa_a);
    }
    for(size_t l = L - 2; l > lb; l--) {
        beta_b = (getD(l) - getA(l) * beta_b) / (getB(l) + getA(l) * alfa_b);
        alfa_b = - (getC(l)) / (getB(l) + getA(l) * alfa_b);
    }
    mydouble
        U_a = (getKl(la) * beta_a + getKl(lb) * beta_b) / (getKl(la) * (1 - alfa_a) + getKl(lb) * (1 - alfa_b)),
        U_b = U_a;
    if(isRound(la)) {
        listPoints.push_front(Point(la * h, U_a));
    }
    if(isRound(lb)) {
        listPoints.push_back(Point(lb * h, U_b));
    }
    U_a = alfa_a * U_a + beta_a;
    U_b = alfa_b * U_b + beta_b;
    if(isRound(la - 1)) {
        listPoints.push_front(Point((la - 1) * h, U_a));
    }
    if(isRound(lb + 1)) {
        listPoints.push_back(Point((lb + 1) * h, U_b));
    }
    for(size_t l = la - 2; l > 0; l--) {
        alfa_a = - (getA(l) + getB(l) * alfa_a) / (getC(l) * alfa_a);
        beta_a = - (beta_a * (getB(l) + getC(l) * alfa_a) - getD(l)) / getC(l);
        U_a = alfa_a * U_a + beta_a;
        if(isRound(l)) {
            listPoints.push_front(Point(l * h, U_a));
        }
    }
    for(size_t l = lb + 2; l < L; l++) {
        alfa_b = - (getC(l) + getB(l) * alfa_b) / (getA(l) * alfa_b);
        beta_b = - (beta_b * (getB(l) + getA(l) * alfa_b) - getD(l)) / getA(l);
        U_b = alfa_b * U_b + beta_b;
        if(isRound(l)) {
            listPoints.push_back(Point(l * h, U_b));
        }
    }
    return listPoints;
}

mydouble NumericalVariableEquation::getA(mydouble l) {
    return getK((l + 0.5) * h);
}

mydouble NumericalVariableEquation::getB(mydouble l) {
    return -(getK((l + 0.5) * h) + getK((l - 0.5) * h) + getQ(l * h) * h * h);
}

mydouble NumericalVariableEquation::getC(mydouble l) {
    return getK((l - 0.5) * h);
}

mydouble NumericalVariableEquation::getD(mydouble l) {
    return -getF(l * h) * h * h;
}
