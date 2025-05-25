#include "parser.h"

using namespace std;


bool ParserE::parserExp(const vector<token>& tokens) {

    size_t state = 0;
    size_t parCount = 0;

    for (const token& tok : tokens) {

        switch (state) {
        case 0:
            if (tok.type == tokenType::OPERATORS) { state = 1; }
            else if (tok.value == "(") { ++parCount; }
            else if (tok.value == ")") { --parCount; }
            else if (tok.type == tokenType::POLYNOM) { state = 2; }
            else return false;
            break;
        case 1:
            if (tok.value == "(") { ++parCount; state = 0; }
            else if (tok.type == tokenType::POLYNOM) { state = 2; }
            else return false;
            break;
        case 2:
            if (tok.type == tokenType::OPERATORS) { state = 3; }
            else if (tok.value == ")") { --parCount; state = 4; }
            else return false;
            break;
        case 3:
            if (tok.type == tokenType::POLYNOM) { state = 2; }
            else if (tok.value == "(") { ++parCount; state = 0; }
            else return false;
            break;
        case 4:
            if (tok.value == ")") { ++parCount; state = 4; }
            else if (tok.type == tokenType::OPERATORS) { state = 3; }
            else return false;
            break;
        default: break;
        }

    }

    if (tokens[tokens.size() - 1].type == tokenType::OPERATORS) {
        throw std::string("where is second number?");
    }

    else if (parCount == 0) {
        return true;
    }

    else {
        throw std::string("expression is wrong");
    }
}

