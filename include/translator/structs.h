#pragma once
#include <vector> 
#include <string> 
#include <unordered_set>
#include <unordered_map>

#define NOTHING std::numeric_limits<double>::max()

//extern std::unordered_set<std::string> con;
//extern std::unordered_set<std::string> func;


//std::unordered_set<std::string> con = { "pi", "e" };
//std::unordered_set<std::string> func = { "sin", "cos", "exp", "ln" };

enum class tokenType {
    VARIABLE, // переменная
    NUMBER,   // число
    OPERATOR, // оператор
    PARENTHESIS, // скобки
    EQUSL, //равно
    FUNCTION, //функция
    CONST,  //констан
    END, // конец
    UNKNOWN // неизвестный токен
};


enum class typeExpression {
    SET, //задание переменной
    EXPRESSION, //обычное выражение
    EQUAL, //повторение операции
    ERROR, //ошибка строки
    SIMPLE //простое выражение (операция + операнд)
};

/*
enum class variableType {
    FUNCTION, //функции
    VARIABLE, //переменные
    CONST,  //константы
    UNKNOW //неизвестно
};*/


// структура для создания токена
struct token {
    token(tokenType t, const std::string& v) : type(t), value(v) {}

    tokenType type;
    //variableType varType;
    std::string value;
};

/*struct variable {
    variable(std::string n, variableType vt = variableType::UNKNOW, const double& v = NOTHING) : value(v), name(n), varType(vt) {}

    std::string name;
    variableType varType;
    double value;
};*/