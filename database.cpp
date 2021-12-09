//
// Created by nezhov on 23.10.2021.
//

#include "database.h"

bool operator == (const Entry& lhs, const Entry& rhs){
    return (lhs.day.rank == rhs.day.rank && lhs.event == rhs.event);
}

bool operator != (const Entry& lhs, const Entry& rhs){
    return (lhs.day.rank != rhs.day.rank && lhs.event == rhs.event);
}

ostream& operator << (ostream &os, const Entry& arg){
    os << arg.day.toString() << ' ' << arg.event;
    return os;
}

void Database::Add(const Date &dateArg, const string &eventArg) {
    try {
        int countEntries = static_cast<int>(exist.at(dateArg).count(eventArg));
        if(countEntries > 0)
            return;
        DB[dateArg].push_back(eventArg);
        exist[dateArg].insert(eventArg);
    }
    catch(...){
        DB[dateArg].push_back(eventArg);
        exist[dateArg].insert(eventArg);
    }
}

ostream& Database::Print(ostream &os) const{
    for(const auto& [day, e] : DB){
        for(const auto &event : e)
            os << day << ' ' << event << endl;
    }
    return os;
}

int Database::RemoveIf(const function<bool(const Date& date, const string& event)>& lambda) {
    int res = 0;
    vector<Date> toErase;
    for(auto& [day, e] : DB){
        auto vec_it = std::stable_partition(begin(e), end(e), [lambda, day = day](const auto& event) {
            return lambda(day, event); } );
        for (auto it = begin(e); it != vec_it; ++it) {
            exist[day].erase(*it);

            ++res;
        }
        e.erase(begin(e), vec_it);
        if(e.empty())
            toErase.push_back(day);
    }
    for(auto &d: toErase){
        DB.erase(d);
        exist.erase(d);
    }
    return res;
}

vector<Entry> Database::FindIf(const function<bool(const Date& date, const string& event)>& lambda) const{
    vector<Entry> res;
    for(auto& [day, e] : DB){
        for(const auto &event : e){
            if(lambda(day, event)){
                res.emplace_back(day, event);
            }
        }
    }
    return res;
}

Entry Database::Last(const Date &dateArg) const{

    auto it = DB.lower_bound(dateArg);
    if(DB.empty() || dateArg < DB.begin()->first){
        throw invalid_argument("Wrong date!");
    }
    else{
        if(it == end(DB) || dateArg < it->first)
            --it;
        return {it->first, *it->second.rbegin()};
    }
}

