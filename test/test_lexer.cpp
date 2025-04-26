#include "gtest/gtest.h"
#include "lexer.h"

TEST(Lexer, CanCreateLexer) {
	EXPECT_NO_THROW(Lexer l);
}

TEST(Lexer, CanMakeTokensWithEmptyStr) {
	Lexer l;
	EXPECT_NO_THROW(l.makeTokens(""));
}

TEST(Lexer, CanNotMakeTokensWithUnknowenToken) {
	std::string test("%");
	Lexer l;
	EXPECT_ANY_THROW(l.makeTokens(test));
}

TEST(Lexer, CanMakeTokensWithKnowenToken) {
	std::string test("0.11 0 + - * / ^ 1 2 3 4 5 6 7 8 9 0 A B C a b c");
	Lexer l;
	EXPECT_NO_THROW(l.makeTokens(test));
}

TEST(Lexer, CanMakeTokenZero) {
	std::string test("0");
	Lexer l;
	EXPECT_NO_THROW(l.makeTokens(test));
}

TEST(Lexer, CanMakeTokensNumberWithDot) {
	std::string test("1.1 2.0 3.1110 0.22 2.");
	Lexer l;
	EXPECT_NO_THROW(l.makeTokens(test));
}

TEST(Lexer, CanNotMakeTokensNumberWithDoubleDot) {
	std::string test("1.1.0");
	Lexer l;
	EXPECT_ANY_THROW(l.makeTokens(test));
}

TEST(Lexer, CanNotMakeTokensNumberWithDoubleZeroInStart) {
	std::string test("00.1");
	Lexer l;
	EXPECT_ANY_THROW(l.makeTokens(test));
}

TEST(Lexer, CanMakeTokensVariables) {
	std::string test("abc _abcd ___a F__A _f_ f__ MeM_ I");
	Lexer l;
	EXPECT_NO_THROW(l.makeTokens(test));
}

TEST(Lexer, CanNotMakeTokensVariables) {
	std::string test("__b&");
	Lexer l;
	EXPECT_ANY_THROW(l.makeTokens(test));
}

TEST(Lexer, CanNotMakeTokensVariables2) {
	std::string test("$2.1");
	Lexer l;
	EXPECT_ANY_THROW(l.makeTokens(test));
}

TEST(Lexer, CanNotMakeTokensVariables3) {
	std::string test("2.1 me&w");
	Lexer l;
	EXPECT_ANY_THROW(l.makeTokens(test));
}

TEST(Lexer, CanMakeTokensWithOnlySpace) {
	std::string test("                                ");
	Lexer l;
	EXPECT_NO_THROW(l.makeTokens(test));
}

TEST(Lexer, CanMakeTokensWithSpacesAndToken) {
	std::string test("        x           ");
	Lexer l;
	EXPECT_NO_THROW(l.makeTokens(test));
}

TEST(Lexer, CanMakeTokensWithSpacesAndManyTokens) {
	std::string test("    (    x      +    z   )      t ");
	Lexer l;
	EXPECT_NO_THROW(l.makeTokens(test));
}

TEST(Lexer, CheckTokensOnCorrect) {
	std::string test("a + - ( 1 sin = pi");
	Lexer l;
	vector<token> tokens = l.makeTokens(test);
	EXPECT_TRUE(tokens[0].type == tokenType::VARIABLE);
	EXPECT_TRUE(tokens[1].type == tokenType::OPERATOR);
	EXPECT_TRUE(tokens[2].type == tokenType::OPERATOR);
	EXPECT_TRUE(tokens[3].type == tokenType::PARENTHESIS);
	EXPECT_TRUE(tokens[4].type == tokenType::NUMBER);
	EXPECT_TRUE(tokens[5].type == tokenType::FUNCTION);
	EXPECT_TRUE(tokens[6].type == tokenType::EQUSL);
	EXPECT_TRUE(tokens[7].type == tokenType::CONST);

	//EXPECT_NO_THROW();
}