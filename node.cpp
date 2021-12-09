#include "node.h"

bool DateComparisonNode::Evaluate(const Date& dateArg, const string& eventArg) const {
    if(this->cmp == Comparison::Less){
        return dateArg.rank < date.rank;
    }
    else if(this->cmp == Comparison::LessOrEqual){
        return dateArg.rank <= date.rank;
    }
    else if(this->cmp == Comparison::Greater){
        return dateArg.rank > date.rank;
    }
    else if(this->cmp == Comparison::GreaterOrEqual){
        return dateArg.rank >= date.rank;
    }
    else if(this->cmp == Comparison::Equal){
        return dateArg.rank == date.rank;
    }
    else if(this->cmp == Comparison::NotEqual){
        return dateArg.rank != date.rank;
    }
    return false;
}

bool EventComparisonNode::Evaluate(const Date& dateArg, const string& eventArg) const {
    switch(this->cmp){
        case Comparison::Less:
            return eventArg < event;
        case Comparison::LessOrEqual:
            return eventArg <= event;
        case Comparison::Greater:
            return eventArg > event;
        case Comparison::GreaterOrEqual:
            return eventArg >= event;
        case Comparison::Equal:
            return eventArg == event;
        case Comparison::NotEqual:
            return eventArg != event;
        default:
            return false;
    }
}

bool EmptyNode::Evaluate(const Date& dateArg, const string& eventArg) const {
    return true;
}

bool LogicalOperationNode::Evaluate(const Date& dateArg, const string& eventArg) const {
    if(this->op == LogicalOperation::And){
        return left->Evaluate(dateArg, eventArg) && right->Evaluate(dateArg, eventArg); 
    }
    else{
        return left->Evaluate(dateArg, eventArg) || right->Evaluate(dateArg, eventArg);
    }
}
