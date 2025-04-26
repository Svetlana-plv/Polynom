#pragma once

#include "structs.h"
#include <stdexcept>
using namespace std;

class Parser {
private:

public:

    bool checkSim(const vector<token>& tokens);
    bool parserExp(const vector<token>& tokens);
    bool checkVarInEXPR(const vector<token>& tokens, const unordered_map<string, double>& variables);
};
