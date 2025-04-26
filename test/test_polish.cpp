#include "gtest/gtest.h"
#include "parser.h"
#include "Lexer.h"
#include "polish.h"

TEST(polishConverter, CanCreatePolishConverter) {
	EXPECT_NO_THROW(polishConverter pc);
}

TEST(polishConverter, SimpleExpression) {
	std::string test("* 7");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	p.checkSim(tokens);
	polishConverter pc;
	EXPECT_NO_THROW(pc.toPolish(tokens));
}

TEST(polishConverter, SimpleExpressionCorrect) {
	std::string test("* 7");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	p.checkSim(tokens);
	polishConverter pc;
	tokens = pc.toPolish(tokens);
	EXPECT_TRUE(tokens[0].value == "7");
	EXPECT_TRUE(tokens[1].value == "*");
}

TEST(polishConverter, ExpressionAddCorrect) {
	std::string test("2 + 2");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	p.checkSim(tokens);
	polishConverter pc;
	tokens = pc.toPolish(tokens);
	EXPECT_TRUE(tokens[0].value == "2");
	EXPECT_TRUE(tokens[1].value == "2");
	EXPECT_TRUE(tokens[2].value == "+");
}

TEST(polishConverter, ExpressionAddDicMulSubCorrect) {
	std::string test("2 + 2 - 2 * 2 / 2");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	p.checkSim(tokens);
	polishConverter pc;
	tokens = pc.toPolish(tokens);
	EXPECT_TRUE(tokens[0].value == ("2"));
	EXPECT_TRUE(tokens[1].value == ("2"));
	EXPECT_TRUE(tokens[2].value == ("+"));
	EXPECT_TRUE(tokens[3].value == ("2"));
	EXPECT_TRUE(tokens[4].value == ("2"));
	EXPECT_TRUE(tokens[5].value == ("*"));
	EXPECT_TRUE(tokens[6].value == ("2"));
	EXPECT_TRUE(tokens[7].value == ("/"));
	EXPECT_TRUE(tokens[8].value == ("-"));
}

TEST(polishConverter, ExpressionAddDicMulSubSkobkiCorrect) {
	std::string test("((2 + 2 - 2) * 2 )/ 2");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	p.checkSim(tokens);
	polishConverter pc;
	tokens = pc.toPolish(tokens);
	EXPECT_TRUE(tokens[0].value == ("2"));
	EXPECT_TRUE(tokens[1].value == ("2"));
	EXPECT_TRUE(tokens[2].value == ("+"));
	EXPECT_TRUE(tokens[3].value == ("2"));
	EXPECT_TRUE(tokens[4].value == ("-"));
	EXPECT_TRUE(tokens[5].value == ("2"));
	EXPECT_TRUE(tokens[6].value == ("*"));
	EXPECT_TRUE(tokens[7].value == ("2"));
	EXPECT_TRUE(tokens[8].value == ("/"));
}

TEST(polishConverter, ExpressionFunctionCorrect) {
	std::string test("sin(2)");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	p.checkSim(tokens);
	polishConverter pc;
	tokens = pc.toPolish(tokens);
	EXPECT_TRUE(tokens[0].value == ("2"));
	EXPECT_TRUE(tokens[1].value == ("sin"));
}

TEST(polishConverter, ExpressionFunctionAndOperatorCorrect) {
	std::string test("sin(2) / 22");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	p.checkSim(tokens);
	polishConverter pc;
	tokens = pc.toPolish(tokens);
	EXPECT_TRUE(tokens[0].value == ("2"));
	EXPECT_TRUE(tokens[1].value == ("sin"));
	EXPECT_TRUE(tokens[2].value == ("22"));
	EXPECT_TRUE(tokens[3].value == ("/"));
}


TEST(polishConverter, SimpleExpressionUnarCorrect) {
	std::string test("-7");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	p.checkSim(tokens);
	polishConverter pc;
	tokens = pc.toPolish(tokens);
	EXPECT_TRUE(tokens[0].value == "7");
	EXPECT_TRUE(tokens[1].value == "u-");
}

TEST(polishConverter, ExpressionAddWithVarCorrect) {
	std::string test("a + s");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	p.checkSim(tokens);
	polishConverter pc;
	tokens = pc.toPolish(tokens);
	EXPECT_TRUE(tokens[0].value == "a");
	EXPECT_TRUE(tokens[1].value == "s");
	EXPECT_TRUE(tokens[2].value == "+");
}

TEST(RPNCalculator, CanCreateRPNCalculator) {
	EXPECT_NO_THROW(RPNCalculator rpn);
}

TEST(RPNCalculator, ExpressionRPNCalculatorEvaluate) {
	std::string test("1 + 1");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	p.checkSim(tokens);
	polishConverter pc;
	tokens = pc.toPolish(tokens);
	RPNCalculator rpn;
	unordered_map<string, double> tmp{};
	double result = rpn.evaluate(tokens, tmp);
	EXPECT_EQ(result, 2);
}

TEST(RPNCalculator, ExpressionRPNCalculatorEvaluateDif) {
	std::string test("((7 + 1^22 - 2) * 88 / ((1 - 2) + 7)) /1");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	p.checkSim(tokens);
	polishConverter pc;
	tokens = pc.toPolish(tokens);
	RPNCalculator rpn;
	unordered_map<string, double> tmp{};
	tmp["a"] = 10;
	double result = rpn.evaluate(tokens, tmp);
	EXPECT_EQ(result, 88);
}

TEST(RPNCalculator, ExpressionRPNCalculatorEvaluateDifAndVariable) {
	std::string test("((7 + bb^22 - 2) * sss / ((bb - 2) + 7)) /bb");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	p.checkSim(tokens);
	polishConverter pc;
	tokens = pc.toPolish(tokens);
	RPNCalculator rpn;
	unordered_map<string, double> tmp{};
	tmp["sss"] = 88;
	tmp["bb"] = 1;
	double result = rpn.evaluate(tokens, tmp);
	EXPECT_EQ(result, 88);
}

TEST(RPNCalculator, ExpressionRPNCalculatorDivZero) {
	std::string test("7/0");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	p.checkSim(tokens);
	polishConverter pc;
	tokens = pc.toPolish(tokens);
	RPNCalculator rpn;
	unordered_map<string, double> tmp{};
	tmp["sss"] = 88;
	tmp["bb"] = 1;
	//double result = rpn.evaluate(tokens, tmp);
	EXPECT_ANY_THROW(rpn.evaluate(tokens, tmp));
}

TEST(RPNCalculator, ExpressionRPNCalculatorDivZeroWithVar) {
	std::string test("t/sss");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	p.checkSim(tokens);
	polishConverter pc;
	tokens = pc.toPolish(tokens);
	RPNCalculator rpn;
	unordered_map<string, double> tmp{};
	tmp["sss"] = 0;
	tmp["t"] = 1;
	//double result = rpn.evaluate(tokens, tmp);
	EXPECT_ANY_THROW(rpn.evaluate(tokens, tmp));
}

TEST(RPNCalculator, ExpressionRPNCalculatorSin) {
	std::string test("sin(2)");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	p.checkSim(tokens);
	polishConverter pc;
	tokens = pc.toPolish(tokens);
	RPNCalculator rpn;
	unordered_map<string, double> tmp{};
	double result = rpn.evaluate(tokens, tmp);
	EXPECT_EQ(result, std::sin(2));
}

TEST(RPNCalculator, ExpressionRPNCalculatorSinUnarSub) {
	std::string test("-sin(2)");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	p.checkSim(tokens);
	polishConverter pc;
	tokens = pc.toPolish(tokens);
	RPNCalculator rpn;
	unordered_map<string, double> tmp{};
	double result = rpn.evaluate(tokens, tmp);
	EXPECT_EQ(result, -1 * std::sin(2));
}

TEST(RPNCalculator, ExpressionRPNCalculatorDifAll) {
	std::string test("(-sin(2) + 22) * 9^2 - +22");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	p.checkSim(tokens);
	polishConverter pc;
	tokens = pc.toPolish(tokens);
	RPNCalculator rpn;
	unordered_map<string, double> tmp{};
	double result = rpn.evaluate(tokens, tmp);
	double tttmp = (-1 * std::sin(2) + 22) * (9 * 9) - +22;
	EXPECT_EQ(result, tttmp);
}

TEST(RPNCalculator, ExpressionRPNCalculatorError) {
	std::string test("log(0)");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	p.checkSim(tokens);
	polishConverter pc;
	tokens = pc.toPolish(tokens);
	RPNCalculator rpn;
	unordered_map<string, double> tmp{};
	EXPECT_ANY_THROW(rpn.evaluate(tokens, tmp));
}