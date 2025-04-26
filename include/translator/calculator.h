#pragma once
#include <cctype>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include "structs.h"
#include "translator.h"

using namespace std;

class expression {
private:

	double value = NOTHING;

	bool isError;
	string expr;
	string simpleExpr = "";

	unordered_map<string, double> variables; //все переменные
	typeExpression type;


public:

	expression();

	expression(string& e);

	void newExpr();
	void newExpr(string& e);
	void setter(double set);
	double getter();
	void outputVariables();
	bool checkError();
};

class screen {
private:

	//очистка экрана для всех систем(в надежде, что это работает)
	void clear_screen();
public:

	void counting();
};

