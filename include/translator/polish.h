#pragma once

#include <stack>
#include <unordered_map>
#include <functional>
#include <stdexcept>
#include "structs.h"
#include "polynom.h"

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
    Polynom evaluate(const vector<token>& tokens);
private:
    // Применить оператор
    Polynom applyOperator(const string& op, Polynom& a, Polynom& b);
    Polynom applyUnaryOperator(const string& op, Polynom& a);
};