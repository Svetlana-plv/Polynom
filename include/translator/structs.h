#pragma once
#include <vector> 
#include <string> 
#include <unordered_set>
#include <unordered_map>

#define NOTHING std::numeric_limits<double>::max()

enum class tokenType {
    OPERATORS, // ��������
    POLYNOM,
    SKOBKA,
    END,
    UNKNOWN // ����������� �����
};

// ��������� ��� �������� ������
struct token {
    token(tokenType t, const std::string& v) : type(t), value(v) {}

    tokenType type;
    std::string value;
};
