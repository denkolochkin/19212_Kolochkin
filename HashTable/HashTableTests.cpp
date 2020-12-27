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

    TEST_F(HashTableTest, brackets_false){
        Value value(19, 170);
        Value b = a["lorem"];
        EXPECT_FALSE(b == value);
    }

    TEST_F(HashTableTest, brackets_true){
        Value value(19, 170);
        Key key = "lorem";
        a.insert(key, value);
        Value b = a["lorem"];
        EXPECT_TRUE(b == value);
    }

    TEST_F(HashTableTest, erase){
        Value value(19, 170);
        Key key = "lorem";
        a.insert(key, value);
        a.erase(key);
        EXPECT_FALSE(a.contains(key));
        EXPECT_FALSE(a.erase("asd"));
    }

    TEST_F(HashTableTest, new_erase){
        Value value(19, 170);
        Key key_1 = "qwe";
        Key key_2 = "ewq";
        a.insert(key_1, value);
        a.insert(key_2, value);
        a.erase(key_2);
        EXPECT_FALSE(a.contains(key_2));
    }

    TEST_F(HashTableTest, const_at){
        Key key_1 = "lor";
        Key key_2 = "em";
        Key key_3 = "ips";
        Key key_4 = "um";
        Key key_5 = "lorem";
        a.insert(key_1, Value(19, 170));
        a.insert(key_2, Value(19, 170));
        a.insert(key_3, Value(19, 170));
        a.insert(key_4, Value(19,170));
        a.insert(key_5, Value(19,170));
        const HashTable b = a;
        EXPECT_EQ(b.at(key_1), Value(19, 170));
    }

    TEST_F(HashTableTest, at_false){
        Value value1(19, 170);
        Value value2(18, 120);
        Key key1 = "test";
        Key key2 = "lorem";
        a.insert(key1, value1);
        a.insert(key2, value2);
        EXPECT_FALSE(a.at(key1) == value2);
    }

    TEST_F(HashTableTest, at){
        HashTable k;
        Value value(19, 170);
        Key key = "qwe";
        Key key1 = "ewq";
        k.insert(key, value);
        k.insert(key1, value);
        EXPECT_EQ(k.at(key1), value);
    }

    TEST_F(HashTableTest, equal){
        HashTable g;
        HashTable j;
        g.insert("qwe", Value(1, 1));
        g.insert("ewq", Value(1, 1));
        j.insert("qwe", Value(1, 1));
        j.insert("ewq", Value(1, 1));
        EXPECT_TRUE(j == g);
    }

    TEST_F(HashTableTest, not_equal){
        HashTable c;
        Value value(19, 175);
        Key key = "qwe";
        Key key1 = "ewq";
        c.insert(key, value);
        c.insert(key1, value);
        c = a;
        EXPECT_FALSE(a != c);
    }

    TEST_F(HashTableTest, swap){
        HashTable a;
        HashTable b;
        Value value(1,1);
        a.insert("som", value);
        b.insert("lorem", value);
        a.swap(b);
        EXPECT_TRUE(a.contains("lorem"));
    }

    TEST_F(HashTableTest, resize){
        HashTable a;
        Value value(1,1);
        a.insert("lor",value);
        a.insert("em",value);
        a.insert("ip",value);
        a.insert("sum",value);
        a.insert("lorem",value);
        EXPECT_TRUE(a.contains("lor") == a.contains("em") == a.contains("sum"));
        EXPECT_TRUE(a.contains("ip") == a.contains("lorem"));
    }
    
    TEST_F(HashTableTest, new_resize){
        HashTable a;
        Value value(1,1);
        a.insert("lor",value);
        a.insert("em",value);
        a.insert("ip",value);
        a.insert("sum",value);
        a.insert("lorem",value);
        a.insert("mor", value);
        a.insert("mus", value);
        EXPECT_TRUE(a.contains("lor") == a.contains("em") == a.contains("sum"));
        EXPECT_TRUE(a.contains("ip") == a.contains("lorem") == a.contains("mor"));
        EXPECT_TRUE(a.contains("mus"));
    }
}
