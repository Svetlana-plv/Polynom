#pragma once
#include "structs.h"
#include <stdexcept>
using namespace std;


class Lexer {
public:
    vector<token> makeTokens(const std::string& inputStr);
private:
    std::unordered_set<std::string> con = { "pi", "e" };
    std::unordered_set<std::string> func = { "sin", "cos", "exp", "log", "tan", "sqrt"};
    vector<token> result;
    std::string input;
    size_t pos;

    token nextToken();
    token tokenVariable();
    token tokenNumber();
    void setVariableType();
    void skipSpace();
};