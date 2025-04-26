#pragma once

#include <iostream>
#include <unordered_map>
#include "structs.h"
#include "parser.h"
#include "lexer.h"
#include "polish.h"
#include "stack.h"
using namespace std;

//��������� ��� �������� ����������

class translator {
private:
    Lexer l;
    Parser p;
    polishConverter polish;
    typeExpression typeExp;
    RPNCalculator cal;
    double result = NOTHING;
    //�������� ���������� ����������� ����������



    void setTypeExp(const vector<token>& tokens, const unordered_map<string, double>& variables, string& simpleStr, const double& lastResult);
public:

    double logicNode(const string& str, unordered_map<string, double>& variables, string& simpleStr, double& lastResult);
};
