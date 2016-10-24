#include <iostream>
#include <signal.h>

#include "func_init.h"
#include "AnaliticalConstEquation.h"
#include "NumericalConstEquation.h"
#include "NumericalVariableEquation.h"

using namespace std;

mydouble M_Ka(mydouble x) {
    return 1;
}

mydouble M_Kb(mydouble x) {
    return std::exp(-(mydouble)1/sqrt(3));
}

mydouble M_Qa(mydouble x) {
    return (mydouble) 1/3;
}

mydouble M_Qb(mydouble x) {
    return (mydouble)1/sqrt(3);
}

mydouble M_Fa(mydouble x) {
    return -(mydouble)2/3;
}

mydouble M_Fb(mydouble x) {
    return 1;
}


void init(AnaliticalConstEquation &equation) {
    equation.initFuncK(ka, kb);
    equation.initFuncQ(Qa, Qb);
    equation.initFuncF(Fa, Fb);
    equation.initX0((mydouble) 1 / sqrt(2));
    equation.initU0U1(1 , 0);
}

void sigHup(int param) {
    cout << "sighup" << endl;
}

int main() {
    signal(SIGHUP, sigHup);
    size_t N;
    cout << "InputN:";
    cin >> N;
    AnaliticalConstEquation equation;
    init(equation);
    ListPoints listPoints = equation.getSolution();
    listPoints.dump("Analitical");
    NumericalConstEquation e2;
    e2.initH(1.0 / N);
    init(e2);
    ListPoints listPoints2 = e2.getSolution();
    listPoints2.dump("Const");
    NumericalVariableEquation e3;
    e3.initH(1.0 / N);
    init(e3);
    ListPoints listPoints3 = e3.getSolution();
    listPoints3.dump("Variable");
    listPoints.mergeAndSub(listPoints2).dump3("Analicital, Const, Analitical - Const");
    e3.initH(0.5 / N);
    ListPoints listPoints4 = e3.getSolution();
    listPoints3.mergeAndSub(listPoints4).dump3("Var h, Var h/2, VarH - VarH/2");
    return 0;
}