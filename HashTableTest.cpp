#include "gtest/gtest.h"
#include "../HashTable.cpp"

namespace {
    class HashTableTest : public ::testing::Test {
    protected:
        HashTable a;
    };

    TEST_F(HashTableTest, insert_resize) {
        HashTable w;
        Key key1 = "Alt";
        Key key2 = "Colt";
        Value value(19, 170);
        w.insert(key1, value);
        w.resize_table(key2, value);
    }

    TEST_F(HashTableTest, size) {
        EXPECT_NE(0, a.size());
    }

    TEST_F(HashTableTest, empty) {
        EXPECT_FALSE(a.empty());
    }

    TEST_F(HashTableTest, contains) {
        HashTable c;
        Value value(19, 170);
        Key key1 = "qwe";
        Key key2 = "ewq";
        c.insert(key1, value);
        c.insert(key2, value);
        EXPECT_TRUE(c.contains(key2));
    }

    TEST_F(HashTableTest, brackets) {
        HashTable y;
        Value value(19, 170);
        Value b = y["lorem"];
        EXPECT_FALSE(b == value);
    }

    TEST_F(HashTableTest, new_brackets) {
        HashTable h;
        Value value(19, 170);
        Key key = "lorem";
        h.insert(key, value);
        Value b = h["lorem"];
        EXPECT_TRUE(b == value);
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

    TEST_F(HashTableTest, new_equal) {
        HashTable g;
        HashTable j;
        g.insert("qwe", Value(1, 1));
        g.insert("ewq", Value(1, 1));
        j.insert("ewq", Value(1, 1));
        j.insert("ewq", Value(1, 1));
        EXPECT_TRUE(j == g);
    }

    TEST_F(HashTableTest, erase) {
        HashTable m;
        Value value(19, 170);
        Key key = "qwerty";
        m.insert(key, value);
        EXPECT_TRUE(m.erase(key));
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
        HashTable k;
        Value value(19, 170);
        Key key = "test";
        k.insert(key, value);
        EXPECT_EQ(k.at(key), value);
    }

    TEST_F(HashTableTest, at_false) {
        Value value(19, 170);
        Key key = "test";
        a.insert(key, value);
        EXPECT_FALSE(a.at("qwedsa") == value);
    }

    TEST_F(HashTableTest, new_at) {
        HashTable k;
        Value value(19, 170);
        Key key = "qwe";
        Key key1 = "ewq";
        k.insert(key, value);
        k.insert(key1, value);
        EXPECT_EQ(k.at(key1), value);
    }

    TEST_F(HashTableTest, equal_operator) {
        HashTable a;
        HashTable b;
        a.insert("lorem", Value(1, 1));
        b.insert("lorem", Value(1, 1));

        EXPECT_TRUE(a == b);
    }

    TEST_F(HashTableTest, swap) {
        HashTable a;
        HashTable b;
        a.swap(b);
    }

    TEST_F(HashTableTest, clear) {
        HashTable p;
        p.insert("lor", Value(1, 1));
        p.insert("ips", Value(1, 1));
    }
}
