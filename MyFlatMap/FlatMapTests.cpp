#include <gtest/gtest.h>
#include "FlatMap.h"

// Тест конструктора по умолчанию
TEST(FlatMapTest, DefaultConstructor) {
    FlatMap map;
    EXPECT_EQ(map.size(), 0);
}

// Тест конструктора копирования
TEST(FlatMapTest, CopyConstructor) {
    FlatMap original;
    original["key1"] = "value1";
    original["key2"] = "value2";

    FlatMap copy(original);

    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy["key1"], "value1");
    EXPECT_EQ(copy["key2"], "value2");
}

// Тест оператора присваивания
TEST(FlatMapTest, AssignmentOperator) {
    FlatMap original;
    original["key1"] = "value1";
    original["key2"] = "value2";

    FlatMap assigned;
    assigned = original;

    EXPECT_EQ(assigned.size(), 2);
    EXPECT_EQ(assigned["key1"], "value1");
    EXPECT_EQ(assigned["key2"], "value2");
}

// Тест метода size()
TEST(FlatMapTest, Size) {
    FlatMap map;
    EXPECT_EQ(map.size(), 0);

    map["key1"] = "value1";
    EXPECT_EQ(map.size(), 1);

    map["key2"] = "value2";
    EXPECT_EQ(map.size(), 2);
}

// Тест метода operator[]
TEST(FlatMapTest, OperatorBrackets) {
    FlatMap map;

    map["key1"] = "value1";
    EXPECT_EQ(map["key1"], "value1");

    map["key1"] = "new_value1";
    EXPECT_EQ(map["key1"], "new_value1");

    map["key2"] = "value2";
    EXPECT_EQ(map["key2"], "value2");
}

// Тест метода contains()
TEST(FlatMapTest, Contains) {
    FlatMap map;

    map["key1"] = "value1";
    EXPECT_TRUE(map.contains("key1"));
    EXPECT_FALSE(map.contains("key2"));

    map["key2"] = "value2";
    EXPECT_TRUE(map.contains("key2"));
}

// Тест метода erase()
TEST(FlatMapTest, Erase) {
    FlatMap map;

    map["key1"] = "value1";
    map["key2"] = "value2";

    EXPECT_EQ(map.erase("key1"), 1);
    EXPECT_EQ(map.size(), 1);
    EXPECT_FALSE(map.contains("key1"));

    EXPECT_EQ(map.erase("key3"), 0);
    EXPECT_EQ(map.size(), 1);
}

// Тест метода clear()
TEST(FlatMapTest, Clear) {
    FlatMap map;

    map["key1"] = "value1";
    map["key2"] = "value2";

    map.clear();
    EXPECT_EQ(map.size(), 0);
    EXPECT_FALSE(map.contains("key1"));
    EXPECT_FALSE(map.contains("key2"));
}

///
TEST(FlatMapTest, InsertAndFindSingleElement) {
    FlatMap map;
    map["first_name"] = "Polina";
    EXPECT_EQ(map["first_name"], "Polina");
}

TEST(FlatMapTest, FindNonExistentKey) {
    FlatMap map;
    EXPECT_EQ(map["unknown_key"], "");
}

TEST(FlatMapTest, InsertMultipleElements) {
    FlatMap map;
    map["first_name"] = "Polina";
    map["last_name"] = "Zueva";
    EXPECT_EQ(map["first_name"], "Polina");
    EXPECT_EQ(map["last_name"], "Zueva");
}

TEST(FlatMapTest, CheckContainsMethod) {
    FlatMap map;
    map["city"] = "Novosibirsk";
    EXPECT_TRUE(map.contains("city"));
    EXPECT_FALSE(map.contains("country"));
}

TEST(FlatMapTest, InsertWithOverwrite) {
    FlatMap map;
    map["key"] = "first";
    map["key"] = "second";
    EXPECT_EQ(map["key"], "second");
}

TEST(FlatMapTest, CheckSizeMethod) {
    FlatMap map;
    map["one"] = "1";
    map["two"] = "2";
    EXPECT_EQ(map.size(), 2);
}

TEST(FlatMapTest, SizeOfEmptyMap) {
    FlatMap map;
    EXPECT_EQ(map.size(), 0);
}

TEST(FlatMapTest, ClearMap) {
    FlatMap map;
    map["first"] = "1";
    map["second"] = "2";
    map.clear();
    EXPECT_EQ(map.size(), 0);
    EXPECT_FALSE(map.contains("first"));
    EXPECT_FALSE(map.contains("second"));
}

TEST(FlatMapTest, CheckResize) {
    FlatMap map;
    for (int i = 0; i < 100; ++i) {
        map["key" + std::to_string(i)] = "value" + std::to_string(i);
    }
    EXPECT_EQ(map.size(), 100);
    EXPECT_EQ(map["key99"], "value99");
}

TEST(FlatMapTest, EraseElement) {
    FlatMap map;
    map["first"] = "1";
    map["second"] = "2";
    size_t erased = map.erase("first");
    EXPECT_EQ(erased, 1);
    EXPECT_EQ(map.size(), 1);
    EXPECT_FALSE(map.contains("first"));
    EXPECT_TRUE(map.contains("second"));
}

TEST(FlatMapTest, EraseNonExistentElement) {
    FlatMap map;
    map["first"] = "1";
    size_t erased = map.erase("nonexistent");
    EXPECT_EQ(erased, 0);
    EXPECT_EQ(map.size(), 1);
    EXPECT_TRUE(map.contains("first"));
}

TEST(FlatMapTest, EraseAllElements) {
    FlatMap map;
    map["key1"] = "value1";
    map["key2"] = "value2";
    map.erase("key1");
    map.erase("key2");
    EXPECT_EQ(map.size(), 0);
}

TEST(FlatMapTest, CheckCopyConstructor) {
    FlatMap map1;
    map1["first"] = "1";
    map1["second"] = "2";

    FlatMap map2 = map1;

    EXPECT_EQ(map2["first"], "1");
    EXPECT_EQ(map2["second"], "2");

    map2["first"] = "3";
    EXPECT_EQ(map1["first"], "1");
    EXPECT_EQ(map2["first"], "3");
}

TEST(FlatMapTest, CheckAssignmentOperator) {
    FlatMap map1;
    map1["first"] = "1";
    map1["second"] = "2";

    FlatMap map2;
    map2 = map1;

    EXPECT_EQ(map2["first"], "1");
    EXPECT_EQ(map2["second"], "2");

    map2["first"] = "3";
    EXPECT_EQ(map1["first"], "1");
    EXPECT_EQ(map2["first"], "3");
}

TEST(FlatMapTest, AssignmentToSelf) {
    FlatMap map;
    map["key"] = "value";
    map = map;
    EXPECT_EQ(map["key"], "value");
}

TEST(FlatMapTest, BinarySearchPerformance) {
    FlatMap map;
    for (int i = 0; i < 1000; ++i) {
        map["key" + std::to_string(i)] = "value" + std::to_string(i);
    }
    EXPECT_EQ(map["key500"], "value500");
    EXPECT_TRUE(map.contains("key999"));
}

TEST(FlatMapTest, InsertionOrderDoesNotMatter) {
    FlatMap map;
    map["z_key"] = "last";
    map["a_key"] = "first";
    map["m_key"] = "middle";

    EXPECT_EQ(map["z_key"], "last");
    EXPECT_EQ(map["a_key"], "first");
    EXPECT_EQ(map["m_key"], "middle");
}

TEST(FlatMapTest, ClearDoesNotCauseMemoryLeaks) {
    FlatMap map;
    for (int i = 0; i < 100; ++i) {
        map["key" + std::to_string(i)] = "value" + std::to_string(i);
    }
    map.clear();
    EXPECT_EQ(map.size(), 0);
    for (int i = 0; i < 100; ++i) {
        EXPECT_FALSE(map.contains("key" + std::to_string(i)));
    }
}

TEST(FlatMapTest, HandlesLargeKeysAndValues) {
    FlatMap map;
    std::string largeKey(10000, 'k');
    std::string largeValue(10000, 'v');

    map[largeKey] = largeValue;
    EXPECT_EQ(map[largeKey], largeValue);
}

TEST(FlatMapTest, HandlesEmptyKeyAndValue) {
    FlatMap map;
    map[""] = "";
    EXPECT_TRUE(map.contains(""));
    EXPECT_EQ(map[""], "");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}