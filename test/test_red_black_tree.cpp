#include "red_black_tree.h"
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

class RBTreeTestRandom : public ::testing::Test {
protected:
    RBTree<std::string, int> tree;
    static std::vector<std::pair<std::string, int>> test_data;

    static void SetUpTestSuite() {
        // Генерация тестовых данных (10000 пар строка-число)
        test_data.reserve(1000000);
        for (int i = 1; i <= 1000000; ++i) {
            test_data.emplace_back("key_" + std::to_string(i), i);
        }

        // Перемешиваем данные для случайного порядка
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(test_data.begin(), test_data.end(), g);
    }

    void TearDown() override {
        tree.clear();
    }
};

class RBTreeTest : public ::testing::Test {
protected:
    RBTree<std::string, int> tree;
    static std::vector<std::pair<std::string, int>> test_data;

    static void SetUpTestSuite() {
        // Генерация тестовых данных (1000000 пар строка-число)
        test_data.reserve(1000000);
        for (int i = 1; i <= 1000000; ++i) {
            test_data.emplace_back("key_" + std::to_string(i), i);
        }
    }

    void TearDown() override {
        tree.clear();
    }
};

// Инициализация статического члена
std::vector<std::pair<std::string, int>> RBTreeTestRandom::test_data;
std::vector<std::pair<std::string, int>> RBTreeTest::test_data;


TEST_F(RBTreeTest, CheckSize) {
    int n = 5;
    for (int i = 0; i < n; i++) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }
    EXPECT_EQ(n, tree.size());
}

TEST_F(RBTreeTest, CheckSizeOfEmptyTree) {
    EXPECT_EQ(0, tree.size());
}

TEST_F(RBTreeTest, Clear) {
    int n = 5;
    for (int i = 0; i < n; i++) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }
    tree.clear();
    EXPECT_EQ(0, tree.size());
}

TEST_F(RBTreeTest, Empty) {
    int n = 5;
    for (int i = 0; i < n; i++) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }
    tree.clear();
    EXPECT_TRUE(tree.empty());
}

TEST_F(RBTreeTest, NotEmpty) {
    int n = 5;
    for (int i = 0; i < n; i++) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }
    EXPECT_FALSE(tree.empty());
}

TEST_F(RBTreeTest, Begin) {
    int n = 5;
    for (int i = 0; i < n; i++) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }
    RBTree<std::string, int>::Iterator it = tree.begin();
    EXPECT_EQ(1, (*it).second);
}

TEST_F(RBTreeTest, End) {
    int n = 5;
    for (int i = 0; i < n; i++) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }
    RBTree<std::string, int>::Iterator it = tree.begin();
    for (int i = 0; i < tree.size(); i++) {
        it++;
    }
    EXPECT_EQ(tree.end(), it);
}

TEST_F(RBTreeTest, PrefixIncrement) {
    int n = 5;
    for (int i = 0; i < n; i++) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }
	RBTree<std::string, int>::Iterator it = tree.begin();
    ++it;
    EXPECT_EQ(2, (*it).second);
}

TEST_F(RBTreeTest, PostfixIncrement) {
    int n = 5;
    for (int i = 0; i < n; i++) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }
    RBTree<std::string, int>::Iterator it = tree.begin();
    it++;
    EXPECT_EQ(2, (*it).second);
}

TEST_F(RBTreeTest, PrefixDecrement) {
    int n = 5;
    for (int i = 0; i < n; i++) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }
    RBTree<std::string, int>::Iterator it = tree.begin();
    ++it;
    --it;
    EXPECT_EQ(1, (*it).second);
}

TEST_F(RBTreeTest, PostfixDecrement) {
    int n = 5;
    for (int i = 0; i < n; i++) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }
    RBTree<std::string, int>::Iterator it = tree.begin();
    it++;
    it--;
    EXPECT_EQ(1, (*it).second);
}

TEST_F(RBTreeTest, CanInsert) {
    int n = 5;
    for (int i = 0; i < n; i++) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }
    EXPECT_EQ(n, tree.size());
}

TEST_F(RBTreeTest, InsertCorrect) {
    int n = 5;
    for (int i = 0; i < n; i++) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }
    RBTree<std::string, int>::Iterator it = tree.begin();
    for (int i = 1; i < tree.size(); i++) {
        EXPECT_EQ(i, (*it).second);
        it++;
    }
}

TEST_F(RBTreeTest, CanErase) {
    int n = 5;
    for (int i = 0; i < n; i++) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }
    for (int i = 0; i < n-1; i++) {
        const auto& [key, value] = test_data[i];
        tree.erase(key);
    }
    EXPECT_EQ(1, tree.size());
}

TEST_F(RBTreeTest, EraseCorrect) {
    int n = 5;
    for (int i = 0; i < n; i++) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }
    for (int i = 0; i < n - 1; i++) {
        const auto& [key, value] = test_data[i];
        tree.erase(key);
    }
    RBTree<std::string, int>::Iterator it = tree.begin();
    EXPECT_EQ(5, (*it).second);
}

TEST_F(RBTreeTest, CanFindExistElem) {
    int n = 5;
    for (int i = 0; i < n; i++) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }
    EXPECT_NO_THROW(tree.find("key_4"));
}

TEST_F(RBTreeTest, CantFindNotExistElem) {
    int n = 5;
    for (int i = 0; i < n; i++) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }
    RBTree<std::string, int>::Iterator it = tree.find("key_10");
    EXPECT_EQ(tree.end(), it);
}

TEST_F(RBTreeTest, CanFindCorrect) {
    int n = 5;
    for (int i = 0; i < n; i++) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }
    RBTree<std::string, int>::Iterator it = tree.find("key_4");
    EXPECT_EQ(4, (*it).second);
}

TEST_F(RBTreeTest, InsertAndFindElements100) {
    // Вставляем только первые 100 элементов для теста
    int n = 100;
    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }

    EXPECT_EQ(n, tree.size());

    // Проверяем некоторые из вставленных элементов
    for (size_t i = 0; i < 10; ++i) {
        const auto& [key, value] = test_data[i];
        auto it = tree.find(key);
        ASSERT_NE(it, tree.end());
        EXPECT_EQ((*it).first, key);
        EXPECT_EQ((*it).second, value);
    }
}

TEST_F(RBTreeTest, InsertAndFindElements10000) {
    // Вставляем только первые 10000 элементов для теста
    int n = 10000;
    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }

    EXPECT_EQ(n, tree.size());

    // Проверяем некоторые из вставленных элементов
    for (size_t i = 0; i < 10; ++i) {
        const auto& [key, value] = test_data[i];
        auto it = tree.find(key);
        ASSERT_NE(it, tree.end());
        EXPECT_EQ((*it).first, key);
        EXPECT_EQ((*it).second, value);
    }
}

TEST_F(RBTreeTest, InsertAndFindElements1000000) {
    // Вставляем все элементы 1000000
    int n = 1000000;
    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }

    EXPECT_EQ(n, tree.size());

    // Проверяем некоторые из вставленных элементов
    for (size_t i = 0; i < 10; ++i) {
        const auto& [key, value] = test_data[i];
        auto it = tree.find(key);
        ASSERT_NE(it, tree.end());
        EXPECT_EQ((*it).first, key);
        EXPECT_EQ((*it).second, value);
    }
}

TEST_F(RBTreeTest, InsertAndErase100) {
    // Вставляем только первые 100 элементов для теста
    int n = 100;
    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }

    EXPECT_EQ(n, tree.size());

    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[i];
        tree.erase(key);
    }
    
    EXPECT_EQ(0, tree.size());
}

TEST_F(RBTreeTest, InsertAndErase10000) {
    // Вставляем только первые 10000 элементов для теста
    int n = 10000;
    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }

    EXPECT_EQ(n, tree.size());

    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[i];
        tree.erase(key);
    }

    EXPECT_EQ(0, tree.size());
}

TEST_F(RBTreeTest, InsertAndErase1000000) {
    // Вставляем все элементы 1000000
    int n = 1000000;
    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }

    EXPECT_EQ(n, tree.size());

    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[i];
        tree.erase(key);
    }

    EXPECT_EQ(0, tree.size());
}

TEST_F(RBTreeTest, ReverseInsertAndFindElements100) {
    // Вставляем только первые 100 элементов для теста
    int n = 100;
    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[n-i-1];
        tree.insert(key, value);
    }

    EXPECT_EQ(n, tree.size());

    // Проверяем некоторые из вставленных элементов
    for (size_t i = 0; i < 10; ++i) {
        const auto& [key, value] = test_data[i];
        auto it = tree.find(key);
        ASSERT_NE(it, tree.end());
        EXPECT_EQ((*it).first, key);
        EXPECT_EQ((*it).second, value);
    }
}

TEST_F(RBTreeTest, ReverseInsertAndFindElements10000) {
    // Вставляем только первые 10000 элементов для теста
    int n = 10000;
    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[n - i - 1];
        tree.insert(key, value);
    }

    EXPECT_EQ(n, tree.size());

    // Проверяем некоторые из вставленных элементов
    for (size_t i = 0; i < 10; ++i) {
        const auto& [key, value] = test_data[i];
        auto it = tree.find(key);
        ASSERT_NE(it, tree.end());
        EXPECT_EQ((*it).first, key);
        EXPECT_EQ((*it).second, value);
    }
}

TEST_F(RBTreeTest, ReverseInsertAndFindElements1000000) {
    // Вставляем все элементы 1000000
    int n = 1000000;
    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[n - i - 1];
        tree.insert(key, value);
    }

    EXPECT_EQ(n, tree.size());

    // Проверяем некоторые из вставленных элементов
    for (size_t i = 0; i < 10; ++i) {
        const auto& [key, value] = test_data[i];
        auto it = tree.find(key);
        ASSERT_NE(it, tree.end());
        EXPECT_EQ((*it).first, key);
        EXPECT_EQ((*it).second, value);
    }
}

TEST_F(RBTreeTestRandom, InsertAndFindElements100) {
    // Вставляем только первые 100 элементов для теста
    int n = 100;
    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }

    EXPECT_EQ(n, tree.size());

    // Проверяем некоторые из вставленных элементов
    for (size_t i = 0; i < 10; ++i) {
        const auto& [key, value] = test_data[i];
        auto it = tree.find(key);
        ASSERT_NE(it, tree.end());
        EXPECT_EQ((*it).first, key);
        EXPECT_EQ((*it).second, value);
    }
}

TEST_F(RBTreeTestRandom, InsertAndFindElements10000) {
    // Вставляем только первые 10000 элементов для теста
    int n = 10000;
    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }

    EXPECT_EQ(n, tree.size());

    // Проверяем некоторые из вставленных элементов
    for (size_t i = 0; i < 10; ++i) {
        const auto& [key, value] = test_data[i];
        auto it = tree.find(key);
        ASSERT_NE(it, tree.end());
        EXPECT_EQ((*it).first, key);
        EXPECT_EQ((*it).second, value);
    }
}

TEST_F(RBTreeTestRandom, InsertAndFindElements1000000) {
    // Вставляем все элементы 1000000
    int n = 1000000;
    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }

    EXPECT_EQ(n, tree.size());

    // Проверяем некоторые из вставленных элементов
    for (size_t i = 0; i < 10; ++i) {
        const auto& [key, value] = test_data[i];
        auto it = tree.find(key);
        ASSERT_NE(it, tree.end());
        EXPECT_EQ((*it).first, key);
        EXPECT_EQ((*it).second, value);
    }
}

TEST_F(RBTreeTestRandom, InsertAndErase100) {
    // Вставляем только первые 100 элементов для теста
    int n = 100;
    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }

    EXPECT_EQ(n, tree.size());

    // Удаляем некоторые из вставленных элементов
    for (size_t i = 0; i < 10; ++i) {
        const auto& [key, value] = test_data[i];
        tree.erase(key);
    }

    EXPECT_EQ(n-10, tree.size());
}

TEST_F(RBTreeTestRandom, InsertAndErase10000) {
    // Вставляем только первые 10000 элементов для теста
    int n = 10000;
    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }

    EXPECT_EQ(n, tree.size());

    // Удаляем некоторые из вставленных элементов
    for (size_t i = 0; i < 100; ++i) {
        const auto& [key, value] = test_data[i];
        tree.erase(key);
    }

    EXPECT_EQ(n - 100, tree.size());
}

TEST_F(RBTreeTestRandom, InsertAndErase1000000) {
    // Вставляем только первые 10000 элементов для теста
    int n = 1000000;
    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }

    EXPECT_EQ(n, tree.size());

    // Удаляем некоторые из вставленных элементов
    for (size_t i = 0; i < 1000; ++i) {
        const auto& [key, value] = test_data[i];
        tree.erase(key);
    }

    EXPECT_EQ(n - 1000, tree.size());
}

TEST_F(RBTreeTest, IteratorOrder) {
    // Вставляем тестовые данные
    int n = 9;
    for (size_t i = 0; i < n; ++i) {
        const auto& [key, value] = test_data[i];
        tree.insert(key, value);
    }

    // Проверяем, что итерация проходит в лексикографическом порядке
    RBTree<std::string, int>::Iterator it = tree.begin();
    for (int i = 1; i < tree.size(); i++) {
        EXPECT_EQ(i, (*it).second);
        it++;
    }
}



//#include <gtest/gtest.h>
//#include "red_black_tree.h"
//
//
//TEST(RBTree, CreateTree) {
//	RBTree<std::string, int> tree;
//	tree.Insert("a", 1);
//	tree.Insert("b", 2);
//	tree.Insert("c", 3);
//	tree.Insert("d", 4);
//	tree.Insert("f", 5);
//     tree.insert("g", 6);
//tree.insert("h", 7);
//	RBTree<std::string, int>::Iterator it(tree.get_root());
//	for (int i = 0; i < tree.size()-1; i++) {
//		it++;
//	}
//
//	for (int i = 0; i < tree.size(); i++) {
//		it--;
//	}
//}
