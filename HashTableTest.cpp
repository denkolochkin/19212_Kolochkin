
#include "gtest/gtest.h"
#include "../HashTable.cpp"

namespace {

    class HashTableTest : public ::testing::Test {
    protected:
        HashTable a;
    };

    TEST_F(HashTableTest, size) {
        EXPECT_NE(0, a.size());
    }

    TEST_F(HashTableTest, empty) {
        EXPECT_FALSE(a.empty());
    }

    TEST_F(HashTableTest, clear) {
        a.clear();
    }

    TEST_F(HashTableTest, insert) {
        Value value(19, 170);
        Key key = "qwe";
        Key key1 = "ewq";
        a.insert(key, value);
        a.contains(key);
        ASSERT_TRUE(a.insert(key1, value));
    }

    TEST_F(HashTableTest, brackets) {
        Key key = "qwe";
        Value value(19, 170);
        a.insert(key, value);
        Value b = a[key];
        EXPECT_EQ(b, value);
    }

    TEST_F(HashTableTest, not_equal) {
        HashTable c = a;
        EXPECT_FALSE(a != c);
    }

    TEST_F(HashTableTest, equal) {
        HashTable b;
        b = a;
        EXPECT_TRUE(a == b);
    }

    TEST_F(HashTableTest, erase) {
        Value value(19, 170);
        Key key = "qwe";
        a.insert(key, value);
        EXPECT_TRUE(a.erase(key));
    }

    TEST_F(HashTableTest, new_erase) {
        Value value(19, 170);
        Key key = "qwe";
        Key key1 = "ewq";
        a.insert(key, value);
        a.insert(key1, value);
        EXPECT_TRUE(a.erase(key1));
    }

    TEST_F(HashTableTest, at) {
        Value value(19, 170);
        Key key = "test";
        a.insert(key, value);
        EXPECT_EQ(a.at(key), value);
    }

    TEST_F(HashTableTest, const_at) {
        HashTable c;
        const Value value(19, 170);
        const Key key = "test";
        c.insert(key, value);
        EXPECT_EQ(c.at(key), value);
    }

    TEST_F(HashTableTest, equal_operator) {
        HashTable a;
        HashTable b;
        b = a;
        EXPECT_EQ(a, b);
    }

}