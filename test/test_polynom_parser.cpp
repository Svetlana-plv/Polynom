#include "polynom_parser.h"

#include <gtest/gtest.h>

TEST(Parser, cant_lex_empty_str)
{
	std::string str = "";

	ASSERT_ANY_THROW(Parser::lex_analysis(str));
}

TEST(Parser, cant_lex_str_with_spase)
{
	std::string str = "     ";

	ASSERT_ANY_THROW(Parser::lex_analysis(str));
}

TEST(Parser, cant_lex_str_with_incorrect_symbol)
{
	std::string str = "1*x^2";

	ASSERT_ANY_THROW(Parser::lex_analysis(str));
}

TEST(Parser, cant_lex_str_with_incorrect_letter)
{
	std::string str = "2 s^1 y^2 z^3";

	ASSERT_ANY_THROW(Parser::lex_analysis(str));
}

TEST(Parser, can_lex_monom)
{
	std::string str = "2 x^1 y^2 z^3";

	ASSERT_NO_THROW(Parser::lex_analysis(str));
}

TEST(Parser, can_lex_polynom)
{
	std::string str = "2 x^0 y^0 z^1  +  12.3 x^1 y^2 z^3  -  1. x^3 y^3 z^3";

	ASSERT_NO_THROW(Parser::lex_analysis(str));
}

TEST(Parser, cant_snt_str_that_have_only_number)
{
	std::string str = "123";

	ASSERT_ANY_THROW(Parser::snt_analysis(str));
}

TEST(Parser, cant_snt_monom_without_z)
{
	std::string str = "5 x^1 y^3";

	ASSERT_ANY_THROW(Parser::snt_analysis(str));
}

TEST(Parser, cant_snt_monom_without_x_degree)
{
	std::string str = "5 x^ y^3 z^2";

	ASSERT_ANY_THROW(Parser::snt_analysis(str));
}

TEST(Parser, cant_snt_monom_without_y_degree)
{
	std::string str = "5 x^1 y^ z^2";

	ASSERT_ANY_THROW(Parser::snt_analysis(str));
}

TEST(Parser, cant_snt_monom_without_z_degree)
{
	std::string str = "5 x^1 y^3 z^";

	ASSERT_ANY_THROW(Parser::snt_analysis(str));
}

TEST(Parser, cant_snt_monom_without_symbol_deg_belong_to_x)
{
	std::string str = "5 x1 y^3 z^2";

	ASSERT_ANY_THROW(Parser::snt_analysis(str));
}

TEST(Parser, cant_snt_monom_without_symbol_deg_belong_to_y)
{
	std::string str = "5 x^1 y3 z^2";

	ASSERT_ANY_THROW(Parser::snt_analysis(str));
}

TEST(Parser, cant_snt_monom_without_symbol_deg_belong_to_z)
{
	std::string str = "5 x^1 y^3 z2";

	ASSERT_ANY_THROW(Parser::snt_analysis(str));
}

TEST(Parser, cant_snt_monom_with_not_digit_degree_x)
{
	std::string str = "5 x^13 y^3 z^2";

	ASSERT_ANY_THROW(Parser::snt_analysis(str));
}

TEST(Parser, cant_snt_monom_with_not_digit_degree_y)
{
	std::string str = "5 x^1 y^33 z^2";

	ASSERT_ANY_THROW(Parser::snt_analysis(str));
}

TEST(Parser, cant_snt_monom_with_not_digit_degree_z)
{
	std::string str = "5 x^1 y^3 z^23";

	ASSERT_ANY_THROW(Parser::snt_analysis(str));
}

TEST(Parser, cant_snt_monom_with_coef_with_two_point)
{
	std::string str = "5.3. x^1 y^3 z^2";

	ASSERT_ANY_THROW(Parser::snt_analysis(str));
}

TEST(Parser, cant_snt_monom_with_coef_with_two_point_near)
{
	std::string str = "5..4 x^1 y^3 z^2";

	ASSERT_ANY_THROW(Parser::snt_analysis(str));
}

TEST(Parser, cant_snt_monom_with_with_two_point_before_coef)
{
	std::string str = "..4 x^1 y^3 z^2";

	ASSERT_ANY_THROW(Parser::snt_analysis(str));
}

TEST(Parser, cant_snt_monom_with_coef_starts_form_zero)
{
	std::string str = "012 x^1 y^3 z^2";

	ASSERT_ANY_THROW(Parser::snt_analysis(str));
}

TEST(Parser, can_snt_monom_with_double_coef_starts_form_zero)
{
	std::string str = "0.4 x^1 y^3 z^2";

	ASSERT_NO_THROW(Parser::snt_analysis(str));
}

TEST(Parser, can_snt_monom_with_double_coef)
{
	std::string str = "1.4 x^1 y^3 z^2";

	ASSERT_NO_THROW(Parser::snt_analysis(str));
}

TEST(Parser, can_snt_monom_without_coef)
{
	std::string str = "x^1 y^3 z^2";

	ASSERT_NO_THROW(Parser::snt_analysis(str));
}

TEST(Parser, can_snt_monom_with_minus_before_coef)
{
	std::string str = "- 1.2 x^1 y^3 z^2";

	Parser::snt_analysis(str);

	ASSERT_NO_THROW(Parser::snt_analysis(str));
}

TEST(Parser, can_snt_monom_with_point_before_coef)
{
	std::string str = ".4 x^1 y^3 z^2";

	ASSERT_NO_THROW(Parser::snt_analysis(str));
}

TEST(Parser, can_snt_monom_with_point_after_coef)
{
	std::string str = "4. x^1 y^3 z^2";

	ASSERT_NO_THROW(Parser::snt_analysis(str));
}

TEST(Parser, can_snt_monom_with_double_coef_long)
{
	std::string str = "123.456 x^1 y^3 z^2";

	ASSERT_NO_THROW(Parser::snt_analysis(str));
}

TEST(Parser, can_snt_polynom)
{
	std::string str = "10.05 x^1 y^3 z^2 + 0.05 x^0 y^9 z^1";

	ASSERT_NO_THROW(Parser::snt_analysis(str));
}

TEST(Parser, can_snt_polynom_with_minuse_before_and_without_coef)
{
	std::string str = "-x^1 y^3 z^2 + 0.05 x^0 y^9 z^1 + x^0 y^9 z^1";

	ASSERT_NO_THROW(Parser::snt_analysis(str));
}


