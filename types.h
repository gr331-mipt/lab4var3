//
// Created by altair on 14.02.16.
//

#ifndef LAB4VAR3_TYPES_H
#define LAB4VAR3_TYPES_H

#include <iostream>
#include <cmath>

#define m_eps 1e-8
#define IS_ZERO(x) ((-m_eps < (x) && (x) < m_eps ) ? true : false )

typedef long double mydouble;
using std::cout;

class Point {
public:
    mydouble x;
    mydouble y;
    mydouble y1;
    mydouble y2;

    Point(mydouble x, mydouble y) : x(x), y(y) { }
    Point(mydouble x, mydouble y, mydouble y1, mydouble y2) : x(x), y(y), y1(y1), y2(y2) { }
};

#include <list>

class ListPoints: public std::list<Point> {
public:
    void dump(const char *str = NULL) {
        cout.setf(std::ios::scientific);
        cout <<"#LIST DUMP " << str << std::endl;
        for(ListPoints::iterator i = begin(); i != end(); i++) {
            cout << "( " << i->x << ", " << i->y << ")\n";
        }
        cout << "#DUMP END\n";
        cout.unsetf(std::ios::scientific);
    }

    void dump3(const char *str = NULL) {
        cout.setf(std::ios::scientific);
        cout.precision(10);
        cout <<"#LIST DUMP " << str << std::endl;
        mydouble max = std::abs(begin()->y2);
        for(ListPoints::iterator i = begin(); i != end(); i++) {
            cout << "( " << i->x << ", " << i->y << ", " <<i->y1 << ", " << i->y2 << ")\n";
            if(i->y2 > max || i->y2 < -max)
                max = std::abs(i->y2);
        }
        cout << "max delta = " << max << std::endl;
        cout << "#DUMP END\n";
        cout.unsetf(std::ios::scientific);
    }

    ListPoints sub(ListPoints &b) {
        ListPoints res;
        ListPoints::iterator i1 = begin();
        ListPoints::iterator i2 = b.begin();
        while(i1 != end() && i2 != b.end() && res.size() < 20) {
            if(IS_ZERO(i1->x - i2->x)) {
                res.push_back(Point(i1->x, i1->y - i2->y));
                i1++;
                i2++;
            } else {
                if(i1->x > i2->x)
                    i2++;
                else
                    i1++;
            }
        }
        return res;
    }

    ListPoints mergeAndSub(ListPoints &b) {
        ListPoints res;
        ListPoints::iterator i1 = begin();
        ListPoints::iterator i2 = b.begin();
        while(i1 != end() && i2 != b.end() && res.size() < 20) {
            if(IS_ZERO(i1->x - i2->x)) {
                res.push_back(Point(i1->x, i1->y, i2->y, i1->y - i2->y));
                i1++;
                i2++;
            } else {
                if(i1->x > i2->x)
                    i2++;
                else
                    i1++;
            }
        }
        return res;
    }
};

#include <map>
#include <string>

class MapCoefficients: public std::map<std::string, mydouble> {};

#endif //LAB4VAR3_TYPES_H
