//
// Created by nezhov on 23.10.2021.
//

#pragma once
#include "date.h"
#include "node.h"
#include <set>
#include <sstream>
#include <map>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <functional>
using namespace std;

struct Entry{
    Entry(const Date& date_, const string &event_): day(date_), event(event_){}
    const Date day;
    const string event;
};

ostream& operator << (ostream &os, const Entry& arg);

bool operator == (const Entry& lhs, const Entry& rhs);

bool operator != (const Entry& lhs, const Entry& rhs);

class Database {
public:
    Database() = default;

    void Add(const Date& dateArg, const string& eventArg);
    ostream& Print(ostream &os) const;
    Entry Last(const Date& dateArg) const;

    int RemoveIf(const function<bool(const Date& date, const string& event)>& lambda);

    vector<Entry> FindIf(const function<bool(const Date& date, const string& event)> &lambda) const;
private:
    map <Date, vector<string>> DB;
    map <Date, set<string>> exist;
};


