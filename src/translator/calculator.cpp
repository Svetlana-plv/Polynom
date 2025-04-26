#include "calculator.h"
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include "translator.h"

using namespace std;


expression::expression() {}

expression::expression(string& e) {
		newExpr(e);
	}

void expression::newExpr() {
	string m;
	std::getline(std::cin, expr);
	newExpr();
}

void expression::newExpr(string& e) {
	expr = e;
	translator t;
	//��������� ������ � ��������� ������
	try {
		value = t.logicNode(expr, variables, simpleExpr, value);
		isError = false;
	}
	catch (const std::string& e) {
		isError = true;
		type = typeExpression::ERROR;
		std::cout << "Error: " << e << std::endl;
	} 

}

void expression::setter(double set) { //��� ��������
	value = set;
}

double expression::getter() {
	return value;
}

void expression::outputVariables() {
		for (const auto& var : variables) {
			std::cout << var.first << std::endl;
	}
}

bool expression::checkError() {
	return isError;
}





	//������� ������ ��� ���� ������(� �������, ��� ��� ��������)
void screen::clear_screen() {
	// ��� Windows
#ifdef _WIN32
	std::system("cls");
	// ��� Linux/macOS
#else
	std::system("clear");
#endif
}

void screen::counting() {

	std::string input;
	expression expr;
	do {
		std::getline(std::cin, input);
		expr.newExpr(input);
		if (input == "stop") { continue; }

		if (expr.getter() != NOTHING && !expr.checkError()) {
			std::cout << "result: " << expr.getter() << endl;
		}

		else {
		}
		//clear_screen();
		//������� ������


		//����� ���������� ����������
		//����������� �������
		//std::cout << "\033[0;0H";


	} while (input != "stop");
}

