#pragma once
#include "polish.h"

using namespace std;

// Приоритет операций
std::unordered_map<std::string, int> precedence = {
    {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}, {"u-", 4}, {"u+", 4}
};

// Левоассоциативные операции
std::unordered_map<std::string, bool> leftAssociative = {
    {"+", true}, {"-", true}, {"*", true}, {"/", true}, {"^", false}
};


// Преобразование в обратную польскую нотацию
vector<token> polishConverter::toPolish(const std::vector<token>& tokens) {
    vector<token> output;
    std::stack<token> operators; //стек для операторов
    bool expectUnary = true;

    for (const token& token : tokens) {
        switch (token.type) {
        case tokenType::NUMBER:
        case tokenType::VARIABLE:
        case tokenType::CONST:
            output.push_back(token);
            expectUnary = false;
            break;

        case tokenType::FUNCTION:
            operators.push(token);
            expectUnary = true;
            break;

        case tokenType::OPERATOR: {
            std::string op = token.value;

            if (expectUnary) {
                if (op == "-") op = "u-";
                else if (op == "+") op = "u+";
            }

            while (!operators.empty() && operators.top().type != tokenType::PARENTHESIS && ((leftAssociative[op] && precedence[op] <= precedence[operators.top().value]) ||
                (!leftAssociative[op] && precedence[op] < precedence[operators.top().value]))) {

                output.push_back(operators.top());
                operators.pop();
            }

            operators.push(struct::token(tokenType::OPERATOR, op));
            expectUnary = true;
            break;
        }

        case tokenType::PARENTHESIS:
            if (token.value == "(") {
                operators.push(token);
                expectUnary = true;
            }
            else if (token.value == ")") {
                while (!operators.empty() && operators.top().value != "(") {
                    output.push_back(operators.top());
                    operators.pop();
                }

                operators.pop(); // удаляем "("

                // если после этого на вершине стека функция, выталкиваем её
                if (!operators.empty() && operators.top().type == tokenType::FUNCTION) {
                    output.push_back(operators.top());
                    operators.pop();
                }
                expectUnary = false;
            }
            
            break;
        default:
            throw std::string("except parenthesis");
        }
    }

    // выталкиваем оставшиеся операторы
    while (!operators.empty()) {
        if (operators.top().type == tokenType::PARENTHESIS) {
            throw std::string("eroor parenthesis");
        }
        output.push_back(operators.top());
        operators.pop();
    }

    return output;
}


double RPNCalculator::evaluate(const vector<token>& tokens, const unordered_map<string, double>& variables) {
    std::stack<double> stack;

    for (const token& token : tokens) {
        if (token.type == tokenType::NUMBER) {
            // Если токен — число, то преобразуем и в стек
            stack.push(stod(token.value));
        }
        else if (token.type == tokenType::CONST) {
            stack.push(applyConst(token.value));
        }
        else if (token.type == tokenType::VARIABLE) {
            auto it = variables.find(token.value);
            stack.push(it->second);
        }
        else if (token.type == tokenType::OPERATOR) {
            // Если токен — оператор, то извлекаем два числа из стека и выполняем операцию

            if ((token.value == "u-" || token.value == "u+") && stack.size() > 0) {

                double a = stack.top(); stack.pop();

                double result = applyUnaryOperator(token.value, a);
                stack.push(result);
            }

            else {
                if (stack.size() < 2) throw std::string("you need two operators for an operation");

                double b = stack.top(); stack.pop();
                double a = stack.top(); stack.pop();

                double result = applyOperator(token.value, a, b);
                stack.push(result);
            }
        }
        else if (token.type == tokenType::FUNCTION) {
            // если токен — функция, то извлекаем одно число из стека и применяем функцию
            if (stack.empty()) throw std::string("function must have a parameter");

            double arg = stack.top(); stack.pop();
            double result = applyFunction(token.value, arg);
            stack.push(result);
        }
        else {
            throw std::string("invalid operation");
        }
    }

    // В стеке должен остаться результат вычисления
    if (stack.size() != 1) throw std::string("you forgot an operation");

    return stack.top();
}


// Применить оператор
double RPNCalculator::applyOperator(const string& op, double a, double b) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) throw std::string("division by zero");
        return a / b;
    }
    if (op == "^") return pow(a, b);

    throw std::string("invalid operation");
}

double RPNCalculator::applyUnaryOperator(const string& op, double a) {
    if (op == "u-") return -a;
    if (op == "u+") return a;
    throw string("error");
}

// Применить функцию
//i don't now how it works but it works
double RPNCalculator::applyFunction(const std::string& func, double arg) {
    static const std::unordered_map<std::string, std::function<double(double)>> functions = {
        {"sin", [](double x) { return sin(x); }},
        {"cos", [](double x) { return cos(x); }},
        {"exp", [](double x) { return exp(x); }},
        {"tan", [](double x) { return tan(x); }},
        {"log", [](double x) {
            if (x <= 0) throw std::string("argument of log must be more than zero");
            return log(x);
        }},
        {"sqrt", [](double x) {
            if (x < 0) throw std::string("argument of sqrt must be more than zero");
            return sqrt(x);
        }},
    };

    auto it = functions.find(func);
    if (it != functions.end()) {
        return it->second(arg);
    }

    throw string("don't found function");
}


double RPNCalculator::applyConst(const string& con) {
    if (con == "pi") return std::atan(1) * 4;
    else if (con == "e") return std::exp(1);
}