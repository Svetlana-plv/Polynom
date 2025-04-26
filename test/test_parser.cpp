#include "gtest/gtest.h"
#include "parser.h"
#include "Lexer.h"

TEST(Parser, CanCreateParser) {
	EXPECT_NO_THROW(Parser p);
}

TEST(Parser, CanCheckSimExpectTrue1) {
	std::string test("* 7");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_TRUE(p.checkSim(tokens));
}

TEST(Parser, CanCheckSimExpectTrue2) {
	std::string test("^ 7.1");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_TRUE(p.checkSim(tokens));
}

TEST(Parser, ExpressionSkobki) {
	std::string test("((()))");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_TRUE(p.parserExp(tokens));
}

TEST(Parser, ExpressionSkobkiAndNumber1) {
	std::string test("(((2)))");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_TRUE(p.parserExp(tokens));
}

TEST(Parser, ExpressionSkobkiAndNumber2) {
	std::string test("(((2.1)))");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_TRUE(p.parserExp(tokens));
}

TEST(Parser, ExpressionSkobkiAndNumbersAndPlus) {
	std::string test("((7 + (2.1)))");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_TRUE(p.parserExp(tokens));
}

TEST(Parser, ExpressionAdd) {
	std::string test("1 + 100.1");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_TRUE(p.parserExp(tokens));
}

TEST(Parser, ExpressionDiv) {
	std::string test("1 / 100");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_TRUE(p.parserExp(tokens));
}

TEST(Parser, ExpressionDivAfterSkobki) {
	std::string test("(7 * 2) / 100");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_TRUE(p.parserExp(tokens));
}

TEST(Parser, ExpressionLastOperator2) {
	std::string test("(7 * 2) / ");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_ANY_THROW(p.parserExp(tokens));
}

TEST(Parser, ExpressionLastOperator1) {
	std::string test("(7 * 2 + ");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_ANY_THROW(p.parserExp(tokens));
}

TEST(Parser, ExpressionErrorSkobki1) {
	std::string test("(7 * 2 + 4 - (");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_ANY_THROW(p.parserExp(tokens));
}

TEST(Parser, ExpressionErrorSkobki2) {
	std::string test("(7 * 2 + 2))");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_ANY_THROW(p.parserExp(tokens));
}

TEST(Parser, ExpressionErrorSkobki3) {
	std::string test("(7 * 2 + 1))");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_ANY_THROW(p.parserExp(tokens));
}

TEST(Parser, ExpressionErrorNoOperant) {
	std::string test("* 7");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_FALSE(p.parserExp(tokens));
}

TEST(Parser, ExpressionMoreOperators) {
	std::string test("7 + 1 - 2.1 * 88.2 / 1.3 - 2 + 7 /1");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_TRUE(p.parserExp(tokens));
}

TEST(Parser, ExpressionMoreOperatorsWithSkob) {
	std::string test("((7 + 1 - 2.1) * 88.2 / ((1.3 - 2) + 7)) /1");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_TRUE(p.parserExp(tokens));
}

TEST(Parser, ExpressionMoreOperatorsWithSkoWithbSt) {
	std::string test("((7 + 1^22 - 2.1) * 88.2 / ((1.3 - 2) + 7)) /1");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_TRUE(p.parserExp(tokens));
}


TEST(Parser, ExpressionUOperator1) {
	std::string test("-11 + -11 / -22");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_TRUE(p.parserExp(tokens));
}

TEST(Parser, ExpressionUOperator2) {
	std::string test("-11 + -11 / -22 * - 11.1");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_TRUE(p.parserExp(tokens));
}

TEST(Parser, ExpressionUOperator3) {
	std::string test("-11 + -11 / -0.111 * - 0.1");
	Lexer l; 
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_TRUE(p.parserExp(tokens));
}

TEST(Parser, ExpressionWithVar) {
	std::string test("e + 22 / c");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_TRUE(p.parserExp(tokens));
}

TEST(Parser, ExpressionErrorInput) {
	std::string test("e u + 22 / c");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_FALSE(p.parserExp(tokens));
}

TEST(Parser, ExpressionErrorInput2) {
	std::string test("2.1 2");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	Parser p;
	EXPECT_FALSE(p.parserExp(tokens));
}

//больше не придумалось 