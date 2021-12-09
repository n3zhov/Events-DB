#pragma once

#include <memory>
#include <iostream>
#include <utility>
#include "date.h"
using namespace std;
enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    And,
    Or
};

class Node{
public:
    [[nodiscard]] virtual bool Evaluate(const Date& dateArg, const string& eventArg) const = 0;
};

class EmptyNode : public Node{
public:
    [[nodiscard]] bool Evaluate(const Date& dateArg, const string& eventArg) const override;
};

class LogicalOperationNode : public Node{
public:
    explicit LogicalOperationNode(LogicalOperation op_, shared_ptr<Node> left_, shared_ptr<Node> right_): op(op_),
    left(std::move(left_)),
    right(std::move(right_)){}

    [[nodiscard]] bool Evaluate(const Date& dateArg, const string& eventArg) const override;
private:
    const LogicalOperation op;
    const shared_ptr<Node> left;
    const shared_ptr<Node> right;
};

class ComparisonNode : public Node{
protected:
    explicit ComparisonNode(const Comparison& cmp_): cmp(cmp_){}
    const Comparison cmp;
};
class DateComparisonNode : public ComparisonNode{
public:
    explicit DateComparisonNode(const Comparison cmp_, const Date& date_): ComparisonNode(cmp_), date(date_){}

    [[nodiscard]] bool Evaluate(const Date& dateArg, const string& eventArg) const override;
private:
    const Date date;
};

class EventComparisonNode : public ComparisonNode{
public:
    explicit EventComparisonNode(const Comparison cmp_, string  event_): ComparisonNode(cmp_), event(std::move(event_)){}

    [[nodiscard]] bool Evaluate(const Date& dateArg, const string& eventArg) const override;
private:
    const string event;
};

using namespace std;