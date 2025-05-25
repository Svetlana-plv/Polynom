#pragma once
#include <vector> 
#include <string> 
#include <unordered_set>
#include <unordered_map>

#define NOTHING std::numeric_limits<double>::max()

enum class tokenType {
    OPERATORS, // оператор
    POLYNOM,
    SKOBKA,
    END,
    UNKNOWN // неизвестный токен
};

// структура для создания токена
struct token {
    token(tokenType t, const std::string& v) : type(t), value(v) {}

    tokenType type;
    std::string value;
};
