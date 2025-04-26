#include "parser.h"

using namespace std;

bool Parser::checkSim(const vector<token>& tokens) {
    if (tokens.size() == 2 && tokens[0].type == tokenType::OPERATOR && (tokens[1].type == tokenType::NUMBER || tokens[1].type == tokenType::VARIABLE)) {

        if (tokens[0].value == "/" && tokens[1].value == "0") {
            throw std::string("division by zero");
        }
        else {
            return true;
        }

    }
    else if (tokens.size() == 3 && tokens[0].value == "*" && tokens[1].value == "*" && (tokens[1].type == tokenType::NUMBER || tokens[1].type == tokenType::VARIABLE)) {
        return true;
    }
    return false;
}

bool Parser::parserExp(const vector<token>& tokens) {

    size_t state = 0;
    size_t parCount = 0;

    for (const token& tok : tokens) {

        switch (state) {
        case 0:
            if (tok.type == tokenType::FUNCTION) { state = 6; }
            else if (tok.type == tokenType::VARIABLE || tok.type == tokenType::NUMBER || tok.type == tokenType::CONST) { state = 2; }
            else if (tok.value == "+" || tok.value == "-") { state = 1; }
            else if (tok.value == "(") { ++parCount; }
            else if (tok.value == ")") { --parCount; }
            else return false;
            break;
        case 1:
            if (tok.value == "(") { ++parCount; state = 0; }
            else if (tok.type == tokenType::FUNCTION) { state = 6; }
            else if (tok.type == tokenType::VARIABLE || tok.type == tokenType::NUMBER || tok.type == tokenType::CONST) { state = 2; }
            else return false;
            break;
        case 2:
            if (tok.type == tokenType::OPERATOR) { state = 4; }
            else if (tok.value == ")") { --parCount; state = 5; }
            else return false;
            break;
        case 3:
            if (tok.type == tokenType::VARIABLE || tok.type == tokenType::NUMBER || tok.type == tokenType::CONST) { state = 2; }
            else if (tok.type == tokenType::FUNCTION) { state = 6; }
            else return false;
            break;
        case 4:
            if (tok.value == "(") { ++parCount; state = 0; }
            else if (tok.type == tokenType::FUNCTION) { state = 6; }
            else if (tok.type == tokenType::VARIABLE || tok.type == tokenType::NUMBER || tok.type == tokenType::CONST) { state = 2; }
            else if (tok.type == tokenType::OPERATOR) { state = 3; }
            else return false;
            break;
        case 5:
            if (tok.value == ")") { --parCount; }
            else if (tok.type == tokenType::OPERATOR) { state = 1; }
            else return false;
            break;
        case 6:
            if (tok.value == "(") { ++parCount; state = 0; }
            else return false;
            break;
        default: break;
        }

    }

    if (tokens[tokens.size() - 1].type == tokenType::OPERATOR) {
        throw std::string("where is second number?");
    }

    else if (parCount == 0) {
        return true;
    }

    else {
        throw std::string("expression is wrong");
    }
}

bool Parser::checkVarInEXPR(const vector<token>& tokens, const unordered_map<string, double>& variables) { 
    //вызов проверки на допустимость всех существующих переменных

    for (const token& token : tokens) {

        if (token.type == tokenType::VARIABLE && !variables.count(token.value)) {
            throw std::string("you are trying to use an uninitialized variable");
        }

    }

    return true;

}

