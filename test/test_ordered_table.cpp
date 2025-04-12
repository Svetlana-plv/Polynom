#include "ordered_table.h"
#include "unordered_table.h"
#include <gtest/gtest.h>

template <typename T>
class TableTest : public ::testing::Test {
protected:
    T table;
};

using TableTypes = ::testing::Types<OrderedTable<std::string, int>, UnorderedTable<std::string, int>>;
TYPED_TEST_SUITE(TableTest, TableTypes);

TYPED_TEST(TableTest, Create) {
    ASSERT_NO_THROW(TypeParam table);
}

TYPED_TEST(TableTest, CheckEmpty) {

    TypeParam table;

    ASSERT_NO_THROW(table.empty());
}

TYPED_TEST(TableTest, TableIsEmpty) {

    TypeParam table;

    EXPECT_EQ(1, table.empty());
}

TYPED_TEST(TableTest, Clear) {

    TypeParam table;

    table.insert("a", 2);
    table.insert("b", 2);

    ASSERT_NO_THROW(table.clear());
    EXPECT_EQ(0, table.size());

}

TYPED_TEST(TableTest, CheckSize) {

    TypeParam table;

    ASSERT_NO_THROW(table.size());
}

TYPED_TEST(TableTest, CheckExist) {

    TypeParam table;

    table.insert("a", 2);

    ASSERT_TRUE(table.exist("a"));
}

TYPED_TEST(TableTest, CheckNotExist) {

    TypeParam table;

    ASSERT_FALSE(table.exist("a"));
}

TYPED_TEST(TableTest, SizeOfEmptyTableIsCorrect) {

    TypeParam table;

    EXPECT_EQ(0, table.size());
}

TYPED_TEST(TableTest, SizeOfTableIsCorrect) {

    TypeParam table;

    table.insert("a", 2);

    EXPECT_EQ(1, table.size());
}

TYPED_TEST(TableTest, InsertInEmptyTable) {

    TypeParam table;

    ASSERT_NO_THROW(table.insert("a", 2););
}

TYPED_TEST(TableTest, InsertInNotEmptyTable) {

    TypeParam table;

    table.insert("b", 3);

    ASSERT_NO_THROW(table.insert("a", 2));
}

TYPED_TEST(TableTest, CantInsertExistingElement) {

    TypeParam table;

    table.insert("a", 2);

    EXPECT_EQ(table.end(), table.insert("a", 2));
}

TYPED_TEST(TableTest, CanInsertSeveralTimes) {

    TypeParam table;

    ASSERT_NO_THROW(table.insert("a", 2));
    ASSERT_NO_THROW(table.insert("b", 3));
    ASSERT_NO_THROW(table.insert("c", 2));
    EXPECT_EQ(3, table.size());
}

TYPED_TEST(TableTest, CantInsertExistingElementInNotEmptyTable) {

    TypeParam table;

    ASSERT_NO_THROW(table.insert("a", 2));
    ASSERT_NO_THROW(table.insert("b", 3));
    ASSERT_NO_THROW(table.insert("a", 8));
    EXPECT_EQ(2, table.size());
}

TYPED_TEST(TableTest, CantRandomInsertExistingElementInNotEmptyTable) {

    TypeParam table;

    ASSERT_NO_THROW(table.insert("a", 2));
    ASSERT_NO_THROW(table.insert("b", 3));
    ASSERT_NO_THROW(table.insert("a", 2));
    ASSERT_NO_THROW(table.insert("a", 5));
    ASSERT_NO_THROW(table.insert("c", 8));
    ASSERT_NO_THROW(table.insert("aa", 8));
    EXPECT_EQ(4, table.size());
}

TYPED_TEST(TableTest, InsertDontChangeValue) {

    TypeParam table;

    ASSERT_NO_THROW(table.insert("a", 2));
    ASSERT_NO_THROW(table.insert("a", 5));

    EXPECT_EQ(1, table.size());
    EXPECT_EQ(2, table["a"]);
}

TYPED_TEST(TableTest, CantEraseFromEmptyTable) {

    TypeParam table;

    ASSERT_EQ(table.end(), table.erase("a"));
}

TYPED_TEST(TableTest, CantEase) {

    TypeParam table;

    table.insert("a", 5);

    ASSERT_EQ(table.begin(), table.erase("a"));
    EXPECT_EQ(0, table.size());

}

TYPED_TEST(TableTest, CanEaseSeveralElement) {

    TypeParam table;

    table.insert("a", 1);
    table.insert("b", 2);
    table.insert("c", 3);

    ASSERT_NO_THROW(table.erase("a"));
    ASSERT_NO_THROW(table.erase("b"));
    ASSERT_NO_THROW(table.erase("c"));
    EXPECT_EQ(0, table.size());
}

TYPED_TEST(TableTest, CantFindInEmptyTable) {

    TypeParam table;

    ASSERT_EQ(table.end(), table.find("a"));
    EXPECT_EQ(0, table.size());

}

TYPED_TEST(TableTest, CanFind) {

    TypeParam table;

    TypeParam::Iterator it = table.insert("a", 5);

    ASSERT_EQ(it, table.find("a"));
    EXPECT_EQ(1, table.size());
}

TYPED_TEST(TableTest, CanGetValueBySqareBrackets) {

    TypeParam table;

    table.insert("a", 5);

    ASSERT_EQ(5, table["a"]);
    EXPECT_EQ(1, table.size());
}

//#include "ordered_table.h"
//#include "unordered_table.h"
//#include <string>
//#include <gtest/gtest.h>  // Обратите внимание на изменение имени заголовка
//
//// Шаблонный тестовый класс
//template <typename T>
//class TableTest : public ::testing::Test {
//protected:
//	T table;  // Тестируемая таблица
//};
//
//// Определяем типы, для которых будут запускаться тесты
//using TableTypes = ::testing::Types<OrderedTable<std::string, int>, UnorderedTable<std::string, int>>;
//TYPED_TEST_SUITE_P(TableTest);  // Используем TYPED_TEST_SUITE_P вместо TYPED_TEST_SUITE
//
//// Регистрируем тесты
//TYPED_TEST_P(TableTest, Create) {
//	ASSERT_NO_THROW(TypeParam table);
//}
//
//// Регистрируем все тестовые случаи
//REGISTER_TYPED_TEST_SUITE_P(TableTest, Create);
//
//// Создаем экземпляры тестов для каждого типа
//INSTANTIATE_TYPED_TEST_SUITE_P(My, TableTest, TableTypes);



//#include "gtest/gtest.h"
//#include "ordered_table.h"
//#include "unordered_table.h"
//#include <string>
//
//template <typename T>
//class TableTest : public ::testing::Test {
//protected:
//    T table;
//};
//
//using TableTypes = ::testing::Types<OrderedTable<std::string, int>, UnorderedTable<std::string, int>>;
//TYPED_TEST_SUITE(TableTest, TableTypes);  // Используем TYPED_TEST_SUITE вместо TYPED_TEST_SUITE_P
//
//TYPED_TEST(TableTest, Create) {
//    ASSERT_NO_THROW(TypeParam table);  // Проверяем создание таблицы
//}




//TEST(OrderedTable, can_create_empty_table)
//{
//	ASSERT_NO_THROW((OrderedTable<std::string, int>()));
//}

//TEST(OrderedTable, can_check_empty_table)
//{
//	OrderedTable<std::string, int> table;
//
//	EXPECT_EQ(table.empty(), 1);
//}
//
//TEST(OrderedTable, can_check_not_empty_table)
//{
//	OrderedTable<std::string, int> table;
//
//	table.insert("a", 2);
//
//	EXPECT_EQ(table.empty(), 0);
//}
//
//TEST(OrderedTable, can_get_size_of_table)
//{
//	OrderedTable<std::string, int> table;
//
//	table.insert("a", 2);
//	table.insert("b", 3);
//
//	EXPECT_EQ(table.size(), 2);
//}
//
//TEST(OrderedTable, can_get_size_of_table)
//{
//	OrderedTable<std::string, int> table;
//
//	table.insert("a", 2);
//	table.insert("b", 3);
//
//	EXPECT_EQ(table.size(), 2);
//}



