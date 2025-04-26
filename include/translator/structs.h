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
    VARIABLE, // ����������
    NUMBER,   // �����
    OPERATOR, // ��������
    PARENTHESIS, // ������
    EQUSL, //�����
    FUNCTION, //�������
    CONST,  //�������
    END, // �����
    UNKNOWN // ����������� �����
};


enum class typeExpression {
    SET, //������� ����������
    EXPRESSION, //������� ���������
    EQUAL, //���������� ��������
    ERROR, //������ ������
    SIMPLE //������� ��������� (�������� + �������)
};

/*
enum class variableType {
    FUNCTION, //�������
    VARIABLE, //����������
    CONST,  //���������
    UNKNOW //����������
};*/


// ��������� ��� �������� ������
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