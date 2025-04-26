#pragma once

#include <stack>
#include <unordered_map>
#include <functional>
#include <stdexcept>
#include "structs.h"

using namespace std;

class polishConverter {
private:
    // Приоритет операций
    std::unordered_map<std::string, int> precedence = {
        {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}, {"u-", 4}, {"u+", 4}
    };

    // Левоассоциативные операции
    std::unordered_map<std::string, bool> leftAssociative = {
        {"+", true}, {"-", true}, {"*", true}, {"/", true}, {"^", false}
    };

public:
    // Преобразование в обратную польскую нотацию
    vector<token> toPolish(const std::vector<token>& tokens);
};


class RPNCalculator {
public:
    double evaluate(const vector<token>& tokens, const unordered_map<string, double>& variables);
private:
    // Применить оператор
    double applyOperator(const string& op, double a, double b);
    double applyConst(const string& con);
    double applyUnaryOperator(const string& op, double a);
    //i don't now how it works but it works
    double applyFunction(const std::string& func, double arg);
};