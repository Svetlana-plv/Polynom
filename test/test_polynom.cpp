#include "polynom.h"

#include <gtest/gtest.h>

TEST(Polynom, can_create_empty_polynom)
{
	ASSERT_NO_THROW(Polynom());
}

TEST(Polynom, can_create_polynom_by_monom)
{
	ASSERT_NO_THROW(Polynom(Monom(1, 123)));
}

TEST(Polynom, can_create_polynom_by_monom_correct)
{
	Polynom p;
	p.add_monom(Monom(1, 123));

	EXPECT_EQ(p, Polynom(Monom(1, 123)));
}

TEST(Polynom, can_create_polynom_by_string)
{
	std::string str = "123.456 x^1 y^3 z^2 - 0.5 x^1 y^0 z^0 + 1.04 x^1 y^1 z^0";

	ASSERT_NO_THROW(Polynom(str));
}

TEST(Polynom, polynom_created_by_string_correct)
{
	std::string str = "123.456 x^1 y^3 z^2 - 0.5 x^1 y^0 z^0 + x^1 y^1 z^0";

	Polynom p1(str);

	Polynom p;
	p.add_monom(Monom(123.456, 132));
	p.add_monom(Monom(-0.5, 100));
	p.add_monom(Monom(1, 110));

	EXPECT_EQ(p, p1);
}

TEST(Polynom, polynom_that_have_the_same_deg_created_by_string_correct)
{
	std::string str = "123.456 x^1 y^3 z^2 - 25.5 x^1 y^0 z^0 + x^1 y^0 z^0";

	Polynom p1(str);

	Polynom p;
	p.add_monom(Monom(123.456, 132));
	p.add_monom(Monom(-24.5, 100));

	EXPECT_EQ(p, p1);
}

TEST(Polynom, can_addmonom)
{
	Polynom p;
	ASSERT_NO_THROW(p.add_monom(Monom(1,123)));
}

TEST(Polynom, can_addmonom_correct)
{
	Polynom p(Monom(1, 123));

	Polynom p1;
	p1.add_monom(Monom(1, 123));
	EXPECT_EQ(p, p1);
}

TEST(Polynom, can_addmonom_in_different_way)
{
	Polynom p;
	p.add_monom(Monom(1, 123));
	p.add_monom(Monom(1, 234));

	Polynom p1;
	p1.add_monom(Monom(1, 234));
	p1.add_monom(Monom(1, 123));

	ASSERT_EQ(p1, p);
}

TEST(Polynom, can_addmonom_that_already_exist_in_first_place)
{
	Polynom p;
	p.add_monom(Monom(1, 123));
	p.add_monom(Monom(1, 234));
	p.add_monom(Monom(0, 000));

	Polynom p1;
	p1.add_monom(Monom(1, 123));
	p1.add_monom(Monom(1, 234));

	ASSERT_EQ(p1, p);
}

TEST(Polynom, can_addmonom_that_already_exist)
{
	Polynom p;
	p.add_monom(Monom(1, 123));
	p.add_monom(Monom(1, 234));
	p.add_monom(Monom(1, 234));

	Polynom p1;
	p1.add_monom(Monom(1, 123));
	p1.add_monom(Monom(2, 234));
	
	ASSERT_EQ(p1, p);
}

TEST(Polynom, can_erase_zero)
{
	Polynom p;
	p.add_monom(Monom(0, 123));
	p.add_monom(Monom(0, 294));
	p.add_monom(Monom(1, 234));
	p.add_monom(Monom(0, 423));

	p.erase_zero();

	ASSERT_NO_THROW(p.erase_zero());
}

TEST(Polynom, can_erase_zero_correct)
{
	Polynom p1;
	p1.add_monom(Monom(0, 123));
	p1.add_monom(Monom(0, 294));
	p1.add_monom(Monom(1, 234));
	p1.add_monom(Monom(0, 423));

	Polynom p;
	p.add_monom(Monom(1, 234));

	p1.erase_zero();

	EXPECT_EQ(p, p1);
}

TEST(Polynom, can_mul_polynom_by_const)
{
	Polynom p;
	p.add_monom(Monom(1, 123));
	p.add_monom(Monom(3, 234));

	Polynom p1;
	p1.add_monom(Monom(2, 123));
	p1.add_monom(Monom(6, 234));

	ASSERT_EQ(p1, p*2);
}

TEST(Polynom, can_friend_mul_monom_by_const)
{
	Polynom p;
	p.add_monom(Monom(1, 123));
	p.add_monom(Monom(3, 234));


	Polynom p1;
	p1.add_monom(Monom(2, 123));
	p1.add_monom(Monom(6, 234));
	
	ASSERT_EQ(p1, 2 * p);
}

TEST(Polynom, can_add_monom_and_deg_not_in_polynom)
{
	Polynom p;
	p.add_monom(Monom(1, 123));

	Polynom p1;
	p1.add_monom(Monom(1, 123));
	p1.add_monom(Monom(2, 234));
	ASSERT_EQ(p1, p + Monom(2, 234));
}

TEST(Polynom, can_add_monom_and_deg_in_polynom)
{
	Polynom p;
	p.add_monom(Monom(1, 111));
	p.add_monom(Monom(1, 123));
	p.add_monom(Monom(2, 234));

	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(3, 123));
	p1.add_monom(Monom(2, 234));

	ASSERT_EQ(p1, p + Monom(2, 123));

}

TEST(Polynom, can_mul_monom)
{
	Polynom p1(Monom(1, 234));
	p1.add_monom(Monom(3, 111));

	Polynom p(Monom(2, 465));
	p.add_monom(Monom(6, 342));

	ASSERT_EQ(p, p1 * Monom(2, 231));
}

TEST(Polynom, can_mul_empty_monom)
{
	Polynom p1(Monom(1, 234));
	p1.add_monom(Monom(3, 111));

	Polynom p;

	ASSERT_EQ(p, p1 * Monom());
}


TEST(Polynom, can_add_polynom_and_all_degs_are_different)
{
	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(2, 222));
	Polynom p2;
	p2.add_monom(Monom(3, 123));
	p2.add_monom(Monom(4, 234));

	Polynom p;
	p.add_monom(Monom(1, 111));
	p.add_monom(Monom(2, 222));
	p.add_monom(Monom(3, 123));
	p.add_monom(Monom(4, 234));
	
	ASSERT_EQ(p, p1 + p2);
}

TEST(Polynom, can_add_polynom_and_one_degs_match)
{
	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(2, 222));
	Polynom p2;
	p2.add_monom(Monom(3, 123));
	p2.add_monom(Monom(4, 111));

	Polynom p;
	p.add_monom(Monom(5, 111));
	p.add_monom(Monom(2, 222));
	p.add_monom(Monom(3, 123));

	ASSERT_EQ(p, p1 + p2);
}

TEST(Polynom, can_add_polynom_with_itself)
{
	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(2, 222));

	Polynom p;
	p.add_monom(Monom(2, 111));
	p.add_monom(Monom(4, 222));

	ASSERT_EQ(p, p1 + p1);
}

TEST(Polynom, can_add_empty_polynom_before)
{
	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(2, 222));

	Polynom p;

	ASSERT_EQ(p1, p + p1);
}

TEST(Polynom, can_add_empty_polynom_after)
{
	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(2, 222));

	Polynom p;

	ASSERT_EQ(p1, p1 + p);
}

TEST(Polynom, can_sub_monom_and_deg_not_in_polynom)
{
	Polynom p;
	p.add_monom(Monom(1, 123));

	Polynom p1;
	p1.add_monom(Monom(1, 123));
	p1.add_monom(Monom(-2, 234));
	ASSERT_EQ(p1, p - Monom(2, 234));
}

TEST(Polynom, can_sub_monom_and_deg_in_polynom)
{
	Polynom p;
	p.add_monom(Monom(1, 111));
	p.add_monom(Monom(5, 123));
	p.add_monom(Monom(2, 234));

	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(2, 123));
	p1.add_monom(Monom(2, 234));

	ASSERT_EQ(p1, p - Monom(3, 123));

}

TEST(Polynom, can_sub_polynom_and_all_degs_are_different)
{
	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(2, 222));
	Polynom p2;
	p2.add_monom(Monom(3, 123));
	p2.add_monom(Monom(4, 234));

	Polynom p;
	
	p.add_monom(Monom(-2, 222));
	p.add_monom(Monom(3, 123));
	p.add_monom(Monom(4, 234));
	p.add_monom(Monom(-1, 111));

	Polynom p3 = p2 -p1;

	ASSERT_EQ(p, p2-p1);
}

TEST(Polynom, can_sub_polynom_and_one_degs_match)
{
	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(2, 222));
	Polynom p2;
	p2.add_monom(Monom(3, 123));
	p2.add_monom(Monom(6, 111));

	Polynom p;
	p.add_monom(Monom(5, 111));
	p.add_monom(Monom(-2, 222));
	p.add_monom(Monom(3, 123));

	ASSERT_EQ(p, p2 - p1);
}

TEST(Polynom, can_sub_polynom_with_itself)
{
	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(2, 222));

	Polynom p;

	ASSERT_EQ(p, p1 - p1);
}

TEST(Polynom, can_sub_empty_polynom)
{
	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(2, 222));

	Polynom p;

	ASSERT_EQ(p1, p1 - p);
}

TEST(Polynom, can_sub_polynom_from_empty_polynom)
{
	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(2, 222));

	Polynom p;

	Polynom p2;
	p2.add_monom(Monom(-1, 111));
	p2.add_monom(Monom(-2, 222));

	ASSERT_EQ(p2, p - p1);
}

TEST(Polynom, can_mul_empty_polynom_after)
{
	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(2, 222));

	Polynom p;

	ASSERT_EQ(p, p1 * p);
}

TEST(Polynom, can_mul_empty_polynom_before)
{
	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(2, 222));

	Polynom p;

	ASSERT_EQ(p, p * p1);
}


TEST(Polynom, can_mul_polynom_and_all_results_degs_are_different)
{
	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(2, 222));
	Polynom p2;
	p2.add_monom(Monom(3, 123));
	p2.add_monom(Monom(4, 112));

	Polynom p;
	p.add_monom(Monom(3, 234));
	p.add_monom(Monom(6, 345));
	p.add_monom(Monom(4, 223));
	p.add_monom(Monom(8, 334));

	ASSERT_EQ(p, p1 * p2);
}

TEST(Polynom, can_mul_polynom_and_one_results_degs_are_match)
{
	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(2, 123));
	Polynom p2;
	p2.add_monom(Monom(3, 333));
	p2.add_monom(Monom(4, 321));

	Polynom p;
	p.add_monom(Monom(6, 456));
	p.add_monom(Monom(4, 432));
	p.add_monom(Monom(11, 444));

	ASSERT_EQ(p, p1 * p2);
}


TEST(Polynom, can_calculate_value_at_point)
{
	Polynom p;
	p.add_monom(Monom(1, 111));
	p.add_monom(Monom(5, 222));

	EXPECT_EQ(186, p.point(1, 2, 3));
}

TEST(Polynom, can_calculate_value_at_zero_point)
{
	Polynom p;
	p.add_monom(Monom(1, 111));
	p.add_monom(Monom(5, 222));

	EXPECT_EQ(0, p.point(0, 0, 0));
}

TEST(Polynom, can_calculate_value_of_empty_polynom_at_zero_point)
{
	Polynom p;

	EXPECT_EQ(0, p.point(0, 0, 0));
}

TEST(Polynom, can_calculate_value_at_point_in_empty_polynom)
{
	Polynom p;

	EXPECT_EQ(0, p.point(1, 2, 3));
}

TEST(Polynom, can_parse_string)
{
	std::string str = "-123.456 x^1 y^3 z^2 - x^1 y^0 z^0 + 1. x^1 y^1 z^0";

	Polynom p;

	ASSERT_NO_THROW(p.parse_string(str));
}

TEST(Polynom, can_parse_string_correct)
{
	std::string str = "-123.456 x^1 y^3 z^2 - x^1 y^0 z^0 + 1. x^1 y^1 z^0";

	Polynom p1;
	p1.parse_string(str);

	Polynom p;
	p.add_monom(Monom(-123.456, 132));
	p.add_monom(Monom(-1 , 100));
	p.add_monom(Monom(1, 110));

	EXPECT_EQ(p, p1);
}