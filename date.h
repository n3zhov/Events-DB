//
// Created by nezhov on 23.10.2021.
//

#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <tuple>
using namespace std;
struct Date {
    Date(const int &year_, const int& month_, const int &day_): rank(tie(year_, month_, day_)), year(year_), month(month_),
                                                                day(day_){}
    [[nodiscard]] string toString() const;
    const int year, month, day;
    const tuple <const int, const int, const int> rank;
};

bool operator < (const Date &lhs, const Date &rhs);
ostream& operator <<(ostream &os, const Date &dateArg);
Date ParseDate(istream &is);

