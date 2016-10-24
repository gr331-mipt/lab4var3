//
// Created by altair on 16.02.16.
//

#include "NumericalConstEquation.h"

ListPoints NumericalConstEquation::getSolution() {
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
        U_a = (Ka(x0) * beta_a + Kb(x0) * beta_b) / (Ka(x0) * (1 - alfa_a) + Kb(x0) * (1 - alfa_b)),
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
/*    ListPoints listPoints;
    size_t L = (size_t) round(1.0 / (double)h);
    mydouble
            a_a = Ka(x0),
            a_b = Kb(x0),
            b_a = -2 * Ka(x0) - Qa(x0) * h * h,
            b_b = -2 * Kb(x0) - Qb(x0) * h * h,
            c_a = Ka(x0),
            c_b = Kb(x0),
            d_a = -Fa(x0) * h * h,
            d_b = -Fb(x0) * h * h;
    mydouble
            alfa_l_a = -a_a / b_a,
            alfa_l_b = -c_b / b_b,
            beta_l_a = (d_a - c_a * U0) / b_a,
            beta_l_b = (d_b - c_b * U1) / b_b;
    mydouble
            alfa_lp1_a = 0, // альфа l + 1
            alfa_lm1_b = 0, // альфа l - 1
            beta_lp1_a = 0,
            beta_lm1_b = 0;
    size_t l_alfa, l_beta;
    for (l_alfa = 0; (l_alfa + 1) * h < x0; l_alfa++);
    for (l_beta = L; (l_beta - 1) * h > x0; l_beta--);
    for (size_t i = 1; i < l_alfa - 0; i++) {
        alfa_lp1_a = - a_a / (b_a + c_a * alfa_l_a);
        beta_lp1_a = (d_a - c_a * beta_l_a) / (b_a + c_a * alfa_l_a);
        alfa_l_a = alfa_lp1_a;
        beta_l_a = beta_lp1_a;
    }
    for (size_t i = L - 1; i > l_beta + 1; i--) {
        alfa_lm1_b = - c_b / (b_b + a_b * alfa_l_b);
        beta_lm1_b = (d_b - a_b * beta_l_b) / (b_b + a_b * alfa_l_b);
        alfa_l_b = alfa_lm1_b;
        beta_l_b = beta_lm1_b;
    }
    mydouble
            u_l_a = (Ka(x0) * beta_l_a + Kb(x0) * beta_l_b) / (Ka(x0) * (1 - alfa_l_a) + Kb(x0) * (1 - alfa_l_b)),
            u_l_b = u_l_a,
            u_lm1_a = alfa_l_a * u_l_a + beta_l_a,
            u_lp1_b = alfa_l_b * u_l_b + beta_l_b;
    if(isRound(l_alfa * h * 10)) {
        listPoints.push_front(Point(l_alfa * h, u_l_a));
    }
    if(isRound((l_alfa - 1) * h * 10)) {
        listPoints.push_front(Point((l_alfa - 1) * h, u_lm1_a));
    }
    if(isRound(l_beta * h * 10)) {
        listPoints.push_front(Point(l_beta * h, u_l_b));
    }
    if(isRound((l_beta + 1) * h * 10)) {
        listPoints.push_front(Point((l_beta + 1) * h, u_lp1_b));
    }
    for (size_t j = l_alfa - 1; j > 0 && j < l_alfa; j--) {
        alfa_l_a = - (a_a + b_a * alfa_l_a) / (c_a * alfa_l_a);
        //alfa_l_b = - (c_b - b_b * alfa_l_b) / (a_b * alfa_l_b);
        beta_l_a = - (beta_l_a * (b_a + c_a * alfa_l_a) - d_a) / c_a;
        //beta_l_b = - (beta_l_b * (b_b + a_a * alfa_l_b) - d_b) / a_b;
        u_lm1_a = alfa_l_a * u_lm1_a + beta_l_a;
        if(isRound(j * h * 10)) {
            listPoints.push_front(Point(j * h, u_lm1_a));
        }
    }
    for (size_t j = l_beta + 2; j < L; j++) {
        alfa_l_b = - (c_b + b_b * alfa_l_b) / (a_b * alfa_l_b);
        beta_l_b = - (beta_l_b * (b_b + a_b * alfa_l_b) - d_b) / a_b;
        u_lp1_b = alfa_l_b * u_lp1_b + beta_l_b;
        if(isRound(j * h * 10)) {
            listPoints.push_back(Point(j * h, u_lp1_b));
        }
    }
    return listPoints;
    */
}

mydouble NumericalConstEquation::getA(mydouble l) {
    assert(!IS_ZERO(l * h - x0));
    if(l * h > x0)
        return Kb(x0);
    return Ka(x0);
}

mydouble NumericalConstEquation::getB(mydouble l) {
    assert(!IS_ZERO(l * h - x0));
    if(l * h > x0)
        return -2 * Kb(x0) - Qb(x0) * h * h;
    return -2 * Ka(x0) - Qa(x0) * h * h;
}

mydouble NumericalConstEquation::getC(mydouble l) {
    assert(!IS_ZERO(l * h - x0));
    if(l * h > x0)
        return Kb(x0);
    return Ka(x0);
}

mydouble NumericalConstEquation::getD(mydouble l) {
    assert(!IS_ZERO(l * h - x0));
    if(l * h > x0)
        return -Fb(x0) * h * h;
    return -Fa(x0) * h * h;
}
