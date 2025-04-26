#include "stack.h"
#include <gtest/gtest.h>
#include <list>
//#include <variant>

using namespace std;

TEST(stack, can_create_stack) {
	stack<int, std::vector<int>> mew;
	EXPECT_NO_THROW();
}

TEST(stack, can_use_constructor_copy) {
	stack<int, std::vector<int>> mew;
	mew.push(20);
	stack<int, std::vector<int>> neww(mew);
	EXPECT_NO_THROW();
}

TEST(stack, can_use_constructor_move) {
	stack<int, std::vector<int>> mew;
	mew.push(20);
	stack<int, std::vector<int>> neww(std::move(mew));
	EXPECT_NO_THROW();
}

TEST(stack, can_use_operator_equal) {
	stack<int, std::vector<int>> mew;
	stack<int, std::vector<int>> meww;
	mew.push(20);
	meww.push(30);
	EXPECT_NO_THROW(mew = meww);
}

TEST(stack, can_use_operator_move) {
	stack<int, std::vector<int>> mew;
	stack<int, std::vector<int>> meww;
	mew.push(20);
	meww.push(30);
	EXPECT_NO_THROW(mew = std::move(meww));
}

TEST(stack, can_use_push) {
	stack<int, std::vector<int>> mew;
	EXPECT_NO_THROW(mew.push(10));
}

TEST(stack, push_element_on_top) {
	stack<int, std::vector<int>> mew;
	mew.push(10);
	EXPECT_NO_THROW(mew.top(), 10);
}

TEST(stack, can_use_pop) {
	stack<int, std::vector<int>> mew;
	mew.push(10);
	EXPECT_NO_THROW(mew.pop());
}

TEST(stack, can_use_pop_with_empty_stack) {
	stack<int, std::vector<int>> mew;
	EXPECT_ANY_THROW(mew.pop());
}

TEST(stack, pop_deleted_last_element) {
	stack<int, std::vector<int>> mew;
	mew.push(10);
	mew.push(100);
	mew.push(10000);
	mew.pop();
	EXPECT_EQ(mew.top(), 100);
}

TEST(stack, can_use_top) {
	stack<int, std::vector<int>> mew;
	mew.push(20);
	EXPECT_NO_THROW(mew.top());
}

TEST(stack, top_return_top_value) {
	stack<int, std::vector<int>> mew;
	mew.push(5);
	mew.push(10);
	mew.push(100);
	EXPECT_EQ(mew.top(), 100);
}

TEST(stack, can_use_top_with_empty_stack) {
	stack<int, std::vector<int>> mew;
	EXPECT_ANY_THROW(mew.top());
}

TEST(stack, can_use_clear) {
	stack<int, std::vector<int>> mew;
	mew.push(20);
	EXPECT_NO_THROW(mew.clear());
}

TEST(stack, can_use_clear_with_empty_stack) {
	stack<int, std::vector<int>> mew;
	EXPECT_NO_THROW(mew.clear());
}

TEST(stack, stask_is_empty_after_clear) {
	stack<int, std::vector<int>> mew;
	mew.push(20);
	mew.clear();
	EXPECT_EQ(mew.size(), 0);
}

TEST(stack, can_use_size_with_empty_stack) {
	stack<int, std::vector<int>> mew;
	EXPECT_NO_THROW(mew.size());
}

TEST(stack, can_use_size) {
	stack<int, std::vector<int>> mew;
	mew.push(20);
	//stack<int, std::variant<int, double>> meww;
	EXPECT_NO_THROW(mew.size());
}