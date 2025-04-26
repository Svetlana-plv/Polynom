#include <gtest/gtest.h>
#include "chained_hashtable.h"
#include <memory>
#include <string>

// Класс для генерации имен
struct HashFunctionNameGenerator {
    std::string operator()(const testing::TestParamInfo<HashTable<std::string, int>::HashFunction>& info) const {
        switch (info.param) {
        case HashTable<std::string, int>::STD: return "STD";
        case HashTable<std::string, int>::DJB2: return "DJB2";
        case HashTable<std::string, int>::SIMPLE: return "SIMPLE";
        default: return "UNKNOWN";
        }
    }
};

// Фикстура для параметризованных тестов
class HashTableTest : public testing::TestWithParam<HashTable<std::string, int>::HashFunction> {
protected:

    HashTable<std::string, int> table;

    void SetUp() override {
        // Создаем хеш-таблицу с текущей хеш-функцией из параметра
        table = HashTable<std::string, int>(10, GetParam());
    }

};

INSTANTIATE_TEST_SUITE_P(
    HashFunctions,
    HashTableTest,
    testing::Values(
        HashTable<std::string, int>::STD,
        HashTable<std::string, int>::DJB2,
        HashTable<std::string, int>::SIMPLE
    ),
    HashFunctionNameGenerator()
);

TEST_P(HashTableTest, CanInsert) {
    ASSERT_NO_THROW(table.insert("key1", 42));
    ASSERT_NO_THROW(table.insert("key2", 12));
    ASSERT_NO_THROW(table.insert("key3", 39));

    EXPECT_EQ(3, table.size());
}

TEST_P(HashTableTest, InsertCorrect) {
    table.insert("key1", 42);
    table.insert("key2", 12);
    table.insert("key3", 39);

    auto it1 = table.find("key1");
    ASSERT_NE(it1, table.end());
    EXPECT_EQ(it1->second, 42);

    auto it2 = table.find("key2");
    ASSERT_NE(it2, table.end());
    EXPECT_EQ(it2->second, 12);

    auto it3 = table.find("key3");
    ASSERT_NE(it3, table.end());
    EXPECT_EQ(it3->second, 39);

    EXPECT_EQ(table.find("nonexistent"), table.end());
}

TEST_P(HashTableTest, CanInsertManyElem) {
    size_t num = 1000;

    for(size_t i=0; i<num; i++) table.insert("key"+std::to_string(i), i);
    for (size_t i = 0; i < num; i++) table.erase("key" + std::to_string(i));

    EXPECT_EQ(0, table.size());
}

TEST_P(HashTableTest, Erase) {
    table.insert("key1", 42);
    table.insert("key2", 123);

    EXPECT_TRUE(table.erase("key1"));
    EXPECT_FALSE(table.erase("key1"));
    EXPECT_EQ(table.find("key1"), table.end());

    EXPECT_TRUE(table.erase("key2"));
    EXPECT_EQ(table.size(), 0);
}

TEST_P(HashTableTest, Rehash) {
    size_t initial_size = table.table_size();

    // Вставляем достаточное количество элементов для срабатывания rehash
    for (int i = 0; i < 20; ++i) {
        table.insert("key" + std::to_string(i), i);
    }

    EXPECT_GT(table.table_size(), initial_size);
    EXPECT_EQ(table.size(), 20);

    // Проверяем, что все элементы на месте после rehash
    for (int i = 0; i < 20; ++i) {
        auto it = table.find("key" + std::to_string(i));
        ASSERT_NE(it, table.end());
        EXPECT_EQ(it->second, i);
    }
}

TEST_P(HashTableTest, ChangeHashFunction) {
    table.insert("key1", 1);
    table.insert("key2", 2);
    table.insert("key3", 3);

    // Меняем хеш-функцию на следующую в списке
    auto new_hash_func = static_cast<HashTable<std::string, int>::HashFunction>((GetParam() + 1) % 3);
    table.set_hash_function(new_hash_func);

    // Проверяем, что элементы остались доступны
    EXPECT_EQ(table["key1"], 1);
    EXPECT_EQ(table["key2"], 2);
    EXPECT_EQ(table["key3"], 3);
}

// Тест итераторов
TEST_P(HashTableTest, Iterator) {
    table.insert("key1", 1);
    table.insert("key2", 2);
    table.insert("key3", 3);

    int sum = 0;
    for (auto it = table.begin(); it != table.end(); ++it) {
        sum += it->second;
    }
    EXPECT_EQ(sum, 6);

    // Проверка range-based for
    sum = 0;
    for (const auto& pair : table) {
        sum += pair.second;
    }
    EXPECT_EQ(sum, 6);
}

TEST_P(HashTableTest, CheckSize) {
    size_t num = 100;

    for (size_t i = 0; i < num; i++) table.insert("key" + std::to_string(i), i);

    EXPECT_EQ(num, table.size());
}


TEST_P(HashTableTest, SubscriptOperator) {
    table.insert("key1", 100);
    table.insert("key2", 200);

    EXPECT_EQ(table["key1"], 100);
    EXPECT_EQ(table["key2"], 200);

    // Проверка создания нового элемента и изменения его значения
    table.insert("new_key", 0);
    EXPECT_EQ(table["new_key"], 0);
    table["new_key"] = 300;
    EXPECT_EQ(table["new_key"], 300);
}

TEST_P(HashTableTest, At) {
    table.insert("key1", 100);
    table.insert("key2", 200);

    EXPECT_EQ(table.at("key1"), 100);
    EXPECT_EQ(table.at("key2"), 200);

    // Проверка создания нового элемента и изменения его значения
    table.insert("new_key", 0);
    EXPECT_EQ(table.at("new_key"), 0);
    table.at("new_key") = 300;
    EXPECT_EQ(table.at("new_key"), 300);
}

TEST_P(HashTableTest, AtCantFindNotExElem) {
    table.insert("key1", 100);
    table.insert("key2", 200);

    EXPECT_EQ(table.at("key1"), 100);
    EXPECT_EQ(table.at("key2"), 200);

    ASSERT_ANY_THROW(table.at("nonexistent"));
}

// Стресс тесты

TEST(HashTable, StressTestSTD) {
    size_t num = 1'000'000;
	HashTable<std::string, int> table(2, HashTable<std::string, int>::STD);
	
    for (size_t i = 0; i < num; i++) table.insert("key" + std::to_string(i), i);

    EXPECT_EQ(num, table.size());
}

TEST(HashTable, StressTestDJB2) {
    size_t num = 1'000'000;
    HashTable<std::string, int> table(2, HashTable<std::string, int>::DJB2);

    for (size_t i = 0; i < num; i++) table.insert("key" + std::to_string(i), i);

    EXPECT_EQ(num, table.size());
}

TEST(HashTable, StressTestSIMPLE) {
    size_t num = 10'000;
    HashTable<std::string, int> table(2, HashTable<std::string, int>::SIMPLE);

    for (size_t i = 0; i < num; i++) table.insert("key" + std::to_string(i), i);

    EXPECT_EQ(num, table.size());
}

TEST(HashTable, StressTestInsertAndEraseSTD) {
    size_t num = 1'000'000;
    HashTable<std::string, int> table(2, HashTable<std::string, int>::STD);

    for (size_t i = 0; i < num; i++) table.insert("key" + std::to_string(i), i);
    for (size_t i = 0; i < num; i++) table.erase("key" + std::to_string(i));

    EXPECT_EQ(0, table.size());
}

TEST(HashTable, StressTestInsertAndEraseDJB2) {
    size_t num = 1'000'000;
    HashTable<std::string, int> table(2, HashTable<std::string, int>::DJB2);

    for (size_t i = 0; i < num; i++) table.insert("key" + std::to_string(i), i);
    for (size_t i = 0; i < num; i++) table.erase("key" + std::to_string(i));

    EXPECT_EQ(0, table.size());
}

TEST(HashTable, StressTestInsertAndEraseSIMPLE) {
    size_t num = 10'000;
    HashTable<std::string, int> table(2, HashTable<std::string, int>::SIMPLE);

    for (size_t i = 0; i < num; i++) table.insert("key" + std::to_string(i), i);
    for (size_t i = 0; i < num; i++) table.erase("key" + std::to_string(i));

    EXPECT_EQ(0, table.size());
}
