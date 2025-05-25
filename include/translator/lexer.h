#pragma once
#include "structs.h"
#include <stdexcept>
using namespace std;


class Lexer {
public:
    vector<token> makeTokens(std::string inputStr);
private:
    std::string input;
    size_t pos;

    token nextToken();
    token tokenNumber();
    void skipSpace();
};