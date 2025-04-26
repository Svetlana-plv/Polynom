#pragma once
#include "translator.h"

using namespace std;

void translator::setTypeExp(const vector<token>& tokens, const unordered_map<string, double>& variables, string& simpleStr, const double& lastResult) {

    //считаем количество равно
    size_t countEquals = 0;
    for (const auto& token : tokens) {
        if (token.value == "=") ++countEquals;
    }

    if (p.checkSim(tokens) && p.checkVarInEXPR(tokens, variables) && lastResult != NOTHING) {
        typeExp = typeExpression::SIMPLE;
    }

    //повторение операции
    else if (countEquals == 1 && tokens.size() == 1 && simpleStr.size() != 0) {
        typeExp = typeExpression::EQUAL;
    }

    //задание переменной
    else if (countEquals == 1 && tokens[0].type == tokenType::VARIABLE && tokens[1].value == "=") {
        vector<token> subTokens(tokens.begin() + 2, tokens.end());
        if (p.parserExp(subTokens) && p.checkVarInEXPR(subTokens, variables)) {
            typeExp = typeExpression::SET;
        }
    }

    //вычисление выражения
    else if (countEquals == 0 && p.parserExp(tokens) && p.checkVarInEXPR(tokens, variables)) {
        typeExp = typeExpression::EXPRESSION;
    }

    else {
        typeExp = typeExpression::ERROR;
    }
}


double translator::logicNode(const string& str, unordered_map<string, double>& variables, string& simpleStr, double& lastResult) {

    if (str.empty()) throw std::string("try to type an expression");
    vector<token> tokens = l.makeTokens(str); //создали токены
    setTypeExp(tokens, variables, simpleStr, lastResult); //узнали тип выражения

    if (typeExp == typeExpression::SIMPLE) {
        simpleStr = str;
        token newToken(tokenType::NUMBER, to_string(lastResult));
        tokens.insert(tokens.begin(), newToken);
        result = cal.evaluate(polish.toPolish(tokens), variables);
    }

    else if (typeExp == typeExpression::EQUAL) {
        Lexer le;
        vector<token> tokens = le.makeTokens(simpleStr);
        token newToken(tokenType::NUMBER, to_string(lastResult));
        tokens.insert(tokens.begin(), newToken);
        result = cal.evaluate(polish.toPolish(tokens), variables);
    }

    else if (typeExp == typeExpression::SET) {

        if (tokens[0].type == tokenType::CONST) {
            throw std::string("you can't change const variable");
        }

        else if (tokens[0].type == tokenType::FUNCTION) {
            throw std::string("you can't use name of function for variable");
        }
        

        vector<token> subTokens(tokens.begin() + 2, tokens.end());
        variables[tokens[0].value] = cal.evaluate(polish.toPolish(subTokens), variables);
        result = NOTHING;

    }

    else if (typeExp == typeExpression::EXPRESSION) {

        result = cal.evaluate(polish.toPolish(tokens), variables);

    }

    else if (typeExp == typeExpression::ERROR) {
        throw std::string("expression is wrong");
    }

    return result;
}

