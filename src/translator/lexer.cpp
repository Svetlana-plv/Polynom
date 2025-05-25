#include "Lexer.h"

using namespace std;


vector<token> Lexer::makeTokens(std::string inputStr) {
    std::string res;
    for (char c : inputStr) {
        if (c != ' ') {
            res += c;
        }
    }
    input = res;
    pos = 0;

    vector<token> result;
    token token = nextToken();
    while (token.type != tokenType::END) {
        if (token.type == tokenType::UNKNOWN) throw std::string("invaliad symbol");
        result.push_back(token);
        token = nextToken();
    }

    return result;
}

token Lexer::nextToken() {
    skipSpace();

    if (pos >= input.length()) return token(tokenType::END, "");

    char current = input.at(pos);

    if (current == '+' || current == '-' || current == '*') {
        pos++;
        return token(tokenType::OPERATORS, std::string(1, current));
    }

    // если символ скобка, 
    else if (current == '(' || current == ')') {
        pos++;
        return token(tokenType::SKOBKA, std::string(1, current));
    }


    else if (current == 'x' || isdigit(current)) {
        return tokenNumber();
    }

    // если ничего не нашли, то возвращаем неизвестный токен
    return token(tokenType::UNKNOWN, std::string(1, current));
}

// пропустить пробелы
void Lexer::skipSpace() {
    while (pos < input.length() && isspace(input.at(pos))) {
        pos++;
    }
}

//пытаемся в полином
token Lexer::tokenNumber() {
    size_t startPos = pos;
    int state = 0;
    while (pos < input.size()) {
        switch (state){
        case 0:
            if (input.at(pos) == '0') state = 1;
            else if (isdigit(input.at(pos))) state = 2;
            else if (input.at(pos) == 'x') state = 4;
            else state = 10;
            break;
        case 1:
            if (input.at(pos) == '.') state = 3;
            else state = 10;
            break;
        case 2: 
            if (isdigit(input.at(pos))) state = 2;
            else if (input.at(pos) == '.') state = 3;
            else if (input.at(pos) == 'x') state = 4;
            else state = 10;
            break;
        case 3:
            if (isdigit(input.at(pos))) state = 3;
            else if (input.at(pos) == 'x') state = 4;
            else state = 10;
            break;
        case 4:
            if (input.at(pos) == '^' &&
                isdigit(input.at(pos + 1)) &&
                input.at(pos + 2) == 'y' &&
                input.at(pos + 3) == '^' &&
                isdigit(input.at(pos + 4)) &&
                input.at(pos + 5) == 'z' &&
                input.at(pos + 6) == '^' &&
                isdigit(input.at(pos + 7))
                ) state = 5;
            else state = 10;
            pos += 7;
            break;
        }


        if (state == 10) throw std::string("wrong the number");
        pos++;

        if (state == 5) break;
    }



    return token(tokenType::POLYNOM, input.substr(startPos, pos - startPos));
}
