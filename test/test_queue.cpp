#include <gtest/gtest.h>
#include "queue.h"
#include <iostream>


//конструктор
TEST(queue, can_create_queue) {
	EXPECT_NO_THROW(queue<int> q(10));
}

TEST(queue, can_not_create_empty_queue) {
	EXPECT_ANY_THROW(queue<int> q(0));
}

TEST(queue, can_not_create_queue_with_negativ_capacity) {
	EXPECT_ANY_THROW(queue<int> q(-1));
}

//конструктор копирования
TEST(queue, can_use_copy_constructor) {
	queue<int> q(10);
	EXPECT_NO_THROW(queue<int> w(q));
}

TEST(queue, copy_constructor_correct_copy) {
	queue<int> q(10);
	q.push(1);
	q.push(3);
	q.push(5);
	queue<int> w(q);

	EXPECT_EQ(q.currentSize(), w.currentSize());
	EXPECT_EQ(q.maxSize(), w.maxSize());

	EXPECT_EQ(q.pop(), w.pop());
	EXPECT_EQ(q.pop(), w.pop());
	EXPECT_EQ(q.pop(), w.pop());
}

TEST(queue, copy_queue_is_independet) {
	queue<int> q(10);
	q.push(1);
	q.push(3);
	q.push(5);
	queue<int> w(q);

	q.push(7);
	
	EXPECT_NE(q.currentSize(), w.currentSize());

	w.push(8);

	EXPECT_EQ(q.pop(), w.pop());
	EXPECT_EQ(q.pop(), w.pop());
	EXPECT_EQ(q.pop(), w.pop());
	EXPECT_NE(q.pop(), w.pop()); //последние элементы разные
}

TEST(queue, copy_constructor_empty_queue) {
	queue<int> q(10);
	queue<int> w(q);

	EXPECT_TRUE(w.empty());
	EXPECT_EQ(w.currentSize(), 0);
	EXPECT_EQ(w.maxSize(), 10);
}

//конструктор перемещения
TEST(queue, can_use_move_constructor) {
	queue<int> q(10);
	EXPECT_NO_THROW(queue<int> w(std::move(q)));
}

TEST(queue, move_constructor_use) {
	queue<int> q(10);
	q.push(3);
	q.push(5);
	q.push(7);

	queue<int> w(std::move(q));

	EXPECT_TRUE(q.empty());
	EXPECT_EQ(w.currentSize(), 3);
	EXPECT_EQ(w.pop(), 3);
	EXPECT_EQ(w.pop(), 5);
	EXPECT_EQ(w.pop(), 7);
	EXPECT_EQ(q.currentSize(), 0);
	EXPECT_EQ(q.maxSize(), 0);
}

TEST(queue, move_constructor_use_empty_queue) {
	queue<int> q(10);

	queue<int> w(std::move(q));

	EXPECT_TRUE(q.empty());
	EXPECT_TRUE(w.empty());
}

//оператор присваивания
TEST(queue, can_use_operator_equal) {
	queue<int> q(10);

	EXPECT_NO_THROW(queue<int> w = q);
}

TEST(queue, operator_equal_correct_copy) {
	queue<int> q(10);
	q.push(1);
	q.push(3);
	q.push(5);
	queue<int> w = q;

	EXPECT_EQ(q.currentSize(), w.currentSize());
	EXPECT_EQ(q.maxSize(), w.maxSize());

	EXPECT_EQ(q.pop(), w.pop());
	EXPECT_EQ(q.pop(), w.pop());
	EXPECT_EQ(q.pop(), w.pop());
}

TEST(queue, move_queue_is_independet) {
	queue<int> q(10);
	q.push(1);
	q.push(3);
	q.push(5);
	queue<int> w = q;

	q.push(7);

	EXPECT_NE(q.currentSize(), w.currentSize());

	w.push(8);

	EXPECT_EQ(q.pop(), w.pop());
	EXPECT_EQ(q.pop(), w.pop());
	EXPECT_EQ(q.pop(), w.pop());
	EXPECT_NE(q.pop(), w.pop()); //последние элементы разные
}

//оператор перемещения
TEST(queue, can_use_operator_move) {
	queue<int> q(10);
	EXPECT_NO_THROW(queue<int> w = std::move(q));
}

TEST(queue,operator_move_use) {
	queue<int> q(10);
	q.push(3);
	q.push(5);
	q.push(7);

	queue<int> w = std::move(q);

	EXPECT_TRUE(q.empty());
	EXPECT_EQ(w.currentSize(), 3);
	EXPECT_EQ(w.pop(), 3);
	EXPECT_EQ(w.pop(), 5);
	EXPECT_EQ(w.pop(), 7);
	EXPECT_EQ(q.currentSize(), 0);
	EXPECT_EQ(q.maxSize(), 0);
}

TEST(queue, operator_move_use_empty_queue) {
	queue<int> q(10);

	queue<int> w = std::move(q);

	EXPECT_TRUE(q.empty());
	EXPECT_TRUE(w.empty());
}

//метод push
TEST(queue, can_use_push_one_element) {
	queue<int> q(10);
	EXPECT_NO_THROW(q.push(1));
}

TEST(queue, element_is_added_for_one_element) {
	queue<int> q(10);
	q.push(10);
	EXPECT_EQ(q.pop(), 10);
}

TEST(queue, element_is_added_for_many_elements) {
	queue<int> q(10);
	q.push(10);
	q.push(12);
	q.push(22);
	EXPECT_EQ(q.pop(), 10);
	EXPECT_EQ(q.pop(), 12);
	EXPECT_EQ(q.pop(), 22);
}

TEST(queue, add_element_in_full_queue) {  //тест на вызов репаковыки
	queue<int> q(3);
	q.push(10);
	q.push(11);
	q.push(12);
	EXPECT_NO_THROW(q.push(13));
}

TEST(queue, current_size_is_changed_after_push) {
	queue<int> q(3);
	q.push(10);
	q.push(11);
	q.push(12);
	EXPECT_EQ(q.currentSize(), 3);
}

TEST(queue,	repack_dont_change_elements) {  //тест на корректность репаковки
	queue<int> q(3);
	q.push(10);
	q.push(11);
	q.push(12);
	q.push(22); //здесь случится репаковка
	EXPECT_EQ(q.pop(), 10);
	EXPECT_EQ(q.pop(), 11);
	EXPECT_EQ(q.pop(), 12);
	EXPECT_EQ(q.pop(), 22);
}

TEST(queue, repack_corrected_increase_capacity) {  //тест на корректность репаковки
	queue<int> q(3);
	q.push(10);
	q.push(11);
	q.push(12);
	q.push(22); //здесь случится репаковка
	EXPECT_EQ(q.maxSize(), 6); //в два раза увелечение
}

TEST(queue,	check_cycle_work_in_push) { 
	queue<int> q(3);
	q.push(10);
	q.push(11);
	q.push(12);
	q.pop();
	EXPECT_NO_THROW(q.push(13));
}

TEST(queue, cycle_correct_init_element_in_push) {
	queue<int> q(3);
	q.push(10);
	q.push(11);
	q.push(12);
	q.pop();
	q.push(13);
	q.pop();
	q.push(145);
	EXPECT_EQ(q.pop(), 12);
	EXPECT_EQ(q.pop(), 13);
	EXPECT_EQ(q.pop(), 145);
}


//тесты на pop
TEST(queue, can_use_pop) {
	queue<int> q(10);
	q.push(50);
	q.push(3);
	EXPECT_NO_THROW(q.pop());
}

TEST(queue, pop_correct_delete_element) {
	queue<int> q(10);
	q.push(50);
	q.push(3);
	q.push(4);
	EXPECT_EQ(q.pop(), 50);
	EXPECT_EQ(q.pop(), 3);
	EXPECT_EQ(q.pop(), 4);
}

TEST(queue, size_changed_after_use_pop) {
	queue<int> q(10);
	q.push(50);
	q.push(3);
	q.pop();
	EXPECT_EQ(q.currentSize(), 1);
}

TEST(queue, pop_cant_delete_anyting_in_empty_queue) {
	queue<int> q(10);
	EXPECT_ANY_THROW(q.pop());
}

TEST(queue, check_cycle_work_in_pop) {
	queue<int> q(3);
	q.push(10);
	q.push(11);
	q.push(12);
	q.pop();
	q.pop();
	q.push(12);
	q.push(12);
	q.pop();
	q.pop();
	q.push(5);
	EXPECT_EQ(q.pop(), 12);
	EXPECT_EQ(q.pop(), 5);
}
//top
TEST(queue, can_use_top) {
	queue<int> q(10);
	q.push(50);
	q.push(3);
	EXPECT_NO_THROW(q.top());
}

TEST(queue, top_correct_work) {
	queue<int> q(10);
	q.push(50);
	q.push(3);
	q.push(4);
	EXPECT_EQ(q.top(), 50);
	EXPECT_EQ(q.top(), 50);
}

TEST(queue, size_dont_changed_after_use_top) {
	queue<int> q(10);
	q.push(50);
	q.push(3);
	q.top();
	q.top();
	EXPECT_EQ(q.currentSize(), 2);
}

TEST(queue, top_cant_watch_anyting_in_empty_queue) {
	queue<int> q(10);
	EXPECT_ANY_THROW(q.top());
}

//clear
TEST(queue, can_use_cleare) {
	queue<int> q(10);
	q.push(50);
	q.push(3);
	EXPECT_NO_THROW(q.clear());
}

TEST(queue, cleare_correct_delete_all_elements) {
	queue<int> q(10);
	q.push(50);
	q.push(3);
	q.clear();
	EXPECT_NO_THROW(q.empty());
}

TEST(queue, queue_correct_work_after_cleare) {
	queue<int> q(10);
	q.push(50);
	q.push(3);
	q.clear();
	q.push(5);
	q.push(10);
	EXPECT_EQ(q.pop(), 5);
	EXPECT_EQ(q.pop(), 10);
}

//empty
TEST(queue, can_use_empty) {
	queue<int> q(10);
	q.push(50);
	q.push(3);
	EXPECT_NO_THROW(q.empty());
}

TEST(queue, can_use_empty_expect_false) {
	queue<int> q(10);
	q.push(50);
	q.push(3);
	EXPECT_FALSE(q.empty());
}

TEST(queue, can_use_empty_expect_true) {
	queue<int> q(10);
	EXPECT_TRUE(q.empty());
}

//currentSize
TEST(queue, can_use_currentSize) {
	queue<int> q(10);
	q.push(50);
	q.push(3);
	EXPECT_NO_THROW(q.currentSize());
}

TEST(queue, currentSize_correct_job_in_not_empty_queue) {
	queue<int> q(10);
	q.push(50);
	q.push(3);
	EXPECT_EQ(q.currentSize(), 2);
}

TEST(queue, currentSize_correct_job_in_empty_queue) {
	queue<int> q(10);
	EXPECT_EQ(q.currentSize(), 0);
}

TEST(queue, currentSize_correct_job_after_repack) {
	queue<int> q(2);
	q.push(10);
	q.push(13);
	q.push(11);
	q.push(12);
	EXPECT_EQ(q.currentSize(), 4);
}

//maxSize
TEST(queue, can_use_MaxSize) {
	queue<int> q(10);
	q.push(50);
	q.push(3);
	EXPECT_NO_THROW(q.maxSize());
}

TEST(queue, MaxSize_correct_work) {
	queue<int> q(10);
	q.push(50);
	q.push(3);
	EXPECT_EQ(q.maxSize(), 10);
}

TEST(queue, MaxSize_correct_work_after_repack) {
	queue<int> q(2);
	q.push(50);
	q.push(3);
	q.push(3);
	EXPECT_EQ(q.maxSize(), 4);
}