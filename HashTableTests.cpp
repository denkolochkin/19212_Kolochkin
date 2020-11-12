#include "gtest/gtest.h"
#include "HashTable.h"

namespace{
    class HashTableTest : public ::testing::Test {
    protected:
        HashTable a;
    };

    TEST_F(HashTableTest, size){
        EXPECT_NE(0, a.size());
    }

    TEST_F(HashTableTest, empty){
        EXPECT_FALSE(a.empty());
    }

    TEST_F(HashTableTest, brackets){
        HashTable::Value value(19, 170);
        HashTable::Value b = a["lorem"];
        EXPECT_FALSE(b == value);
    }

    TEST_F(HashTableTest, new_brackets){
        HashTable::Value value(19, 170);
        Key key = "lorem";
        a.insert(key, value);
        HashTable::Value b = a["lorem"];
        EXPECT_TRUE(b == value);
    }

    TEST_F(HashTableTest, erase){
        HashTable m;
        HashTable::Value value(19, 170);
        Key key = "qwerty";
        m.insert(key, value);
        EXPECT_TRUE(m.erase(key));
    }

    TEST_F(HashTableTest, new_erase){
        HashTable::Value value(19, 170);
        Key key = "qwe";
        Key key1 = "ewq";
        a.insert(key, value);
        a.insert(key1, value);
        EXPECT_TRUE(a.erase(key1));
    }

    TEST_F(HashTableTest, const_at){
        Key key_1 = "Daad";
        Key key_2 = "Qwe";
        Key key_3 = "MHla";
        Key key_4 = "Alt";
        Key key_5 = "Colt";
        a.insert(key_1, HashTable::Value(19, 170));
        a.insert(key_2, HashTable::Value(19, 170));
        a.insert(key_3, HashTable::Value(19, 170));
        a.insert(key_4, HashTable::Value(19,170));
        a.insert(key_5, HashTable::Value(19,170));
        const HashTable b = a;
        EXPECT_EQ(b.at(key_1), HashTable::Value(19, 170));
    }

    TEST_F(HashTableTest, at_false){
        HashTable::Value value(19, 170);
        Key key = "test";
        a.insert(key, value);
        EXPECT_FALSE(a.at("qwedsa") == value);
    }

    TEST_F(HashTableTest, at){
        HashTable k;
        HashTable::Value value(19, 170);
        Key key = "qwe";
        Key key1 = "ewq";
        k.insert(key, value);
        k.insert(key1, value);
        EXPECT_EQ(k.at(key1), value);
    }

    TEST_F(HashTableTest, not_equal){
        HashTable c;
        c = a;
        EXPECT_FALSE(a != c);
    }

    TEST_F(HashTableTest, equal){
        HashTable g;
        HashTable j;
        g.insert("qwe", HashTable::Value(1, 1));
        g.insert("ewq", HashTable::Value(1, 1));
        j.insert("ewq", HashTable::Value(1, 1));
        j.insert("ewq", HashTable::Value(1, 1));
        EXPECT_TRUE(j == g);
    }

    TEST_F(HashTableTest, swap){
        HashTable a;
        HashTable b;
        a.swap(b);
    }
}
