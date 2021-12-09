//
// Created by nezhov on 23.10.2021.
//

#include "date.h"

Date ParseDate(istream &is){
    int year, day, month;
    char bufChar;
    if(is >> year >> bufChar >> month >> bufChar >> day &&
    (1 <= month && month <= 12) && (1 <= day && day <= 31) && (0 < year) && (year < 9999)){
        return Date(year, month, day);
    }
    else{
        throw invalid_argument("Wrong date format!");
    }
}

bool operator < (const Date &lhs, const Date &rhs){
    return lhs.rank < rhs.rank;
}

ostream& operator <<(ostream &os, const Date &dateArg){
    os << setw(4) << setfill('0') << dateArg.year << '-' << setw(2) << setfill('0') << dateArg.month
    << '-' << setw(2) << setfill('0') << dateArg.day;
    return os;
}

string Date::toString() const{
    ostringstream out;
    out << *this;
    return out.str();
}
