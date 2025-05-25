#pragma once
#include "polish.h"


using namespace std;

// ��������� ��������
std::unordered_map<std::string, int> precedence = {
    {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}, {"u-", 4}, {"u+", 4}
};

// ����������������� ��������
std::unordered_map<std::string, bool> leftAssociative = {
    {"+", true}, {"-", true}, {"*", true}, {"/", true}, {"^", false}
};


// �������������� � �������� �������� �������
vector<token> polishConverter::toPolish(const std::vector<token>& tokens) {
    vector<token> output;
    std::stack<token> operators; //���� ��� ����������
    bool expectUnary = true;

    for (const token& token : tokens) {
        switch (token.type) {
        case tokenType::POLYNOM:
            output.push_back(token);
            expectUnary = false;
            break;

        case tokenType::OPERATORS: {
            std::string op = token.value;

            if (expectUnary) {
                if (op == "-") op = "u-";
                else if (op == "+") op = "u+";
            }

            while (!operators.empty() && operators.top().type != tokenType::SKOBKA && ((leftAssociative[op] && precedence[op] <= precedence[operators.top().value]) ||
                (!leftAssociative[op] && precedence[op] < precedence[operators.top().value]))) {

                output.push_back(operators.top());
                operators.pop();
            }

            operators.push(struct::token(tokenType::OPERATORS, op));
            expectUnary = true;
            break;
        }

        case tokenType::SKOBKA:
            if (token.value == "(") {
                operators.push(token);
                expectUnary = true;
            }
            else if (token.value == ")") {
                while (!operators.empty() && operators.top().value != "(") {
                    output.push_back(operators.top());
                    operators.pop();
                }

                operators.pop(); // ������� "("
                expectUnary = false;
            }
            
            break;
        default:
            throw std::string("except parenthesis");
        }
    }

    // ����������� ���������� ���������
    while (!operators.empty()) {
        if (operators.top().type == tokenType::SKOBKA) {
            throw std::string("eroor parenthesis");
        }
        output.push_back(operators.top());
        operators.pop();
    }

    return output;
}


Polynom RPNCalculator::evaluate(const vector<token>& tokens) {
    std::stack<Polynom> stack;

    for (const token& token : tokens) {
        if (token.type == tokenType::POLYNOM) {
            // ���� ����� � �����, �� ����������� � � ����
            stack.push(Polynom(token.value));
        }
        else if (token.type == tokenType::OPERATORS) {
            // ���� ����� � ��������, �� ��������� ��� ����� �� ����� � ��������� ��������

            if ((token.value == "u-" || token.value == "u+") && stack.size() > 0) {

                Polynom a = stack.top(); stack.pop();

                Polynom result = applyUnaryOperator(token.value, a);
                stack.push(result);
            }

            else {
                if (stack.size() < 2) throw std::string("you need two operators for an operation");

                Polynom b = stack.top(); stack.pop();
                Polynom a = stack.top(); stack.pop();

                Polynom result = applyOperator(token.value, a, b);
                stack.push(result);
            }
        }
        else {
            throw std::string("invalid operation");
        }
    }

    // � ����� ������ �������� ��������� ����������
    if (stack.size() != 1) throw std::string("you forgot an operation");

    return stack.top();
}


// ��������� ��������
Polynom RPNCalculator::applyOperator(const string& op, Polynom& a, Polynom& b) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    throw std::string("invalid operation");
}

Polynom RPNCalculator::applyUnaryOperator(const string& op, Polynom& a) {
    if (op == "u-") return a * -1;
    if (op == "u+") return a;
    throw string("error");
}
